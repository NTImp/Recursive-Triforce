#include <math.h>
#include <SDL2/SDL.h>

#define SCREEN_SIZE 500
#define PI 3.14159f
#define DEG_TO_RAD (PI / 180.f)

SDL_Window* win = 0;
SDL_Renderer* render = 0;


/**
 * This function draws a equilateral triangle whose bottom left corner is at (lx, ly) coordinates.
 * Also divide the triangle in other three and call drawTriforce for one of them.
 * */
void drawTriforce(float lx, float ly, float size, int remaining)
{
	//Draws the triangle
	float tx, ty, rx, ry;
	tx = lx + size * cos(60 * DEG_TO_RAD);
	ty = ly - size * sin(60 * DEG_TO_RAD);
	rx = size + lx;
	ry = ly;

	SDL_Point vertices[4] = {
		{lx, ly},
		{tx, ty},
		{rx, ry},
		{lx, ly}
	};

	SDL_RenderDrawLines(render, vertices, 4);

	if (remaining <= 0) return;

	//Create the subtriangles
	float st1x, st1y, st2x, st2y, st3x, st3y; //The x and y coordinates of the three subtriangles bottom left corners
	st1x = lx;
	st1y = ly;
	st2x = lx + (size / 2) * cos(60 * DEG_TO_RAD);
	st2y = ly - (size / 2) * sin(60 * DEG_TO_RAD);
	st3x = lx + (size / 2);
	st3y = ly;

	drawTriforce(st1x, st1y, size / 2, remaining - 1);
	drawTriforce(st2x, st2y, size / 2, remaining - 1);
	drawTriforce(st3x, st3y, size / 2, remaining - 1);
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
			drawTriforce(0, SCREEN_SIZE - 1, SCREEN_SIZE - 1, 5);
			SDL_RenderPresent(render);
		}
	}
}
