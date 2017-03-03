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
