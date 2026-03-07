#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_render.h"
#include <stdio.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#define CLAY_IMPLEMENTATION
#include <clay/clay.h>
#include <clay/renderer.h>
#include "layout.h"



	
typedef struct {
	SDL_Window* window;
	Clay_SDL3RendererData renderer_data;
} App;


App app;

#define WINDOW_W 1000
#define WINDOW_H 1000

#define QUIT 1
#define CONTINUE 0

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}


void init_sdl(void) {

	SDL_Init(SDL_INIT_VIDEO);

	

        if (!TTF_Init()) {
		printf("failed to init TTF\n");
		return;
	}


	SDL_Window** window = &(app.window);
	SDL_Renderer** renderer = &(app.renderer_data.renderer);

	int create_window = SDL_CreateWindowAndRenderer("Hello World", WINDOW_W, WINDOW_H, SDL_WINDOW_FULLSCREEN, window, renderer);
		
	if (!create_window) {
		printf("failed to create window\n");
		SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
	};

    /* Initialize Clay */
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = (Clay_Arena) {
        .memory = SDL_malloc(totalMemorySize),
        .capacity = totalMemorySize
    };

    int width, height;


    Clay_Initialize(
		    clayMemory, 
		    (Clay_Dimensions) {
			    (float) width,
			    (float) height 
		    },
		    (Clay_ErrorHandler) { HandleClayErrors }
	);

	SDL_ShowWindow(app.window);
	SDL_RaiseWindow(app.window);
}


// handle global events every iteration
int handle_global_events(App* app, SDL_Event* event) {
	
	if (event->type == SDL_EVENT_QUIT) {
		return QUIT;
	}
	
	if (event->key.key == SDLK_ESCAPE) {
		printf("got escape\n");
		return QUIT;
	}
	

	return CONTINUE;
}


// handle events (global and frame-specific)
int handle_events(App* app) {
	
	 SDL_Event event;
	 while (SDL_PollEvent(&event)) {  
		// handle global events and quit if neccessary
		if (handle_global_events(app, &event) == QUIT) {
			return QUIT;
		};

	 }

	return CONTINUE;
}


static void render(App* app) {
	printf("rendering app\n");

	SDL_Renderer* renderer = app->renderer_data.renderer;
	// clear the screen w/ black
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderClear(renderer);
	Clay_RenderCommandArray render_commands = create_layout();
	

	SDL_Clay_RenderClayCommands(&(app->renderer_data), &render_commands);

	SDL_RenderPresent(renderer);
}


void loop_start(App* app) {

	
	int ticks = SDL_GetTicks();

	while (true) {
		
		int new_ticks = SDL_GetTicks();

		if (new_ticks - ticks > 20) {
		    // set ticks to new_ticks
		    ticks = new_ticks;

		    // handle global events and quit if neccessary
		    if (handle_events(app) == QUIT) break;
			
		    // render the app
		    render(app);
		}
	}
}


int main(void) {

	printf("main!\n");

	init_sdl();
	
	loop_start(&app);


	return 0;

}
