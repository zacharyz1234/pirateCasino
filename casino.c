#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<string.h>
#include<time.h>

/*NOTICE: I used chatGPT for help and understanding of how this function works
This is the only thing in this project made with the help of chatGPT, but
since the concept of changing text colors is new to me, I asked the bot 
for a little help.*/
void setTextColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}



//PRINT MENU==========================================================================================================
void displayMenu(long long bank)
{
    /*Editor's note from Zak: I know this looks absolutely atrocious but I promise it looks great when printed.
        Do not fear the sectioned out text, for it looks great!*/
    
    setTextColor(FOREGROUND_RED);
    printf("--------------------------------------------------\n");
    printf("|                                                |\n");

    printf("|");
    setTextColor(FOREGROUND_BLUE);
    printf("          ****************************          ");          
    setTextColor(FOREGROUND_RED);    
    printf("|\n");

    printf("|");
    setTextColor(FOREGROUND_BLUE);
    printf("          *");
    setTextColor(FOREGROUND_GREEN);
    printf(" Welcome-To-Pirate-Casino");
    setTextColor(FOREGROUND_BLUE);
    printf(" *");
    setTextColor(FOREGROUND_RED);
    printf("          |\n");
    
    printf("|");
    setTextColor(FOREGROUND_BLUE);
    printf("          ****************************          ");          
    setTextColor(FOREGROUND_RED);    
    printf("|                                                \n");

    printf("|                                                |\n");
    printf("|          ");
    setTextColor(FOREGROUND_GREEN);
    printf("What would you like to play?          ");
    setTextColor(FOREGROUND_RED);
    printf("|\n");

    printf("|                                                |\n");
    printf("|                                                |\n");

    printf("|  ");
    setTextColor(FOREGROUND_GREEN);
    printf("1. Texas Hold Em' Poker                       ");
    setTextColor(FOREGROUND_RED);
    printf("|\n");

    printf("|                                                |\n");

    printf("|  ");
    setTextColor(FOREGROUND_GREEN);
    printf("2. Blackjack                                  ");
    setTextColor(FOREGROUND_RED);
    printf("|\n");

    printf("|                                                |\n");
    printf("|  ");
    setTextColor(FOREGROUND_GREEN);
    printf("3. Roulette                                   ");
    setTextColor(FOREGROUND_RED);
    printf("|\n");

    printf("|                                                |\n");

    printf("|  ");
    setTextColor(FOREGROUND_GREEN);
    printf("4. Lucky Slots                                ");
    setTextColor(FOREGROUND_RED);
    printf("|\n");
    printf("|                                                |\n");

    printf("|  ");
    setTextColor(FOREGROUND_GREEN);
    printf("0. Quit                                       ");
    setTextColor(FOREGROUND_RED);
    printf("|\n");
    printf("|                                                |\n");
    printf("--------------------------------------------------\n\n");

    //Prints Bank total
    printf("--------------------------------------------------\n");
    printf("Bank Balance: $%d                               \n", bank);
    printf("--------------------------------------------------\n");

    setTextColor(FOREGROUND_GREEN);
}
//PRINT MENU==========================================================================================================




//POKER==========================================================================================================



void printCard(int number, int suit)
{
    char *numStr;
    char *suitStr;

    // Convert card numbers to face card names
    switch(number)
    {
    case 1:
        numStr = "Ace";
        break;

    case 11:
        numStr = "Jack";
        break;

    case 12:
        numStr = "Queen";
        break;

    case 13:
        numStr = "King";
        break;

    default:
        static char buffer[3];
        sprintf(buffer, "%d", number);
        numStr = buffer;

    }

    // Converts suit number to suit name
    switch(suit)
    {
    case 1:
        suitStr = "Diamonds";
        break;

    case 2:
        suitStr = "Hearts";
        break;

    case 3:
        suitStr = "Spades";
        break;

    case 4:
        suitStr = "Clubs";
        break;

    default:
        suitStr = "Unknown";
    }

    printf("%s of %s", numStr, suitStr);
}

