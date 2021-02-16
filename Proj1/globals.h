//
//  globals.h
//  Proj1
//
//  Created by Kratik Agrawal on 1/8/21.
//

#ifndef globals_h
#define globals_h

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in a city
const int MAXCOLS = 30;               // max number of columns in a city
const int MAXFLATULANS = 120;         // max number of Flatulans allowed
const int INITIAL_PLAYER_HEALTH = 12;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

#endif /* globals_h */
