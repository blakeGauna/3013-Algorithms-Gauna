/*****************************************************************************
*                    
*  Author:           Blake Gauna
*  Label:            PO2
*  Title:            Processing in Linear Time
*  Course:           CMPS 3013
*  Semester:         Spring 2022
* 
*  Description:
*        This program reads in over 120000 words from a dictionary
*        file using a linked list, and allows you to search through
*        it linearlly. It compairs the string the user enters from the
*        getch() function to the words in the linked list.
*          
*  Usage: 
*      - Enter one letter in at a time (First letter usually takes 35 seconds) 
*      - Enter Capital Z to exit
*      
*  Files:            
*       main.cpp       : driver program 
*       mygetch.hpp    : header file with getch() function
*       timer.hpp      : timer implementation
*       dictionary.txt : .txt file with a lot of words
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include "mygetch.hpp"
#include <vector>
#include "timer.hpp"

using namespace std;

/**
 * wordNode
 * 
 * Description:
 *
 *      This struct creates wordNodes to store our words from
 *      our file in, as well as a pointer that defaults to nullptr.
 * 
 * Public Methods:
 *
 *       wordNode(string d)               //Constructors
 *       wordNode(string d, wordNode* n)        
 * 
 * Usage: 
 * 
 *      wordNode name = new wordNode(string)           
 *      
 */
struct wordNode{
public:
    wordNode(string d){                   //"default" constructor
      data = d;
      next = nullptr;
    }
    wordNode(string d, wordNode* n){     //prepend constructor
      data = d;
      next = n;
}
    string data;
    wordNode* next;
    
};

/**
 * LList
 * 
 * Description:
 *
 *      Simple linked list 
 * 
 * Public Methods:
 *                LList()                               
 *                ~LList()
 *      void      prepend(string)
 *      void      append(string)
 *      void      remove(string searchKey)
 *      void      print()
 *      void      Total()
 *      void      Compare()
 *
 * Usage: 
 * 
 *     LList list;
 *     //function
 *
 */
class LList{
  private:
    wordNode* head;
    int size = 0;
    
  
  public:
    int count = 0;
    vector<string> list;              //holds words that match key
    int totalWords = 0;
  
  /**
     * Public : LList
     * 
     * Description:
     *      make head nullptr (constructor)
     *  
     */
  LList(){                            
    head = nullptr;
  }

  /**
     * Public : ~LList
     * 
     * Description:
     *      deletes list (destructor)
     * 
     */ 
 ~LList(){                            
    wordNode* travel = head;
    while(travel != nullptr){
        wordNode* tempnode = travel;
        travel = travel->next;
        delete tempnode;
    }                                 
    head = nullptr;
  }

  /**
     * Public : prepend
     * 
     * Description:
     *      Creates a wordNode at the beginning of the list.
     * 
     * Params:
     *      string   data
     * 
     * Returns:
     *      None
     */
 void prepend(string data){           //prepend
    // // Create a new node
    wordNode* N = new wordNode(data);
    // // Store the passed in value into the node
    N->data = data;
    // // The new node should point to head
    N->next = head;

    // Node* N = new Node(val, head);
    // // Update head
    // head = N;

    head = new wordNode(data, head);
}

  /**
     * Public : append
     * 
     * Description:
     *      Creates a wordNode at the end of the list.
     * 
     * Params:
     *      string   data
     * 
     * Returns:
     *      None
     */  
  void append(string data){           //append
    if(head == nullptr){
        head = new wordNode(data);    //if empty, make head
        return;
    }else{
        wordNode* travel = head;
        while(travel->next != nullptr){
            travel = travel->next;
        } // Goes until travel is the last item
        // Create a new node at the end
        travel->next = new wordNode(data);
        return;
    }
  }
  /**
     * Public : remove
     * 
     * Description:
     *      Removes a wordNode from the list.
     * 
     * Params:
     *      string   searchKey
     * 
     * Returns:
     *      None
     */ 
  void remove(string searchKey){       //remove
    if(head != nullptr && head->data == searchKey){
        wordNode* deleteMe = head;
        head = head->next;
        delete deleteMe;
        return;
    }else{
        wordNode* travel = head; // Traverses the list
        wordNode* trail = nullptr; // Stays one node back
        while(travel != nullptr){
            if(travel->data == searchKey){
                trail->next = travel->next;
                delete travel;
                return;
            }
            trail = travel;
            travel = travel->next;
        }
        cout << "Item '" << searchKey << "' cannot be removed because it is not in the list!\n";
    }
  }

  /**
     * Public : print
     * 
     * Description:
     *      Prints List
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      None
     */
  void print(){ 
    cout << endl << "Top 10 words: (Type Capital Z to stop)" << "\n\n";
    if(count >= 10){                    //10 or more words
      for(int i = 0; i < 10; i++){
        cout << list[i] << " ";
    }
    }
    else if (count < 10)                //less that 10 words
    {
      for(int i = 0; i < count; i++){
        cout << list[i] << " ";    
      }  
    }
    cout << "\n\nTotal words found: " << count;
  }

  /**
     * Public : Compare
     * 
     * Description:
     *      Runs getch to get character from console, compares
     *      it to the words in the linked list, then calls function
     *      to print.  
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      None
     */
  void Compare(){
    Timer T2;
    char c;
    string key;
    wordNode* travel = head;
    
    while(c != 'Z'){               //if c = Z, then it stops
      cout << endl;
      c = getch();
      auto start = chrono::steady_clock::now();
      if(c == 8){                  //trying to make backspace work
        key.pop_back(); 
        cout << key << endl;      
      while(travel != nullptr){    
        if(travel->data.substr(0,key.length()) == key.substr(0,key.length())){
          list.push_back(travel->data); //compares the substring from 
          count++;                      //the 0th pos to key length    
          travel = travel->next;
        }
        else 
          travel = travel->next;
        
      }
      }
      else{
      key.push_back(c);
      cout <<"Word: "<< key << endl;
      
      while(travel != nullptr){
        if(travel->data.substr(0,key.length()) == key.substr(0,key.length())){
          list.push_back(travel->data); //compares the substring from  
          count++;                      //the 0th pos to key length    
          travel = travel->next;
        }
        else 
          travel = travel->next;
        
      }
      }
      auto end = chrono::steady_clock::now();
      cout << endl;
      print();
      cout << endl;
      count = 0;
      cout << "Elapsed time in milliseconds: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " ms" << "\n\n"; 
      list.clear();
      travel = head;
      
      
    }
  }
};

int main(){
  LList list;
  string keyword;
  ifstream infile;
  char c;
  Timer T;
  auto start = chrono::steady_clock::now();
  infile.open("dictionary.txt");
  while(infile >> keyword){
    list.append(keyword);
  }
  auto end = chrono::steady_clock::now();
  cout << "Elapsed time in seconds to load linked list: " << chrono::duration_cast<chrono::seconds>(end - start).count()
         << " sec" << "\n\n";
  list.Compare();
    
  return 0;
}