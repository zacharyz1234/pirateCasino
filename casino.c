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

int setBet(int bank)
{
    int bet;
    printf("You currently have $%d in your bank. How much money would you like to bet: ");
    scanf("%d", &bet);
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
        printf("You need at least $50 to buy-in for poker! Come back when you've got more cash.");
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
        tableCardNo[i] = getCard(dealerCardNo, diamondCheck, heartCheck, spadeCheck, clubCheck, dealerCardSuit, i);
    }


    //FOR TESTING PURPOSES TO SEE CARD TYPES FOR BOTH PLAYER AND DEALER
    for(int i = 0; i < 2; i++)
    {
        printf("PLAYER CARD NO: %d SUIT: %d DEALER CARD NO: %d SUIT: %d\n", playerCardNo[i], playerCardSuit[i], dealerCardNo[i], dealerCardSuit[i]);
    }

    //NEED TO MAKE A PRINT CARDS FUNCTION HERE


    int turnChoice; //I was going to use a char for this but chars didn't want to work with my scanf function
    
    while(turnChoice < 1 || turnChoice > 3)
    {
        printf("Would you like to bet (1), stand (2), or fold (3): ");
        scanf(" %d", &turnChoice);
    }

    if(turnChoice == 1)
    {
        int bet;
        bet = setBet(bank);

    }
    else if(turnChoice == 2)
    {
        
    }
    else if(turnChoice == 3)
    {
        printf("Player folded, ending game...");
        sleep(1); //I like it to pause for a second so the player can read that the game is ending and stuff
        system("cls");
        return bank;
    }




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
        return bank;

    case 1:
        system("cls"); //THIS SYSTEM CLEAR FUNCTION ONLY WORKS ON WINDOWS. FOR IT TO WORK ON LINUX/UNIX ENTER "clear" INSTEAD OF "cls"
        bank = playPoker(bank);
        return bank;

    case 2:
        system("cls");
        pokerRules();
        pokerMenu(bank);
        //Hooray for recursive functions!
        break;
    
    default:
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

    switch(gameChoice)
    {
    case 0:
        return;


    case 1:

        bank = pokerMenu(bank);
        gameChoiceSwitch(bank);

    case 2:


        gameChoiceSwitch(bank);

    case 3:

        gameChoiceSwitch(bank);

    case 4:

        gameChoiceSwitch(bank);


    default:
        return;

    }

}

int main()
{
    int gameChoice; //Will be used in the switch statement
    long long bank = 1000; //Starting value for bank is $1000


    gameChoiceSwitch(bank);

    // switch(gameChoice)
    // {
    // case 0:
    //     return 0;


    // case 1:

    //     bank = pokerMenu(bank);
    //     main();

    // case 2:


    //     main();

    // case 3:

    //     main();

    // case 4:

    //     main();


    // default:
    //     return 0;

    // }

    
}
