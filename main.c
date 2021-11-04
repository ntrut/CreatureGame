#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


struct room
{
    int roomNum;
    int roomStatus;
    int roomTotal;
    int north;
    int south;
    int east;
    int west;
};

struct Creatures
{
    int creatureType;
    int creatureNum;
    int location;

};


int Respect = 40;

void createRooms(int numberofrooms,struct room *AllRooms);
void createCreatures(int numberofcreatures, struct Creatures* AllCreatures,struct room* AllRooms);
void movePC(int numberofcreatures, struct Creatures* AllCreatures,int numberofrooms,struct room* AllRooms,char decsion[]);
void moveCreatures(int numberofcreatures, struct Creatures* AllCreatures,int numberofrooms,struct room* AllRooms);
void look(int numberofcreatures, struct Creatures* AllCreatures,int numberofrooms,struct room* AllRooms,char decision[]);
void clean(int numberofcreatures, struct Creatures* AllCreatures,struct room* AllRooms,char decision[]);
void dirty(int numberofcreatures, struct Creatures* AllCreatures,struct room* AllRooms,char decision[]);
void PCMovesCreature(int creatureNum,char decision[], int numberofcreatures, struct Creatures* AllCreatures,struct room* AllRooms);
void creatureDirtyORClean(int creatureNum, char decision[], int numberofcreatures, struct Creatures* AllCreatures,struct room* AllRooms);
int fullRoom(int numberofcreatures, int creatureNum, struct Creatures* AllCreatures,struct room* AllRooms);
void helps();

int main()
{
    int numberofrooms = 0;
    int numberofcreatures = 0;
    int MaxRooms = 10;
    int maxChar = 10;
    srand(time(NULL));


    /*create rooms*/

    /*ask user for rooms and creatures*/
    printf("How many rooms? Max 100 rooms: ");
    scanf("%d",&numberofrooms);
    /*make sure its under 10 rooms*/
    while(numberofrooms > 100)
    {
        printf("\nToo many rooms!\n");
        printf("How many rooms? Max 10 rooms: ");
        scanf("%d",&numberofrooms);
    }

    printf("How many creatures? Max 100 creatures: ");
    scanf("%d",&numberofcreatures);

    while(numberofcreatures > 100)
    {
        printf("\nToo many creatures! MAX 100 creatures please!\n");
        printf("How many creatures? Max 100 creatures: ");
        scanf("%d",&numberofcreatures);
    }

    struct Creatures *AllCreatures = malloc(numberofcreatures * sizeof *AllCreatures);
    struct room *AllRooms = malloc(numberofrooms * sizeof *AllRooms);

    createRooms(numberofrooms, AllRooms);
    createCreatures(numberofcreatures,AllCreatures,AllRooms);

    int ends = 1;
    int creature;
    char decision[20];
    char looks[20] = "look";
    char dirtyChar[20] = "dirty";
    char cleanChar[20] = "clean";
    char moveCreature[20] = "movecreature";
    char makeCreature[20] = "creatureaction";
    char exit[20] = "exit";
    char help[20] = "help";

    /*while loop that holds the menu*/
    while(ends == 1)
    {

        printf("\nEnter north south east west,look,clean,dirty,movecreature,creatureaction,help,exit: ");
        scanf("%s",decision);

        if(strcmp(exit,decision) == 0)
        {
            ends = 0;
        }
        else if(strcmp(looks,decision) == 0)
        {
            look(numberofcreatures,AllCreatures,numberofrooms,AllRooms,decision);
        }
        else if(strcmp(cleanChar,decision) == 0)
        {
            clean(numberofcreatures,AllCreatures,AllRooms,decision);
            moveCreatures(numberofcreatures,AllCreatures,numberofrooms,AllRooms);

        }
        else if(strcmp(dirtyChar,decision) == 0)
        {
            dirty(numberofcreatures,AllCreatures,AllRooms,decision);
            moveCreatures(numberofcreatures,AllCreatures,numberofrooms,AllRooms);

        }
        else if(strcmp(moveCreature,decision) == 0)
        {
            printf("\nEnter Creature Number: ");
            scanf("%d",&creature);
            printf("\nEnter north south east west: ");
            scanf("%s",decision);
            PCMovesCreature(creature,decision,numberofcreatures,AllCreatures,AllRooms);

        }
        else if(strcmp(makeCreature,decision) == 0)
        {
            printf("\nEnter Creature Number: ");
            scanf("%d",&creature);
            printf("\nEnter clean or dirty ");
            scanf("%s",decision);
            creatureDirtyORClean(creature,decision,numberofcreatures,AllCreatures,AllRooms);
            moveCreatures(numberofcreatures,AllCreatures,numberofrooms,AllRooms);
        }
        else if(strcmp(help,decision) == 0)
        {
            helps();
        }
        else
        {
            movePC(numberofcreatures,AllCreatures,numberofrooms,AllRooms,decision);
            moveCreatures(numberofcreatures,AllCreatures,numberofrooms,AllRooms);


        }

        if(Respect <= 0 || Respect >= 80)
        {
            ends = 0;
        }
    }

    /*end game*/
    if(Respect >= 80)
    {
        printf("\nGood job you won the game!!!!!\n");
    }
    else if(Respect <= 0)
    {
        printf("\nShame you lost!\n");

    }
    else
        printf("\nYou have exited the game\n");


    free(AllCreatures);
    free(AllRooms);
    return 0;
}

/*help command*/
void helps()
{
    printf("\n***********************************************************");
    printf("\nAll commands");
    printf("\nnorth: moves your PC north");
    printf("\nsouth: moves your PC south");
    printf("\neast: moves your PC east");
    printf("\nwest: moves your PC west");
    printf("\nlook: shows the information in the current room where the PC is in");
    printf("\nclean: cleans the room in the current room where the PC is in");
    printf("\ndirty: dirtys the room in the current room where the PC is in");
    printf("\nmovecreature: moves a creature in a direction the PC wants, it will ask for creature number and where do you want to move it");
    printf("\nactioncreature: makes a creature perform clean or dirty, it will ask for creature number and whether PC wants the creature to clean or dirty");
    printf("\nexit: exit the game");
    printf("\n***********************************************************");

}

