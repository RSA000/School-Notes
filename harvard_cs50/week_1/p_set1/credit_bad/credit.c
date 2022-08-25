#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long card_number = get_long("Please enter your credit card number: ");
    int card_total = 0;
    for (long i = 10; i < 1000000000000000000; i = i * 100)
    {
        long card = card_number / i % 10;
        int num_first = card * 2;
        int num_last = (card * 2) % 10;
        if (num_first > 10)
        {
            while(num_first >= 10)
                {
                num_first = num_first / 10;
                }
        }
        else
        {
            num_first = 0;
        }
        card_total = card_total + num_first + num_last;
    }
    for (long i = 1; i < 10000000000000000; i = i * 100)
    {
        long card = card_number / i % 10;
        card_total = card_total + card;
    }
    if (card_total % 10 == 0)
    {
        while (card_number >= 10)
            {
                card_number = card_number / 10;
            }
        printf("%li", card_number);
        if (card_number == 3)
            {
                printf("AMEX\n");
            }
        else if (card_number == 5)
            {
                printf("MASTERCARD\n");
            }
        else if (card_number == 4)
            {
                printf("VISA\n");
            }
    }
    else
    {
        printf("INVALID\n");
    }
}

