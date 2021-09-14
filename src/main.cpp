#include <iostream>
#include <cstdio>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "./effect_plasma.h"
#include "./effect_blob.h"
#include "./effect_fire.h"
#include "./effect_bob.h"
#include "./effect_copperbars.h"
#include "./effect_barscroller.h"

using namespace std;

#undef main

enum {PLASMA, BLOB, FIRE, BOB, COPPERBARS, BARSCROLLER, MAX_EFFECTS};
char *effect_names[MAX_EFFECTS] = {"PLASMA", "BLOB", "FIRE", "BOB", "COPPER BARS", "BARSCROLLER"};

int main()
{
	//int window_xw = 1280;	// Output Window Size or Fullscreen Size
	//int window_yw = 960;

	int window_xw = 640;	// Output Window Size or Fullscreen Size
	int window_yw = 480;

	int output_xw = 640;	// Render Size for the Demo -> Scaled toWindow Size
	int output_yw = 480;

	uint32_t pixelformat = SDL_PIXELFORMAT_RGBA8888;

	float frame_time = 0.0f;

	float fps = 52.f;
	uint64_t pf_frequency = SDL_GetPerformanceFrequency();

	uint64_t counter_max = pf_frequency / fps;
	uint64_t counter1 = 0;

	TTF_Font *font_01;
	SDL_Surface *text_surface;

	SDL_Texture *img1_texture;
	SDL_Texture *font_texture;

	int current_view_effect = BARSCROLLER;
	bool changed_effect = false;

	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		cout << "Error: SDL_Init." << endl;
		cout << SDL_GetError() << endl;
		return (-1);
	}

	if(TTF_Init() != 0)
	{
		cout << "Error: TTF_Init." << endl;
		cout << TTF_GetError() << endl;
		SDL_Quit();
		return (-1);
	}

	int img_flags = IMG_INIT_PNG;
	if(IMG_Init(img_flags) != img_flags)
	{
		cout << "Error: IMG_Init." << endl;
		cout << IMG_GetError() << endl;
		TTF_Quit();
		SDL_Quit();
		return (-1);
	}

	char font_filename[1024];
	sprintf(font_filename, "%s/MuktiNarrowBold.ttf", DATA_PATH);
	cout << font_filename << endl;

	font_01 = TTF_OpenFont(font_filename, 36);
	if(!font_01)
	{
		cout << "Error: TTF_OpenFont." << endl;
		cout << TTF_GetError() << endl;

		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		return (-1);
	}

	SDL_Color color = {255,255,255,0};

	SDL_Window *window = SDL_CreateWindow("Oldschool Demo Effects - [change effect with cursor left and rigth]",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_xw, window_yw, SDL_WINDOW_OPENGL | /*SDL_WINDOW_FULLSCREEN_DESKTOP |*/ SDL_WINDOW_RESIZABLE);
	if(window == nullptr)
	{
		cout << "Error: SDL Window is not open." << endl;
		cout << SDL_GetError();
		TTF_CloseFont(font_01);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		return (-1);
	}

	SDL_Renderer *renderer_out = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE /*| SDL_RENDERER_PRESENTVSYNC*/);
	if(renderer_out == nullptr)
	{
		cout << "Error: SDL_Renerer ist not initialize." << endl;
		cout << SDL_GetError();
		TTF_CloseFont(font_01);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		return (-1);
	}

	SDL_Texture *texture_01 = SDL_CreateTexture(renderer_out, pixelformat, SDL_TEXTUREACCESS_STREAMING, output_xw, output_yw);

	char filename[1024];
	sprintf(filename, "%s/eye.png", DATA_PATH);
	cout << filename << endl;

	img1_texture = IMG_LoadTexture(renderer_out, filename);
	if(img1_texture == nullptr)
	{
		cout << "Error: Image not loadet." << endl;
		cout << SDL_GetError();
		TTF_CloseFont(font_01);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		return (-1);
	}

	sprintf(filename, "%s/font.pcx", DATA_PATH);
	cout << filename << endl;

	font_texture = IMG_LoadTexture(renderer_out, filename);
	if(font_texture == nullptr)
	{
		cout << "Error: Image not loadet." << endl;
		cout << SDL_GetError();
		TTF_CloseFont(font_01);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
		return (-1);
	}


	// init effects

	EffectPlasma *plasma = new EffectPlasma(output_xw, output_yw);
	EffectBlob *blob = new EffectBlob(output_xw, output_yw);
	EffectFire *fire = new EffectFire(output_xw, output_yw);
	EffectBob *bob = new EffectBob(renderer_out, img1_texture, output_xw, output_yw);
	EffectCopperBars *copper = new EffectCopperBars(renderer_out, output_xw, output_yw);
	EffectBarscroller *barscroller = new EffectBarscroller(renderer_out, font_texture, output_xw, output_yw);

	bool exit = false;

	// Main Loop
	while (!exit)
	{
		SDL_Event event;
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				exit = true;
			}

			if (event.type == SDL_KEYDOWN)
			{
				if(event.key.keysym.sym == SDLK_ESCAPE)
					exit = true;

                if(event.key.keysym.sym == SDLK_RIGHT)
                {
                    current_view_effect++;
                    if(current_view_effect == MAX_EFFECTS)
                        current_view_effect = 0;
					changed_effect = true;
                }

                if(event.key.keysym.sym == SDLK_LEFT)
                {
                    current_view_effect--;
                    if(current_view_effect < 0)
                        current_view_effect = MAX_EFFECTS-1;
					changed_effect = true;
                }
			}
		}

		uint32_t *pixelbuffer;
		int pitch;

        switch(current_view_effect)
        {
		case PLASMA:
			SDL_LockTexture(texture_01, 0, (void**)&pixelbuffer, &pitch);
			pitch /= SDL_BYTESPERPIXEL(pixelformat);
            plasma->RenderEffect(pixelbuffer, pitch, frame_time);
			SDL_UnlockTexture(texture_01);
			SDL_RenderCopy(renderer_out, texture_01, 0, 0);
            break;
        case BLOB:
			if(changed_effect)
				blob->ResetEffect();
			SDL_LockTexture(texture_01, 0, (void**)&pixelbuffer, &pitch);
			pitch /= SDL_BYTESPERPIXEL(pixelformat);
            blob->RenderEffect(pixelbuffer, pitch, frame_time);
			SDL_UnlockTexture(texture_01);
			SDL_RenderCopy(renderer_out, texture_01, 0, 0);
            break;
		case FIRE:
			SDL_LockTexture(texture_01, 0, (void**)&pixelbuffer, &pitch);
			pitch /= SDL_BYTESPERPIXEL(pixelformat);
			if(changed_effect)
				fire->ResetEffect(pixelbuffer, pitch);
			fire->RenderEffect(pixelbuffer, pitch, frame_time);
			SDL_UnlockTexture(texture_01);
			SDL_RenderCopy(renderer_out, texture_01, 0, 0);
			break;
		case BOB:
			bob->RenderEffect();
			break;
        case COPPERBARS:
			copper->RenderEffect();
            break;
		case BARSCROLLER:
			barscroller->RenderEffect();
			break;
        }

		changed_effect = false;

		/// overlay text output

        text_surface = TTF_RenderText_Blended(font_01, effect_names[current_view_effect], color);

		SDL_Rect src_rec = {0,0,text_surface->w, text_surface->h};
		SDL_Rect dst_rec = src_rec;
		dst_rec.y = -5;
        dst_rec.x = 10;
		SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_out, text_surface);
		SDL_RenderCopy(renderer_out, texture, &src_rec, &dst_rec);
		SDL_DestroyTexture(texture);
		SDL_FreeSurface(text_surface);

		// calculate frametime
		frame_time = (float)counter1 / pf_frequency;

		// counter reset
		counter1 = counter1 - counter_max;

		SDL_RenderPresent(renderer_out);

		SDL_Delay(20);
	}

	delete barscroller;
    delete copper;
	delete bob;
	delete fire;
	delete blob;
	delete plasma;

	SDL_DestroyTexture(font_texture);
	SDL_DestroyTexture(img1_texture);
	SDL_DestroyTexture(texture_01);
	TTF_CloseFont(font_01);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
