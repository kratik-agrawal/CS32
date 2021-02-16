//
//  Sequence.cpp
//  Proj2
//
//  Created by Kratik Agrawal on 1/17/21.
//

#include <stdio.h>
#include <iostream>
#include "Sequence.h"


Sequence::Sequence():
m_seq(), m_numItems(0)
{
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
    if(m_numItems == DEFAULT_MAX_ITEMS){
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
    if(m_numItems >= DEFAULT_MAX_ITEMS){
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
    if(this != &other){
        int items;
        if(this->m_numItems > other.m_numItems)
            items = this->m_numItems;
        else
            items = other.m_numItems;
        
        for(int i = 0; i< items; i++){
            ItemType temp;
            this->get(i, temp);
            other.get(i, m_seq[i]);
            other.set(i, temp);
        }

        int tempItems = other.m_numItems;
        other.m_numItems = this->m_numItems;
        this->m_numItems = tempItems;
        
        
    }
}

void Sequence::dump() const{
    for(int i = 0; i < size(); i++){
        std::cerr << m_seq[i] << ", ";
    }
    std::cerr << std::endl;
    std::cerr << "size " << m_numItems << std::endl;
    std::cerr << std::endl;
}
