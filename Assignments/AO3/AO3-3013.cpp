/*****************************************************************************
*                    
*  Author:           Blake Gauna
*  Label:            A03
*  Title:            Linked List Class
*  Course:           CMPS 3013
*  Semester:         Spring 2022
* 
*  Description:
*        This program implements a class that allows a linked list to be used just like 
*        an array. It overloads the "[]" (square brackets) to simulate accessing seperate 
*        array elements, but really it traverses the list to find the specified node using
*        an index value. It also overloads the "+" and "<<" signs allowing a user to "add"
*        or "push" items onto the end of the list, as well as "pop" items off the end of our 
*        array. This class is not meant to replace the STL vector library, its simply a project
*        to introduce the beginnings of creating complex / abstract data types. 
*        
*       
*  Files:            
*       main.cpp    : driver program 
*****************************************************************************/

#include <iostream>

using namespace std;

int A[100];               //Declaring int array of size 100


 /**
     * Public : Node
     * 
     * Description:
     *      The structure of a node. A node contains an integer
     *      and a pointer to the next node.
     * 
     * Params:
     *      int    x;
     *      Node*  next;
     * 
     * Returns:
     *      None.
     */
struct Node {
    int x;
    Node *next;           
    Node() {              
        x = -1;
        next = NULL;
    }
    Node(int n) {         //Overloaded constructor which allows us to pass
        x = n;            //a value
        next = NULL;
    }
};

/**
 * List
 * 
 * Description:
 *      This class contains functions that allow us to create a 
 *      linked list. In this linked list we can insert nodes, push
 *      nodes to the end of the list
 * 
 * Public Methods:
 *                          List()                               
 *      void                Push(int val)
 *      void                Insert(int val)
 *      void                PrintTail()
 *      string              Print()
 *      int                 Pop()
 *      List                operator+(const List &Rhs)
 *      int                 operator[](int index)
 *      friend              ostream &operator<<(ostream &os, List L)
 *  
 * Private:
 *       Node               *Head;
 *       Node               *Tail;
 *       int                Size;
 * 
 */
class List {
private:
    Node *Head;
    Node *Tail;
    int Size;

public:
    List() {
        Head = Tail = NULL;
        Size = 0;
    }

    /**
     * Public : Push
     * 
     * Description:
     *      Pushes an integer to the end of the list and if list is empty
     *      it makes it the head.
     * 
     * Params:
     *     int  val
     * 
     * Returns:
     *      Nothing
     */
    void Push(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    /**
     * Public : Insert
     * 
     * Description:
     *      Inserts a node into the linked list.
     * 
     * Params:
     *      int   val
     * 
     * Returns:
     *      Nothing
     */
    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }

    /**
     * Public : PrintTail
     * 
     * Description:
     *      Prints tail
     * 
     * Returns:
     *      Tail.
     */
    void PrintTail() {
        cout << Tail->x << endl;
    }

    /**
     * Public : Print
     * 
     * Description:
     *      Prints a string of characters
     * 
     * Params:
     *      int   list
     * 
     * Returns:
     *      string of characters
     */
    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    /**
     * Public : Pop
     * 
     * Description:
     *      Not implemented
     * 
     * Params:
     *      
     *      
     * Returns:
     *      integer popped
     */
    int Pop() {
        Size--;
        return 0; //
    }

    /**
     * Public : Operator +
     * 
     * Description:
     *      Adds two values of integers
     * 
     * Params:
     *      const   List &Rhs

     * 
     * Returns:
     *      [type] List*   : a pointer to a linked list of integers.
     */
    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

  
    /**
     * Public : Operator []
     * 
     * Description:
     *      // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
     * 
     * Params:
     *      int     index
     * 
     * Returns:
     *      integer
     */
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }


   /**
     * Public : Operator <<
     * 
     * Description:
     *      overloading the << operator
     * 
     * Params:
     *      ostream&   os
     *      List       L
     * 
     * Returns:
     *      os
     */
    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

    
int main(int argc, char **argv) {
    List L1;        //Creating instances of List
    List L2;

    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}
