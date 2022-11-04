import csv
import sys


def main():

    # TODO: Check for command-line usage

    if len(sys.argv) != 3:
        print('Incorrenct number of arguements')
        sys.exit()
    file_people = sys.argv[1]
    file_sequence = sys.argv[2]

    # TODO: Read database file into a variable
    # Creating list of people and their strs
    people_list = []

    with open(file_people, mode='r') as file:
        people = csv.reader(file)
        # Creating list of strs to check
        str_list_people = next(people)
        del str_list_people[0]

        # Appending lists of people and their str counts
        for line in people:
            people_list.append(line)

    # TODO: Read DNA sequence file into a variable

    with open(file_sequence, mode='r') as file:
        sequence = (file.read())

    # TODO: Find longest match of each STR in DNA sequence
    str_list = []
    for i in range(len(str_list_people)):
        str_list.append(longest_match(sequence, str_list_people[i]))

    # TODO: Check database for matching profiles
    same_different = [0 for x in range(len(people_list))]
    length = len(str_list)

    for i in range(len(people_list)):
        current_person = [int(x) for x in people_list[i][1:]]

        for j in range(length):
            if current_person[j] != str_list[j]:
                same_different[i] = 1
                break

    for k in range(len(same_different)):
        if same_different[k] == 0:
            print(people_list[k][0])
            return
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
