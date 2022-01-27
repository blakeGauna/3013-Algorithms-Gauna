///////////////////////////////////////////////////////////////////////////////
//
// Author:           Blake Gauna
// Email:            blakegauna@yahoo.com
// Label:            P01
// Course:           3013 Algorithms
// Semester:         Spring 2022
//
// Description:
//       Overview of a class implementing an array based stack
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack {
  private:
    int *A;   // pointer to array of int's
    double size; // current max stack size
    int top;  // top of stack
    double threshHold = .85;
    double fullRatio = 0.0;         
    double fullThres = 0.0;       //params
    double emptyThres = 0.0;
    double growRat = 0.0;
    double shrinkRat = 0.0;

    // top = number of items in the stack + 1
    // size = array size

    // size = 100
    // (top + 1) / size

public:

    int maxsize = 0;
    int changed = 0;
    int commands = 0;
    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack() {
        size = 10;
        A = new int[size];
        top = -1;
    }

    /**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
    ArrayStack(int s) {
        size = s;
        A = new int[s];
        top = -1;
    }

    /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
    bool Empty() {
        return (top <= -1);
    }

    /**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
    bool Full() {
        return (top >= size - 1);
    }

    /**
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Peek() {
        if (!Empty()) {
            return A[top];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
    int Pop() {
        if (!Empty()) {
            checkResize();
            return A[top--];
        }

        return -99; // some sentinel value
                    // not a good solution
    }

    /**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
    void Print() {
      string s(35,'#');       //Print function that prints proper output.
      cout << s << endl;
      cout << "Assignment 4 - Resizing the Stack" << endl;
      cout << "CMPS 3013" << endl;
      cout << "Blake Gauna" << endl << endl;
      cout << "Config Params" << endl << endl;
      cout << "Full Threshold: " << fullThres << endl;
      cout << "Empty Threshold: " << emptyThres << endl;
      cout << "Grow Ratio: " << growRat << endl;
      cout << "Shrink Ratio: " << shrinkRat << endl << endl;
      cout << "\nProcessed " << commands << " commands." << endl;
      cout << "\nMax stack size: " << maxsize << endl;
      cout << "End stack size: " << size << endl;
      cout << "Stack resized: " << changed << " times." << endl;
      cout << s << endl;
    }

    /**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      [bool] ; success = true
  */
    bool Push(int x) {
        if (Full()) {
            ContainerGrow();        //if full(will only happen with a 1.0
            A[++top] = x;           //full threshold), will enlarge container
            return true;            //and push the new int on top.
        }
        else if(top == -1){
          A[++top] = x;             //Base case
          return true;
        }
        else if (!Full()) { 
            A[++top] = x;           //Any average case, push and check for
            checkResize();          //a resize.
            
            return true;
        }
        else 
          return false;
    }

     /**
  * Public void: ContainerGrow
  * 
  * Description:
  *      Enlarges the array by however much the grow Ratio is
  * 
  * Params:
  *      none
  * 
  * Returns:
  *      nothing
  */

    void ContainerGrow(){
        int newSize = (size * growRat);    
        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

      if(size > maxsize){
        maxsize = size;
      }
        A = B; // reset array pointer
    }

    /**
  * Public void: ContainerShrink
  * 
  * Description:
  *      Shrinks the array by however much the shrink Ratio is
  * 
  * Params:
  *      none
  * 
  * Returns:
  *      nothing
  */

    void ContainerShrink(){
        int newSize = (size * shrinkRat);    
        int *B = new int[newSize]; // allocate new memory

        for (int i = 0; i < top; i++) { // copy values to new array
            B[i] = A[i];
        }

        delete[] A; // delete old array

        size = newSize; // save new size

        A = B; // reset array pointer
    }

/**
  * Public bool: checkResize
  * 
  * Description:
  *      Checks to see if the array needs to be resized.
  * 
  * Params:
  *      none
  * 
  * Returns:
  *      bool. True = success
  */
    bool checkResize() {
      fullRatio = double((top + 1)/size);     //find fullRatio
        if(fullRatio >= fullThres){           //comparing values
            ContainerGrow();                
            Change();                         //keeping track of changes 
            return true;                      //in size
          }
        else if(fullRatio <= emptyThres){
            ContainerShrink();      
            Change();
            return true;
        }
        else
          return true;
    }

/**
  * Public void: Change
  * 
  * Description:
  *    function to keep track of the number of changes  
  * 
  * Params:
  *      none
  * 
  * Returns:
  *      none
  */
    void Change(){
      changed++;         
    }

/**
  * Public void: command
  * 
  * Description:
  *    function to keep track of number of inputs  
  * 
  * Params:
  *      none
  * 
  * Returns:
  *      none
  */
    void command(){
      commands++;         
    } 

/**
  * Public void: setParams
  * 
  * Description:
  *    function to take in input from the command line via argc argv  
  * 
  * Params:
  *      double   a
  *      double   b
  *      double   c
  *      double   d
  * 
  * Returns:
  *      none
  */
    void setParams(double a, double b, double c, double d){
      fullThres = a;          
      emptyThres = b;
      growRat = c;
      shrinkRat = d;
    }

      
};


// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char* argv[]) {

    if(argc == 1){      //default argument count, (ex. pressing run on replit)
      cout << "Usage: program_name filename fullThres emptyThres growRat shrinkRat" << endl; 
    }
    else{
      int x = 0;
      ifstream infile;
      infile.open(argv[1]);       //second argument = filename
      ArrayStack stack;
      stack.setParams(stod(argv[2]), stod(argv[3]), stod(argv[4]), stod(argv[5]));

      while(infile >> x){ 
        if(x%2 == 0){
        stack.command();          //every even number gets pushed
        stack.Push(x);
        }
        else{
        stack.command();          //every odd number makes an even number
        stack.Pop();              //be popped.
        }      
      }
      stack.Print();
      return 0;
    }   
}

//./main num2.dat 0.85 0.15 2.0 0.5