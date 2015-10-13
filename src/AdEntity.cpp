/*
*/

#include "AdLevel.h"
#include "AdEntity.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
AdEntity::AdEntity(void) {}

//-----------------------------------------------------------------------------
AdEntity::~AdEntity(void) {}

//-----------------------------------------------------------------------------
void AdEntity::Load(duk_context* pCtx) {
	Unload();

	duk_get_prop_string(pCtx, -1, "type");
	strcpy(m_pType, duk_get_string(pCtx, -1));
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "x");
	m_recTrigger.x = duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "y");
	m_recTrigger.y = duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "width");
	m_recTrigger.w = duk_to_int(pCtx, -1);
	duk_pop(pCtx);

	duk_get_prop_string(pCtx, -1, "height");
	m_recTrigger.h = duk_to_int(pCtx, -1);
	duk_pop(pCtx);
}

//-----------------------------------------------------------------------------
void AdEntity::Unload(void) {
	m_bTriggered = false;
	memset(m_pType, 0x00, NAME_LENGTH);
	memset(&m_recTrigger, 0x00, sizeof(SDL_Rect));
}

//-----------------------------------------------------------------------------
void AdEntity::Update(AdLevel* pLvl) {
	SDL_Rect Result;
	SDL_Rect Player = {
		8*pLvl->GetPlayer()->m_iI, 8*pLvl->GetPlayer()->m_iJ, 8*6, 8*6
	};

	if(SDL_IntersectRect(&m_recTrigger, &Player, &Result))
		m_bTriggered = true;
	else
		m_bTriggered = false;
}

//-----------------------------------------------------------------------------
void AdEntity::Render(AdLevel* pLvl) {
	if(m_bTriggered) {
		// TESTING
		int inds[] = {
			64*1+44, 64*1+45, 64*1+45, 64*1+45, 64*1+45, 64*1+45, 64*1+45, 64*1+45, 64*1+49,
			64*2+44, 64*2+45, 64*2+45, 64*2+45, 64*2+45, 64*2+45, 64*2+45, 64*2+45, 64*2+49,
			64*3+44, 64*3+45, 64*3+45, 64*3+45, 64*3+45, 64*3+45, 64*3+45, 64*3+45, 64*3+49,
		};

		SDL_Surface* bkg = AdSpriteManager::BuildSprite(9, 3, inds);

		SDL_Surface* spr = AdSpriteManager::BuildSprite("EVENT!!");

		/*
		int offset_x = AdBase::GetWidth()/2-48/2+pLvl->GetPlayer()->m_recTrigger.x;
		int offset_y = AdBase::GetHeight()/2-48/2+pLvl->GetPlayer()->m_recTrigger.y;

		SDL_Point pnt = {m_recTrigger.x+offset_x, m_recTrigger.y+offset_y};
		*/
		SDL_Point pnt = {8, 8};
		AdScreen::DrawSprite(pnt, bkg);
		pnt.x += 8; pnt.y += 7;
		AdScreen::DrawSprite(pnt, spr);

		SDL_FreeSurface(spr);
		SDL_FreeSurface(bkg);
		//
	}
}
