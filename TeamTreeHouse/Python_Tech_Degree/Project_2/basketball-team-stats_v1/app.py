import copy
import constants
import os
import time

# Changes Height to an integer value and experience to boolean
def clean_data(data):
    for i in range(len(data)):
        data[i]['height'] = (data[i]['height'][:2])
        if data[i]['experience'] == 'YES':
            data[i]['experience'] = True
        else:
            data[i]['experience'] = False
    return data

# Divides players into two lists based on experience
def create_exp_inexp_lists(data):
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


def display_menu():
    os.system('clear')
    print('BASKETBALL TEAM STATS TOOL \n\n ---MENU---')
    print('Options: \n A) Display Team Stats \n B) Quit \n\n')
    option = input('Enter your choice: ').lower()
    return option


def choose_team(teams_sorted):
    os.system('clear')
    print('TEAMS:')
    print(f'A) {teams_sorted[0]} \nB) {teams_sorted[2]} \nC) {teams_sorted[4]} \n')
    team_choice = input('Enter Your Choice: ').lower()
    return team_choice


def display_team_info(team_num, teams_sorted):
    names = [teams_sorted[team_num + 1][i]['name'] for i in range(len(teams_sorted))]
    print(f'Team: {teams_sorted[team_num]} \n ----------')
    print(f'Total Players: {len(teams_sorted[team_num + 1])} \n ------------')
    print(str(names).replace('\'', '')[1:-1])
    input(' \n Enter any key to return to menu: ')


def team_display(team_choice, teams_sorted):
    if team_choice == 'a':
        os.system('clear')
        display_team_info(0, teams_sorted)
    elif team_choice == 'b':
        os.system('clear')
        display_team_info(2, teams_sorted)
    elif team_choice == 'c':
        os.system('clear')
        display_team_info(4, teams_sorted)


if __name__ == '__main__':
    data_copy = copy.deepcopy(constants.PLAYERS)
    data_clean = clean_data(data_copy)
    experienced, inexperienced = create_exp_inexp_lists(data_clean)
    teams_sorted = make_teams(constants.TEAMS, experienced, inexperienced)
    
    while True:
        option = display_menu()
        if option not in ['a', 'b']:
            os.system('clear')
            print('invalid choice :/')
            time.sleep(1)
            continue
        elif option == 'a':
            team_choice = choose_team(teams_sorted)
            if team_choice not in ['a', 'b', 'c']:
                os.system('clear')
                print('invalid choice :/')
                time.sleep(1)
                continue
            team_display(team_choice, teams_sorted)
        elif option == 'b':
            break
