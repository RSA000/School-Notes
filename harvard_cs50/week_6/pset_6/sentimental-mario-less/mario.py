# Creating mario function
def mario(height):
    for i in range(height, 0, -1):
        print(" " * (i - 1), end="")
        print("#" * (height + 1 - i), end="")
        print()

# Main Function


def main():
    while True:
        try:
            height = int(input("Height: "))
        except ValueError:
            continue
        # Checking if height is between 0 and 9
        if height > 0 and height < 9:
            mario(height)
            break


# Running main
main()