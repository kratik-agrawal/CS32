//
//  ScoreList.cpp
//  Proj2
//
//  Created by Kratik Agrawal on 1/17/21.
//

#include <stdio.h>
#include "ScoreList.h"

ScoreList::ScoreList(){
}

bool ScoreList::add(unsigned long score){
    if(score < 0 || score > 100){
        return false;
    }
    if(m_list.insert(score) != -1){
        return true;
    }
    return false;
}

bool ScoreList::remove(unsigned long score){
    int pos = m_list.find(score);
    return m_list.erase(pos);
}

int ScoreList::size() const{
    return m_list.size();
}

unsigned long ScoreList::minimum() const{
    if(m_list.size() == 0)
        return NO_SCORE;
    unsigned long min = 101;
    for(int i = 0; i < m_list.size();i++){
        unsigned long temp = 0;
        m_list.get(i, temp);
        if(temp < min){
            min = temp;
        }
    }
    
    return min;
}

unsigned long ScoreList::maximum() const{
    if(m_list.size() == 0)
        return NO_SCORE;
    unsigned long max = 0;
    for(int i = 0; i < m_list.size();i++){
        unsigned long temp = 0;
        m_list.get(i, temp);
        if(temp > max){
            max = temp;
        }
    }
    
    return max;
}

