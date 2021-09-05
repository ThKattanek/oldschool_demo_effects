#include <iostream>
#include <SDL2/SDL.h>

#include "./effect_plasma.h"

using namespace std;

#undef main

int main()
{
	int window_xw = 1920;	// Output Window Size or Fullscreen Size
	int window_yw = 1080;

	int output_xw = 640;	// Render Size for the Demo -> Scaled toWindow Size
	int output_yw = 480;

	uint32_t pixelformat = SDL_PIXELFORMAT_RGBA8888;

	float frame_time = 0.0f;

	float fps = 52.f;
	uint64_t pf_frequency = SDL_GetPerformanceFrequency();

	uint64_t counter_max = pf_frequency / fps;
	uint64_t counter1 = 0;

	EffectPlasma *plasma = new EffectPlasma(output_xw, output_yw);

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window *window = SDL_CreateWindow("Oldschool Demo Effects",SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_xw, window_yw, SDL_WINDOW_OPENGL | /*SDL_WINDOW_FULLSCREEN_DESKTOP |*/ SDL_WINDOW_RESIZABLE);
	if(window == nullptr)
	{
		cout << "Error: SDL Window is not open." << endl;
		cout << SDL_GetError();
		return (-1);
	}

	SDL_Renderer *renderer_out = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/);
	if(renderer_out == nullptr)
	{
		cout << "Error: SDL_Renerer ist not initialize." << endl;
		cout << SDL_GetError();
		return (-1);
	}

	SDL_Texture *texture_01 = SDL_CreateTexture(renderer_out, pixelformat, SDL_TEXTUREACCESS_STREAMING, output_xw, output_yw);

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
			}
		}

		uint32_t *pixelbuffer;
		int pitch;

		SDL_LockTexture(texture_01, 0, (void**)&pixelbuffer, &pitch);
		pitch /= SDL_BYTESPERPIXEL(pixelformat);

		plasma->RenderEffect(pixelbuffer, pitch, frame_time);

		SDL_UnlockTexture(texture_01);

		SDL_RenderCopy(renderer_out, texture_01, 0, 0);

		// calculate frametime
		frame_time = (float)counter1 / pf_frequency;

		// counter reset
		counter1 = counter1 - counter_max;

		SDL_RenderPresent(renderer_out);

		SDL_Delay(15);
	}

	delete plasma;

	SDL_DestroyTexture(texture_01);
	SDL_Quit();
	return 0;
}
