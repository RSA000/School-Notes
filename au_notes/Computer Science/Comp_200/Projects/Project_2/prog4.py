# This program calculates the perimeter and area of rectangles, squares, and circles.
from os import system
from sys import platform

def show_menu():
    print("\nProgram author: Richard Sullivan Andison \nID#: 3634206 \nProgram 4: Functions \n ")
    print("Calculations Menu")
    print("1: Area (Square)")
    print("2: Area (Rectangle)")
    print("3: Area (Circle)")
    print("4: Perimeter (Square)")
    print("5: Perimeter (Rectangle)")
    print("6: Perimeter (Circle)")
    print("7: Exit")

    while True:
        try:
            selection_number = int(input("Please select a calculation: "))
        except ValueError:
            print("Invalid selection")
            continue
        if selection_number > 0 and selection_number < 8:
            if platform == "linux" or platform == "darwin" or platform == "linux2":
                system('clear')
            if platform == "win32":
                system('cls')
            
            return selection_number
        print("Invalid selection")
        continue


def squarea():
    while True:
        try:  
            side = int(input("Input square side: "))
        except ValueError:
            print("Invalid input.")
            continue
        break
    print(f"\nThe area of a square with a side length of {side} is {side * side}\n")


def rectarea():
    while True:
        try:  
            length = int(input("Input length: "))
        except ValueError:
            print("Invalid input.")
            continue
        try:  
            width = int(input("Input width: "))
        except ValueError:
            print("Invalid input.")
            continue
        break
    print(f"\nThe area of a rectangle with a side length of {length} and a width of {width} is {length * width}\n")


def circarea():
    while True:
        try:  
            radius = int(input("Input radius: "))
        except ValueError:
            print("Invalid input.")
            continue
        break
    print(f"\nThe area of a circle with a radius of {radius} is  {3.14 * radius**2}\n")


def squarimeter():
    while True:
        try:  
            side = int(input("Input side: "))
        except ValueError:
            print("Invalid input.")
            continue
        break
    print(f"\nThe perimeter of a square with side lengths of {side} is {side * 4}\n")


def rectimeter():
    while True:
        try:  
            length = int(input("Input length: "))
        except ValueError:
            print("Invalid input.")
            continue
        try:  
            width = int(input("Input width: "))
        except ValueError:
            print("Invalid input.")
            continue
        break
    print(f"\nThe perimeter of a rectangle with a length of {length} and a width of {width} is {(width * 2 )+ (length * 2)}\n")


def circimeter():
    while True:
        try:  
            diameter = int(input("Input diameter: "))
        except ValueError:
            print("Invalid input.")
            continue
        break
    print(f"\nThe perimeter of a circle with a diameter length of {diameter} is {3.14 * diameter}\n")


def calculation_selector(num):
    if num == 1:
        squarea()
    elif num == 2:
        rectarea()
    elif num == 3:
        circarea()
    elif num == 4:
        squarimeter()
    elif num == 5:
        rectimeter()
    elif num == 6:
        circimeter()
    elif num == 7:
        return 7


while True:
    if calculation_selector(show_menu()) == 7:
        print("See you next time!")
        break
