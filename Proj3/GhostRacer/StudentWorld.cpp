//Kratik Agrawal
//Proj 3

#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <sstream>
#include <iomanip>
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
void StudentWorld::addWaterProjectile(double startX, double startY, int direction) {
    actors.push_back(new HolyWaterProjectile(this, startX, startY, direction));
}
void StudentWorld::currLaneLeftRight(int lane, double &left, double &right){
    if(lane == 0){
        left = LEFT_EDGE_BORDER;
        right = WHITE_X_LEFT_VAL;
        return;
    }
    if(lane == 1){
        left = WHITE_X_LEFT_VAL;
        right = WHITE_X_RIGHT_VAL;
    }
    if(lane == 2){
        left = WHITE_X_RIGHT_VAL;
        right = RIGHT_EDGE_BORDER;
    }
}

GhostRacer* StudentWorld::overlapGhostRacer(Actor* a){
    double deltaX = abs(a->getX() - m_ghostRacer->getX());
    double deltaY = abs(a->getY() - m_ghostRacer->getY());
    double sumRadius = a->getRadius() + m_ghostRacer->getRadius();
    if(deltaX < sumRadius*.25 && deltaY < sumRadius*0.6)
        return m_ghostRacer;
    return nullptr;
}


int StudentWorld::init()
{
    soulsSaved = 0;
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
    if(soulsSaved == (getLevel()*2 +5))
        return GWSTATUS_FINISHED_LEVEL;
    if(!m_ghostRacer->getAlive())
        return GWSTATUS_PLAYER_DIED;
    
    
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
    
    //Add Holy Water Goodies
    int chanceHolyWater = 100 + 10 * getLevel();
    if(randInt(0, chanceHolyWater-1) == 0){
        actors.push_back(new HolyWaterGoodie(this, randInt(LEFT_EDGE_BORDER+SPRITE_WIDTH, RIGHT_EDGE_BORDER-SPRITE_WIDTH), VIEW_HEIGHT));
    }
    
    //Add Soul Goodies
    int chanceSoulGoodie = 100;
    if(randInt(0, chanceSoulGoodie-1) == 0){
        actors.push_back(new SoulGoodie(this, randInt(LEFT_EDGE_BORDER+SPRITE_WIDTH, RIGHT_EDGE_BORDER-SPRITE_WIDTH), VIEW_HEIGHT));
    }
    
    //Add Oil Slicks
    int chanceOilSlick = max(150 - getLevel()*40, 40);
    if(randInt(0, chanceOilSlick-1) == 0){
        actors.push_back(new OilSlick(this, randInt(LEFT_EDGE_BORDER+SPRITE_WIDTH, RIGHT_EDGE_BORDER-SPRITE_WIDTH), VIEW_HEIGHT));
    }
    
    int chanceZombieCab = max(100 - getLevel()*10, 20);
    if(randInt(0, chanceZombieCab-1) == 0){
        int currLane = randInt(0, 2);
        double yClosestToBottom = VIEW_HEIGHT+1;
        double yClosestToTop = -1;
        int cabY = 0;
        int cabYSpeed = 0;
        bool viableFound = false;
        for(int i = 0; i < 3; i++){
            double left;
            double right;
            currLaneLeftRight(currLane, left, right);
            if(m_ghostRacer->getX() >= left && m_ghostRacer->getX()<=right){
                if(m_ghostRacer->getY() < yClosestToBottom)
                    yClosestToBottom = m_ghostRacer->getY();
                if(m_ghostRacer->getY() > yClosestToTop)
                    yClosestToTop = m_ghostRacer->getY();
            }
                
            for(int i = 0; i < actors.size(); i++){
                if(actors[i]->isCollisionAvoidanceWorthy() && actors[i]->getX() >= left && actors[i]->getX() <= right){
                    if(actors[i]->getY() < yClosestToBottom)
                        yClosestToBottom = actors[i]->getY();
                    if(actors[i]->getY() > yClosestToTop)
                        yClosestToTop = actors[i]->getY();
                }
            }
            if(yClosestToBottom == VIEW_HEIGHT+1 || yClosestToBottom > VIEW_HEIGHT/3){
                cabY = SPRITE_HEIGHT/2;
                cabYSpeed = getGhostRacer()->ySpeed() + randInt(2,4);
                viableFound = true;
                break;
            } else if(yClosestToTop == -1 || yClosestToTop < VIEW_HEIGHT*2.0/3){
                cabY = VIEW_HEIGHT - SPRITE_HEIGHT/2;
                cabYSpeed = getGhostRacer()->ySpeed() - randInt(2,4);
                viableFound = true;
                break;
            } else{
                currLane = (currLane+1)%3;
                yClosestToBottom = VIEW_HEIGHT+1;
                yClosestToTop = -1;
            }
        }
        if(viableFound){
            int cabX = ROAD_CENTER;
            if(currLane == 0)
                cabX -= ROAD_WIDTH/3;
            else if(currLane == 2)
                cabX += ROAD_WIDTH/3;
            actors.push_back(new ZombieCab(this, cabX, cabY, cabYSpeed));
        }
        
       
    }
    
    ostringstream oss;
    oss << "Score: " << setw(3) << getScore();
    oss << " Lvl: " << setw(2) << getLevel();
    oss << " Souls2Save: " << setw(3) << (getLevel()*2 +5) - soulsSaved;
    oss << " Lives: " << setw(3) << getLives();
    oss << " Health: " << setw(4) << m_ghostRacer->getHealth();
    oss << " Sprays: " << setw(3) << m_ghostRacer->getSprays();
    oss << " Bonus: " << setw(4) << "5000";

    string s = oss.str();
    setGameStatText(s);
    
    
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
