//
//  Game.h
//  Proj1
//
//  Created by Kratik Agrawal on 1/8/21.
//

#ifndef Game_h
#define Game_h

class City;

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();

        // Mutators
    void play();

  private:
    City* m_city;
};


#endif /* Game_h */