void printPlayerAndTableCards(int playerCardNo[], int playerCardSuit[], int tableCardNo[], int tableCardSuit[], int tableCardsShown)
{
    printf("\nYour Hand:\n");
    for (int i = 0; i < 2; i++)
    {
        printf("- ");
        printCard(playerCardNo[i], playerCardSuit[i]);
        printf("\n");
    }

    printf("\nTable Cards:\n");
    for (int i = 0; i < tableCardsShown; i++)
    {
        printf("- ");
        printCard(tableCardNo[i], tableCardSuit[i]);
        printf("\n");
    }
}

void printAllCards(int playerCardNo[], int playerCardSuit[], int tableCardNo[], int tableCardSuit[], int tableCardsShown, int dealerCardNo[], int dealerCardSuit[])
{
    printf("\nYour Hand:\n");
    for (int i = 0; i < 2; i++)
    {
        printf("- ");
        printCard(playerCardNo[i], playerCardSuit[i]);
        printf("\n");
    }

    printf("\nTable Cards:\n");
    for (int i = 0; i < tableCardsShown; i++)
    {
        printf("- ");
        printCard(tableCardNo[i], tableCardSuit[i]);
        printf("\n");
    }

    printf("\nDealer Cards:\n");
    for(int i = 0; i < 2; i++)
    {
        printf("- ");
        printCard(dealerCardNo[i], dealerCardSuit[i]);
        printf("\n");
    }

}

int evaluateHands(int allCardNum[], int allCardSuit[])
{
    //Sorts the arrays so they are ordered from least to greatest. Makes it easier to check for a straight later on
    //This is bubble sort
    for (int i = 0; i < 7; i++) 
    {

        for (int j = i + 1; j < 7; j++)
        {

            if (allCardNum[i] > allCardNum[j]) \
            {
                // Swap card numbers
                int tempNum = allCardNum[i];
                allCardNum[i] = allCardNum[j];
                allCardNum[j] = tempNum;
    
                // Swap card suits with the numbers
                int tempSuit = allCardSuit[i];
                allCardSuit[i] = allCardSuit[j];
                allCardSuit[j] = tempSuit;
            }
        }
    }

    //Counts the amount of which cards and which suits are used
    int numCount[13] = {0};
    int suitCount[4] = {0};

    //Subtracts 1 to correctly place the number in the right index
    for(int i = 0; i < 7; i++)
    {
        numCount[allCardNum[i] - 1]++;
        suitCount[allCardSuit[i] - 1]++;
    }

    //Checks for a flush
    bool isFlush = false;
    for(int i = 0; i < 4; i++)
    {
        if(suitCount[i] >= 5)
        {
            isFlush = true;
            break;
        }
    }


    //Checks for a straight
    bool isStraight = false;
    for(int i = 0; i < 3; i++) //Iterates 3 times because there are 7 elements, so there could only be 3 possible iterations of 5 in a row
    {
        if(allCardNum[i] + 1 == allCardNum[i + 1] && allCardNum[i + 1] + 1 == allCardNum[i + 2] && allCardNum[i + 2] + 1 == allCardNum[i + 3] && allCardNum[i + 3] + 1 == allCardNum[i + 4])
        {
            isStraight = true;
            break;
        }
    }
    //Checks for a straight with an Ace, 10, Jack, Queen, and King. They're out of order so I'm checking seperately
    if(numCount[0] >= 1 && numCount[10] >= 1 && numCount[11] >= 1 && numCount[12] >= 1 && numCount[13] >= 1)
    {
        isStraight = true;

    }

    //Checks for the royal flush
    //Loops through each suit
    for (int i = 0; i < 4; i++) 
    {
        //Five booleans to check that the specific card values and suits all exist within a hand
        bool has10 = false, hasJack = false, hasQueen = false, hasKing = false, hasAce = false;

        //Loops through the 7 cards in the array
        for (int j = 0; j < 7; j++) 
        {
            //If the current card suit is the suit we are looking at
            if (allCardSuit[j] == i) 
            {
                if (allCardNum[j] == 1) 
                {
                    hasAce = true;
                }
                if (allCardNum[j] == 10)
                {
                    has10 = true;
                } 
                if (allCardNum[j] == 11) 
                {
                    hasJack = true;
                }
                if (allCardNum[j] == 12) 
                {
                    hasQueen = true; 
                }
                if (allCardNum[j] == 13) 
                {
                    hasKing = true;
                }
            }
        }

        //If there are these 5 cards all within the same suit then it is a royal flush
        if (has10 && hasJack && hasQueen && hasKing && hasAce) 
        {
            return 10; // Royal Flush
        }
    }


    //Check for straight flush
    if(isFlush && isStraight)
    {
        return 9; //Straight Flush
    }

    //Check for four of a kind
    for(int i = 0; i < 13; i++)
    {
        if(numCount[i] == 4)
        {
            return 8; //Four of a kind
        }
    }

    //Check for full house
    for(int i = 0; i < 13; i++)
    {
        if(numCount[i] == 3)
        {
            for(int j = i; j < 13; j++)
            {
                if(j != i)
                {
                    if(numCount[j] == 2)
                    {
                        return 7; //Full house
                    }
                }
            }
        }
    }

    //Return statement for flush
    if(isFlush)
    {
        return 6; //Flush
    }

    //Return statemenet for straight
    if(isStraight)
    {
        return 5; //Straight
    }

    //Check for three of a kind
    for(int i = 0; i < 13; i++)
    {
        if(numCount[i] == 3)
        {
            return 4; //Three of a kind
        }
    }

    //Check for two pair
    for(int i = 0; i < 13; i++)
    {
        if(numCount[i] == 2)
        {
            for(int j = i + 1; j < 13; j++) //Iterates at i + 1, because everything before i should've been checked already
            {
                if(numCount[j] == 2)
                {
                    return 3; //Two pair
                }
            }
        }
    }

    //Check for pair. I think I could implement this within the two pair check but I just want to be safe and implement here
    for(int i = 0; i < 13; i++)
    {
        if(numCount[i] == 2)
        {
            return 2; //Pair
        }
    }

    //Returns a high card if no other hand types are found
    return 1; //High card
}