/*check if the creatures rooms are all full, if all other rooms are full then it leaves the house*/
int fullRoom(int numberofcreatures, int creatureNum, struct Creatures* AllCreatures,struct room* AllRooms)
{
    int Roomsisfull = 0;
    int findPC;
    int rooms = 0;
    int isfull = 0;

    /*find where the PC is in the array*/
    for(int i=0; i < numberofcreatures; i++)
    {
        if(AllCreatures[i].creatureType == 0)
        {
            findPC = i;
        }
    }

    //check what rooms the creature cant go to
    if(AllRooms[AllCreatures[creatureNum].location].north != -1)
    {
        rooms++;
    }
    if(AllRooms[AllCreatures[creatureNum].location].south != -1)
    {
        rooms++;
    }
    if(AllRooms[AllCreatures[creatureNum].location].east != -1)
    {
        rooms++;
    }
    if(AllRooms[AllCreatures[creatureNum].location].west != -1)
    {
        rooms++;
    }


    if(AllRooms[AllRooms[AllCreatures[creatureNum].location].north].roomTotal == 10)
    {
        isfull++;
    }
    if(AllRooms[AllRooms[AllCreatures[creatureNum].location].south].roomTotal == 10)
    {
        isfull++;
    }
    if(AllRooms[AllRooms[AllCreatures[creatureNum].location].east].roomTotal == 10)
    {
        isfull++;
    }
    if(AllRooms[AllRooms[AllCreatures[creatureNum].location].west].roomTotal == 10)
    {
        isfull++;
    }

    /*if all rooms around the creature are full*/
    /*then do all the things in the if statement*/
    if(rooms == isfull)
    {
        Roomsisfull = 1;
        printf("\nCreature %d drills a hole and crawls out of the house\n", AllCreatures[creatureNum].creatureNum);
        AllRooms[AllCreatures[creatureNum].location].roomTotal = AllRooms[AllCreatures[creatureNum].location].roomTotal - 1;
        AllCreatures[creatureNum].creatureType = -1;
        AllCreatures[creatureNum].location = -1;


        for(int j = 0; j < numberofcreatures; j++)
        {
            if(AllCreatures[j].location == AllCreatures[findPC].location)
            {
                if(AllCreatures[j].creatureType == 1)
                {
                    printf("\nAnimal %d growls at you because PC has been inconsiderate\n",AllCreatures[j].creatureNum);
                    Respect = Respect - 1;

                }
                else if(AllCreatures[j].creatureType == 2)
                {
                    printf("\nNPC %d grumbles at you because PC has been inconsiderate\n",AllCreatures[j].creatureNum);
                    Respect = Respect - 1;
                }
            }
        }
    }

    return Roomsisfull;
}

