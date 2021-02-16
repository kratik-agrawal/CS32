//
//  Sequence.cpp
//  Proj2
//
//  Created by Kratik Agrawal on 1/21/21.
//

#include <stdio.h>
#include <iostream>
#include "Sequence.h"


Sequence::Sequence(): //default constructor
head(nullptr), m_numItems(0)
{
    
}
//destructor to clean memory leaks
Sequence::~Sequence(){
    
    if(head == nullptr) //if head is a nullptr simply return
        return;
    else if(head->next == nullptr) //if only one item delete head
        delete head;
    else{ //else iterate through rest of list and delete each node
        ListNode* temp = head;
        while(temp != nullptr){ //deletes each item in the linked list one by one
            ListNode* curr = temp->next;
            delete temp;
            temp = curr;
            
        }
    }
}

//copy constructor
Sequence::Sequence(const Sequence& copy){
    head = nullptr;
    m_numItems = copy.m_numItems;//copys number of items
    if(m_numItems == 0){
        return;
    }
    head = new ListNode; //assign head to a new head
    head->prev = nullptr;
    
    ListNode* n = head;
    ListNode* otherNode = copy.head; //copies heads
    
    while(otherNode->next != nullptr){ //copies each item in the linked list to create a new one
        ListNode* temp = new ListNode;
        n->val = otherNode->val;
        n->next = temp;
        temp->prev = n;
        
        n = n->next;
        otherNode = otherNode->next;
    }
    n->val = otherNode->val;
    n->next = nullptr; //sets next pointer to nullptr
    
    
}
//Operator = method
Sequence& Sequence::operator=(const Sequence& other){
    if(this != &other){ //don't do anything if same list
        Sequence temp(other); //else use swap method to complete the switch
        swap(temp);
    }
    return *this; //returns reference to itself
}

//method to see if empty
bool Sequence::empty() const{
    return m_numItems == 0;
}

//method that returns size
int Sequence::size() const{
    return m_numItems;
}

//inserts value at given pos
int Sequence::insert(int pos, const ItemType& value){
    
    if(pos < 0 || pos > m_numItems){ //if invalid pos, returns -1
        return -1;
    }
    
    //creates a new listnode with value which will be inserted
    ListNode* n = new ListNode;
    n->val = value;
    
    //if items is 0, then we update head
    if(m_numItems == 0){
        n->next = nullptr;
        n->prev = nullptr;
        head = n;
        m_numItems++;
        return 0;
    }
    
    //if we are adding to the beginning of the list we need to take care of head
    if(pos == 0){
        n->next = head;
        n->prev = nullptr;
        head->prev = n;
        head = n;
        m_numItems++;
        return 0;
    }
    
    //create a temp pointer to iterate through list until we reach the item where we want to insert
    ListNode* tempHead = head;
    for(int i = 0; i < pos-1;i++){
        if(tempHead->next != nullptr)
            tempHead = tempHead->next;
    }
    
    //if its the last item we need to adjust only the tempHead
    if(pos == m_numItems){
        n->next = nullptr;
        n->prev = tempHead;
        tempHead->next = n;
        m_numItems++;
        return pos;
    }
    //else if in the middle we add to it and adjust both next and prev pointers
    n->next = tempHead->next;
    n->prev = tempHead;
    if(tempHead->next != nullptr) //have to check its not null so we can accest next->prev
        tempHead->next->prev = n;
    tempHead->next = n;
    m_numItems++;
    return pos;
    
    
}

//inserts item in order
int Sequence::insert(const ItemType& value){
    
    
    //if no items, the new item will be the head
    if(m_numItems == 0){
        return insert(0,value);
    }
    //Create node for iteration and int to keep track of position
    ListNode* temp = head;
    int i = 0;
    
    while(temp->next != nullptr){
        if(value <= temp->val){
            return insert(i, value);
        }
        i++;
        temp = temp->next;
    }
    if(value <= temp->val){
        return insert(i, value);
    }
    return insert(m_numItems, value);
    
}

