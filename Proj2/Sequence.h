//
//  Sequence.h
//  Proj2
//
//  Created by Kratik Agrawal on 1/21/21.
//


#ifndef Sequence_h
#define Sequence_h

#include <string>
#include "OurType.h"

using ItemType = OurType;



class Sequence
{
  public:
    Sequence();//default constructor
    ~Sequence(); //destructor
    Sequence(const Sequence& copy); //constructor to create sequence based off different sequence
    Sequence& operator=(const Sequence& other); //operator to copy one sequence into other
    
    bool empty() const; //Method to see if empty
    int size() const; //method to return size
    int insert(int pos, const ItemType& value); //inserts item at certain position
    int insert(const ItemType& value); //inserts item based off sorted value
    bool erase(int pos); //erases item as pos
    int remove(const ItemType& value); //removes all occurrences of value
    bool get(int pos, ItemType& value) const; //gets the value at item pos and stores in reference
    bool set(int pos, const ItemType& value); //sets value at given pos
    int find(const ItemType& value) const; //finds pos of value given
    void swap(Sequence& other); //swaps two sequences
    
    void dump() const;
    
private:
    struct ListNode { //ListNode struct
        ListNode* prev;
        ListNode* next;
        ItemType val;
    };
    ListNode* head;
    int m_numItems;
};


int subsequence(const Sequence& seq1, const Sequence& seq2); //finds and returns starting index of seq2 in seq1
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result); //alternately inserts items into result


#endif /* Sequence_h */