/*PC moves the creature*/
void PCMovesCreature(int creatureNum,char decision[], int numberofcreatures, struct Creatures* AllCreatures,struct room* AllRooms)
{
    char north[10] = "north";
    char south[10] = "south";
    char east[10] = "east";
    char west[10] = "west";
    int foundCreature;
    int findPC;

    /*find creature with respected number*/
    for(int i = 0; i<numberofcreatures; i++)
    {
        if(AllCreatures[i].creatureNum == creatureNum)
        {
            foundCreature = i;
        }
        if(AllCreatures[i].creatureType == 0)
        {
            findPC = i;
        }
    }

    if(fullRoom(numberofcreatures,creatureNum,AllCreatures,AllRooms) == 0)
    {

        if(AllCreatures[foundCreature].location == AllCreatures[findPC].location || AllCreatures[foundCreature].location != -1)
        {
            /*if PC wants to move creature north*/
            if(strcmp(north,decision) == 0)
            {
                int success = 0;

                if(AllRooms[AllCreatures[foundCreature].location].north != -1)/*check if room is full*/
                {
                    if(AllRooms[AllRooms[AllCreatures[foundCreature].location].north].roomTotal != 10)
                    {
                        AllRooms[AllCreatures[foundCreature].location].roomTotal = AllRooms[AllCreatures[foundCreature].location].roomTotal - 1;/*left room so -1*/
                        AllCreatures[foundCreature].location = AllRooms[AllCreatures[foundCreature].location].north;/*move the creature north*/
                        AllRooms[AllCreatures[foundCreature].location].roomTotal = AllRooms[AllCreatures[foundCreature].location].roomTotal + 1;/*went to a different room so +1*/
                        success = 1;
                    }
                    else
                    {
                        printf("\nRoom is full\n");
                    }


                    /*print out that you moved animal or NPC*/
                    if(AllCreatures[foundCreature].creatureType == 1 && success == 1)/*if aniual is unhappy with new room, perform clean*/
                    {
                        printf("\nAnimal %d moved north\n",AllCreatures[foundCreature].creatureNum);

                            if(AllRooms[AllCreatures[foundCreature].location].roomStatus == 2)
                            {
                                AllRooms[AllCreatures[foundCreature].location].roomStatus = AllRooms[AllCreatures[foundCreature].location].roomStatus - 1;
                            }

                    }
                    else if(AllCreatures[foundCreature].creatureType == 2 && success == 1)/*if NPC and if its unhappy with new room, perform dirty*/
                    {
                         printf("\nNPC %d moved north\n",AllCreatures[foundCreature].creatureNum);

                         if(AllRooms[AllCreatures[foundCreature].location].roomStatus == 0)
                            {
                                AllRooms[AllCreatures[foundCreature].location].roomStatus = AllRooms[AllCreatures[foundCreature].location].roomStatus + 1;
                            }
                    }
                }
                else if(success == 1)/*if room is full,grumble or growl at PC*/
                {
                    if(AllCreatures[foundCreature].creatureType == 1)/*animal growl*/
                    {
                        printf("\n%d growls\n",AllCreatures[foundCreature].creatureNum);
                        Respect = Respect -1;
                    }
                    else if(AllCreatures[foundCreature].creatureType == 2)/*NPC grumble*/
                    {
                        printf("\n%d grumbles\n",AllCreatures[foundCreature].creatureNum);
                        Respect = Respect - 1;
                    }
                }
                else
                    printf("\nTheres a wall there cant move creature there\n");

            }

            /*if PC wants to move creature south*/
            else if(strcmp(south,decision) == 0)
            {
                int success = 0;
                if(AllRooms[AllCreatures[foundCreature].location].south != -1)/*check if room is full*/
                {
                    if(AllRooms[AllRooms[AllCreatures[foundCreature].location].north].roomTotal != 10)
                    {
                        AllRooms[AllCreatures[foundCreature].location].roomTotal = AllRooms[AllCreatures[foundCreature].location].roomTotal - 1;/*left room - 1*/
                        AllCreatures[foundCreature].location = AllRooms[AllCreatures[foundCreature].location].south;/*move the creature south*/
                        AllRooms[AllCreatures[foundCreature].location].roomTotal = AllRooms[AllCreatures[foundCreature].location].roomTotal + 1;/*went to a different room so +1*/
                        success = 1;
                    }
                    else
                    {
                        printf("\nRoom is full\n");
                    }


                    /*print out that you moved animal or NPC*/
                    if(AllCreatures[foundCreature].creatureType == 1 && success == 1)/*if aniual is unhappy with new room, perform clean*/
                    {
                        printf("\nAnimal %d moved south",AllCreatures[foundCreature].creatureNum);

                            if(AllRooms[AllCreatures[foundCreature].location].roomStatus == 2)
                            {
                                AllRooms[AllCreatures[foundCreature].location].roomStatus = AllRooms[AllCreatures[foundCreature].location].roomStatus - 1;
                            }

                    }
                    else if(AllCreatures[foundCreature].creatureType == 2 && success == 1)//if NPC and if its unhappy with new room, perform dirty
                    {
                         printf("\nNPC %d moved south",AllCreatures[foundCreature].creatureNum);

                         if(AllRooms[AllCreatures[foundCreature].location].roomStatus == 0)
                            {
                                AllRooms[AllCreatures[foundCreature].location].roomStatus = AllRooms[AllCreatures[foundCreature].location].roomStatus + 1;
                            }
                    }
                }
                else if(success == 1)//if room is full,grumble or growl at PC
                {
                    if(AllCreatures[foundCreature].creatureType == 1)//animal growl
                    {
                        printf("\n%d growls\n",AllCreatures[foundCreature].creatureNum);
                        Respect = Respect -1;
                    }
                    else if(AllCreatures[foundCreature].creatureType == 2)//NPC grumble
                    {
                        printf("\n%d grumbles\n",AllCreatures[foundCreature].creatureNum);
                        Respect = Respect - 1;
                    }
                }
                else
                    printf("\nTheres a wall there cant move creature there\n");
            }

            //if PC wants to move creature east
            if(strcmp(east,decision) == 0)
            {
                int success = 0;
                if( AllRooms[AllCreatures[foundCreature].location].east != -1)//check if room is full
                {
                    if(AllRooms[AllRooms[AllCreatures[foundCreature].location].east].roomTotal != 10)
                    {
                        AllRooms[AllCreatures[foundCreature].location].roomTotal = AllRooms[AllCreatures[foundCreature].location].roomTotal - 1;//left room so - 1
                        AllCreatures[foundCreature].location = AllRooms[AllCreatures[foundCreature].location].east;//move the creature east
                        AllRooms[AllCreatures[foundCreature].location].roomTotal = AllRooms[AllCreatures[foundCreature].location].roomTotal + 1;//went to a different room so +1
                        success = 1;
                    }
                    else
                    {
                        printf("\nRoom is full\n");
                    }

                    //print out that you moved animal or NPC
                    if(AllCreatures[foundCreature].creatureType == 1 && success == 1)//if aniual is unhappy with new room, perform clean
                    {
                        printf("\nAnimal %d moved east\n",AllCreatures[foundCreature].creatureNum);

                            if(AllRooms[AllCreatures[foundCreature].location].roomStatus == 2)
                            {
                                AllRooms[AllCreatures[foundCreature].location].roomStatus = AllRooms[AllCreatures[foundCreature].location].roomStatus - 1;
                            }

                    }
                    else if(AllCreatures[foundCreature].creatureType == 2 && success == 1)//if NPC and if its unhappy with new room, perform dirty
                    {
                         printf("\nNPC %d moved east\n",AllCreatures[foundCreature].creatureNum);

                         if(AllRooms[AllCreatures[foundCreature].location].roomStatus == 0)
                            {
                                AllRooms[AllCreatures[foundCreature].location].roomStatus = AllRooms[AllCreatures[foundCreature].location].roomStatus + 1;
                            }
                    }
                }
                else if(success == 1)//if room is full,grumble or growl at PC
                {
                    if(AllCreatures[foundCreature].creatureType == 1)//animal growl
                    {
                        printf("\n%d growls\n",AllCreatures[foundCreature].creatureNum);
                        Respect = Respect -1;
                    }
                    else if(AllCreatures[foundCreature].creatureType == 2)//NPC grumble
                    {
                        printf("\n%d grumbles\n",AllCreatures[foundCreature].creatureNum);
                        Respect = Respect - 1;
                    }
                }
                else
                    printf("\nTheres a wall there cant move creature there\n");


            }

            //If PC wants creature to move west
             if(strcmp(west,decision) == 0)
            {
                int success = 0;
                if(AllRooms[AllCreatures[foundCreature].location].west != -1)//check if room is full
                {
                    if(AllRooms[AllRooms[AllCreatures[foundCreature].location].west].roomTotal != 10)
                    {
                        AllRooms[AllCreatures[foundCreature].location].roomTotal = AllRooms[AllCreatures[foundCreature].location].roomTotal - 1;//left room so - 1
                        AllCreatures[foundCreature].location = AllRooms[AllCreatures[foundCreature].location].west;//move the creature west
                        AllRooms[AllCreatures[foundCreature].location].roomTotal = AllRooms[AllCreatures[foundCreature].location].roomTotal + 1;//went to a different room so +1
                        success = 1;
                    }
                    else
                    {
                        printf("\nRoom is full\n");
                    }

                    //print out that you moved animal or NPC
                    if(AllCreatures[foundCreature].creatureType == 1 && success == 1)//if aniual is unhappy with new room, perform clean
                    {
                        printf("\nAnimal %d moved west",AllCreatures[foundCreature].creatureNum);

                            if(AllRooms[AllCreatures[foundCreature].location].roomStatus == 2)
                            {
                                AllRooms[AllCreatures[foundCreature].location].roomStatus = AllRooms[AllCreatures[foundCreature].location].roomStatus - 1;

                            }

                    }
                    else if(AllCreatures[foundCreature].creatureType == 2 && success == 1)//if NPC and if its unhappy with new room, perform dirty
                    {
                         printf("\nNPC %d moved west",AllCreatures[foundCreature].creatureNum);

                         if(AllRooms[AllCreatures[foundCreature].location].roomStatus == 0)
                            {
                                AllRooms[AllCreatures[foundCreature].location].roomStatus = AllRooms[AllCreatures[foundCreature].location].roomStatus + 1;

                            }
                    }

                }
                else if(success == 1)//if room is full,grumble or growl at PC
                {
                    if(AllCreatures[foundCreature].creatureType == 1)//animal growl
                    {
                        printf("\n%d growls\n",AllCreatures[foundCreature].creatureNum);
                        Respect = Respect -1;
                    }
                    else if(AllCreatures[foundCreature].creatureType == 2)//NPC grumble
                    {
                        printf("\n%d grumbles\n",AllCreatures[foundCreature].creatureNum);
                        Respect = Respect - 1;
                    }
                }
                else
                    printf("\nTheres a wall there cant move creature there\n");

            }
        }
        else
        {
            printf("\nCreature %d is not in the room with you",creatureNum);
        }
    }


}

