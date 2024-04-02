#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>


// define SIZE
#define LIST_SIZE 64
#define ITEM_NAME_SIZE 32
#define UNIT_NAME_SIZE 32
#define USER_INPUT_SIZE 32


// item struct
typedef struct {
    char itemName[ITEM_NAME_SIZE];
    int  quantity;
    char unitMeasure[UNIT_NAME_SIZE];
    int lowCutoff;
    bool isLow;
} item;


// create hash table 
item * itemHashTable[LIST_SIZE];


// initialize hash table
void init_hash_table() 
{
    for (int i = 0; i < LIST_SIZE; i++)
    {
        itemHashTable[i] = NULL;
    }
}


// hash function
unsigned int hashFunction(char *itemName)
{
    int len = strlen(itemName);
    unsigned int hash_value = 0;

    for (int i = 0; i < len; i++) 
    {
        hash_value += itemName[i];
        hash_value = (hash_value * itemName[i]) % LIST_SIZE;
    }
}


//print item info
void printItemInfo(item *itemToPrint)
{
    printf("%s\t%d\t%s\t%d", itemToPrint->itemName, itemToPrint->quantity, itemToPrint->unitMeasure, itemToPrint->lowCutoff);
}


// print table as current inventory list
void printFullInventory()
{
    for (int i = 0; i < LIST_SIZE; i++)
    {
        if(itemHashTable[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t%s\n", i, itemHashTable[i]->itemName);
        }
    }
}


// print table as shopping list
void printShoppingList()
{
    for (int i = 0; i < LIST_SIZE; i++)
    {
        if(itemHashTable[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t%s\n", i, itemHashTable[i]->itemName);
        }
    }
}


// insert to table
bool insertToTable(item *itemToAdd)
{
    if (itemToAdd == NULL) { return false; }
    
    int addIndex = hashFunction(itemToAdd->itemName);
    if (itemHashTable[addIndex] != NULL)
    {
        return false;
    }

    itemHashTable[addIndex] = itemToAdd;
    return true;
}



// search table
item *searchHashTable(char *iName)
{
    int searchIndex = hashFunction(iName);
    if ( itemHashTable[searchIndex] != NULL && 
        strncmp(itemHashTable[searchIndex]->itemName, iName, LIST_SIZE) == 0 )
    {
        return itemHashTable[searchIndex];
    }
    else
    {
        return NULL;
    }
}


// createItem function
item *createItem()
{
    item createdItem = {"", 0, "", 0, true};

    printf("What is the item called?\n");
    char newItemName[ITEM_NAME_SIZE];
    gets(newItemName);
    strcpy(createdItem.itemName, newItemName);

    printf("What is the current quantity of this item?\n");
    int newItemQuantity;
    scanf("%d", &newItemQuantity);
    createdItem.quantity = newItemQuantity;

    printf("What unit is used to measure this item?\n");
    char newItemUnit[ITEM_NAME_SIZE];
    gets(newItemUnit);
    strcpy(createdItem.unitMeasure, newItemUnit);

    printf("What is considered low quantity for this item?\n");
    int newItemLowCutoff;
    scanf("%d", &newItemLowCutoff);
    createdItem.lowCutoff = newItemLowCutoff;

    int newItemLowStatus;
    if (newItemQuantity <= newItemLowCutoff) {newItemLowStatus = true;}
    else {newItemLowStatus = false;}
    createdItem.isLow = newItemLowStatus;

    //createdItem = {.itemName=newItemName, .quantity=newItemQuantity, .unitMeasure=newItemUnit, .lowCutoff=newItemLowCutoff, .isLow=newItemLowStatus};

    return &createdItem;
}


// editItem
void editItem(item *itemToEdit)
{
    printItemInfo(itemToEdit);
    int yesno;
    
    printf("Edit name? (1 - yes, 0 - no)\n");
    scanf("%d", &yesno);
    if ( yesno == 1 )
    {
        printf("Enter new item name:\n");
        gets(itemToEdit->itemName);
    }

    printf("Edit quantity? (1 - yes, 0 - no)\n");
    scanf("%d", &yesno);
    if ( yesno == 1 )
    {
        printf("Enter new item quantity:\n");
        scanf("%d", itemToEdit->quantity);
    }

    printf("Edit unit measure? (1 - yes, 0 - no)\n");
    scanf("%d", &yesno);
    if ( yesno == 1 )
    {
        printf("Enter new unit measure:\n");
        gets(itemToEdit->unitMeasure);
    }

    printf("Edit low quantity cutoff? (1 - yes, 0 - no)\n");
    scanf("%d", &yesno);
    if ( yesno == 1 )
    {
        printf("Enter new low quantity cutoff:\n");
        scanf("%d",itemToEdit->lowCutoff);
    }

    if (itemToEdit->quantity <= itemToEdit->lowCutoff) {itemToEdit->isLow = true;}
    else {itemToEdit->isLow = false;}
}


// search option (3) selected by user
void searchOption()
{
    char inputItemName[ITEM_NAME_SIZE];
    printf("Please enter the name of the item you are interested in: \n");
    gets(inputItemName);
    
    item *searchedItem = searchHashTable(inputItemName);
    if (searchedItem == NULL)
    {
        printf("Item was not found. Would you like to add it to the inventory? (1 - yes, 0 - no)\n");
        int addItemChoice;
        scanf("%d", &addItemChoice);
        if (addItemChoice == 1) 
        {
            item *newItem = createItem();
            insertToTable(newItem);
        }
    }
    else
    {
        printf("Item found. Would you like to edit it? (1 - yes, 0 - no)\n");
        int editItemChoice;
        scanf("%d", &editItemChoice);
        if (editItemChoice == 1)
        {
            printItemInfo(searchedItem);
            editItem(searchedItem);
        }
    }
}


////////////////// MAIN ////////////////////////
int main() 
{
    printf("welcome to the inventory tracker! please select an option:\n");
    printf("1 - view the current full inventory list\n");
    printf("2 - view the shopping list\n");
    printf("3 - search for an item in the inventory\n");
    printf("0 - exit program\n");

    //init_hash_table();

    int userChoice = 0;
    scanf("%d", &userChoice);
    
    //char userInput[USER_INPUT_SIZE];
    //gets(userInput);

    while ( userChoice > 0 ) 
    {
        switch(userChoice)
        {
            case 1: printFullInventory();
                break;
            case 2: printShoppingList();
                break;
            case 3: searchOption();///// FILL IN SEARCH AND ADD
                break;
            case 0: exit(0);
            default: break;
        }

        printf("MAIN MENU\n");
        printf("1 - view the current full inventory list\n");
        printf("2 - view the shopping list\n");
        printf("3 - search for an item in the inventory\n");
        printf("0 - exit program\n");
        scanf("%d", &userChoice);
    }

    return 0;
}






// add editItem
// edit both print table functions