# import models
from models import (Base, session, Book, engine)
import csv
import datetime
import time


# main menu - add, search analysis, exit, view
def menu():
    while True:
        print('''
        \n PROGRAMMING BOOKS
        \r1) Add Book
        \r2) View all books
        \r3) Search for book
        \r4) Book Analysis
        \r5) Exit''')
        choice = input('\nPlease Choose an option: ')
        if choice in ['1', '2', '3', '4', '5']:
            return choice
        else:
            input('''
            \rPlease Choose one of the options above (1-5)
            \rPress any key to continue
            ''')

# add books to database
def add_csv():
    with open('suggested_books.csv') as csvfile:
        data = csv.reader(csvfile)
        for row in data:
            book_in_db = session.query(Book).filter(Book.title==row[0]).one_or_none()
            if book_in_db == None:
                title = row[0]
                author = row[1]
                date = clean_date(row[2])
                price = clean_price(row[3])
                new_book = Book(title=title, author=author, published_date=date, price=price)
                session.add(new_book)
        session.commit()
# edit and delete books
# search books


def clean_date(date_str):
    months = ['January', 'February', 'March', 'April', 'May',
             'June', 'July', 'August', 'September',
             'October', 'November', 'December']
    
    split_date = date_str.split(' ')
    try:
        month = int(months.index(split_date[0]) + 1)
        day = int(split_date[1].split(',')[0])
        year = int(split_date[2])
        return datetime.date(year, month, day)
    except ValueError:
        input('''
        \n DATE ERROR
        The Date format should include a valid Month
        EX: January 13, 2003
         ''')
        return
    else:
        return return_date
    


def clean_price(price_str):
    try:
        price_float = float(price_str)
    except  ValueError:
        print('''
        Invalid entry, you must input a number
        Number should not have any currency symbol
        ''')
        return
    else:
        return int(price_float * 100)
def app():
    app_running = True
    while app_running:
        choice = menu()
        if choice == '1':
            title = input('Title: ')
            author = input('Author: ')
            date_error = True
            while date_error:
                date = input('Published Date (ex: October 25, 2017): ')
                date = clean_date(date)
                if type(date) == datetime.date:
                    date_error = False
            price_error = True
            while price_error:
                price = input('Price (ex 26.80): ')
                price = clean_price(price)
                if type(price) == int:
                    price_error = False
            new_book = Book(title=title, author=author, published_date=date, price=price)
            session.add(new_book)
            session.commit()
            print('Book Added!')
            time.sleep(1.5)
        elif choice == '2':
            # view books
            for book in session.query(Book):
                print(f'{book.id} | {book.title} | {book.author} | {book.published_date} | {book.price}')
            input('\n Press any key to continue')
        elif choice == '3':
            # search
            pass
        elif choice == '4':
            # analysis
            pass
        elif choice == '5':
            print('GOODBYE')
            app_running = False


if __name__ == '__main__':
    Base.metadata.create_all(engine)
    add_csv()
    app()