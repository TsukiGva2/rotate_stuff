#include <raylib.h>
#include <inttypes.h>

typedef uint32_t u32;

#define FOR(I, n) for(u32 I=0;I<n;I++)
#define FROM(I, v, n) for(u32 I=v;I<n;I++)

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
const u32 W = SCREEN_WIDTH;
const u32 H = SCREEN_HEIGHT;

void init_window()
{
	InitWindow(W, H, "Rotate Stuff");
	SetTargetFPS(60);
}

void init_textures()
{
}

void clean_textures()
{
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
		BeginDrawing();
			
			ClearBackground(WHITE);

		EndDrawing();
	}

	clean_textures();
	clean_window();

	return 0;
}

