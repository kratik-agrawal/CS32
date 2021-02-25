//Kratik Agrawal
//Proj 3

#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <vector>

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp
const double LEFT_EDGE_BORDER = ROAD_CENTER - ROAD_WIDTH/2;
const double RIGHT_EDGE_BORDER = ROAD_CENTER + ROAD_WIDTH/2;
const double WHITE_X_LEFT_VAL = LEFT_EDGE_BORDER + ROAD_WIDTH/3;
const double WHITE_X_RIGHT_VAL = RIGHT_EDGE_BORDER - ROAD_WIDTH/3;

class StudentWorld : public GameWorld
{
    public:
        StudentWorld(std::string assetPath);
        ~StudentWorld();
        virtual int init();
        virtual int move();
        virtual void cleanUp();
        void addWaterProjectile(double startX, double startY, int direction);
        Actor* getGhostRacer() { return m_ghostRacer; }
        GhostRacer* overlapGhostRacer(Actor* a);
        void increaseSoulsSaved() { soulsSaved++; }
        void ghostRacerDies() { m_ghostRacer->setAlive(false);
            decLives();
        }

    private:
        GhostRacer* m_ghostRacer;
        std::vector<Actor*> actors;
        int lastBorderAddedWhite;
        void currLaneLeftRight(int lane, double &left, double &right);
        int soulsSaved;
};

#endif // STUDENTWORLD_H_
