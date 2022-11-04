from cs50 import get_int

# checking validity of card


def is_valid(number):
    # list comprehension changing number into a list of strings
    number = [int(x) for x in str(number)]
    # number_1 is now a list of every second element times to starting from the end
    number_1 = [str(x * 2) for x in number[-2::-2] if x != 0]
    number_2 = [x for x in number[-1::-2]]

    for i in range(len(number_1)):
        if len(number_1[i]) > 1:
            number_1[i] = int(number_1[i][0]) + int(number_1[i][1])
    number_1 = [int(x) for x in number_1]

    if (sum(number_1) + sum(number_2)) % 10 == 0:
        return True
    return False

# checking type of card


def check_type(number):
    number = str(number)
    if number[0:2] in ['34', '37'] and len(number) == 15:
        print("AMEX")
    elif number[0:2] in ['51', '52', '53', '54', '55'] and len(number) == 16:
        print("MASTERCARD")
    elif number[0] == '4' and len(number) == 16 or len(number) == 13:
        print("VISA")
    else:
        print("INVALID")

# Main function


def main():
    card_number = get_int("Please Input Card Number: ")

    if is_valid(card_number):
        print(check_type(card_number))
    else:
        print("INVALID")


main()