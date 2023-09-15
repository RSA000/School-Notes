# This program prompts the user for a password. If the password is correct, the program asks for the users name and displays a message greeting the user.

print("\nProgram author: Richard Sullivan Andison \nID#: 3634206 \nProgram 3: Loops And If Conditions \n ")

my_name = "Sullivan"
password = "hello"

while True:
    user_password = input("Please Input Password: ")
    if user_password == password:
        break
    print("Invalid password. Try again.")
print("\nWelcome!")

user_name = input("\nWhat is your name?: ").title()

if user_name in ["Madonna", "Cher"]:
    print("\nMay I have your autograph, please?")
elif user_name == my_name:
    print("What a great name!")
else:
    print(f'{user_name}, that\'s a nice name')
    