# Program 2 Using Input

# Printing Out Credentials
print("\nProgram author: Richard Sullivan Andison \nID#: 3634206 \nProgram 2: Using Input \n ")

# Creating an empty list to store strings/integers
lst_str = []
lst_int = []

# Creating a while loop that asks for input until user has entered the correct data
# While the length of the list is less than 2
# ask user for input of string
while len(lst_str) < 2:
    # The string variable is assigned to the input of the user. 
    # All user input is converted to a string datatype
    string = str(input(f"Please input a string #{len(lst_str) + 1}: "))
    # The string variable must be alphabetical
    if string.isalpha():
        # If the string variable is alphabetical, append to lst
        lst_str.append(string)
    else:
        # Otherwise, print (invalid input try again) and start the loop over
        print("invalid input, must input only alphabetical characters: ")

# Next, we can do the same thing for the integers

# while the length of the list is less than 4
# ask user for input of integer
while len(lst_int) < 2:
    # The integer variable is assigned to the input of the user
    # all user input is converted to an int type
    try:
        integer = int(input(f"Please input integer # {len(lst_int) + 1}: "))
        # If there is a value error (integer not entered) prompt user to try again.
    except ValueError:
        print("invalid input, Can only input numbers: ")
        # continue resets the loop to the beginning
        continue
    # If the input is indeed a number, append to lst
    lst_int.append(integer)

#empty print to look neater
print()
# printing out the added strings
print(lst_str[0] + lst_str[1])
# printing out the added integers
print(lst_int[0] + lst_int[1])