//make a room clean
void clean(int numberofcreatures, struct Creatures* AllCreatures,struct room* AllRooms,char decision[])
{
    int findPC = 0;
    int alreadyClean = 0;
    //find pc
    for(int i=0; i < numberofcreatures; i++)
    {
        if(AllCreatures[i].creatureType == 0)
        {
            findPC = i;
        }
    }


    //minus the room status to clean
    if(AllRooms[AllCreatures[findPC].location].roomStatus == 1 || AllRooms[AllCreatures[findPC].location].roomStatus == 2)
    {
        AllRooms[AllCreatures[findPC].location].roomStatus =  AllRooms[AllCreatures[findPC].location].roomStatus - 1;
    }
    else
    {
        printf("\nRoom already clean\n");
        alreadyClean = 1;
    }

    //if used clean action then animal will lickface or npc will grumble at you
    if(alreadyClean == 0)
    {
        for(int j = 0; j < numberofcreatures; j++)
        {
            if(AllCreatures[j].location == AllCreatures[findPC].location && AllCreatures[j].creatureType != 0 && AllCreatures[j].creatureType == 1)
            {
                printf("\nAnimal %d licks your face!\n",AllCreatures[j].creatureNum);
                Respect = Respect + 1;
            }
            else if(AllCreatures[j].location == AllCreatures[findPC].location && AllCreatures[j].creatureType != 0 && AllCreatures[j].creatureType == 2)
            {
                printf("\nNPC %d grumbles at you!\n",AllCreatures[j].creatureNum);
                Respect = Respect - 1;
            }

        }
    }


}

//make a room dirty
void dirty(int numberofcreatures, struct Creatures* AllCreatures,struct room* AllRooms,char decision[])
{
    int findPC = 0;
    int alreadyDirty = 0;
    //find pc
    for(int i=0; i < numberofcreatures; i++)
    {
        if(AllCreatures[i].creatureType == 0)
        {
            findPC = i;
        }
    }

    if(AllRooms[AllCreatures[findPC].location].roomStatus == 0 || AllRooms[AllCreatures[findPC].location].roomStatus == 1)
    {
        AllRooms[AllCreatures[findPC].location].roomStatus =  AllRooms[AllCreatures[findPC].location].roomStatus + 1;
    }
    else
    {
        printf("\nRoom already dirty\n");
        int alreadyDirty = 1;
    }

    //if used clean action then animal will lickface or npc will grumble at you
    if(alreadyDirty == 0)
    {
        for(int j = 0; j < numberofcreatures; j++)
        {
            if(AllCreatures[j].location == AllCreatures[findPC].location && AllCreatures[j].creatureType != 0 && AllCreatures[j].creatureType == 1)
            {
                printf("\nAnimal %d growls at your face!\n",AllCreatures[j].creatureNum);
                Respect = Respect - 1;
            }
            else if(AllCreatures[j].location == AllCreatures[findPC].location && AllCreatures[j].creatureType != 0 && AllCreatures[j].creatureType == 2)
            {
                printf("\nNPC %d smiles at you!\n",AllCreatures[j].creatureNum);
                Respect = Respect + 1;
            }

        }
    }

}

//PC makes a creature use the dirty function
void creatureDirtyORClean(int creatureNum, char decision[], int numberofcreatures, struct Creatures* AllCreatures,struct room* AllRooms)
{
    char dirty[10] = "dirty";
    char clean[10] = "clean";
    int noCreature = 0;

    //find player PC
    int findPC;
     for(int i=0; i < numberofcreatures; i++)
     {
        if(AllCreatures[i].creatureType == 0)
        {
            findPC = i;
        }
     }

    //accordding to the user decsion, the choice is made.
    //if dirty and creatureNum is 2 then NPC(which is 2) performs dirty and then smiles at you
    //etc...
    if(AllCreatures[findPC].location == AllCreatures[creatureNum].location)
    {
        if(strcmp(dirty,decision) == 0 && AllCreatures[creatureNum].creatureType == 2)
        {
            if(AllRooms[AllCreatures[creatureNum].location].roomStatus == 0 || AllRooms[AllCreatures[creatureNum].location].roomStatus == 1)
            {
                printf("\nNPC %d performs dirty",AllCreatures[creatureNum].creatureNum);
                printf("\nNPC %d smiles at you alot\n",AllCreatures[creatureNum].creatureNum);
                AllRooms[AllCreatures[creatureNum].location].roomStatus = AllRooms[AllCreatures[creatureNum].location].roomStatus + 1;
                Respect = Respect + 3;
            }
            else
            {
                printf("\nRoom is already dirty");
            }
        }
        else if(strcmp(clean,decision) == 0 && AllCreatures[creatureNum].creatureType == 2)
        {
            if(AllRooms[AllCreatures[creatureNum].location].roomStatus == 2 || AllRooms[AllCreatures[creatureNum].location].roomStatus == 1)
            {
                printf("\nNPC %d performs clean",AllCreatures[creatureNum].creatureNum);
                printf("\nNPC %d grumbles at you alot\n",AllCreatures[creatureNum].creatureNum);
                AllRooms[AllCreatures[creatureNum].location].roomStatus = AllRooms[AllCreatures[creatureNum].location].roomStatus - 1;
                Respect = Respect - 3;
            }
            else
            {
                printf("\nRoom is already clean");
            }
        }
        else if(strcmp(dirty,decision) == 0 && AllCreatures[creatureNum].creatureType == 1)
        {
            if(AllRooms[AllCreatures[creatureNum].location].roomStatus == 0 || AllRooms[AllCreatures[creatureNum].location].roomStatus == 1)
            {
                printf("\nAnimal %d performs dirty",AllCreatures[creatureNum].creatureNum);
                printf("\nAanimal %d growls at you alot\n",AllCreatures[creatureNum].creatureNum);
                Respect = Respect - 3;
                AllRooms[AllCreatures[creatureNum].location].roomStatus = AllRooms[AllCreatures[creatureNum].location].roomStatus + 1;
            }
            else
            {
                printf("\nRoom is already dirty");
            }
        }
        else if(strcmp(clean,decision) == 0 && AllCreatures[creatureNum].creatureType == 1)
        {
            if(AllRooms[AllCreatures[creatureNum].location].roomStatus == 2 || AllRooms[AllCreatures[creatureNum].location].roomStatus == 1)
            {
                printf("\nAnimal %d performs clean",AllCreatures[creatureNum].creatureNum);
                printf("\nAnimal %d licks your face alot\n",AllCreatures[creatureNum].creatureNum);
                Respect = Respect + 3;
                AllRooms[AllCreatures[creatureNum].location].roomStatus = AllRooms[AllCreatures[creatureNum].location].roomStatus - 1;
            }
            else
        {
            printf("\nRoom is already clean");
        }
        }


    }
    else
    {
        printf("\nCreature is %d not in your room\n",AllCreatures[creatureNum].creatureNum);
        noCreature = 1;
    }

    //All other creatures react to the change but only add 1 or -1 to respect
    if(noCreature == 0)
    {
        for(int j = 0; j < numberofcreatures; j++)
        {
            //if clean was performed by a creature because of the PC, the make the changes for the clean action
            if(strcmp(clean,decision) == 0)
            {
                if(AllCreatures[j].location == AllCreatures[findPC].location && AllCreatures[j].creatureType != 0 && AllCreatures[j].creatureNum != creatureNum && AllCreatures[j].creatureType == 1)
                {
                    printf("\nAnimal %d licks your face!\n",AllCreatures[j].creatureNum);
                    Respect = Respect + 1;
                }
                else if(AllCreatures[j].location == AllCreatures[findPC].location && AllCreatures[j].creatureType != 0 && AllCreatures[j].creatureNum != creatureNum && AllCreatures[j].creatureType == 2)
                {
                    printf("\nNPC %d grumbles at you!\n",AllCreatures[j].creatureNum);
                    Respect = Respect - 1;
                }
            }
            //if dirty was perfmored becuase PC told a creature to do it, the make the changes for the dirty action
            else if(strcmp(dirty,decision) == 0)
            {
                if(AllCreatures[j].location == AllCreatures[findPC].location && AllCreatures[j].creatureNum != creatureNum && AllCreatures[j].creatureType != 0 && AllCreatures[j].creatureType == 1)
                {
                    printf("\nAnimal %d growls at your face!\n",AllCreatures[j].creatureNum);
                    Respect = Respect - 1;
                }
                else if(AllCreatures[j].location == AllCreatures[findPC].location && AllCreatures[j].creatureNum != creatureNum && AllCreatures[j].creatureType != 0 && AllCreatures[j].creatureType == 2)
                {
                    printf("\nNPC %d smiles at you!\n",AllCreatures[j].creatureNum);
                    Respect = Respect + 1;
                }
            }
        }
    }
}

