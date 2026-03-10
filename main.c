#include "SDL3/SDL_video.h"
#define CLAY_IMPLEMENTATION
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_render.h"
#include <stdio.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include <clay/clay.h>
#include <clay/renderer.h>
#include "layout.h"



	
typedef struct {
	SDL_Window* window;
	Clay_SDL3RendererData renderer_data;
} App;


App app;

#define WINDOW_W 2000
#define WINDOW_H 2000

#define QUIT 1
#define CONTINUE 0


static const Uint32 FONT_ID = 0;

void HandleClayErrors(Clay_ErrorData errorData) {
    printf("%s", errorData.errorText.chars);
}



static inline Clay_Dimensions SDL_MeasureText(Clay_StringSlice text, Clay_TextElementConfig *config, void *userData)
{
    TTF_Font **fonts = userData;
    TTF_Font *font = fonts[config->fontId];
    int width, height;

    TTF_SetFontSize(font, config->fontSize);
    if (!TTF_GetStringSize(font, text.chars, text.length, &width, &height)) {
	printf("Failed to measure text\n");
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to measure text: %s", SDL_GetError());
    }

    return (Clay_Dimensions) { (float) width, (float) height };
}

void init_sdl(void) {

	SDL_Init(SDL_INIT_VIDEO);
	
	int height, width;
	
	int displayCount = 1;

	SDL_DisplayID* displayId = SDL_GetDisplays(&displayCount);

	SDL_DisplayMode* displayMode = (SDL_DisplayMode*)SDL_GetDesktopDisplayMode(*displayId);



	int create_window = SDL_CreateWindowAndRenderer("Hello World", displayMode->w, displayMode->h, SDL_WINDOW_FULLSCREEN, &(app.window), &(app.renderer_data.renderer));
		
	if (!create_window) {
		printf("failed to create window\n");
		SDL_Log("Couldn't create window and renderer: %s", SDL_GetError());
	};


        if (!TTF_Init()) {
		printf("failed to init TTF\n");
		return;
	}


        app.renderer_data.textEngine = TTF_CreateRendererTextEngine(app.renderer_data.renderer);
        if (!app.renderer_data.textEngine) {
	     printf("failed to create text engine\n");
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create text engine from renderer: %s", SDL_GetError());
            return;
        }

        app.renderer_data.fonts = SDL_calloc(1, sizeof(TTF_Font *));
        if (!app.renderer_data.fonts) {
	    printf("Failed to allocate memory for the font array\n");
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to allocate memory for the font array: %s", SDL_GetError());
            return;
        }

        TTF_Font *font = TTF_OpenFont("resources/Roboto-Regular.ttf", 24);
        if (!font) {
	    printf("Failed to load font\n");
            SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font: %s", SDL_GetError());
            return;
        }

        app.renderer_data.fonts[FONT_ID] = font;


    /* Initialize Clay */
    uint64_t totalMemorySize = Clay_MinMemorySize();
    Clay_Arena clayMemory = (Clay_Arena) {
        .memory = SDL_malloc(totalMemorySize),
        .capacity = totalMemorySize
    };


    Clay_Initialize(
		    clayMemory, 
		    (Clay_Dimensions) {
			    (float)displayMode->w,
			    (float)displayMode->h, 
		    },
		    (Clay_ErrorHandler) { HandleClayErrors }
	);

    Clay_SetMeasureTextFunction(SDL_MeasureText, app.renderer_data.fonts);


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


void render(App* app) {

	SDL_Renderer* renderer = app->renderer_data.renderer;
	// clear the screen w/ black
	// SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	Clay_RenderCommandArray render_commands = create_layout();

	SDL_Clay_RenderClayCommands(&(app->renderer_data), &render_commands);

	SDL_RenderPresent(renderer);
}


void loop_start(App* app) {

	SDL_Renderer* renderer = app->renderer_data.renderer;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	
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
