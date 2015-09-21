#ifndef __ADBASE_H_
#define __ADBASE_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Duktape.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_net.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#define WINDOW_TITLE "Prototype"

//-----------------------------------------------------------------------------
class AdBase {
private:
	static duk_context*  s_pJSCtx;
	static SDL_Window*   s_pWindow;
	static SDL_Renderer* s_pRenderer;

protected:
	static int             s_iWinScale;
	static int             s_iWinWidth;
	static int             s_iWinHeight;
	static class AdPlayer* s_pPlayer;

protected:
	static duk_context*  GetJSCtx(void)    {return s_pJSCtx;}
	static SDL_Window*   GetWindow(void)   {return s_pWindow;}
	static SDL_Renderer* GetRenderer(void) {return s_pRenderer;}

public:
	static class AdLevel* s_pCurLvl;

public:
	static bool Init(int iWidth, int iHeight, int iScale);
	static void Quit(void);

public:
	static void Update(SDL_Event* sdlEvent);
	static void Render(void);

public:
	static void SetLevel(class AdLevel* pLvl);
	static int  GetWidth(void)  {return s_iWinWidth;}
	static int  GetHeight(void) {return s_iWinHeight;}
};

#endif