/*Look function for the look command*/
void look(int numberofcreatures, struct Creatures* AllCreatures,int numberofrooms,struct room* AllRooms,char decision[])
{

    int findPC = 0;
    char status[10];
    char dirty[10] = "dirty";
    char clean[10] = "clean";
    char halfdirty[15] = "half-dirty";

    //find where the PC is in the array
    for(int i=0; i < numberofcreatures; i++)
    {
        if(AllCreatures[i].creatureType == 0)
        {
            findPC = i;
        }

    }

    //get the dirty clean or halfdirty string from the location of the PC
    //if PC is a clean room, then status will equal clean
    if(AllRooms[AllCreatures[findPC].location].roomStatus == 0)
    {
        strcpy(status,clean);
    }
    else if(AllRooms[AllCreatures[findPC].location].roomStatus == 1)
    {
        strcpy(status,halfdirty);
    }
    else if(AllRooms[AllCreatures[findPC].location].roomStatus == 2)
    {
        strcpy(status,dirty);
    }
    else
    {
        printf("\nNo room status\n");
    }

    printf("\nRespect is %d, ",Respect);
    printf("Room Total is %d, ", AllRooms[AllCreatures[findPC].location].roomTotal);

    printf("Room %d, %s, ",AllRooms[AllCreatures[findPC].location].roomNum, status);

    printf(" neighbors ");

    //find the neighbors of the PC location
    if(AllRooms[AllCreatures[findPC].location].north != -1)
    {
        printf("%d to the north, ",AllRooms[AllCreatures[findPC].location].north);
    }
    if(AllRooms[AllCreatures[findPC].location].south != -1)
    {
        printf("%d to the south, ",AllRooms[AllCreatures[findPC].location].south);
    }
    if(AllRooms[AllCreatures[findPC].location].east != -1)
    {
        printf("%d to the east, ",AllRooms[AllCreatures[findPC].location].east);
    }
    if(AllRooms[AllCreatures[findPC].location].west != -1)
    {
        printf("%d to the west, ",AllRooms[AllCreatures[findPC].location].west);
    }

    printf(", contains: ");

    //print out the creatures in PC location
    for(int i =0;i < numberofcreatures;i++)
    {
        if(AllCreatures[i].location == AllCreatures[findPC].location)
        {
            if(AllCreatures[i].creatureType == 0)
            {
                printf("\nPC");
            }
            if(AllCreatures[i].creatureType == 1)
            {
                printf("\nAnimal %d", AllCreatures[i].creatureNum );
            }
            if(AllCreatures[i].creatureType == 2)
            {
                printf("\nNPC %d", AllCreatures[i].creatureNum);
            }
        }
    }
    printf("\n");
}