//Sets the four boolean arrays to be true when the game starts so that the getCard function works correctly
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

long long setBet(long long bank, long long *pot)
{
    system("cls");
    long long bet;
    printf("You currently have $%d in your bank. There are $%d in the pot. How much money would you like to bet (Enter 0 to cancel your bet and stand): ", bank, *pot);
    scanf("%d", &bet);

    if(bet <= 0)
    {
        printf("Player chose not to bet...");
        sleep(1);
        return bank;
    }
    while(bet > bank)
    {
        printf("You currently have $%d in your bank. There are $%d in the pot. How much money would you like to bet (Enter 0 or below to cancel your bet and stand): ", bank, *pot);
        scanf("%d", &bet);
    }

    bank -= bet;
    *pot += bet * 2; //Doubles bet to account for dealer adding to the pot as well

    printf("Player bets $%d. There are now $%d in the pot...", bet, *pot);
    sleep(1);

    return bank;
}

int printWinner(int playerHandType, int dealerHandType, int playerHand[], int dealerHand[], long long bank, long long *pot)
{

    if(playerHandType > dealerHandType)
    {
        switch(playerHandType)
        {
            case 1:

                printf("Player wins with High Card. Payout: $%lld", *pot);
                bank += *pot;
                *pot = 0;
                return bank;

            case 2:

                printf("Player wins with a Pair. Payout: $%lld", *pot);
                bank += *pot;
                *pot = 0;
                return bank;

            case 3:

                printf("Player wins with Two Pair. Payout: $%lld", *pot);
                bank += *pot;
                *pot = 0;
                return bank;

            case 4:

                printf("Player wins with Three of A Kind. Payout: $%lld", *pot);
                bank += *pot;
                *pot = 0;
                return bank;

            case 5:

                printf("Player wins with a Straight. Payout: $%lld", *pot);
                bank += *pot;
                *pot = 0;
                return bank;

            case 6:

                printf("Player wins with a Flush. Payout: $%lld", *pot);
                bank += *pot;
                *pot = 0;
                return bank;

            case 7:

                printf("Player wins with Full House. Payout: $%lld", *pot);
                bank += *pot;
                *pot = 0;
                return bank;

            case 8:

                printf("Player wins with Four of A Kind. Payout: $%lld", *pot);
                bank += *pot;
                *pot = 0;
                return bank;
            
            case 9:

                printf("Player wins with Straight Flush. Payout: $%lld", *pot);
                bank += *pot;
                *pot = 0;
                return bank;

            case 10:

                printf("Player wins with Royal Flush! Insanely lucky! Payout: $%lld", *pot);
                bank += *pot;
                *pot = 0;
                return bank;
            
        }
    }
    else if(dealerHandType > playerHandType)
    {
        switch(dealerHandType)
        {
            case 1:

                printf("Dealer wins with High Card.");
                *pot = 0;
                return bank;

            case 2:

                printf("Dealer wins with One Pair.");
                *pot = 0;
                return bank;

            case 3:

                printf("Dealer wins with Two Pair.");
                *pot = 0;
                return bank;

            case 4:

                printf("Dealer wins with Three of A Kind.");
                *pot = 0;
                return bank;

            case 5:

                printf("Dealer wins with Straight.");
                *pot = 0;
                return bank;

            case 6:

                printf("Dealer wins with Flush.");
                *pot = 0;
                return bank;

            case 7:

                printf("Dealer wins with Full House.");
                *pot = 0;
                return bank;

            case 8:

                printf("Dealer wins with Four of A Kind.");
                *pot = 0;
                return bank;
            
            case 9:

                printf("Dealer wins with Straight Flush.");
                *pot = 0;
                return bank;

            case 10:

                printf("Dealer wins with a Royal Flush!");
                *pot = 0;
                return bank;
            
        }
    }
    else if(dealerHandType == playerHandType)
    {

        if((playerHand[0] > dealerHand[0] && playerHand[0] > dealerHand[1]) || (playerHand[1] > dealerHand[0] && playerHand[1] > dealerHand[1]))
        {
            printf("Tied hands. Player wins with higher card. Payout: $%lld", *pot);
        }
        else if((playerHand[0] < dealerHand[0] && playerHand[0] < dealerHand[1]) || (playerHand[1] < dealerHand[0] && playerHand[1] < dealerHand[1]))
        {
            printf("Tied hands. Dealer wins with higher card.");
        }
        else
        {
            printf("Tied hands with no single highest card. Pot will be split. Payout: $%lld", *pot / 2);
            bank -= *pot / 2;
        }
        
        return bank;
    }
}


