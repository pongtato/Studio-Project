#ifndef _SCORE_H
#define _SCORE_H

#include "Framework\timer.h"
#include <fstream>
#include <string>
#include "game.h"
#include <sstream>
#include "common.h"

using std::ifstream;
using std::ofstream;
using std::string;
using std::ostringstream;
using std::endl;
extern GLOBAL combined;

void normalscore();
void Writetohighscore();
void print();
void playerShoot();

#endif // _SCORE_H