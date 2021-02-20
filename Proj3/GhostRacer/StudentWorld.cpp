//Kratik Agrawal
//Proj 3

#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    m_ghostRacer = nullptr;
    lastBorderAddedWhite = 0;
    actors.clear();
}

StudentWorld::~StudentWorld(){

    cleanUp();
}

int StudentWorld::init()
{
    m_ghostRacer = new GhostRacer(this);
    
    //Border Lines
    
    //Yellow Border Lines
    for(int i = 0; i < VIEW_HEIGHT/SPRITE_HEIGHT; i++){
        double YELLOW_Y_VAL = i*SPRITE_HEIGHT;
        actors.push_back(new BorderLine(this, IID_YELLOW_BORDER_LINE, LEFT_EDGE_BORDER, YELLOW_Y_VAL));
        actors.push_back(new BorderLine(this, IID_YELLOW_BORDER_LINE, RIGHT_EDGE_BORDER, YELLOW_Y_VAL));
    }
    
    //White BorderLines
    for(int i = 0; i < VIEW_HEIGHT/(4*SPRITE_HEIGHT); i++){
        double WHITE_Y_VAL = i*SPRITE_HEIGHT*4;
        lastBorderAddedWhite = WHITE_Y_VAL;
        actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, WHITE_X_LEFT_VAL, WHITE_Y_VAL));
        actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, WHITE_X_RIGHT_VAL, WHITE_Y_VAL));
    }
    
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    
    //Each actor has to do something
    m_ghostRacer->doSomething();
    for(int i = 0; i < actors.size(); i++){
        actors[i]->doSomething();
    }
    
    //we need to remove all dead actors
    vector<Actor*>::iterator it = actors.begin();
    for(; it != actors.end(); ){
        if(!(*it)->getAlive()){
            delete *it;
            it = actors.erase(it);
        }
        else
            it++;
    }
    
    //Check if we need to add new border lines
    lastBorderAddedWhite += (-4-getGhostRacer()->ySpeed());
    int newBorderY = VIEW_HEIGHT - SPRITE_HEIGHT;
    int deltaY = newBorderY - lastBorderAddedWhite;
    if(deltaY >= SPRITE_HEIGHT){
        actors.push_back(new BorderLine(this, IID_YELLOW_BORDER_LINE, LEFT_EDGE_BORDER, newBorderY));
        actors.push_back(new BorderLine(this, IID_YELLOW_BORDER_LINE, RIGHT_EDGE_BORDER, newBorderY));
        
    }
    if(deltaY >= (4*SPRITE_HEIGHT)){
        actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, WHITE_X_LEFT_VAL, newBorderY));
        actors.push_back(new BorderLine(this, IID_WHITE_BORDER_LINE, WHITE_X_RIGHT_VAL, newBorderY));
        lastBorderAddedWhite = newBorderY;
    }
    
    //Add Human Peds
    int chanceHumanPed = max(200 - getLevel() * 10, 30);
    if(randInt(0, chanceHumanPed-1) == 0){
        actors.push_back(new HumanPedestrian(this, randInt(0, VIEW_WIDTH), VIEW_HEIGHT));
    }
    //Add Zombie Peds
    int chanceZombiePed = max(100 - getLevel() * 10, 20);
    if(randInt(0, chanceZombiePed-1) == 0){
        actors.push_back(new ZombiePedestrian(this, randInt(0, VIEW_WIDTH), VIEW_HEIGHT));
    }
    
    
    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    if(m_ghostRacer != nullptr)
        delete m_ghostRacer;
    m_ghostRacer = nullptr;
    for(int i = 0; i < actors.size(); i++){
        delete actors[i];
    }
    actors.clear();
}
