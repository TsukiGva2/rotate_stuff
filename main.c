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

// useful adjustment
vec OFFSET = VEC(0, 0); // additional offset if wished

// constants
const vec ORIGIN = VEC(0, 0);
const vec CENTER = VEC(.5, .5);
const vec SCREEN = VEC(SCREEN_WIDTH, SCREEN_HEIGHT);

#define PROJECT(v) v = vec_add(\
		vec_add(vec_mul(CENTER, SCREEN), v),\
		OFFSET)

// Vars
vec mouse = VEC(0.0, 0.0);
float radius = 100;

// might do an array of stuff
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
	vec mouse_point = vec_div(GetMousePosition(), SCREEN);

	// getting the vector: MOUSE_POINT - CENTER
	mouse = vec_sub(mouse_point, CENTER);
}

void draw_circle(vec a, scalar r, Color color)
{
	PROJECT(a);

	DrawCircleLines(a.x, a.y, r, color);
}

void draw_line(vec a, vec b, Color color)
{
	vec r, w, r2, w2;

	r = vec_sub(b, a);
	w = vec_scale(vec_norm(r), radius);

	DrawText(TextFormat("r = <%f,%f>", r.x, r.y), 50, 50, 30, RED);
	DrawText(TextFormat("w = <%f,%f>", w.x, w.y), 50, 80, 30, PURPLE);

	PROJECT(r);
	PROJECT(w);

	DrawLineEx(r, w, 3.0f, BLUE);
}

void draw_stuff()
{
	const int SW = stuff.width;
	const int SH = stuff.height;

	draw_circle(ORIGIN, radius, BLACK);
	draw_line(ORIGIN, mouse, BLACK);
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

