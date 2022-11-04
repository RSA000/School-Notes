import cs50

# main change function


def change(total):
    # first we times the total by 100
    total = total * 100
    # Then we divide by 25, 10, 5, 1 and deduct it from the total
    quarters = total // 25
    total -= quarters * 25

    dimes = total // 10
    total -= dimes * 10

    nickels = total // 5
    total -= nickels * 5

    pennies = total // 1
    total -= pennies * 1
    # printing out coin total
    print(int(quarters + dimes + nickels + pennies))

# main function


def main():
    while True:
        total = cs50.get_float("Enter Amount: ")
        if total > 0:
            break

    change(total)


main()
