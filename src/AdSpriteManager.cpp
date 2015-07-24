/*
*/

#include "AdBase.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
SDL_Surface** AdSpriteManager::s_pTiles;
int           AdSpriteManager::s_iNumTile;

int           AdSpriteManager::s_iSprWidth;
int           AdSpriteManager::s_iSprHeight;

//-----------------------------------------------------------------------------
bool AdSpriteManager::Init(int iWidth, int iHeight, const char* pFileName) {
	s_iSprWidth  = iWidth;
	s_iSprHeight = iHeight;

	SDL_Surface* surface = SDL_LoadBMP(pFileName);

	if(surface == NULL) {
		fprintf(stderr, SDL_GetError());
		return false;
	}

	s_iNumTile = (surface->w/s_iSprWidth)*(surface->h/s_iSprHeight)+1;
	s_pTiles   = (SDL_Surface**) malloc(s_iNumTile*sizeof(SDL_Surface*));

	int i, x, y;
	SDL_Rect rect = {0, 0, s_iSprWidth, s_iSprHeight};
	for(i=0; i<s_iNumTile; i++) {
		s_pTiles[i] = SDL_CreateRGBSurface(0, s_iSprWidth, s_iSprHeight, 24, 0x00, 0x00, 0x00, 0x00);
		if(i!=0) {
			x = (i-1)%(surface->w/s_iSprWidth);
			y = (i-x)/(surface->w/s_iSprWidth);
			rect.x = s_iSprWidth*x, rect.y = s_iSprHeight*y;
			SDL_BlitSurface(surface, &rect, s_pTiles[i], NULL);
		}
	}

	SDL_FreeSurface(surface);
	surface = NULL;

	return true;
}

//-----------------------------------------------------------------------------
void AdSpriteManager::Quit(void) {
	int i;
	for(i=0; i<s_iNumTile; i++) {
		SDL_FreeSurface(s_pTiles[i]);
		s_pTiles[i] = NULL;
	}

	free(s_pTiles);
	s_pTiles = NULL;
}

//-----------------------------------------------------------------------------
SDL_Surface* AdSpriteManager::BuildSprite(int iWidth, int iHeight, int pIndices[]) {
	SDL_Surface* pSprite = NULL;
	pSprite = SDL_CreateRGBSurface(
		0, s_iSprWidth*iWidth, s_iSprHeight*iHeight,
		24, 0x00, 0x00, 0x00, 0x00
	);

	SDL_SetColorKey(pSprite, 1, 0xFF00FF);
	SDL_FillRect(pSprite, 0, 0xFF00FF);

	int i, j;
	SDL_Rect rect = {0, 0, s_iSprWidth, s_iSprHeight};
	for(j=0; j<iHeight; j++) {
		for(i=0; i<iWidth; i++) {
			rect.x = s_iSprWidth*i, rect.y = s_iSprHeight*j;
			SDL_BlitSurface(s_pTiles[pIndices[iWidth*j+i]], NULL, pSprite, &rect);
		}
	}

	return pSprite;
}

//-----------------------------------------------------------------------------
SDL_Surface* AdSpriteManager::BuildSprite(const char* pString) {
	if(pString == NULL) return NULL;

	int iStrLen = (int) strlen(pString);

	SDL_Surface* pSprite = NULL;
	pSprite = SDL_CreateRGBSurface(
		0, s_iSprWidth*iStrLen, s_iSprHeight,
		24, 0x00, 0x00, 0x00, 0x00
	);

	SDL_SetColorKey(pSprite, 1, 0xFF00FF);
	SDL_FillRect(pSprite, 0, 0xFF00FF);

	int i;
	for(i=0; i<iStrLen; i++) {
		SDL_Rect rect = {0, 0, s_iSprWidth, s_iSprHeight};

		int iIndex = 0x00;
		if(pString[i]=='A') {
			iIndex = 0x01;
		} else if(pString[i]=='B') {
			iIndex = 0x02;
		} else if(pString[i]=='C') {
			iIndex = 0x03;
		} else if(pString[i]=='D') {
			iIndex = 0x04;
		} else if(pString[i]=='E') {
			iIndex = 0x05;
		} else if(pString[i]=='F') {
			iIndex = 0x06;
		} else if(pString[i]=='G') {
			iIndex = 0x07;
		} else if(pString[i]=='H') {
			iIndex = 0x08;
		} else if(pString[i]=='I') {
			iIndex = 0x09;
		} else if(pString[i]=='J') {
			iIndex = 0x0A;
		} else if(pString[i]=='K') {
			iIndex = 0x0B;
		} else if(pString[i]=='L') {
			iIndex = 0x0C;
		} else if(pString[i]=='M') {
			iIndex = 0x0D;
		} else if(pString[i]=='N') {
			iIndex = 0x0E;
		} else if(pString[i]=='O') {
			iIndex = 0x0F;
		} else if(pString[i]=='P') {
			iIndex = 0x10;
		} else if(pString[i]=='Q') {
			iIndex = 0x11;
		} else if(pString[i]=='R') {
			iIndex = 0x12;
		} else if(pString[i]=='S') {
			iIndex = 0x13;
		} else if(pString[i]=='T') {
			iIndex = 0x14;
		} else if(pString[i]=='U') {
			iIndex = 0x15;
		} else if(pString[i]=='V') {
			iIndex = 0x16;
		} else if(pString[i]=='W') {
			iIndex = 0x17;
		} else if(pString[i]=='X') {
			iIndex = 0x18;
		} else if(pString[i]=='Y') {
			iIndex = 0x19;
		} else if(pString[i]=='Z') {
			iIndex = 0x1A;
		} else if(pString[i]=='0') {
			iIndex = 0x1B;
		} else if(pString[i]=='1') {
			iIndex = 0x1C;
		} else if(pString[i]=='2') {
			iIndex = 0x1D;
		} else if(pString[i]=='3') {
			iIndex = 0x1E;
		} else if(pString[i]=='4') {
			iIndex = 0x1F;
		} else if(pString[i]=='5') {
			iIndex = 0x20;
		} else if(pString[i]=='6') {
			iIndex = 0x21;
		} else if(pString[i]=='7') {
			iIndex = 0x22;
		} else if(pString[i]=='8') {
			iIndex = 0x23;
		} else if(pString[i]=='9') {
			iIndex = 0x24;
		}

		rect.x = s_iSprWidth*i;
		SDL_BlitSurface(s_pTiles[iIndex], NULL, pSprite, &rect);
	}

	return pSprite;
}
