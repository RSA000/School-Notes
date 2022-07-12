# Create your Phrase class logic here.
class Phrase():

    def __init__(self, phrase):
        self.phrase = list(phrase.lower())
    

    def display(self, guesses):
            correct_guessed = []
            for i in self.phrase:
                if i in guesses:
                    correct_guessed.append(i)
                else:
                    correct_guessed.append('_')
            return ''.join(correct_guessed)


    def check_letter(self, guess):
        if guess in self.phrase:
            return True
        else:
            return False


    def check_complete(self, guesses):
        if (''.join(self.phrase)) == self.display(guesses):
            return True
        else:
            return False
    