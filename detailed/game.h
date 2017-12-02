#ifndef game_h
#define game_h

#include <stdio.h>
#include "player.h"
#include "game.h"
#include "arm.h"
#include "leg.h"
#include "HP.h"

class Game
{
    Player p1 {1};
    Player p2 {2};
	HP hp_bar; 
    // test 
protected:
	bool exit = false;
	bool timeout = false;
	bool ko = false; 
	int winner = 0;
	int lastDecade = 0;
	int lastUnit = 0;
public:
    void Run(void);
    void SetCharacter(int pn1, int pn2); // player No 1 and 2
	const bool isExit(void) const; // return exit flag 
	const bool isTimeout(void) const; // return timeout flag 
	const bool isKo(void) const; // return ko flag 
	void setExit(void); // set exit flag
	void setTimeout(void); // set timeout flag
	void setKo(void); // set ko flag
	void DrawHpBar(int hp1, int hp2);
	int getWinner(void);
	void End(void);
	void setLastDecade(int lastDecade);
	void setLastUnit(int lastUnit);
	int getLastDecade(void);
	int getLastUnit(void);
};

#endif
