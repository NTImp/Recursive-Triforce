#include <SDL2/SDL.h>

#define SCREEN_SIZE 500
#define PI 3.14159f
#define DEG_TO_RAD (PI / 180.f)

SDL_Window* win = 0;
SDL_Renderer* render = 0;

float mid(float a, float b)
{
	return a + (b - a) / 2;
}


void triangle(float x1, float y1, float x2, float y2, float x3, float y3, char first, int remaining)
{
	if (remaining == 0) return;

	if (first)
	{
		SDL_RenderDrawLine(render, x1, y1, x2, y2);
		SDL_RenderDrawLine(render, x2, y2, x3, y3);
		SDL_RenderDrawLine(render, x3, y3, x1, y1);
	}

	//Draw the inverse triangle
	SDL_RenderDrawLine(render, mid(x1, x3), mid(y1, y3), mid(x1, x2), mid(y1, y2));
	SDL_RenderDrawLine(render, mid(x1, x2), mid(y1, y2), mid(x3, x2), mid(y3, y2));
	SDL_RenderDrawLine(render, mid(x2, x3), mid(y2, y3), mid(x1, x3), mid(y1, y3));

	//Top subtriangle
	triangle(mid(x1, x3), mid(y1, y3), //bottom left vertice
			mid(x3, x2), mid(y3, y2), //bottom right vertice
			x3, y3, 0, remaining - 1); //top vertice

	//Bottom left triangle
	triangle(x1, y1, //bottom left vertice
			mid(x2, x1), mid(y2, y1), //bottom right vertice
			mid(x1, x3), mid(y1, y3), 0, remaining - 1); //top vertice
	
	//Bottom right triangle
	triangle(mid(x1, x2), mid(y1, y2), //bottom left vertice
			x2, y2, //bottom right vertice
			mid(x3, x2), mid(y3, y2), 0, remaining - 1); //top vertice
}
void subtriangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
	SDL_RenderDrawLine(render, x1, y1, x2, y2);
	SDL_RenderDrawLine(render, x2, y2, x3, y3);
	SDL_RenderDrawLine(render, x3, y3, x1, y1);
}

int main(int argc, char** argv)
{
	win = SDL_CreateWindow("Recursive triforce", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_SIZE, SCREEN_SIZE, SDL_WINDOW_SHOWN);
	render = SDL_CreateRenderer(win, -1, 0);

	char drawn = 0;
	char running = 1;

	SDL_Event ev;
	while (running)
	{
		while (SDL_WaitEventTimeout(&ev, 10))
		{
			if (ev.type == SDL_QUIT)
			{
				running = 0;
			}
		}
		if (!drawn)
		{
			SDL_SetRenderDrawColor(render, 0, 0, 0, 0);
			SDL_RenderClear(render);

			SDL_SetRenderDrawColor(render, 255, 255, 255, 0);
			triangle(0, SCREEN_SIZE - 1, //Left bottom vertice
					SCREEN_SIZE - 1, SCREEN_SIZE - 1, //Right bottom vertice
					SCREEN_SIZE / 2, 0, //Top vertice
					1, 5);
			SDL_RenderPresent(render);
		}
	}
}
