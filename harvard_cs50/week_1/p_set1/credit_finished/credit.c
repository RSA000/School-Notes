#include <cs50.h>
#include <stdio.h>

int check_sum(long card_num);
void check_valid(long card_num);

int main(void)
{
    check_valid(get_long("Please input your card number\n"));
}

// This is luhns algorithm. It returns true if the sum ends in 0 and false otherwise
int check_sum(long card_num)
{
    // num is the current number that we are looping through
    int card_sum = 0;
    int num = 0;
    int num_last = 0;
    for (long i = 10; i < 100000000000000000; i *= 100)
    {
        // the tmp_card_num will be divided by 100, 1000 ect.. so we can get the last number
        // for this loop it starts at 10 so we start at the second last digit
        long tmp_card_num = card_num / i;
        num = tmp_card_num % 10 * 2;
        int num_first = num;
        num_last = num % 10;
        if (num_first >= 10)
        {
            // Here, we check if the numbers multiplied is greater than ten so we can
            // grab the first and last digits of our multiplied numbers
            while (num_first >= 10)
            {
                num_first = num_first / 10;
            }
        }
        else
        {
            num_first = 0;
        }
        card_sum = card_sum + num_first + num_last;
    }
    for (long j = 1; j < 1000000000000000; j = j * 100)
        // here, we grab the numbers that we don't multiply and add it to the sum
    {

        long tmp_card_num = card_num / j;
        num = tmp_card_num % 10;
        card_sum = card_sum + num;
    }
    // this is the final check to see if the sum ends in 0
    if (card_sum % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// This checks if the card length is correct and what type of card it is
void check_valid(long card_num)
{
    if (check_sum(card_num))
    {
        long amex_master = card_num;
        long visa = card_num;
        // this grabs the first two digits for mastercard and amex checking
        // the visa grabs the first number
        while (amex_master >= 100)
        {
            amex_master /= 10;
        }
        while (visa >= 10)
        {
            visa /= 10;
        }
        if (amex_master >= 51 && amex_master <= 55)
        {
            // we are checking here if the card number is the correct amount of digits
            // mastercard uses 16 so anything larger than 1000000000000000 or below 9999999999999999
            // is valid
            if (card_num >= 1000000000000000 && card_num <= 9999999999999999)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (amex_master == 34 || amex_master == 37)
        {
            if (card_num >= 100000000000000 && card_num <= 999999999999999)
            {
                printf("AMEX\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else if (visa == 4)
        {
            if (card_num >= 1000000000000 || card_num >= 1000000000000000)
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // this is for if check_sum returns false
    else
    {
        printf("INVALID\n");
    }
}



