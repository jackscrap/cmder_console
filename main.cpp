#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

std::map<
	std::string,
	int
> sz = {
	{
		"wd",
		800
	}, {
		"ht",
		600
	}
};

std::vector<SDL_Texture*> tex;
std::vector<SDL_Rect> rect;

std::vector<std::string> rd(
	std::string name
) {
	std::ifstream f(name);
	std::string l;

	std::vector<std::string> word;

	while (
		std::getline(
			f,
			l
		)
	) {
		if (!l.empty()) {
			word.push_back(l);
		} else {
			word.push_back("\n");
		}
	}

	return word;
}

void get_txt_and_rect(
		SDL_Renderer* rend,
		std::map<
			char,
			int
		> pos,
		char* txt,
		TTF_Font* font,
		SDL_Texture** texture,
		SDL_Rect* rect
	) {
		SDL_Surface* surf;
		SDL_Color col = {
			150,
			178,
			135,
			0
		};

		surf = TTF_RenderText_Solid(
			font,
			txt,
			col
		);
		*texture = SDL_CreateTextureFromSurface(
			rend,
			surf
		);

		SDL_FreeSurface(
			surf
		);

		rect->x = pos['x'];
		rect->y = pos['y'];
		rect->w = surf->w;
		rect->h = surf->h;
}

int run = true;
void handle_key(
	SDL_Event e
) {
	if (e.type == SDL_KEYDOWN) {
		switch (e.key.keysym.sym) {
			case SDLK_y:
				run = false;

			case SDLK_n:
				run = false;

			case SDLK_ESCAPE:
				run = false;
		}
	}
}

int main() {
	std::vector<std::string> word = rd("intro");

	SDL_Renderer* rend;

	for (
		int i = 0;
		i < 1000; // todo fix whatever this is
		i++
	) {
		SDL_Texture* theTex;

		tex.push_back(
			theTex
		);

		SDL_Rect theRect;

		rect.push_back(
			theRect
		);
	}

	// window
	SDL_Window* win;

	SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(
		sz["wd"],
		sz["ht"],
		0,
		&win,
		&rend
	);

	// text
	char* name = "terminus.bdf";

	TTF_Init();
	TTF_Font* font = TTF_OpenFont(
		name,
		24
	);

	for (
		int i = 0;
		i < word.size();
		i++
	) {
		std::map<
			char,
			int
		> pos = {
			{
				'x',
				0
			},
			{
				'y',
				i * 32
			}
		};

		get_txt_and_rect(
			rend,
			pos,
			(char*) word[i].c_str(),
			font,
			&tex[i],
			&rect[i]
		);
	}

	SDL_Event e;
	while (run) {
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				run = false;
			}

			handle_key(
				e
			);
		}

		SDL_SetRenderDrawColor(
			rend,
			/* 36, */
			/* 39, */
			/* 35, */
			34,
			36,
			32,
			0
		);
		SDL_RenderClear(
			rend
		);

		for (
			int i = 0;
			i < word.size();
			i++
		) {
			SDL_RenderCopy(
				rend,
				tex[i],
				NULL,
				&rect[i]
			);
		}

		SDL_RenderPresent(
			rend
		);
	}

	for (
		int i = 0;
		i < tex.size();
		i++
	) {
		SDL_DestroyTexture(
			tex[i]
		);
	}

	TTF_Quit();

	SDL_DestroyRenderer(
		rend
	);
	SDL_DestroyWindow(
		win
	);
	SDL_Quit();

	return 0;
}