/*move the Creature around*/
void moveCreatures(int numberofcreatures, struct Creatures* AllCreatures,int numberofrooms,struct room* AllRooms)
{

for(int j = 0; j < numberofcreatures; j++)
{
        int growl = 1;
       int successful = 0;
       int fullroom = 0;
       int findPC;

       //find PC
        for(int i=0; i < numberofcreatures; i++)
        {
            if(AllCreatures[i].creatureType == 0)
            {
                findPC = i;
            }
        }

       //check if the animal is happy or if it needs to be moved
       if(AllCreatures[j].creatureType == 1)
       {
           if(AllRooms[AllCreatures[j].location].roomStatus == 0 || AllRooms[AllCreatures[j].location].roomStatus == 1)
           {
              // printf("\nAnimal %d stayed and still is in room number %d",AllCreatures[j].creatureNum,AllCreatures[j].location);
               successful = 1;
           }
       }
       //check if the NPC is happy or if it needs to be moved
       else if(AllCreatures[j].creatureType == 2)
       {
           if(AllRooms[AllCreatures[j].location].roomStatus == 1 || AllRooms[AllCreatures[j].location].roomStatus == 2)
           {

               //printf("\nNPC %d stayed and still is in room number %d",AllCreatures[j].creatureNum,AllCreatures[j].location);
               successful = 1;
           }
       }
       else if(AllCreatures[j].creatureType == 0)
       {
           successful = 1;
       }
       else if(AllCreatures[j].creatureType == -1)
       {
           successful = 1;
       }

        //check if the rooms are full
        if(AllCreatures[j].creatureNum != 0 && successful == 0)
        {
            if(fullRoom(numberofcreatures,AllCreatures[j].creatureNum,AllCreatures,AllRooms) == 1)
            {
                successful = 1;
            }
        }



        //move a creature execpt the PC randomly using rand
        while(successful == 0)
        {
            int moves;
            moves = (rand()% 4) + 1;

            /* If creature wants to go North*/
            if(moves == 1)
            {
                //find which room has south number same as north number
                int dontgoagain = 0;
                for(int k=0;k < numberofrooms;k++)
                {
                        if(AllRooms[k].roomNum == AllRooms[AllCreatures[j].location].north && AllCreatures[j].creatureType != 0)
                        {

                                if(AllRooms[AllRooms[AllCreatures[j].location].north].roomTotal != 10)
                                {
                                    AllRooms[AllCreatures[j].location].roomTotal = AllRooms[AllCreatures[j].location].roomTotal - 1;//leaves the rooms
                                    if(AllCreatures[findPC].location == AllCreatures[j].location)
                                    {
                                        printf("\n%d moves north\n", AllCreatures[j].creatureNum);
                                    }
                                    while(dontgoagain == 0)
                                    {
                                        AllCreatures[j].location = AllRooms[AllCreatures[j].location].north;//move creature
                                        //enteres a new room
                                        dontgoagain = 1;
                                    }
                                    AllRooms[AllCreatures[j].location].roomTotal = AllRooms[AllCreatures[j].location].roomTotal + 1;


                                    successful = 1;

                                    //if moved, check if its happy, if not do clean or dirty
                                        if(AllCreatures[j].creatureType == 1)//animal
                                        {
                                            if(AllRooms[AllCreatures[j].location].roomStatus == 2)
                                            {
                                                AllRooms[AllCreatures[j].location].roomStatus = AllRooms[AllCreatures[j].location].roomStatus - 1;
                                                //printf("\Animal %d performed clean action is in room number %d, its room status is",AllCreatures[j].creatureNum,AllCreatures[j].location,AllRooms[AllCreatures[j].location].roomStatus);
                                                successful = 1;
                                            }
                                        }

                                        //check if the NPC is happy or if it needs to be moved
                                        if(AllCreatures[j].creatureType == 2)//NPC
                                        {
                                            if(AllRooms[AllCreatures[j].location].roomStatus == 0)
                                            {

                                                AllRooms[AllCreatures[j].location].roomStatus = AllRooms[AllCreatures[j].location].roomStatus + 1;
                                                //printf("\NPC %d performed dirty action is in room number %d, its room status is %d\n",AllCreatures[j].creatureNum,AllCreatures[j].location,AllRooms[AllCreatures[j].location].roomStatus);
                                                successful = 1;
                                            }
                                        }

                                }


                        }
                }
            }
                /* If PC goes south*/
            else if(moves == 2)
            {
                int moved = 0;
                    //find which room has south number same as north number
                    int dontgoagain = 0;
                    for(int k=0;k < numberofrooms;k++)
                    {
                            if(AllRooms[k].roomNum == AllRooms[AllCreatures[j].location].south && AllCreatures[j].creatureType != 0)
                            {

                                    if(AllRooms[AllRooms[AllCreatures[j].location].south].roomTotal != 10 )
                                    {
                                        AllRooms[AllCreatures[j].location].roomTotal = AllRooms[AllCreatures[j].location].roomTotal - 1;//leaves the rooms
                                        if(AllCreatures[findPC].location == AllCreatures[j].location)
                                        {
                                             printf("\n%d moves south\n", AllCreatures[j].creatureNum);
                                        }

                                        while(dontgoagain == 0)
                                        {
                                            AllCreatures[j].location = AllRooms[AllCreatures[j].location].south;//moves south
                                            dontgoagain = 1;

                                        }
                                         AllRooms[AllCreatures[j].location].roomTotal = AllRooms[AllCreatures[j].location].roomTotal + 1;//enteres a new room


                                        //printf("\n location for room the creature %d is in %d",AllCreatures[j].creatureNum,AllCreatures[j].location);
                                        moved = 1;
                                        successful = 1;

                                          //if moved, check if its happy, if not do clean or dirty
                                        if(AllCreatures[j].creatureType == 1)//animal
                                           {
                                               if(AllRooms[AllCreatures[j].location].roomStatus == 2)
                                               {

                                                   AllRooms[AllCreatures[j].location].roomStatus = AllRooms[AllCreatures[j].location].roomStatus - 1;
                                                   //printf("\Animal %d performed clean action is in room number %d, its room status is",AllCreatures[j].creatureNum,AllCreatures[j].location,AllRooms[AllCreatures[j].location].roomStatus);
                                                   successful = 1;
                                               }
                                           }

                                           //check if the NPC is happy or if it needs to be moved
                                           if(AllCreatures[j].creatureType == 2)//NPC
                                           {
                                               if(AllRooms[AllCreatures[j].location].roomStatus == 0)
                                               {

                                                   AllRooms[AllCreatures[j].location].roomStatus = AllRooms[AllCreatures[j].location].roomStatus + 1;
                                                   //printf("\NPC %d performed dirty action is in room number %d, its room status is %d\n",AllCreatures[j].creatureNum,AllCreatures[j].location,AllRooms[AllCreatures[j].location].roomStatus);
                                                   successful = 1;
                                               }
                                           }
                                    }


                                    //successful = 1;
                            }
                    }
                }
                /* For East*/
                else if(moves == 3)
                {
                    //find which room has south number same as north number
                    int dontgoagain = 0;
                    for(int k=0;k < numberofrooms;k++)
                    {
                            if(AllRooms[k].roomNum == AllRooms[AllCreatures[j].location].east && AllCreatures[j].creatureType != 0)
                            {

                                    if(AllRooms[AllRooms[AllCreatures[j].location].east].roomTotal != 10)
                                    {
                                        AllRooms[AllCreatures[j].location].roomTotal = AllRooms[AllCreatures[j].location].roomTotal - 1;//leaves the rooms
                                        if(AllCreatures[findPC].location == AllCreatures[j].location)
                                        {
                                             printf("\n%d moves east\n", AllCreatures[j].creatureNum);
                                        }

                                        while(dontgoagain == 0)
                                        {
                                            AllCreatures[j].location = AllRooms[AllCreatures[j].location].east;//moves east
                                            dontgoagain = 1;
                                        }

                                        AllRooms[AllCreatures[j].location].roomTotal = AllRooms[AllCreatures[j].location].roomTotal + 1;//enteres a new room

                                        successful = 1;

                                          //if moved, check if its happy, if not do clean or dirty
                                        if(AllCreatures[j].creatureType == 1)//animal
                                           {
                                               if(AllRooms[AllCreatures[j].location].roomStatus == 2)
                                               {

                                                   AllRooms[AllCreatures[j].location].roomStatus = AllRooms[AllCreatures[j].location].roomStatus - 1;
                                                   //printf("\Animal %d performed clean action is in room number %d, its room status is",AllCreatures[j].creatureNum,AllCreatures[j].location,AllRooms[AllCreatures[j].location].roomStatus);
                                                   successful = 1;
                                               }
                                           }

                                           //check if the NPC is happy or if it needs to be moved
                                           if(AllCreatures[j].creatureType == 2)//NPC
                                           {
                                               if(AllRooms[AllCreatures[j].location].roomStatus == 0)
                                               {

                                                   AllRooms[AllCreatures[j].location].roomStatus = AllRooms[AllCreatures[j].location].roomStatus + 1;
                                                   //printf("\NPC %d performed dirty action is in room number %d, its room status is %d\n",AllCreatures[j].creatureNum,AllCreatures[j].location,AllRooms[AllCreatures[j].location].roomStatus);
                                                   successful = 1;
                                               }
                                           }
                                    }

                            }
                    }
                }

                /*For west*/
                else if(moves == 4)
                {
                    //find which room has south number same as north number
                    int dontgoagain = 0;
                    for(int k=0;k < numberofrooms;k++)
                    {
                        if(AllRooms[k].roomNum == AllRooms[AllCreatures[j].location].west && AllCreatures[j].creatureType != 0)
                        {

                                    if(AllRooms[AllRooms[AllCreatures[j].location].west].roomTotal != 10)
                                    {
                                        AllRooms[AllCreatures[j].location].roomTotal = AllRooms[AllCreatures[j].location].roomTotal - 1;//leaves the rooms
                                        if(AllCreatures[findPC].location == AllCreatures[j].location)
                                        {
                                             printf("\n%d moves west\n", AllCreatures[j].creatureNum);
                                        }

                                        while(dontgoagain == 0)
                                        {
                                            AllCreatures[j].location = AllRooms[AllCreatures[j].location].west;//moves west
                                            dontgoagain = 1;
                                        }
                                        AllRooms[AllCreatures[j].location].roomTotal = AllRooms[AllCreatures[j].location].roomTotal + 1;//enteres a new room

                                        successful = 1;

                                        //if moved, check if its happy, if not do clean or dirty
                                        if(AllCreatures[j].creatureType == 1)//animal
                                           {
                                               if(AllRooms[AllCreatures[j].location].roomStatus == 2)
                                               {

                                                   AllRooms[AllCreatures[j].location].roomStatus = AllRooms[AllCreatures[j].location].roomStatus - 1;
                                                   //printf("\Animal %d performed clean action is in room number %d, its room status is",AllCreatures[j].creatureType,AllCreatures[j].location,AllRooms[AllCreatures[j].location].roomStatus);
                                                   successful = 1;
                                               }
                                           }
                                           //check if the NPC is happy or if it needs to be moved
                                           if(AllCreatures[j].creatureType == 2)//NPC
                                           {
                                               if(AllRooms[AllCreatures[j].location].roomStatus == 0)
                                               {

                                                   AllRooms[AllCreatures[j].location].roomStatus = AllRooms[AllCreatures[j].location].roomStatus + 1;
                                                   //printf("\NPC %d performed dirty action is in room number %d, its room status is %d\n",AllCreatures[j].creatureType,AllCreatures[j].location,AllRooms[AllCreatures[j].location].roomStatus);
                                                   successful = 1;
                                               }
                                           }
                                    }

                        }

                    }
                }

        }

    }
}



