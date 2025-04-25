#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<windows.h>


/*NOTICE: I used chatGPT for help and understanding of how this function works
This is the only thing in this project made with the help of chatGPT, but
since the concept of changing text colors is new to me, I asked the bot 
for a little help.*/
void setTextColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}




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




}


//POKER==========================================================================================================
void pokerRules()
{

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

    switch(gameChoice)
    {
    case 1:

        main();
    
    case 2:

        main();

    case 3:

        main();

    case 4:

        main();

    case 0:
        break;
    }
}

