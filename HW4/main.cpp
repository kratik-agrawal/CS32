////
////  main.cpp
////  HW4
////
////  Created by Kratik Agrawal on 2/12/21.
////
//
//#include "Sequence.h"
//#include <iostream>
//#include <string>
//#include <cassert>
//using namespace std;
//
//void test()
//{
//    Sequence<int> si;
//    assert(si.empty());
//    assert(si.size() == 0);
//    assert(si.insert(0, 20) == 0);
//    assert(si.insert(10) == 0);
//    assert(si.find(20) == 1);
//    assert(si.remove(10) == 1);
//    int i;
//    assert(si.get(0, i));
//    assert(si.set(0, 30));
//    assert(si.erase(0));
//    Sequence<int> si2(si);
//    si2.swap(si);
//    si2 = si;
//    assert(subsequence(si,si) == -1);
//    interleave(si,si2,si);
//    
//    Sequence<string> ss;
//    assert(ss.empty());
//    assert(ss.size() == 0);
//    assert(ss.insert(0, "Hello") == 0);
//    assert(ss.insert("Goodbye") == 0);
//    assert(ss.find("Hello") == 1);
//    assert(ss.remove("Goodbye") == 1);
//    string s;
//    assert(ss.get(0, s));
//    assert(ss.set(0, "Aloha"));
//    assert(ss.erase(0));
//    Sequence<string> ss2(ss);
//    ss2.swap(ss);
//    ss2 = ss;
//    assert(subsequence(ss,ss2) == -1);
//    interleave(ss,ss2,ss);
//}
//
//int main()
//{
//    test();
//    cout << "Passed all tests" << endl;
//}