void movePC(int numberofcreatures, struct Creatures* AllCreatures,int numberofrooms,struct room* AllRooms,char decision[])
{
    int findPC;
    int moves;
    int successful = 0;
    char north[10] = "north";
    char south[10] = "south";
    char east[10] = "east";
    char west[10] = "west";

    for(int i=0; i < numberofcreatures; i++)
    {
        if(AllCreatures[i].creatureType == 0)
        {
            findPC = i;
        }
    }

        int moved = 0;

        /* If PC wants to go North*/
        if(strcmp(decision,north)== 0)
        {

            //find which room has south number same as north number
            int dontgoagain = 0;
            for(int k=0;k < numberofrooms;k++)
            {

                if(AllRooms[k].roomNum == AllRooms[AllCreatures[findPC].location].north)
                {
                    while(dontgoagain == 0)
                    {
                        if(AllCreatures[findPC].location != -1 && AllRooms[AllRooms[AllCreatures[findPC].location].north].roomTotal != 10)
                        {
                            AllRooms[AllCreatures[findPC].location].roomTotal = AllRooms[AllCreatures[findPC].location].roomTotal - 1;//PC leaves room
                            AllCreatures[findPC].location = AllRooms[AllCreatures[findPC].location].north;//move PC north
                            AllRooms[AllCreatures[findPC].location].roomTotal = AllRooms[AllCreatures[findPC].location].roomTotal + 1;//PC enters room

                            //printf("\n location for room the PC is in %d",AllCreatures[findPC].location);
                            dontgoagain = 1;
                            successful = 1;
                            moved =1;
                        }
                        else
                        {
                            printf("\n room is full");
                            successful = 1;
                            dontgoagain = 1;
                        }
                    }

                }

            }
            if(moved == 1)
            {
                printf("\nYou have moved north");
                //printf("\nYou are now in room number %d",AllCreatures[findPC].location);

            }
            else if(AllRooms[AllCreatures[findPC].location].north == -1)
            {
                printf("\nTheres a wall, cant move\n");
            }

        }

        /* If PC goes south*/
         else if(strcmp(decision,south)== 0)
        {

            int moved = 0;


            //find which room has south number same as north number
            int dontgoagain = 0;
            for(int k=0;k < numberofrooms;k++)
            {

                if(AllRooms[k].roomNum == AllRooms[AllCreatures[findPC].location].south)
                {
                    while(dontgoagain == 0)
                    {
                        if(AllCreatures[findPC].location != -1 && AllRooms[AllRooms[AllCreatures[findPC].location].south].roomTotal != 10)
                        {
                            AllRooms[AllCreatures[findPC].location].roomTotal = AllRooms[AllCreatures[findPC].location].roomTotal - 1;//PC leaves room
                            AllCreatures[findPC].location = AllRooms[AllCreatures[findPC].location].south;
                            AllRooms[AllCreatures[findPC].location].roomTotal = AllRooms[AllCreatures[findPC].location].roomTotal + 1;//PC enters room

                            //printf("\n location for room the PC is in %d",AllCreatures[findPC].location);
                            moved = 1;
                            dontgoagain = 1;
                            successful = 1;
                        }
                        else
                        {
                            printf("\n room is full");
                            successful = 1;
                            dontgoagain = 1;
                        }

                    }

                }

            }
            if(moved == 1)
            {
                printf("\nYou have moved south");
                //printf("\nYou are now in room number %d",AllCreatures[findPC].location);

            }
            else if(AllRooms[AllCreatures[findPC].location].south == -1)
            {
                printf("\nTheres a wall, cant move\n");
            }

        }
        /* For East*/
        else if(strcmp(decision,east)== 0)
        {

            int moved = 0;

            //find which room has south number same as north number
            int dontgoagain = 0;
            for(int k=0;k < numberofrooms;k++)
            {

                if(AllRooms[k].roomNum == AllRooms[AllCreatures[findPC].location].east)
                {
                    while(dontgoagain == 0)
                    {
                        if(AllCreatures[findPC].location != -1 && AllRooms[AllRooms[AllCreatures[findPC].location].east].roomTotal != 10)
                        {
                            AllRooms[AllCreatures[findPC].location].roomTotal = AllRooms[AllCreatures[findPC].location].roomTotal - 1;//PC leaves room
                            AllCreatures[findPC].location = AllRooms[AllCreatures[findPC].location].east;
                            AllRooms[AllCreatures[findPC].location].roomTotal = AllRooms[AllCreatures[findPC].location].roomTotal + 1;//PC enters room

                            moved = 1;
                            dontgoagain = 1;
                            successful = 1;
                        }
                        else
                        {
                            printf("\n room is full");
                            dontgoagain = 1;
                            successful = 1;
                        }

                    }
                        //successful = 1;
                }
            }
            if(moved == 1)
            {
                printf("\nYou have moved east");
                //printf("\nYou are now in room number %d",AllCreatures[findPC].location);

            }
            else if(AllRooms[AllCreatures[findPC].location].east == -1)
            {
                printf("\nTheres a wall, cant move\n");
            }

        }

        /*For west*/
        else if(strcmp(decision,west)== 0)
        {

            int moved = 0;

            //find which room has south number same as north number
            int dontgoagain = 0;
            for(int k=0;k < numberofrooms;k++)
            {

                if(AllRooms[k].roomNum == AllRooms[AllCreatures[findPC].location].west)
                {
                    while(dontgoagain == 0)
                    {
                        if(AllCreatures[findPC].location != -1 && AllRooms[AllRooms[AllCreatures[findPC].location].west].roomTotal != 10)
                        {
                            AllRooms[AllCreatures[findPC].location].roomTotal = AllRooms[AllCreatures[findPC].location].roomTotal - 1;//PC leaves room
                            AllCreatures[findPC].location = AllRooms[AllCreatures[findPC].location].west;
                            AllRooms[AllCreatures[findPC].location].roomTotal = AllRooms[AllCreatures[findPC].location].roomTotal + 1;//PC enters room

                            //printf("\n location for room the PC is in %d",AllCreatures[findPC].location);
                            moved = 1;
                            dontgoagain = 1;
                            successful = 1;
                        }
                        else
                        {
                            printf("\n room is full");
                            dontgoagain = 1;
                            successful = 1;
                        }

                    }
                        //successful = 1;
                }
            }
            if(moved == 1)
            {
                printf("\nYou have moved west");
               // printf("\nYou are now in room number %d",AllCreatures[findPC].location);

            }

            else if(AllRooms[AllCreatures[findPC].location].west == -1)
            {
                printf("\nTheres a wall, cant move\n");
            }



        }
        //ask again if theres a wall

}

