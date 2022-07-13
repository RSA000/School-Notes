# Create your Game class logic in here.
from phrasehunter.phrase import Phrase
import random
import os
import time

class Game():
    active_phrase = None
    guesses = [' ']
    missed = 0

    def __init__(self, phrases):
        self.phrases = [Phrase(phrase) for phrase in phrases]

    def welcome(self):
        print('Welcome To The Phrase Guessing Game! \n')
    

    def get_random_phrase(self):
        self.active_phrase = random.choice(self.phrases)


    def get_guess(self):
        guess = input('Guess a letter: ').lower()
        if guess in self.guesses:
            print('\n Already Guessed')
            time.sleep(1)
        elif len(guess) > 1 or (not guess.isalpha()):
            print('\n Invalid Input :/')
            time.sleep(1)
        elif guess in self.active_phrase.phrase:
            self.guesses.append(guess)
        else:
            self.guesses.append(guess)
            self.missed += 1
            print(f'\n Not in phrase :/ \n lives left: {5 - self.missed}')
            time.sleep(1.5)


    def game_over(self):
        if self.active_phrase.check_complete(self.guesses):
            print('You Won!')
        else:
            print('Better Luck Next Time')


    def start(self):
        os.system('clear')
        self.welcome()
        self.get_random_phrase()
        print(self.active_phrase.display(self.guesses))
        while self.missed < 5:
            self.get_guess()
            os.system('clear')
            print(self.active_phrase.display(self.guesses))
            if self.active_phrase.check_complete(self.guesses):
                break
        self.game_over()


    def reset(self):
        self.guesses = [' ']

