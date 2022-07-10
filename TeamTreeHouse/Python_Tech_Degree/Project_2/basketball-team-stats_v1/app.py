import copy
import constants
import os
import random

def clean_data(data):
    clean_data = copy.deepcopy(data)
    for i in range(len(clean_data)):
        clean_data[i]['height'] = (clean_data[i]['height'][:2])
        if clean_data[i]['experience'] == 'YES':
            clean_data[i]['experience'] = True
        else:
            clean_data[i]['experience'] = False
    return clean_data


def balance_teams(teams, clean_data):
    team_list = []
    players_per_team = len(clean_data)//len(teams)
    for team in teams:
        team_list.append(team)
        team_list.append( [clean_data.pop(random.randint(0, len(clean_data)-1)) for i in range(players_per_team)])
    return  team_list


def display(team_num, teams_sorted):
        print(f'Team: {teams_sorted[team_num]}')
        print('------------')
        print(f'Total Players: {len(teams_sorted[team_num + 1])}')
        print('------------')
        print(str([teams_sorted[team_num + 1][i]['name'] for i in range(len(teams_sorted))])[1:-1].replace('\'', ('')))
        input(' \n Enter any key to return to menu: ')


def display_teams(teams_sorted):
    while True:
        os.system('clear')
        print('BASKETBALL TEAM STATS TOOL \n\n ---MENU---')
        print('Options: \n A) Display Team Stats \n B) Quit \n\n')
        
        option = input('Enter your choice: ').lower()
        
        if option != 'a' and option != 'b':
            os.system('clear')
            print('invalid choice')
            continue
        elif option == 'a':
            os.system('clear')
            print('TEAMS:')
            print(f'A) {teams_sorted[0]} \nB) {teams_sorted[2]} \nC) {teams_sorted[4]} \n')
            team_choice = input('Enter Your Choice: ').lower()
            
            if team_choice == 'a':
                os.system('clear')
                display(0, teams_sorted)
            elif team_choice == 'b':
                os.system('clear')
                display(2, teams_sorted)
            elif team_choice == 'c':
                os.system('clear')
                display(4, teams_sorted)
        elif option == 'b':
            break

if __name__ == '__main__':
    team_list = clean_data(constants.PLAYERS)
    teams_sorted = balance_teams(constants.TEAMS, team_list)
    display_teams(teams_sorted)
