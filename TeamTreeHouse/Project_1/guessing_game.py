# Object of this project is to utilize basic Python functionality to create a number guessing game
# Random Library will be used

import random
import os
highscore = 10000

def guessing_game(r):
    global highscore
    number = random.randint(1, r)
    guess = None
    attempts = 0

    while guess != number:
        try:
            guess = int(input('Take a guess! '))
        except ValueError:
            os.system('clear')
            print('Thats not a number :/ \n')
            continue
        
        if guess < 1 or guess > r:
            os.system('clear')
            print('Out of range :/')
            continue
        attempts += 1
        if guess > number:
            os.system('clear')
            print('Too High')
        elif guess < number:
            os.system('clear')
            print('Too Low')
    os.system('clear')
    print(f'Huzzah! You guessed the number in {attempts} tries! \n')
    if attempts < highscore:
        highscore = attempts
        print(f'You got a new Highscore! : {highscore} \n')
    else:
        print('You didn\'t beat the highscore :/ \n')


def main():
    os.system('clear')
    print('Guessing Game!')

    while True:
        try:
            r = int(input('Please choose a range (1 - ?): '))
        except ValueError:
            os.system('clear')
            print('Thats not a valid input (must be a number) ')
            continue
        break 
    
    while True:
        guessing_game(r)
        while True:
            play_again = input('Play again? y/n: ').lower()
            os.system('clear')
            if play_again != 'y' and play_again != 'n':
                print('Not a valid choice :/ (y or n) \n')
                continue
            break
        if play_again == 'n':
            break
        elif play_again == 'y':
            continue

main()

