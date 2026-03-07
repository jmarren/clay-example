#ifndef CLAY_SDL3_RENDERER_H
#define CLAY_SDL3_RENDERER_H

#include "clay.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    SDL_Renderer *renderer;
    TTF_TextEngine *textEngine;
    TTF_Font **fonts;
} Clay_SDL3RendererData;

/* Current clipping rectangle used by scissor commands */
extern SDL_Rect currentClippingRectangle;

/* Main render entry point for Clay render commands */
void SDL_Clay_RenderClayCommands(
    Clay_SDL3RendererData *rendererData,
    Clay_RenderCommandArray *rcommands
);

#ifdef __cplusplus
}
#endif

#endif /* CLAY_SDL3_RENDERER_H */
