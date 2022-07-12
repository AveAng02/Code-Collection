#include <iostream>


struct node
{
    // data 
    int data;
    // position of next node
    node* nexPos;
};

/*
Write functions for the following features:
 * insert one element to the list
 * remove one element from the list
 * count length of list
 * read specific cell
 * modify the value of specific cell
 * print entire list
 */


/*
 * Syntax: insert(integer, pointer of type node)
 * Return Value: returns a pointer to the newly created node (The calling function needs to replace the start value by this pointer.)
 * Functionality: adds a node to the present linked list.
 */
node* insert(int new_data, node* old_pointer)
{
    node* temp = (node*)malloc(sizeof(node));
    (*temp).data = new_data;
    (*temp).nexPos = old_pointer;
    return temp;
}


/*
 * Syntax: remove(pointer of type node)
 * Return Value: pointer of type node
 * Functionality: removes a node from the linked list.
 */
node* remove(node* startPosition)
{
    if(startPosition != NULL)
    {
        node* temp = (*startPosition).nexPos;
        std::cout << (*startPosition).data << " getting freed......" << std::endl;
        free(startPosition);
        return temp;
    }
    else
    {
        std::cout << "No nodes to be removed......." << std::endl;
        return NULL;
    }
}


/*
 * Syntax: length(pointer of type node)
 * Return Value: void
 * Functionality: prints the length of the linked list.
 */
void length(node* starting_point)
{
    int count = 0;

    while(starting_point != NULL)
    {
        count++;
        starting_point = (*starting_point).nexPos;

    } 

    std::cout << "The length of the list: " << count << std::endl;
}


/*
 * Syntax: readData(integer, pointer of type node)
 * Return Value: void
 * Functionality: prints the value in a specific location.
 */
void readData(int position, node* startPos)
{
    int count = 0;

    while(count != position)
    {
        startPos = (*startPos).nexPos;
        count++;
    }
    std::cout << (*startPos).data << std::endl;
}


/*
 * Syntax: modData(integer, integer, pointer of type node)
 * Return Value: void
 * Functionality: replaces the sent position with the sent new data.
 */
void modData(int position, int new_data, node* startPos)
{
    int count = 0;

    while(count != position)
    {
        startPos = (*startPos).nexPos;
        count++;
    }
    (*startPos).data = new_data;
}


/*
 * Syntax: printLst(pointer of type node)
 * Return Value: void
 * Functionality: prints all the values in the linked list.
 */
void printLst(node* starting_point)
{
    std::cout << "The entire list is:\n";

    std::cout << "[ ";

    while(starting_point != NULL)
    {
        std::cout << (*starting_point).data << "  ";
        starting_point = (*starting_point).nexPos;

    } 
    std::cout << "]\n";
}


/*
 * Syntax: removeAll(pointer of type node)
 * Return Value: void
 * Functionality: frees all the allocated memory in the linked list
 */
void removeAll(node* starting_point)
{
    node* temp = NULL;

    while(starting_point != NULL)
    {
        temp = starting_point;
        std::cout << (*starting_point).data << " getting freed......" << std::endl;
        starting_point = (*starting_point).nexPos;
        free(temp);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    node* start = NULL;

    int flag = 0, inp = 0, pos = 0, newData = 0;

    while (flag != 7)
    {
        /*
        Call functions for the following features:
        * enter 1 for insert one element to the list
        * enter 2 for remove one element from the list
        * enter 3 for count length of list
        * enter 4 for read data specific cell position
        * enter 5 for modify the value of specific cell
        * enter 6 for print entire list
        */

       std::cout << "Enter:\n1 for adding new node at the beginning\n2 for remove a node from beginning\n3 for length of list\n";
       std::cout << "4 for read data specific cell position(starts from 0)\n5 for modify the value of specific cell(starts from 0)\n6 for printing list\n7 for exit program\n";
       std::cin >> flag;

       switch (flag)
       {
       case 1:
            std::cout << "Enter integer type data for new node:";
            std::cin >> inp;
            start = insert(inp, start);
            break;

       case 2:
            start = remove(start);
            break;

       case 3:
            length(start);
            break;

       case 4:
            std::cout << "Enter position:";
            std::cin >> pos;
            readData(pos, start);
            break;

       case 5:
            std::cout << "Enter position:";
            std::cin >> pos;
            std::cout << "Enter new data:";
            std::cin >> newData;
            modData(pos, newData, start);
            break;

       case 6:
            printLst(start);
            break;

       case 7:
            removeAll(start);
            return 0;

       default:
            break;
       }
    }
    

    return 0;
}






