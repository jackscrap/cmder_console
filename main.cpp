#include <vector>
#include <string>
#include <fstream>
#include <map>

#include <ctime>
#include <iostream>

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

SDL_Renderer* rend;
void print(
	std::vector<std::string> p
) {
	TTF_Font* font = TTF_OpenFont(
		"terminus.bdf",
		24
	);

	for (
		int i = 0;
		i < p.size();
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
			(char*) p[i].c_str(),
			font,
			&tex[i],
			&rect[i]
		);
	}
}

// loop
int run = true;

std::string input;
std::vector<std::string> bff;

void handle_key(
	SDL_Event e
) {
	if (e.type == SDL_KEYDOWN) {
		char c;

		switch (e.key.keysym.sym) {
			case SDLK_0:
			case SDLK_1:
			case SDLK_2:
			case SDLK_3:
			case SDLK_4:
			case SDLK_5:
			case SDLK_6:
			case SDLK_7:
			case SDLK_8:
			case SDLK_9:

			case SDLK_a:
			case SDLK_b:
			case SDLK_c:
			case SDLK_d:
			case SDLK_e:
			case SDLK_f:
			case SDLK_g:
			case SDLK_h:
			case SDLK_i:
			case SDLK_j:
			case SDLK_k:
			case SDLK_l:
			case SDLK_m:
			case SDLK_o:
			case SDLK_p:
			case SDLK_q:
			case SDLK_r:
			case SDLK_s:
			case SDLK_t:
			case SDLK_u:
			case SDLK_v:
			case SDLK_w:
			case SDLK_x:
			case SDLK_y:
			case SDLK_z:

			case SDLK_SPACE: {
				c = (char) e.key.keysym.sym;

				input += c;

				char* prompt = "*= ";

				std::vector<
					std::string
				> l;
				l.push_back(prompt + input + '_');
				print(l);

				break;
			}

			case SDLK_BACKSPACE: {
				input = input.substr(0, input.size() - 1);

				char* prompt = "*= ";

				std::vector<
					std::string
				> l;
				l.push_back(prompt + input + '_');
				print(l);

				break;
			}

			case SDLK_RETURN:
				bff.push_back(input);
				print(bff);

				input = "";

				char* prompt = "*= ";

				std::vector<
					std::string
				> l;
				l.push_back(prompt + input + '_');
				print(l);

				break;

			// respond
			/* case SDLK_y: */
			/* 	run = false; */

			/* case SDLK_n: */
			/* 	run = false; */

			/* case SDLK_ESCAPE: */
				/* run = false; */
		}
	}
}

int main() {
	for (
		int i = 0;
		i < 10000; // todo fix whatever this is
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

	/* text */
	TTF_Init();
	TTF_Font* font = TTF_OpenFont(
		"terminus.bdf",
		24
	);

	// status bar
	time_t now;
	time(&now);

	char buff[1024];
	strftime(
		buff,
		sizeof buff,
		"%F %H:%M",
		gmtime(&now)
	);

	get_txt_and_rect(
		rend,
		{
			{
				'x',
				0
			}, {
				'y',
				0
			}
		},
		buff,
		font,
		&tex[0],
		&rect[0]
	);

	// upper content
	std::vector<
		std::string
	>	head = rd("head");

	std::vector<
		std::string
	>	intro = rd("intro");

	/* print(head); */
	/* print(intro); */

	// I
	char* prompt = "*= ";

	get_txt_and_rect(
		rend,
		{
			{
				'x',
				0
			}, {
				'y',
				0
			}
		},
		prompt,
		font,
		&tex[0],
		&rect[0]
	);

	// loop
	SDL_Event e;
	while (run) {
		// event
		while (SDL_PollEvent(&e)) {
			handle_key(
				e
			);

			if (e.type == SDL_QUIT) {
				run = false;
			}
		}

		// background
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
			i < 1000;
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
