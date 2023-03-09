#include <SDL.h>
#include "lvgl/display.h"

#include "app.h"
#include "app/events.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER | SDL_INIT_HAPTIC);
    app_t app = {
            .running = true
    };

    /* Caveat: Don't use SDL_WINDOW_FULLSCREEN_DESKTOP on webOS. On older platforms it's not supported. */
    SDL_Window *window = SDL_CreateWindow("Gamepads", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 320, 240,
                                          SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_SetWindowResizable(window, SDL_FALSE);
    lv_init();
    lv_disp_t *disp = app_lv_disp_init(window);
    lv_disp_set_default(disp);
    lv_obj_t *label = lv_label_create(lv_scr_act());
    uint64_t counter = 0;
    while (app.running) {
        app_process_events(&app);
        lv_label_set_text_fmt(label, "%llu", ++counter);
        uint32_t next_delay = lv_task_handler();
        if (next_delay == 0 || next_delay == LV_NO_TIMER_READY) {
            next_delay = 1;
        }
        SDL_Delay(next_delay);
    }
    app_lv_disp_deinit(disp);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
