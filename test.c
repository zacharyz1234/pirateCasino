#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include<time.h>

// int main(void) {

//     for(int i = 0; i < 10; i++)
//     {
//         srand(time(NULL)); // Seed the RNG each time the loop iterates so numbers are always (hopefully) different

//         int suit = (rand() % 13) + 1;
//         rand();
//         printf("%d ", suit);
//         sleep(1);
//     }
// }

void setArraysTrue(bool arr[])
{
    for(int i = 0; i < 13; i++)
    {
        arr[i] = true;
    }
}


int getCard(int cards[], bool diamondCheck[], bool heartCheck[], bool spadeCheck[], bool clubCheck[], int cardSuit[], int num)
{
    unsigned int val;

    rand_s(&val);   //rand_s lets me generate a random number with higher chances of it being more random then rand(). There's also no need to set a seed (That rhymes!)

    int suit = (val % 4) + 1;
    int cardNo = (val % 13) + 1;

    switch(suit)
    {
        case 1:
            if(diamondCheck[cardNo] == false)
            {
                getCard(cards, diamondCheck, heartCheck, spadeCheck, clubCheck, cardSuit, num); //Recursive function to make sure it chooses a card that has not been chosen already
            }
            else
            {
                diamondCheck[cardNo] = false;
                cardSuit[num] = 1;
                return cardNo;
            }
            

            case 2:
            if(heartCheck[cardNo] == false)
            {
                getCard(cards, diamondCheck, heartCheck, spadeCheck, clubCheck, cardSuit, num); //Recursive function to make sure it chooses a card that has not been chosen already
            }
            else
            {
                heartCheck[cardNo] = false;
                cardSuit[num] = 2;
                return cardNo;
            }

            case 3:
            if(spadeCheck[cardNo] == false)
            {
                getCard(cards, diamondCheck, heartCheck, spadeCheck, clubCheck, cardSuit, num); //Recursive function to make sure it chooses a card that has not been chosen already
            }
            else
            {
                spadeCheck[cardNo] = false;
                cardSuit[num] = 3;
                return cardNo;
            }

            case 4:
            if(clubCheck[cardNo] == false)
            {
                getCard(cards, diamondCheck, heartCheck, spadeCheck, clubCheck, cardSuit, num); //Recursive function to make sure it chooses a card that has not been chosen already
            }
            else
            {
                clubCheck[cardNo] = false;
                cardSuit[num] = 4;
                return cardNo;
            }

    }

}


int playPoker(long long bank)
{
    long long pot = 0;
    int playerCardNo[2], dealerCardNo[2]; //Two arrays to hold the hands for both player and dealer
    int playerCardSuit[2], dealerCardSuit[2]; //This array holds the suits so that there isn't any confusion if two of the same card number are pulled
    int tableCards[5]; //An array to hold the cards that will be on the table
    

    //Two sets of arrays, one to represent the numbered cards and another to represent if the cards have been used.
    int diamonds[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int hearts[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int spades[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int clubs[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    //Boolean arrays initialize as true. If a card is used, the element matching that card will be set to false
    //So that it can't be used again
    bool diamondCheck[13];
    bool heartCheck[13];
    bool spadeCheck[13];
    bool clubCheck[13];

    setArraysTrue(diamondCheck);
    setArraysTrue(heartCheck);
    setArraysTrue(spadeCheck);
    setArraysTrue(clubCheck);
    
    


    if(bank < 50)
    {
        printf("You need at least $50 to buy-in for poker! Come back when you've got more cash.");
        return bank;
    }

    bank -= 50;
    pot += 50;

    for(int i = 0; i < 2; i++)
    {
        srand(time(NULL)); // Seed the RNG each time the loop iterates so numbers are always (hopefully) different
        playerCardNo[i] = getCard(playerCardNo, diamondCheck, heartCheck, spadeCheck, clubCheck, playerCardSuit, i);
        dealerCardNo[i] = getCard(dealerCardNo, diamondCheck, heartCheck, spadeCheck, clubCheck, dealerCardSuit, i);
    }

    for(int i = 0; i < 2; i++)
    {
        printf("PLAYER CARD NO: %d SUIT: %d DEALER CARD NO: %d SUIT: %d\n", playerCardNo[i], playerCardSuit[i], dealerCardNo[i], dealerCardSuit[i]);
    }

    

}

int main()
{
    int bank = 1000;
    playPoker(bank);
}