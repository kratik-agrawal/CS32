//
//  newSequence.cpp
//  Proj2
//
//  Created by Kratik Agrawal on 1/18/21.
//

#include <stdio.h>
#include <iostream>
#include "newSequence.h"

Sequence::Sequence():
m_numItems(0)
{
    m_seq = new ItemType[DEFAULT_MAX_ITEMS];
    m_maxSize = DEFAULT_MAX_ITEMS;
}

Sequence::Sequence(int size):
m_numItems(0)
{
    m_seq = new ItemType[size];
    m_maxSize = size;
}

Sequence::~Sequence(){
    delete [] m_seq;
}

Sequence::Sequence(const Sequence& copy){
    m_maxSize = copy.m_maxSize;
    m_numItems = copy.m_numItems;
    m_seq = new ItemType[m_maxSize];
    
    for(int i = 0; i < m_numItems;i++){
        m_seq[i] = copy.m_seq[i];
    }
}

Sequence& Sequence::operator=(const Sequence& other){
    if(this != &other){
        delete [] m_seq;
        m_maxSize = other.m_maxSize;
        m_numItems = other.m_numItems;
        m_seq = new ItemType[m_maxSize];
        for(int i = 0; i < m_numItems;i++){
            m_seq[i] = other.m_seq[i];
        }
    }
    return *this;
}

bool Sequence::empty() const{
    return m_numItems == 0;
}

int Sequence::size() const{
    return m_numItems;
}

int Sequence::insert(int pos, const ItemType& value){
    if(pos < 0 || pos > m_numItems){
        return -1;
    }
    if(m_numItems >= m_maxSize){
        return -1;
    }
    for(int i = m_numItems; i >pos;i--){
        m_seq[i] = m_seq[i-1];
    }
    m_seq[pos] = value;
    m_numItems++;
    return pos;
}

int Sequence::insert(const ItemType& value){
    if(m_numItems >= m_maxSize){
        return -1;
    }
    int i = 0;
    for(i =0; i < m_numItems; i++){
        if(value <= m_seq[i]){
            break;
        }
    }
    if(insert(i, value) != -1){
        return i;
    }
    
    return -1;
}

bool Sequence::erase(int pos){
    if(pos < 0 || pos >= m_numItems){
        return false;
    }
    for(int i = pos; i < m_numItems-1; i++){
        m_seq[i] = m_seq[i+1];
    }
    m_numItems--;
    return true;
    
}

int Sequence::remove(const ItemType& value){
    int cnt = 0;
    int i = 0;
    while(i < m_numItems){
        if(m_seq[i] == value){
            cnt++;
            erase(i);
        }else{
            i++;
        }
    }
    return cnt;
    
}

bool Sequence::get(int pos , ItemType& value) const{
    if(pos < 0 || pos >= m_numItems){
        return false;
    }
    value = m_seq[pos];
    
    return true;
}

bool Sequence::set(int pos, const ItemType& value){
    if(pos < 0 || pos >= m_numItems){
        return false;
    }
    m_seq[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const{
    for(int i = 0; i < m_numItems;i++){
        if(m_seq[i] == value){
            return i;
        }
    }
    return -1;
}

void Sequence::swap(Sequence& other){
    ItemType* tempSeq;
    tempSeq = m_seq;
    m_seq = other.m_seq;
    other.m_seq = tempSeq;
    
    int tempMax = m_maxSize;
    m_maxSize = other.m_maxSize;
    other.m_maxSize = tempMax;
    
    int tempNum = m_numItems;
    m_numItems = other.m_numItems;
    other.m_numItems = tempNum;
}

void Sequence::dump() const{
    for(int i = 0; i < size(); i++){
        std::cerr << m_seq[i] << ", ";
    }
    std::cerr << std::endl;
    std::cerr << "size " << m_numItems << std::endl;
    std::cerr << std::endl;
}