//erases item at given pos
bool Sequence::erase(int pos){
    if(pos < 0 || pos >= m_numItems){//checks if given pos is valid
        return false;
    }
    if(m_numItems == 1){//if only one item, the list becomes emoty
        ListNode* n = head;
        delete n;
        head = nullptr;
        m_numItems--;
        return true;
    }
    if(pos == 0){//if we deleting the first node we need to reassign head
        ListNode* n = head;
        head = head->next;
        head->prev = nullptr;
        delete n;
        m_numItems--;
        return true;
    }
    
    //create pointer to iterate and iterate to node that we want to erase
    ListNode* tempHead = head;
    for(int i = 0; i !=pos;i++){
        tempHead = tempHead->next;
    }
    if(tempHead->next == nullptr){//if its the last node we need to adjust previous
        tempHead->prev->next = nullptr;
        delete tempHead;
        m_numItems--;
        return true;
    }
    //else we have to adjust both previous and next
    tempHead->prev->next = tempHead->next;
    tempHead->next->prev = tempHead->prev;
    delete tempHead;
    m_numItems--;
    return true;
    
}

//removes all instances of given value
int Sequence::remove(const ItemType& value){
    int cnt = 0; //cnt value of how many instances value appears
    //create pointer and i to keep track of instances
    while(find(value) != -1){
        erase(find(value));
        cnt++;
    }
    return cnt; //return the count
}

//returns value at given pos
bool Sequence::get(int pos , ItemType& value) const{
    if(pos < 0 || pos >= m_numItems){ //checks if the pos is valid
        return false;
    }
    
    //create node to iterate through list until we get to pos
    ListNode* tempHead = head;
    for(int i = 0; i < pos;i++){
        tempHead = tempHead->next;
    }
    value = tempHead->val; //stores val in value and returns true
    return true;
}

//sets value at given pos
bool Sequence::set(int pos, const ItemType& value){
    if(pos < 0 || pos >= m_numItems){ //checks if valid position
        return false;
    }
    //create pointer to iterate through list until we get to item
    ListNode* tempHead = head;
    for(int i = 0; i <pos;i++){
        if(tempHead->next != nullptr)
            tempHead = tempHead->next;
        else
            break;
    }
    tempHead->val = value; //changes the value
    return true;
}

//finds the first occuruence of value in list
int Sequence::find(const ItemType& value) const{
    //create pointer to iterate through list
    ListNode* tempHead = head;
    for(int i = 0; i < m_numItems;i++){
        if(tempHead->val == value){//if item val is equal to one we are looking for return index
            return i;
        }
        tempHead = tempHead->next;
    }
    return -1; //else return -1
}

//function swaps two sequences
void Sequence::swap(Sequence& other){
    
    //swaps number of items
    int tempItems = other.m_numItems;
    other.m_numItems = this->m_numItems;
    this->m_numItems = tempItems;
    
    
    //swaps heads
    ListNode* tempHead = head;
    head = other.head;
    other.head = tempHead;
    
    
}

//function for testing purposes
void Sequence::dump() const{
    ListNode* temp = head;
    while(temp != nullptr){
        std::cerr << temp->val << ", ";
        temp = temp->next;
    }
    std::cerr << "size " << m_numItems << std::endl;
    std::cerr << std::endl;
    
}

//method checks if seq2 is in seq1
int subsequence(const Sequence& seq1, const Sequence& seq2){
    if(seq1.size() < seq2.size()) //if seq2 is bigger not possible
        return -1;
    if(seq1.size() == 0 || seq2.size() == 0) //edge case, they can't be empty
        return -1;
    
    ItemType x,y;
    
    
    for(int i = 0; i < seq1.size()-seq2.size()+1;i++){//nested for loops to iterate through all combos
        bool sub = true; //boolean to keep track if it is a sub-sequence
        for(int j = 0; j < seq2.size();j++){
            seq1.get(i+j,x);
            seq2.get(j,y);
            if(x != y){//if not the same, can't be subsequence to next iteration
                sub = false;
                break;
            }
        }
        if(sub)//if we get here it means that it is a sub and we return the first index or i
            return i;
    }
    
    return -1; //means we didnt find subsequence so we return -1
    
}

//method to go weave together two sequences
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result){
    Sequence r; //creates a sequence we will insert too
    int len = 0;
    if(seq1.size() >= seq2.size()) //we are getting the max length here
        len = seq1.size();
    else
        len = seq2.size();
    ItemType x;
    int i = 0;//this is for index to add too on r
    for(int j = 0; j < len; j++){ //to iterate through sequence
        if(seq1.get(j,x)){ //if list has item then we add or we skip
            r.insert(i, x);
            i++;
        }
        if(seq2.get(j,x)){//if list has item then we add or we skip
            r.insert(i, x);
            i++;
        }
    }
    result = r; //store r in result
    
}
