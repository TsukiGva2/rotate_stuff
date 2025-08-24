#include <raylib.h>
#include <raymath.h>
#include <inttypes.h>

#ifndef PI
    #define PI 3.14159265358979323846f
#endif

typedef uint32_t u32;

#define FOR(I, n) for(u32 I=0;I<n;I++)
#define FROM(I, v, n) for(u32 I=v;I<n;I++)
#define MIN(x, y) ((x)<(y)?(x):(y))

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
const u32 W = SCREEN_WIDTH;
const u32 H = SCREEN_HEIGHT;

// useful adjustment
Vector2 OFFSET = (Vector2){0, 0}; // additional offset if wished

// constants
const Vector2 ORIGIN = (Vector2){0, 0};
const Vector2 CENTER = (Vector2){.5, .5};
const Vector2 SCREEN = (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT};

#define PROJECT(v) v = Vector2Add(\
		Vector2Add(Vector2Multiply(CENTER, SCREEN), v),\
		OFFSET)

// Vars
Vector2 mouse = (Vector2){0.0, 0.0};
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
	Vector2 mouse_point = Vector2Divide(GetMousePosition(), SCREEN);

	// getting the vector: MOUSE_POINT - CENTER
	mouse = Vector2Subtract(mouse_point, CENTER);
}

void draw_circle(Vector2 a, float r, Color color)
{
	PROJECT(a);

	DrawCircleLines(a.x, a.y, r, color);
}

void draw_line(Vector2 a, Vector2 b, Color color)
{
	Vector2 r, w, r2, w2;

	r = Vector2Subtract(b, a);
	w = Vector2Scale(Vector2Normalize(r), radius);

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

	Vector2 image_start = (Vector2)
	{
		W / 2 - SW / 2,
		H / 2 - SH / 2
	};

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