int playPoker(long long bank)
{
    long long pot = 0;
    int playerCardNo[2], dealerCardNo[2]; //Two arrays to hold the hands for both player and dealer
    int playerCardSuit[2], dealerCardSuit[2]; //This array holds the suits so that there isn't any confusion if two of the same card number are pulled

    int tableCardNo[5], tableCardSuit[5]; //An array to hold the cards that will be on the table
    

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
        printf("You need at least $50 to buy-in for poker! Come back when you've got more cash.\n");
        return bank;
    }

    bank -= 50;
    pot += 100; //Total amount of both the player and dealers' buy-ins

    for(int i = 0; i < 2; i++) //For loop to get both the player and dealers' cards
    {
        playerCardNo[i] = getCard(playerCardNo, diamondCheck, heartCheck, spadeCheck, clubCheck, playerCardSuit, i);
        dealerCardNo[i] = getCard(dealerCardNo, diamondCheck, heartCheck, spadeCheck, clubCheck, dealerCardSuit, i);
    }

    for(int i = 0; i < 5; i++) //For loop to get all cards for the table. 
    {
        tableCardNo[i] = getCard(tableCardNo, diamondCheck, heartCheck, spadeCheck, clubCheck, tableCardSuit, i);
    }

    //FOR TESTING PURPOSES TO SEE CARD TYPES FOR BOTH PLAYER AND DEALER
    // for(int i = 0; i < 2; i++)
    // {
    //     printf("PLAYER CARD NO: %d SUIT: %d \nDEALER CARD NO: %d SUIT: %d\n", playerCardNo[i], playerCardSuit[i], dealerCardNo[i], dealerCardSuit[i]);
    // }

    //     printf("\n");

    // for(int i = 0; i < 5; i++)
    // {
    //     printf("TABLE CARD NO: %d SUIT: %d\n", tableCardNo[i], tableCardSuit[i]);
    // }


    int tableCardsRevealed = 3; // Start by revealing 3 cards
    int turnCount = 0;


    //Where the game of poker actually runs
