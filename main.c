#include "raylib2d.h"
#include <inttypes.h>

typedef uint32_t uint;

#define FOR(I, n) for(uint I=0;I<n;I++)
#define FROM(I, v, n) for(uint I=v;I<n;I++)
#define MIN(x, y) ((x)<(y)?(x):(y))

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
const uint W = SCREEN_WIDTH;
const uint H = SCREEN_HEIGHT;

vec OFFSET = VEC(0, 0); // additional offset if wished

const vec ORIGIN = VEC(0, 0);
const vec CENTER = VEC(.5, .5);
const vec SCREEN = VEC(SCREEN_WIDTH, SCREEN_HEIGHT);

#define PROJECT(v) v = vec_add(\
		vec_add(vec_mul(CENTER, SCREEN), v),\
		OFFSET)

vec mouse;
vec mouse_vel;
vec mouse_pos;

scalar radius = 100;

Texture2D stuff;

void init_window()
{
	InitWindow(W, H, "Rotate Stuff");
	SetTargetFPS(60);
}

void init_textures()
{
	stuff = LoadTexture("assets/teto_image/tetoteto.png");
}

void update_stuff()
{
	vec mouse_new;

	mouse_new = vec_div(GetMousePosition(), SCREEN);
	mouse_vel = vec_sub(mouse_new, mouse_pos);

	mouse_pos = mouse_new;
	mouse     = vec_sub(mouse_pos, CENTER);
}

void draw_circle(vec a, scalar r, Color color)
{
	PROJECT(a);

	DrawCircleLines(a.x, a.y, r, color);
}

void draw_line(vec a, vec b, Color color)
{
	vec r, w;

	r = vec_sub(b, a);
	w = vec_scale(vec_norm(r), radius);

	PROJECT(r);
	PROJECT(w);

	DrawLineEx(r, w, 3.0f, color);
}

void draw_mouse_vel(Color color)
{
	vec a, b;

	a = mouse_pos;
	b = vec_add(mouse_pos, vec_scale(mouse_vel, -10));

	// no need to PROJECT here
	a = vec_mul(a, SCREEN);
	b = vec_mul(b, SCREEN);

	DrawLineEx(a, b, 3.0f, color);
}

void draw_stuff()
{
	const int SW = stuff.width;
	const int SH = stuff.height;

	draw_circle(ORIGIN, radius, BLACK);

	draw_line(ORIGIN, mouse, BLUE);

	draw_mouse_vel(RED);
}

void clean_textures()
{
	UnloadTexture(stuff);
}

void clean_window()
{
	CloseWindow();
}

int main()
{
	init_window();
	init_textures();

	while (!WindowShouldClose())
	{
		update_stuff();

		BeginDrawing();
			
			ClearBackground(WHITE);

			draw_stuff();

		EndDrawing();
	}

	clean_textures();
	clean_window();

	return 0;
}

