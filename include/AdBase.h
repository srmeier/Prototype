#ifndef __ADBASE_H_
#define __ADBASE_H_

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_net.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

//-----------------------------------------------------------------------------
class AdBase {
private:
	static SDL_Window*        s_pWindow;
	static SDL_Renderer*      s_pRenderer;

public:
	static int                s_iWinScale;
	static int                s_iWinWidth;
	static int                s_iWinHeight;
	static class AdProcedure* s_pActiveProc;

public:
	static class AdProcedure* s_pGameProc;

public:
	static bool Init(int iWidth, int iHeight, int iScale);
	static void Quit(void);

public:
	static void Update(void);
	static void Render(void);

public:
	static SDL_Window*   GetWindow(void) {return s_pWindow;}
	static SDL_Renderer* GetRenderer(void) {return s_pRenderer;}
	static void          SetActiveProc(class AdProcedure* pProc);
};

#endif