while (turnCount < 3) //Should only run 3  times
{
    int turnChoice = 0;

    while (turnChoice < 1 || turnChoice > 3)
    {

        system("cls");
        printPlayerAndTableCards(playerCardNo, playerCardSuit, tableCardNo, tableCardSuit, tableCardsRevealed);

        printf("\nWould you like to bet (1), stand (2), fold (3): ");
        scanf("%d", &turnChoice);
    }

    if (turnChoice == 1)
    {
        bank = setBet(bank, &pot);
    }
    else if (turnChoice == 2)
    {
        system("cls");
        printf("Player decided to stand...\n");
        sleep(1);
    }
    else if (turnChoice == 3)
    {
        printf("Player folded, ending game...");
        sleep(1);
        system("cls");
        return bank;
    }

    turnCount++;
    if (turnCount == 1)
    {
        tableCardsRevealed = 4;
        printf("\nDealer places a new card on the table...\n");
        sleep(1);
    }
    else if (turnCount == 2)
    {
        tableCardsRevealed = 5;
        printf("\nDealer places the final card on the table...\n");
        sleep(1);
    }
    // Do NOT print anything if turnCount == 3 (all 5 cards already out)
    
}

//EVALUATE THE WINNER

//Make four new arrays that combine the table cards with both the dealer card arrays and the player card arrays for easier evaluation
int playerAllCardNum[7], playerAllCardSuit[7];
int dealerAllCardNum[7], dealerAllCardSuit[7];

//Fills the arrays with the player and dealers' cards and suits
for(int i = 0; i < 2; i++)
{
    playerAllCardNum[i] = playerCardNo[i];
    playerAllCardSuit[i] = playerCardSuit[i];

    dealerAllCardNum[i] = dealerCardNo[i];
    dealerAllCardSuit[i] = dealerCardSuit[i];
}

//Fills the rest of the arrays with the table cards
for(int i = 0; i < 5; i++)
{
    playerAllCardNum[i + 2] = tableCardNo[i];
    playerAllCardSuit[i + 2] = tableCardSuit[i];

    dealerAllCardNum[i + 2] = tableCardNo[i];
    dealerAllCardSuit[i + 2] = tableCardSuit[i];
}


int playerHandType = evaluateHands(playerAllCardNum, playerAllCardSuit);
int dealerHandType = evaluateHands(dealerAllCardNum, dealerAllCardSuit);

printAllCards(playerCardNo, playerCardSuit, tableCardNo, tableCardSuit, tableCardsRevealed, dealerCardNo, dealerCardSuit);


//DEBUG PRINT HAND TYPES
// printf("%d \n", playerHandType);
// printf("%d \n", dealerHandType);

printf("\n\n");

