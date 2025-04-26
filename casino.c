#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>
#include<string.h>


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

int playPoker(int bank)
{
    int diamonds[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int hearts[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int spades[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int clubs[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    bool diamondCheck[13];
    bool heartCheck[13];
    bool spadeCheck[13];
    bool clubCheck[13];

    
}

void pokerRules(int bank)
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



int pokerMenu(int bank)
{
    int choice = 0;
    printf("Welcome to Texas Hold Em' Poker! Enter 1 to play, 2 to view the rules, or 0 to quit: ");
    scanf("%d", &choice);

    switch(choice)
    {
    case 0:
        return bank;

    case 1:
        
        return bank;

    case 2:
        system("cls");
        pokerRules(bank);
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

int main()
{
    int gameChoice; //Will be used in the switch statement
    long long bank = 1000; //Starting value for bank is $1000


    displayMenu(bank);
    scanf("%d", &gameChoice);
    system("cls");

    switch(gameChoice)
    {
    case 1:

        bank = pokerMenu(bank);
        main();

    case 2:


        main();

    case 3:

        main();

    case 4:

        main();

    case 0:
        return 0;

    default:
        return 0;

    }

    
}
