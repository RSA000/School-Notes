import copy
import constants
import os
import random
import time

def clean_data(data):
    for i in range(len(data)):
        data[i]['height'] = (data[i]['height'][:2])
        if data[i]['experience'] == 'YES':
            data[i]['experience'] = True
        else:
            data[i]['experience'] = False
    return data


def divide_teams(data):
    experienced = [teammate for teammate in data if teammate['experience'] == True]
    inexperienced = [teammate for teammate in data if teammate['experience'] == False]
    return experienced, inexperienced

    
def make_teams(teams, experienced, inexperienced):
    teams_balanced = []
    for team in range(len(teams), 0, -1):
        teams_balanced.append(teams[team-1])
        experienced_players =  [experienced.pop() for i in range(len(experienced)//(team))]
        inexperienced_players = [inexperienced.pop() for i in range(len(inexperienced)//(team))]
        teams_balanced.append(experienced_players + inexperienced_players)
    return  teams_balanced


def display_team_info(team_num, teams_sorted):
    names = [teams_sorted[team_num + 1][i]['name'] for i in range(len(teams_sorted))]
    print(f'Team: {teams_sorted[team_num]} \n ----------')
    print(f'Total Players: {len(teams_sorted[team_num + 1])}')
    print('------------')
    print(str(names).replace('\'', '')[1:-1])
    input(' \n Enter any key to return to menu: ')


def main(teams_sorted):
    while True:
        os.system('clear')
        print('BASKETBALL TEAM STATS TOOL \n\n ---MENU---')
        print('Options: \n A) Display Team Stats \n B) Quit \n\n')
        option = input('Enter your choice: ').lower()
        if option != 'a' and option != 'b':
            os.system('clear')
            print('invalid choice :/')
            time.sleep(1)
            continue
        elif option == 'a':
            os.system('clear')
            print('TEAMS:')
            print(f'A) {teams_sorted[0]} \nB) {teams_sorted[2]} \nC) {teams_sorted[4]} \n')
            team_choice = input('Enter Your Choice: ').lower()
            if team_choice == 'a':
                os.system('clear')
                display_team_info(0, teams_sorted)
            elif team_choice == 'b':
                os.system('clear')
                display_team_info(2, teams_sorted)
            elif team_choice == 'c':
                os.system('clear')
                display_team_info(4, teams_sorted)
            elif option == 'b':
                break
            else:
                print('Invalid Choice :/')
                time.sleep(1)
                continue

if __name__ == '__main__':
    data_copy = copy.deepcopy(constants.PLAYERS)
    data_clean = clean_data(data_copy)
    experienced, inexperienced = divide_teams(data_clean)
    teams = make_teams(constants.TEAMS, experienced, inexperienced)
    main(teams)
