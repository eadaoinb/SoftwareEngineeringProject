#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

//Struct to store the information of the player
typedef struct
{
    char name[20];
    char type[20];
    int lifePoints;
    int smartness,strength, magicSkills, luck,dexterity;
    
}

player;

//struct to store the information of the slot
typedef struct
{
    char slotType[20];
    int slotTypeNo;
    int playerNo;
}

slot;

//array to store the player types
char playerTypes[4][20]={"Elf","Human","Ogre","Wizard"};

//array to store the slot types
char slotType[3][20]={"Level Ground","Hill","City"};

//method to set the capabilities of a player
void setCapabilities(player playerArray[],int playerNumber,int playerTypeChoice);

//method to update the capabilities of the player on moving to next slot
void updateCapabiltitesOnMovingSlot(player playerArray[],int playerNumber,int slotTypeMovedTo);

//method to print the details after a successful turn
void printDetails(player playerArray[],int noOfPlayers);

//method to find the closest player to attack
int findClosestPlayer(int attackerPlayerNo,slot slotArray[], int noOfSlots);

//method to implement the attack
void implementingAttack(player playerArray[],int attackerPlayerNo,int attackedPlayerNo);

//method to perform the actions
void performActions(player playerArray[],slot slotArray[],int noOfPlayers,int noOfSlots);


int main()
{
    int noOfPlayers;
    
    printf("Enter the number of players: ");
    scanf("%d",&noOfPlayers);
    
    while(!(noOfPlayers>=2 && noOfPlayers<=6))
    {
        printf("Minimum number of players is 2 and Maximum number of players is 6\nPlease re-enter your choice: ");
        scanf("%d",&noOfPlayers);
    }
    
    //make a player array to store the player information
    player playerArray[noOfPlayers];
    
    //loop to store the player information
    for(int a=0;a<noOfPlayers;a++)
    {
        //input the player name
        printf("Please enter the name of Player %d: ",(a+1));
        scanf("%s",playerArray[a].name);
        
        //input the player type
        printf("Please enter the type of Player %d\n",(a+1));
        printf("Enter 1 for Elf\nEnter 2 for Human\nEnter 3 for Orge\nEnter 4 for Wizard: ");
        int playerTypeChoice=0;
        scanf("%d",&playerTypeChoice);
        
        //loop to check if input is correct
        //if not again asks for input
        while(!(playerTypeChoice>=1 && playerTypeChoice<=4))
        {
            printf("Wrong Choice Entered\nRe-enter your choice: ");
            scanf("%d",&playerTypeChoice);
            
        }
        
        //this works
        
        strcpy(playerArray[a].type,playerTypes[playerTypeChoice-1]);
        
        //calling the method to set the capability of the player
        setCapabilities(playerArray, a,playerTypeChoice);
    }
    
    
    //input the number of slots
    printf("Please Enter the number of slots (Maximum is 20):");
    int noOfSlots;
    scanf("%d",&noOfSlots);
    
    //checks if number of slots is within range
    //if not takes another input
    while(!(noOfSlots>noOfPlayers && noOfSlots<=20))
    {
        printf("Number of slots selected is out of bound\nRe-enter the number of slots: ");
        scanf("%d",&noOfSlots);
    }
    
    //creates slot array to store information about the slots
    slot slotsArray[noOfSlots];
    
    //initialising the slot
    //initialising the slotTypeNo and PlayerNo to -1
    for(int a=0;a<noOfSlots;a++)
    {
        slotsArray[a].slotTypeNo=-1;
        slotsArray[a].playerNo=-1;
    }
    srand((unsigned int)time(NULL));
    
    
    //stores the slotType
    for(int a=0;a<noOfSlots;a++)
    {
        slotsArray[a].slotTypeNo=rand()%3;
        strcpy(slotsArray[a].slotType,slotType[slotsArray[a].slotTypeNo]);
    }
    
    
    //stores the playerNumber
    for(int a=0;a<noOfPlayers;a++)
    {
        //generates a random number
        int randomNumber=rand()%noOfSlots;
        
        //if the slot is not occupied by any player
        //then the player is allocated to the slot
        if(slotsArray[randomNumber].playerNo==-1)
        {
            slotsArray[randomNumber].playerNo=a;
        }
        else
        {
            //generating a random number
            randomNumber=rand()%noOfSlots;
            
            //loop runs until it finds a slot position which was empty and had no player in it
            while(!(slotsArray[randomNumber].playerNo==-1))
            {
                //generating random number
                randomNumber=rand()%noOfSlots;
                
            }
            
            //stores the player in the slot
            slotsArray[randomNumber].playerNo=a;
        }
        
    }
    
    //call the method to start the game
    performActions(playerArray, slotsArray, noOfPlayers, noOfSlots);
    
}

//method to perform the actions
void performActions(player playerArray[],slot slotArray[],int noOfPlayers,int noOfSlots)
{
    //loop which runs throught the number of players
    //each player gets one chance
    for(int a=0;a<noOfPlayers;a++)
    {
        //boolean to store if the players turn was successful
        //if not successful then player does his turn again
        bool turnSuccessful=false;
        
        //Player gets his turn
        printf("%s : Please do your turn\n",playerArray[a].name);
        
        //player inputs his move
        printf("Enter 1 to attack the closest player\nEnter 2 to move to the previous slot\nEnter 3 to move to the next slot\n");
