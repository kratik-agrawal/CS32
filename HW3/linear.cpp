//
//  linear.cpp
//  HW3
//
//  Created by Kratik Agrawal on 2/4/21.
//

#include <stdio.h>
#include <array>
#include <iostream>
#include <cassert>


using namespace std;

bool somePredicate(double x)
{
    return x > 10.421;
}

// Return true if the somePredicate function returns true for at
// least one of the array elements, false otherwise.
bool anyTrue(const double a[], int n)
{
    if(n <= 0) return false;
    if(n == 1)
        return somePredicate(a[0]);

    if(somePredicate(a[n-1]) || anyTrue(a, n-1) )
        return true;

    return false;
}

// Return the number of elements in the array for which the
// somePredicate function returns true.
int countTrue(const double a[], int n)
{
    if(n <= 0)
        return 0;

    int count = 0;
    if(somePredicate(a[n-1]))
        count++;

    return count + countTrue(a, n-1);

}

// Return the subscript of the first element in the array for which
// the somePredicate function returns true.  If there is no such
// element, return -1.
int firstTrue(const double a[], int n)
{
    if(n <= 0)
        return -1;
    if(somePredicate(a[0])) return 0;
    int first = firstTrue(a+1, n-1);

    if(first == -1)
        return -1;
    else
        return first+1;



}

// Return the subscript of the largest element in the array (i.e.,
// return the smallest subscript m such that a[m] >= a[k] for all
// k from 0 to n-1).  If the function is told to examine no
// elements, return -1.
int positionOfMax(const double a[], int n)
{
    if(n <= 0)
        return -1;
    if(n == 1)
        return 0;
    int maxIndex = positionOfMax(a+1,n-1) + 1;
    if(a[0] > a[maxIndex])
        return 0;
    else
        return maxIndex;

}

// If all n1 elements of a1 appear in the n2 element array a2, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 is not a
// not-necessarily-contiguous subsequence of a2), return false.
// (Of course, if a1 is empty (i.e., n1 is 0), return true.)
// For example, if a2 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a1 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a1 is
//    50 30 20
// or
//    10 20 20
bool isIn(const double a1[], int n1, const double a2[], int n2)
{
    if(n1 <= 0)
        return true;
    if(n2 < n1)
        return false;
    if(a1[0] == a2[0])
        return isIn(a1 + 1, n1 -1, a2 + 1, n2 - 1);
    else
        return isIn(a1, n1, a2 + 1, n2 - 1);
}

int main(){

    const double a[] = {1.1, 2.2, 3.3, 5.5, 9.9, 11.2, 1.2};
    int n = 7;
    assert(anyTrue(a, n));
    assert(countTrue(a,n) == 1);
    assert(firstTrue(a, n) == 5);
    assert(positionOfMax(a, n) == 5);

    const double b[] = {1.1, 2.2, 3.3, 5.5, 9.9, 11.2, 12.2};
    assert(anyTrue(b, n));
    assert(countTrue(b,n) == 2);
    assert(firstTrue(b, n) == 5);
    assert(positionOfMax(b, n) == 6);

    const double c[] = {1.1, 2.2, 3.3, 5.5, 9.9, 10.2, 12.2};
    n = 7;
    assert(anyTrue(c, n));
    assert(countTrue(c,n) == 1);
    assert(firstTrue(c, n) == 6);
    assert(positionOfMax(c, n) == 6);

    const double d[] = {12.1, 2.2, 3.3, 5.5, 9.9, 10.2, 1.2};
    n = 7;
    assert(anyTrue(d, n));
    assert(countTrue(d,n) == 1);
    assert(anyTrue(d, n));
    assert(countTrue(d,n) == 1);
    assert(firstTrue(d, n) == 0);
    assert(positionOfMax(d, n) == 0);

    const double e[] = {1.1, 2.2, 3.3, 5.5, 9.9, 10.2, 1.2};
    n = 7;
    assert(!anyTrue(e, n));
    assert(countTrue(e,n) == 0);
    assert(!anyTrue(e, n));
    assert(countTrue(e,n) == 0);
    assert(firstTrue(e, n) == -1);
    assert(positionOfMax(e, n) == 5);

    assert(!anyTrue(e, 0));
    assert(countTrue(e,0) ==0);
    assert(firstTrue(e, 0) == -1);

    const double f[] = {1.1, 1.1, 3.3, 5.5, 9.9, 10.2, 1.2};
    n = 2;

    assert(positionOfMax(f, 0) == -1);

    const double a1[] = { 10, 20, 60};
    const double a2[] = { 10, 30, 40, 50, 20, 30};
    int n1 = 3;
    int n2 = 6;
    assert(!isIn(a1, n1, a2, n2));
    assert(isIn(a1, 0, a2, n2));
    assert(!isIn(a1, 2, a2, 2));
    assert(isIn(a1, -5, a2, n2));
    assert(!isIn(a1, 10, a2, 2));
    assert(!isIn(a1, n1, a2, n2));
    assert(!isIn(a1, n1, a2, 3));


//    cout << "all passed" << endl;
}
