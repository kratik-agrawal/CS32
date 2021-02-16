//
//  testnewSequence.cpp
//  Proj2
//
//  Created by Kratik Agrawal on 1/18/21.
//

#include <stdio.h>


#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence a(10);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 55;
    
    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(k) != -1);
    for (int k = 0; k < 15; k++)
        assert(c.insert(k) != -1);
    for (int k = 0; k < 10; k++)
        assert(a.insert(k) != -1);
    
    // Failure if we try to insert a sixth item into b
    assert(b.insert(v) == -1);
    assert(a.insert(v) == -1);
    assert(c.insert(v) != -1);
    
    assert(b.find(1) == 1);
    assert(a.find(2) == 2);
    assert(c.find(55) != -1);
    assert(!a.set(10,2));
    assert(a.set(9,2)== true);
    Sequence d(a);
    a.dump();
    d.dump();
    
    d= b;
    b.dump();
    d.dump();
    
    
    a.dump();
    b.dump();
    c.dump();
    
    // When two Sequences' contents are swapped, their capacities are
    // swapped as well:
    a.swap(b);
    a.dump();
    b.dump();
    c.dump();
    d.dump();
    cout<< "passed" << endl;
}

