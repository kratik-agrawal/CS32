//
//  testSequence.cpp
//  Proj2
//
//  Created by Kratik Agrawal on 1/17/21.
//

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);

    assert(s.insert(42) == 0);
    assert(s.insert(42) == 0);
    assert(s.insert(42) == 0);
    s.dump();
    assert(s.insert(43) == 4);
    assert(s.insert(1) == 0);
    s.dump();
    assert(s.insert(5) == 1);
    assert(s.insert(5,2) == 5);
    s.dump();
    assert(s.size() == 8  &&  s.find(42) == 2);
    assert(s.remove(42) == 4);
    assert(s.size() == 4  &&  s.find(42) == -1);
    s.dump();
    assert(s.erase(1) == true);
    assert(s.size() == 3  &&  s.find(5) == -1);
    assert(s.find(43) == 2);
    
    
    cout << "Passed all tests" << endl;
}