//create all creatures
void createCreatures(int numberofcreatures, struct Creatures* AllCreatures,struct room* AllRooms)
{
    int location;

    int counter = 0;
    int PC = 0;

    //ask the user for creatures and check the inputs
    for(int i=0; i < numberofcreatures; i++)
    {
        int creatureType;

            printf("\nType of Creature, Location: ");
            scanf("%d%d",&creatureType,&location);

            //if room is full
            while(AllRooms[location].roomTotal == 10)
            {
                printf("\nRoom is already full!\n");
                printf("\nType of Creature, Location: ");
                scanf("%d%d",&creatureType,&location);

                //make sure isnt invalid creature num in nested while loop
                while(creatureType < 0 || creatureType > 2)
                {
                    printf("\ninvalid creature type\n");
                    printf("\nType of Creature, Location: ");
                    scanf("%d%d",&creatureType,&location);
                }
            }

            //if room isnt full but invalid creature type
            while(creatureType < 0 || creatureType > 2)
            {
                printf("\ninvalid creature type\n");
                printf("\nType of Creature, Location: ");
                scanf("%d%d",&creatureType,&location);
            }

             if(creatureType == 0)
             {
                 PC++;
                 while(PC > 1)
                {
                     printf("\nThere is already a PC player, enter again");
                     printf("\nType of Creature, Location: ");
                     scanf("%d%d",&creatureType,&location);
                     if(creatureType == 1 || creatureType == 2)
                     {
                         PC--;
                     }
                }
             }


        //print out the creatures with the room numbers
        AllCreatures[i].location = location;
        AllCreatures[i].creatureType = creatureType;
        AllCreatures[i].creatureNum = counter;

        AllRooms[AllCreatures[i].location].roomTotal = AllRooms[AllCreatures[i].location].roomTotal + 1;
        counter++;
    }

    for(int i=0; i < numberofcreatures; i++)
    {
        printf("\n Creature num %d, type %d, location %d\n",AllCreatures[i].creatureNum, AllCreatures[i].creatureType,AllCreatures[i].location);
    }
}

//create all rooms
void createRooms(int numberofrooms,struct room* AllRooms)
{
    int counter = 0;
    int status;
    int north;
    int south;
    int east;
    int west;

    //ask the user for the cords
    for(int i =0; i < numberofrooms;i++)
    {
        printf("Room Number %d state north south east west: ",counter);
        scanf("%d%d%d%d%d",&status,&north,&south,&east,&west);
        AllRooms[i].roomStatus = status;
        AllRooms[i].north = north;
        AllRooms[i].south = south;
        AllRooms[i].east = east;
        AllRooms[i].west = west;
        AllRooms[i].roomNum = counter;
        AllRooms[i].roomTotal = 0;
        counter++;
    }

    //print out the cords
    for(int i =0; i < numberofrooms;i++)
    {
        printf("\n%d,%d,%d,%d,%d\n",AllRooms[i].roomStatus,AllRooms[i].north,AllRooms[i].south,AllRooms[i].east,AllRooms[i].west);
    }
}
