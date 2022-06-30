#include <iostream>


struct Node
{
    // data 
    int data;
    // position of next Node
    Node* next;
};

/*
Write functions for the following features:
 * insert one element to the list
 * remove one element from the list
 * count length of list
 * read specific cell
 * modify the value of specific cell
 * print entire list

TODO:
 * delete node with specific value
 * append two linked lists
 * reverse the linked list
 * search for a specific value
 * create a copy of the list
 * insert node at specific position(and efficiently)
 * delete node from specific position
 * insert node at the end of the list
 */


/*
 * Syntax: insert(integer, pointer of type Node)
 * Return Value: returns a pointer to the newly created Node (The calling function needs to replace the start value by this pointer.)
 * Functionality: adds a Node to the present linked list.
 */
// FIXME:
// Malloc can fain. Thus add a NULL check.
Node* insert(int new_data, Node* old_pointer)
{
    Node* temp = (Node*)malloc(sizeof(Node));
    (*temp).data = new_data;
    (*temp).next = old_pointer;
    return temp;
}


/*
 * Syntax: remove(pointer of type Node)
 * Return Value: pointer of type Node
 * Functionality: removes a Node from the linked list.
 */
Node* remove(Node* startPosition)
{
    if(startPosition != NULL)
    {
        Node* temp = (*startPosition).next;
        std::cout << (*startPosition).data << " getting freed......" << std::endl;
        free(startPosition);
        return temp;
    }
    else
    {
        std::cout << "No Nodes to be removed......." << std::endl;
        return NULL;
    }
}


/*
 * Syntax: length(pointer of type Node)
 * Return Value: int
 * Functionality: returns the length of the linked list.
 */
int length(Node* starting_point)
{
    int count = 0;

    while(starting_point != NULL)
    {
        count++;
        starting_point = (*starting_point).next;

    } 

    return count;
}


/*
 * Syntax: readData(integer, pointer of type Node)
 * Return Value: int
 * Functionality: prints the value in a specific location.
 */
// 
int readData(int position, Node* startPos)
{
    int count = 0;

    while(count != position)
    {
        startPos = (*startPos).next;
        count++;
    }
    return count;
}


/*
 * Syntax: update(integer, integer, pointer of type Node)
 * Return Value: void
 * Functionality: replaces the sent position with the sent new data.
 */
// FIXME:
// return a bool to make sure the change is made
// Null check on Node
// if position > length of list
void update(int position, int new_data, Node* startPos)
{
    int count = 0;

    while(count != position)
    {
        startPos = (*startPos).next;
        count++;
    }
    (*startPos).data = new_data;
}


/*
 * Syntax: printLst(pointer of type Node)
 * Return Value: void
 * Functionality: prints all the values in the linked list.
 */
void printLst(Node* starting_point)
{
    std::cout << "The entire list is:\n";

    std::cout << "[ ";

    while(starting_point != NULL)
    {
        std::cout << (*starting_point).data << "  ";
        starting_point = (*starting_point).next;

    } 
    std::cout << "]\n";
}


/*
 * Syntax: removeAll(pointer of type Node)
 * Return Value: void
 * Functionality: frees all the allocated memory in the linked list
 */
void removeAll(Node* starting_point)
{
    Node* temp = NULL;

    while(starting_point != NULL)
    {
        temp = starting_point;
        std::cout << (*starting_point).data << " getting freed......" << std::endl;
        starting_point = (*starting_point).next;
        free(temp);
        temp = NULL;
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    Node* start = NULL;

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

       std::cout << "Enter:\n1 for adding new Node at the beginning\n2 for remove a Node from beginning\n3 for length of list\n";
       std::cout << "4 for read data specific cell position(starts from 0)\n5 for modify the value of specific cell(starts from 0)\n6 for printing list\n7 for exit program\n";
       std::cin >> flag;

       switch (flag)
       {
       case 1:
            std::cout << "Enter integer type data for new Node:";
            std::cin >> inp;
            start = insert(inp, start);
            break;

       case 2:
            start = remove(start);
            break;

       case 3:
            std::cout << length(start) << std::endl;
            break;

       case 4:
            std::cout << "Enter position:";
            std::cin >> pos;
            std::cout << readData(pos, start) << std::endl;
            break;

       case 5:
            std::cout << "Enter position:";
            std::cin >> pos;
            std::cout << "Enter new data:";
            std::cin >> newData;
            update(pos, newData, start);
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






