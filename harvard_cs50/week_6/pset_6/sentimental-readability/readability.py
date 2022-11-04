from cs50 import get_string

# main function


def main():
    sentences = get_string("Please input sentence: ")
    avg_w = avg_word_len(sentences)
    avg_s = avg_sentence_len(sentences)
    cli_index = round(0.0588 * avg_w - 0.296 * avg_s - 15.8)
    print(cli_index)
    check_grade(cli_index)

# returns average length of words


def avg_word_len(sentences):
    word_length = 0
    word_count = 0

    for i in range(len(sentences)):
        # if current character is alphabetical
        if sentences[i].isalpha():
            word_length += 1
        # if current character is a space or the end of the sentece
        elif sentences[i] == ' ' or i == len(sentences) - 1:
            word_count += 1

    return (word_length / word_count * 100)

# returns average sentence length


def avg_sentence_len(sentences):
    total_words = 0
    total_sentences = 0

    for i in range(len(sentences)):
        # if character is a space ++ total words
        if sentences[i] == ' ':
            total_words += 1
        # if character is ., ?, or !
        elif sentences[i] in ['.', '?', '!']:
            if i == len(sentences) - 1:
                total_sentences += 1
                total_words += 1
            else:
                total_sentences += 1
    return total_sentences / total_words * 100

# prints out grade level


def check_grade(number):
    for i in range(16):
        if i == number:
            print(f"Grade {i}")

    if number < 0:
        print("Before Grade 1")
    elif number > 16:
        print("Grade 16+")


main()
