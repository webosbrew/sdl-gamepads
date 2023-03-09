#include "app.h"

#include <stdbool.h>
#include <SDL.h>
#include "events.h"

void app_process_events(app_t *app) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                app->running = false;
                break;
            }
        }
    }
}