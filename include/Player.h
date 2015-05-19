#ifndef __PLAYER_H_
#define __PLAYER_H_

#include "AdBase.h"

//-----------------------------------------------------------------------------
class Player {
private:
	static int m_iHealth;
	static int m_iHunger;
	static int m_iThirst;

public:
	static int m_iCogs;
	static int m_iLenses;
	static int m_iSprings;
	static int m_iTorches;
	static int m_iWrenches;
	static int m_iDrillBits;

public:
	static int m_iElementalType;

public:
	static SDL_Point m_pntPosition;

public:
	static int Health(void) {return m_iHealth;}
	static int Hunger(void) {return m_iHunger;}
	static int Thirst(void) {return m_iThirst;}

	static void DamageHealth(void) {if(m_iHealth>0) m_iHealth--;}
	static void DamageHunger(void) {if(m_iHunger>0) m_iHunger--;}
	static void DamageThirst(void) {if(m_iThirst>0) m_iThirst--;}

	static void RestoreHealth(void) {if(m_iHealth<=11) m_iHealth++;}
	static void RestoreHunger(void) {if(m_iHunger<= 6) m_iHunger++;}
	static void RestoreThirst(void) {if(m_iThirst<= 6) m_iThirst++;}

public:
	static void Update(void);
	static void Render(SDL_Point pntOffset);
};

#endif
