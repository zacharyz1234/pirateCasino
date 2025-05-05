#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<string.h>
#include<time.h>

//Options menu for the blackjack game.
void blackjackMenu()
{
    printf("\nWelcome to Blackjack!\n\nSelect an option below:\n");
    printf("1. Start the game! Bet required: \n");
    printf("2. Blackjack Rules\n");
    printf("3. Current cash available\n");
    printf("0. Return to main menu\n");

}

//Rules for Blackjack.
void blackjackRules()
{
    printf("How to play blackjack:\n");
    printf("The dealer will give the player and themself two cards, one face up and the second face down.\n");
    printf("The goal is to get as close to 21 as possible. If you pass 21 or your total is below the dealer's, you lose.\n");
    printf("The player wins if they have a higher number than the dealer but still below 21, or the dealer loses and exceeds 21.\n");
    printf("Note: An Ace can be played as either a 1 or an 11.\n");
}

//Used to output the card that is currently given.
//For this game, suits don't matter, so only the card number/name is given. 
void displayCard(int card)
{
    switch(card)
    {
        case 1: 
            printf("Ace\n");
            break;
        case 11:
            printf("Jack\n");
            break;
        case 12:
            printf("Queen\n");
            break;
        case 13:
            printf("King\n");
            break;
        default:
            printf("%d\n", card);
    }
}

//Deals cards to the player and the dealer. Each person gets two cards, with the first one displayed and the second one hidden. 
void dealCards(int player[], int dealer[], int* playerCount, int* dealerCount)
{
    printf("\nDealing Cards...\n\n");
    
    for(int count = 0; count < 4; count++)
    {
        if(count % 2 == 0)
        {
            dealer[*dealerCount] = (rand() % 13) + 1;
            (*dealerCount)++;
        }
        else    
        {
            player[*playerCount] = (rand() % 13) + 1;
            (*playerCount)++;
        }
    }
    printf("The dealer's first card is: ");
    displayCard(dealer[0]);
    //printf("The dealer's second card is: (debug) ");
    //displayCard(dealer[1]);
    printf("The player's first card is: ");
    displayCard(player[0]);
    //printf("The player's second card is: (debug) ");
    //displayCard(player[1]);
}

//Gives the player a random card between 1 and 13. 
void hitCard(int player[], int* playerCount)
{
    //srand(time(0));
    player[*playerCount] = rand() % 13 + 1;
    printf("Card given: ");
    displayCard(player[*playerCount]);
    (*playerCount)++;
}

//Lets the player decide if they want their ace to count for a 1 or 11. 
void ace(int* total, bool dealer)
{
    //Automatically calculates for the dealer. 
    if(dealer == true)
    {
        if(*total - 1 + 11 <= 21)
            *total = *total - 1 + 11;
        return;
    }

    //Manual input from the user. 
    printf("Would you like your ace to count for a 1 or 11?\n");
    printf("Current total is: %d\n", *total);
    printf("(Ace is counted as 1 currently)\n\n");
    printf("Enter 1 or 11 to answer: ");
    int input = 0; 
    while(input != 1 || input != 11)
    {
        scanf("%d", &input);
        if(input == 1 || input == 11)
        {
            total = total - 1 + input; 
            return; 
        }
        printf("\nPlease enter a valid input.\n");
    }
    
    
}

//Totals all the cards of the current hand.
int total(int player[], int playerCount, bool dealer)
{
    int total = 0; 
    int aceCount = 0;   //In case a player has multiple aces. 
    bool aceExist = false;
    for(int count = 0; count < playerCount; count++)
    {   
        if(player[count] == 1)
        {
            aceExist = true;
            aceCount++;
        }
            
        if(player[count] >= 11 && player[count] <= 13)
        {
            total += 10;
            continue;
        }
        total += player[count];
    }
    if(aceExist == true)
    {
        for(int count = 0; count < aceCount; count++)
        {
            //Accounts for choosing if the player wants a 1 or 11 for their Ace.
            //If this is the dealer, then it calculates the best case automatically. 
            ace(&total, dealer);   
        }
    }
    
    return total; 
}

//Dealer's turn to draw cards to reach close to 21. 
bool dealerTurn(int dealer[], int* dealerCount)
{
    printf("\nDealer's Turn:\nDealer's face-down card is: ");
    displayCard(dealer[1]);

    int dealerTotal = total(dealer, *dealerCount, true);
    while(dealerTotal <= 16) //If the dealer reaches 17 or more, per the rules, they stop drawing.
    {
        hitCard(dealer, dealerCount);
        if(dealer[*dealerCount - 1] == 1)
        {
            dealerTotal += 1; 
            ace(&dealerTotal, true);
        }
        else if(dealer[*dealerCount - 1] >= 11 && dealer[*dealerCount - 1] <= 13)
        {
            dealerTotal += 10;
        }
        else
            dealerTotal += dealer[*dealerCount - 1];
    }
    printf("Dealer's total is: %d\n", dealerTotal);
    if(dealerTotal <= 21)   
    {
        printf("\nThe dealer is still in!\n");
        return true; 
    }
    else
    {
        printf("\nThe dealer has exceeded 21.\n");
        return false; 
    }
}

//Function that starts the game. 
void gameStart()
{
    int player[7];
    int playerCount = 0; 
    int dealer[7];
    int dealerCount = 0; 
    int playerTotal = 0;
    int dealerTotal = 0;

    dealCards(player, dealer, &playerCount, &dealerCount);
    //printf("(Debug) playerCount: %d", playerCount);
    //printf("(Debug) dealerCount: %d", dealerCount);
    int decision = 0; 
    while(decision != 2)
    {
        printf("\n1. Hit\n2. Stand\n");
        scanf("%d", &decision);
        if(decision < 1 || decision > 2)
        {
            printf("Please enter a valid input.\n");
            continue;
        }
        if(decision == 2)
        {
            printf("\nThe player's face-down card is: ");
            displayCard(player[1]);
            playerTotal = total(player, playerCount, false);
            if(playerTotal > 21)
            {
                printf("\nYour total is greater than 21.\n\nSorry! You lose.\n");
                return; 
            }
            break;
        }
        hitCard(player, &playerCount);
    }


    if(dealerTurn(dealer, &dealerCount))
    {
        dealerTotal = total(dealer, dealerCount, true);
        
        printf("\nTotals:\nDealer: %d\nPlayer: %d\n",dealerTotal, playerTotal);
        if(playerTotal > 21 || playerTotal < dealerTotal)
        {
            printf("\nSorry! You lose.\n");
            return;
        }
        else if(playerTotal > dealerTotal)
        {
            printf("\nYou win!\n");
            return;
        }
        else if(playerTotal == dealerTotal)
        {
            printf("\nIt's a tie! Nothing rewarded.\n");
            return;
        }
    }
    else
    {
        printf("\nYou win!\n");
        return;
    }
    
    
}

int main()
{
    srand(time(0));
    int option = 1; 
    while(option != 0)
    {
        blackjackMenu();
        scanf("%d", &option);
        switch(option)
        {
            case 0:
                printf("\nReturning to main menu...\n\n");
                return 0;
            case 1:
                gameStart();
                break;
            case 2: 
                blackjackRules();
                break;
            case 3:
                //function to display current gambling balance.
                break;
            default:
                printf("Please enter a valid input.\n");
                break;
        }
    }
    

}