import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_stocks = db.execute(
        "SELECT stock_symbol, SUM(amount) AS total FROM buy_sell JOIN users ON (users.id = buy_sell.account_id) WHERE users.id = (?) GROUP BY stock_symbol;", session["user_id"])
    user_cash = db.execute(
        "SELECT cash FROM users WHERE users.id = (?)", session["user_id"])
    user_stocks_bought = db.execute(
        "SELECT stock_symbol, SUM(amount) AS total FROM buy_sell JOIN users ON (users.id = buy_sell.account_id) WHERE users.id = (?) AND buy_sell = 1 GROUP BY stock_symbol;", session["user_id"])
    user_stocks_sold = db.execute(
        "SELECT stock_symbol, SUM(amount) AS total FROM buy_sell JOIN users ON (users.id = buy_sell.account_id) WHERE users.id = (?) AND buy_sell = 0 GROUP BY stock_symbol;", session["user_id"])

    user_total_stocks = []
    for i in range(len(user_stocks_bought)):
        try:
            user_stocks_bought[i]['total'] -= user_stocks_sold[i]['total']
        except IndexError:
            continue

    current_prices = [lookup(stock["stock_symbol"])["price"] for stock in user_stocks]
    total_stock_value = 0
    for i in range(len(user_stocks)):
        total_stock_value += lookup(user_stocks[i]["stock_symbol"])["price"] * user_stocks_bought[i]["total"]

    return render_template("index.html", user_cash=usd(user_cash[0]["cash"]), user_stocks=user_stocks_bought, current_prices=current_prices, total_stock_value=usd(total_stock_value), len=len, range=range)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = (request.form.get("shares"))
        if lookup(symbol) == None or shares.isalpha() or float(shares) < 1 or (float(shares) % 1 != 0):
            return apology("invalid symbol or share quantity", 400)
        else:
            user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            user_cash = (user[0]["cash"])

            stock = lookup(request.form.get("symbol"))
            stock_price = float(stock["price"])
            stock_symbol = stock["symbol"]
            quantity = request.form.get("shares")
            price = ((stock_price * int(quantity)))

            if user_cash - price > 0:
                db.execute("INSERT INTO buy_sell (account_id, stock_symbol, buy_sell, amount, cost, time) VALUES (?, ?, ?, ?, ?, ?)",
                           session["user_id"], stock_symbol, 1, quantity, price, datetime.datetime.now())
                db.execute("UPDATE users SET cash=? WHERE id=?", (user_cash - price), session["user_id"])
                return redirect("/")
            else:
                return apology("You don't have enough funds to purchase those stocks")
    else:
        return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        stocks = db.execute(
            "SELECT COUNT(stock_symbol) as amount, stock_symbol FROM buy_sell WHERE account_id = (?) GROUP BY stock_symbol", session["user_id"])
        symbol = request.form.get("symbol")
        shares = (request.form.get("shares"))
        user_shares = db.execute("SELECT amount FROM buy_sell WHERE account_id = (?) AND stock_symbol = (?)",
                                 session["user_id"], symbol)
        print(symbol)

        if lookup(symbol) == None or shares.isalpha() or float(shares) < 1 or (float(shares) % 1 != 0):
            return apology("invalid symbol or share quantity", 400)
        elif user_shares[0]["amount"] < int(shares):
            return apology("You don't own enough shares", 400)

        else:
            user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            user_cash = float((user[0]["cash"]))
            stock = lookup(request.form.get("symbol"))
            stock_price = float(stock["price"])
            stock_symbol = stock["symbol"]
            quantity = request.form.get("shares")
            price = ((stock_price * int(quantity)))

            db.execute("INSERT INTO buy_sell (account_id, stock_symbol, buy_sell, amount, cost, time) VALUES (?, ?, ?, ?, ?, ?)",
                       session["user_id"], stock_symbol, 0, quantity, price, datetime.datetime.now())

            db.execute("UPDATE users SET cash=? WHERE id=?", ((user_cash + price)), session["user_id"])
            return redirect("/")
    else:
        stocks = db.execute(
            "SELECT COUNT(stock_symbol) as amount, stock_symbol FROM buy_sell WHERE account_id = (?) GROUP BY stock_symbol", session["user_id"])
        return render_template("sell.html", stocks=stocks)


@app.route("/history")
@login_required
def history():
    history = db.execute("SELECT transaction_id, stock_symbol, buy_sell, amount, cost, time FROM buy_sell")
    return render_template("history.html", history=history, len=len, range=range, usd=usd)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    else:
        stock = lookup(request.form.get("symbol"))
        if stock == None:
            return apology("Invalid stock symbol")
        return render_template("quoted.html", stock=stock, usd=usd)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 400)

        # Ensure password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password", 403)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match, please try again")

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        print(rows)
        # if username already exists
        print(len(rows))
        if len(rows) >= 1:
            return apology("That username already exists", 400)
        # else, set username, password
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                   request.form.get("username"), generate_password_hash(request.form.get("password")))

        return render_template("login.html")

    else:
        return render_template("register.html")


@app.route("/change_password", methods=["GET", "POST"])
def change_password():

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure password confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide confirmation password", 400)

        # Ensure new password was submitted
        elif not request.form.get("new_password"):
            return apology("must provide new password", 403)

        # Ensure new password confirmation was submitted
        elif not request.form.get("new_password_confirmation"):
            return apology("must provide confirmation of new password", 400)

        # Check if current passwords match
        if request.form.get("password") != request.form.get("confirmation"):
            return apology("Passwords do not match, please try again")

        # Check if new passwords match
        if request.form.get("new_password") != request.form.get("new_password_confirmation"):
            return apology("New passwords do not match, please try again")

         # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("Incorrect Current Password", 403)

        db.execute("UPDATE users SET hash = ? WHERE id = ?", generate_password_hash(request.form.get("new_password")),
                   session["user_id"])
        return redirect("/")

    else:
        return render_template("change_password.html")