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

def submenu():
    while True:
        print('''
        \n PROGRAMMING BOOKS
        \r1) edit
        \r2) delete
        \r3) return to main menu''')
        choice = input('\nPlease Choose an option: ')
        if choice in ['1', '2', '3']:
            return choice
        else:
            input('''
            \rPlease Choose one of the options above (1-3)
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
        

def edit_check(column_name, current_value):
    print(f'\n EDIT {column_name}')
    if column_name == 'Price':
        print(f'\rCurrent Value: {current_value/100}')
    elif column_name == 'Date':
        print(f'\rCurrent Value: {current_value.strftime("%B %d %Y")}')
    else:
        print(f'\rCurrent Value: {current_value}')

    if column_name == 'Date' or column_name == 'Price':
        while True:
            changes = input('What would like to change the value to?')
            if column_name == 'Date':
                changes = clean_date(changes)
                if type(changes) == datetime.date:
                    return changes
            elif column_name == 'Price':
                changes = clean_price(changes)
                if type(changes) == int:
                    return changes
    else:
        return input('What would like to change the value to?')


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

def clean_id(id_str, options):
    try:
        book_id = int(id_str)
    except ValueError:
        input(''' ID ERROR
                ID Should be a number
                press any key to continue
                ''')
        return
    else:
        if book_id in options:
            return book_id
        else:
            input('''
            INPUT ERROR
            ID Not on file
            press any key to continue
            ''')
            return



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
            id_options = [book.id for book in session.query(Book)]
            id_error = True
            while id_error:
                id_choice = input(f'''
                \n Id Options: {id_options}
                \rBook id: 
                ''')
                id_choice = clean_id(id_choice, id_options)
                if type(id_choice) == int:
                    id_error = False
            the_book = session.query(Book).filter(Book.id==id_choice).first()
            print(f'''
            \n{the_book.title} by {the_book.author} published on {the_book.published_date} for {the_book.price}
            ''')
            sub_choice = submenu()
            if sub_choice == '1':
                the_book.title = edit_check('Title', the_book.title)
                the_book.author = edit_check('Author', the_book.author)
                the_book.published_date = edit_check('Date', the_book.published_date)
                the_book.price = edit_check('Price', the_book.price)
                session.commit()
                print('Book Updated!')
                time.sleep(2)
            elif sub_choice == '2':
                session.delete(the_book)
                session.commit()
                print('Book Deleted')
                time.sleep(1.5)
        elif choice == '4':
            # analysis
            oldest_book = session.query(Book).order_by(Book.published_date).first()
            newest_book = session.query(Book).order_by(Book.published_date.desc()).first()
            total_books = session.query(Book).count()
            python_books = session.query(Book).filter(Book.title.like('%Python%')).count()
            print(f'''
            \n BOOK ANALYSIS \n
            \r * Oldest Book: {oldest_book} \n 
            \r *  Neweest Book: {newest_book} \n 
            \r * Total Books: {total_books} \n 
            \r * Number of Python Books: {python_books}
            ''')
            input('press any key to continue')
        elif choice == '5':
            print('GOODBYE')
            app_running = False


if __name__ == '__main__':
    Base.metadata.create_all(engine)
    add_csv()
    app()