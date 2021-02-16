//
//  testScoreList.cpp
//  Proj2
//
//  Created by Kratik Agrawal on 1/17/21.
//
//Check destructor, copy constructor, assignment operator


#include "ScoreList.h"
#include <iostream>
#include <cassert>

using namespace std;

int main()
{
    ScoreList s;
    
    
    assert(s.size() == 0);
    assert(s.add(42) == true);
    assert(s.add(420) == false);

    assert(s.remove(42) == true);
    assert(s.remove(43) == false);
    assert(s.size() == 0);
    assert(s.add(42) == true);
    assert(s.add(42) == true);
    assert(s.add(42) == true);
    assert(s.add(42) == true);
    assert(s.size() == 4);
    assert(s.remove(42) == true);
    assert(s.size() == 3);
    assert(s.add(99) == true);
    
    assert(s.maximum() == 99);
    assert(s.minimum() == 42);
    assert(s.add(100));
    assert(s.add(0));
    
    
    
    
    cout << "Passed all tests" << endl;
}
