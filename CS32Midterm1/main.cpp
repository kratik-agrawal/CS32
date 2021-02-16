//
//  main.cpp
//  CS32Midterm1
//
//  Created by Kratik Agrawal on 1/28/21.
//

#include <iostream>
#include <cassert>
using namespace std;

class StringList
{
  public:
    StringList();
    ~StringList();
    // You may declare other member functions for your test code to call
    void eraseEvens();
    void insert(char value);
    void dump();
  private:
    struct Node
    {
      char  value;
      Node* next;
    };
    Node* head;  // points to first Node in the list
};

StringList::StringList()
{
  head = nullptr;
}
StringList::~StringList(){
    Node* p;
    p = head;
    while(p != nullptr){
        Node* n = p->next;
        delete p;
        p = n;
    }
}
// You may implement other member functions here for test purposes,
// but you will not turn them in as part of your submission.

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT AFTER THE END OF THE eraseEvens IMPLEMENTATION

//void StringList::eraseEvens(){
//    if(head == nullptr || head->next == nullptr)
//        return;
//    Node* curr = head;
//    while(curr->next != nullptr){
//        if(curr->next != nullptr){
//            Node* temp = curr->next;
//            curr->next = curr->next->next;
//            delete temp;
//        }
//        if(curr->next != nullptr)
//            curr = curr->next;
//    }
//}
void StringList::eraseEvens()
{
    Node* p = head;
    int size = 0;
    while(p!= nullptr)
    {
        size++;
        if(p->next == nullptr)
        {
            break;
        }
        p = p->next;
    }
        
    
    if(size < 2)
    {
        return;
    }
    int i;
    for(i = 0, p = head; p->next != nullptr;)
    {
        if(i%2 == 1)
        {
            Node* temp = p->next;
            if(temp->next == nullptr)
            {
                delete temp;
                p->next = nullptr;
                return;
            }
            p->next = temp->next;
            delete temp;
            p = p->next;
            i++;
        }
        else
        {
            i++;
        }
    }

}
void StringList::insert(char value){
    Node* newNode = new Node;
    newNode->value = value;
    if(head == nullptr){
        head = newNode;
        head->next = nullptr;
        return;
    }
    Node* curr = head;
    while(curr->next != nullptr){
        curr = curr->next;
    }
    curr->next = newNode;
    newNode->next = nullptr;

}
void StringList::dump(){
    Node* temp = head;
    while(temp != nullptr){
        cerr << temp->value << ", ";
        temp = temp->next;
    }

    cerr << endl;
}

// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
// COMMENT BEFORE THE START OF THE eraseEvens IMPLEMENTATION

int main()
{
  // You may put some code here for test purposes
    StringList s;
    s.insert('k');
    s.insert('r');
    s.insert('a');
    s.insert('t');
    s.insert('i');
    s.insert('k');
    s.insert('z');
    s.insert('v');
    s.dump();
    s.eraseEvens();
    s.dump();
    StringList a;
    
    
    
    a.dump();
    a.eraseEvens();
    a.dump();

  cout << "All tests succeeded" << endl;
}

//
//
//#include <iostream>
//#include <cassert>
//using namespace std;
//
//class Num
//{
//  public:
//    Num(int i) : m_i(i) {}
//    int geti() const { return m_i; }
//  private:
//    int m_i;
//};
//
//class Blah
//{
//  public:
//    Blah(int i);
//    ~Blah();
//    int getii(){
//        return m_ii;
//    }
//    int* geteyes(){
//        return m_eyes;
//    }
//    Blah(const Blah& other);
//  private:
//    Num* m_num;
//    int m_ii;
//    int* m_eyes;
//};
//
//Blah::Blah(int i)
//{
//  m_num = new Num(i);
//  m_ii = 2 * i;
//  m_eyes = &m_ii;
//}
//
//// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
//// COMMENT AFTER THE END OF THE DESTRUCTOR AND COPY CONSTRUCTOR
//// IMPLEMENTATIONS
//
//Blah::~Blah(){
//    delete m_num;
//}
//
//Blah::Blah(const Blah& other){
//    m_num = new Num(other.m_num->geti());
//    m_ii = other.m_ii;
//    m_eyes = &m_ii;
//}
//
//// SUBMIT AS YOUR ANSWER ONLY THE CODE BETWEEN THIS COMMENT AND THE
//// COMMENT BEFORE THE START OF THE DESTRUCTOR AND COPY CONSTRUCTOR
//// IMPLEMENTATIONS
//
//void test()
//{
//  Blah b1(3);
//    cout << b1.getii() << endl;
//    cout << b1.geteyes() << " " << *(b1.geteyes())<< endl;
//  Blah b2(b1);
//    cout << b2.getii() << endl;
//    cout << b2.geteyes() << " " << *(b2.geteyes()) << endl;
//    Blah b3(9);
//    cout << b3.getii() << endl;
//    cout << b3.geteyes() << " " << *(b3.geteyes()) << endl;
//    Blah b4(b3);
//    cout << b4.getii() << endl;
//    cout << b4.geteyes() << " " << *(b4.geteyes()) << endl;
//
//}
//
//int main()
//{
//  test();
//  cout << "All tests succeeded" << endl;
//}
