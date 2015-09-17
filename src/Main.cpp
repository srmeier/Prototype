/*
//-----------------------------------------------------------------------------
// TODO
//-----------------------------------------------------------------------------
- need to wrap this Tiled/Duktape stuff into something that is easy to use
- many a debug key to reload the level? (for quick edit and play)

//-----------------------------------------------------------------------------
// DESIGN DECISIONS
//-----------------------------------------------------------------------------
- 
*/

#include "AdBase.h"
#include "AdScreen.h"
#include "AdSpriteManager.h"

//-----------------------------------------------------------------------------
int SDL_main(int argc, char* argv[]) {
	if(AdBase::Init(8*60, 8*40, 2) == false) {
		fprintf(stderr, "ERROR: Failed to initiate.\n");
		system("pause");
		return -1;
	}

	// TESTING
	SDL_Surface* spr  = AdSpriteManager::BuildSprite("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	SDL_Surface* spr0 = AdSpriteManager::BuildSprite("1234567890!#$%&*()-+=[]\"\'<>.?/");

	duk_context* ctx = duk_create_heap_default();

	int* inds = NULL;
	int width, height;

	duk_push_string_file(ctx, "data/maps/testing.json");
	duk_json_decode(ctx, -1);
	
	duk_get_prop_string(ctx, -1, "layers");
	if(duk_is_array(ctx, -1)) {
		printf("this is an array\n");
		duk_size_t size = duk_get_length(ctx, -1);
		printf("this array has %d elements\n", size);

		duk_get_prop_index(ctx, -1, 0);

		duk_get_prop_string(ctx, -1, "height");
		height = duk_to_int(ctx, -1);
		duk_pop(ctx);

		duk_get_prop_string(ctx, -1, "width");
		width = duk_to_int(ctx, -1);
		duk_pop(ctx);

		duk_get_prop_string(ctx, -1, "data");
		if(duk_is_array(ctx, -1)) {
			printf("this is an array\n");
			size = duk_get_length(ctx, -1);
			printf("this array has %d elements\n", size);

			inds = (int*) malloc(size*sizeof(int));
			for(int i=0; i<size; ++i) {
				duk_get_prop_index(ctx, -1, i);
				inds[i] = duk_to_int(ctx, -1);
				duk_pop(ctx);
			}
		}
		duk_pop(ctx);
	}
	duk_pop(ctx);

	duk_pop(ctx);

	printf("%d %d\n", width, height);

	SDL_Surface* spr1 = AdSpriteManager::BuildSprite(width, height, inds);
	free(inds);

	SDL_Event sdlEvent = {};
	while(sdlEvent.type != SDL_QUIT) {
		SDL_PollEvent(&sdlEvent);

		AdScreen::Clear();

		// TESTING
		SDL_Point pnt = {0, 0};
		AdScreen::DrawSprite(pnt, spr1);
		pnt.y += 8*height-16;
		AdScreen::DrawSprite(pnt, spr);
		pnt.y += 8;
		AdScreen::DrawSprite(pnt, spr0);

		AdBase::Update(&sdlEvent);
		AdBase::Render();

		AdScreen::Present();
	}

	// TESTING
	SDL_FreeSurface(spr);
	SDL_FreeSurface(spr0);
	SDL_FreeSurface(spr1);
	duk_destroy_heap(ctx);

	AdBase::Quit();

	return 0;
}
