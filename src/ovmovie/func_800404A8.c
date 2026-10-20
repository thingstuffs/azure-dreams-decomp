#include "modules/ovmovie_game.h"

void upload_movie_strip_and_advance_buffer(void) {
    MovieRect rectangle;
    MovieState *movie;
    if (D_801781E0 & 1) {
        if (D_80086D8C) {
            func_8006390C();
            D_80086D8C = 0;
        }
    }
    rectangle = D_80189390->strip;
    if (D_801781E0 & 1) {
        rectangle.x += (D_801781D8 / 3) * 3;
        rectangle.y += (D_801781DC / 3) * 3;
    } else {
        rectangle.x += D_801781D8;
        rectangle.y += D_801781DC;
    }
    func_800672D8(&rectangle, D_80189390->output);
    func_80067014(0);
    movie = D_80189390;
    movie->strip.x += movie->strip.w;
    if (movie->strip.x < movie->screen[movie->screen_index].x + movie->screen[movie->screen_index].w) {
        request_decoder_output_dma((s32)movie->output, (movie->strip.w * movie->strip.h) / 2);
    } else {
        movie->ready = 1;
        movie->screen_index = !movie->screen_index;
        movie->strip.x = movie->screen[movie->screen_index].x;
        movie->strip.y = movie->screen[movie->screen_index].y;
    }
}
