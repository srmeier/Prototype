#ifndef __ADLEVEL_H_
#define __ADLEVEL_H_

#include "AdBase.h"
#include "AdTiledManager.h"

//-----------------------------------------------------------------------------
class AdLevel {
protected:
	AdTiledManager m_objMap;
	SDL_Surface**  m_pLayers;
	char           m_pName[NAME_LENGTH];

	// TEMP
	int _x, _y;
	int _i, _j;
	int _moveframe;
	int _movedirec;
	bool _moving;
	bool _tomove;
	int _fmovedirec;
	bool _forceMove;

	bool _up;
	bool _down;
	bool _left;
	bool _right;
	bool _a, _b;

	bool _upc;
	bool _downc;
	bool _leftc;
	bool _rightc;
	bool _ac, _bc;

public:
	void Update(SDL_Event* sdlEvent);
	void Render(void);

public:
	void Load(const char* pName);
	void Unload(void);

public:
	AdLevel(void);
	~AdLevel(void);
};

#endif
