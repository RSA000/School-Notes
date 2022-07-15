# Import your Game class
from phrasehunter.game import Game
import os
import time

# Create your Dunder Main statement.
if '__main__' == __name__:
    phrases = ['This old world is a new world', 'something something darkside',
               'The best laid plans of mice and men', 'simple is better then complex',
               'complex is better then complicated']
    while True:
        game = Game(phrases)
        game.reset()
        game.start()
        while True:
            play_again = input('Play Again? Y/N: ').lower()
            if play_again == 'y' or 'no':
                if play_again == 'y':
                    break
                elif play_again == 'n':
                    break
                else:
                    os.system('clear')
                    print('Invalid Choice')
                    time.sleep(1)
                    os.system('clear')
                    continue
        if play_again == 'y':
            continue
        elif play_again == 'n':
            os.system('clear')
            print('Thanks For Playing!')
            break