bank = printWinner(playerHandType, dealerHandType, playerCardNo, dealerCardNo, bank, &pot);


int playAgain;
printf("\n\n\n\nEnter 1 to play again (There is still a $50 buy-in) or anything else to return to the menu: ");
scanf("%d", &playAgain);

if(playAgain == 1)
{
    system("cls");
    printf("Starting new game...");
    sleep(2);
    bank = playPoker(bank);
} 



system("cls");

return bank;
}

void pokerRules()
{
    //Prints out poker rules
    printf("How to play Texas Hold Em' Poker:\n");
    printf("You and the dealer will be dealt two random cards from a 52 card deck. The dealer will place three cards on the table.\n");
    printf("You may choose to raise your bet, stand, or fold your cards. Each time you bet or stand, the dealer will place\n");
    printf("one more card until there are 5 cards on the table. With the five cards on the table and the two cards in your hand,\n");
    printf("you will see who, between you and the dealer, has a better hand. The dealer will always match your bet, so if you win\n\n");
    printf("you get double your total bet. At the beginning of play, both player and dealer will make a $50 buy-in. \n\n");
    printf("The specific hand types are as follows, from best to least:\n\n");

    //Print all hand types
    printf("Royal Flush: Ace, 10, Jack, King, Queen of the same suit. This is the rarest hand in poker.\n\n");
    printf("Straight Flush: Five cards in a sequence, all in the same suit.\n\n");
    printf("Four of A Kind: All four cards are of the same rank.\n\n");
    printf("Full House: Three of a kind with a pair.\n\n");
    printf("Flush: Any five cards of the same suit, but not in a sequence.\n\n");
    printf("Straight: Five cards in a sequence, but not of the same suit.\n\n");
    printf("Three of A Kind: Three cards of the same rank.\n\n");
    printf("Two Pair:Two different pairs.\n\n");
    printf("Pair: Two cards of the same rank.\n\n");
    printf("High Card: When you haven't made any of the hands above, the highest card plays.\n\n");
}



int pokerMenu(long long bank)
{
    int choice = 0;
    printf("Welcome to Texas Hold Em' Poker! There's a $50 buy-in to play. Enter 1 to play, 2 to view the rules, or 0 to quit: ");
    scanf("%d", &choice);

    switch(choice)
    {
    case 0:
        system("cls");
        return bank;

    case 1:
        system("cls"); //THIS SYSTEM CLEAR FUNCTION ONLY WORKS ON WINDOWS. FOR IT TO WORK ON LINUX/UNIX CHANGE TO "clear" INSTEAD OF "cls"
        bank = playPoker(bank);
        return bank;

    case 2:
        system("cls");
        pokerRules();
        pokerMenu(bank);
        //Hooray for recursive functions!
        break;
    
    default:
        system("cls");
        return bank;
    
    }
}
//POKER==========================================================================================================








//BLACKJACK==========================================================================================================
void blackjackRules()
{

}

//BLACKJACK==========================================================================================================







//ROULETTE==========================================================================================================
void rouletteRules()
{

}

//ROULETTE==========================================================================================================






//SLOTS==========================================================================================================
void slotsRules()
{

}


//SLOTS==========================================================================================================

void gameChoiceSwitch(int bank)
{
    int gameChoice;

    displayMenu(bank);
    scanf("%d", &gameChoice);
    system("cls");


    //Tried making a switch statement to account for these but it was being weird. Had to enter 0 multiple times over to quit
    //This just works better
    if(gameChoice <=  0 || gameChoice >= 5)
    {
        return;
    }

    switch(gameChoice)
    {
    case 1:

        bank = pokerMenu(bank);
        gameChoiceSwitch(bank);

    case 2:


        gameChoiceSwitch(bank);

    case 3:

        gameChoiceSwitch(bank);

    case 4:

        gameChoiceSwitch(bank);

    }

}

int main()
{
    long long bank = 1000; //Starting value for bank is $1000

    gameChoiceSwitch(bank);
}
