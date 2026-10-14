#include "common.h"
typedef struct { s16 x,y,w,h; } MovieRect;
typedef struct {
    s32 tag;
    void *frame_buffers[2];
    s32 frame_buffer_index;
    void *output;
    MovieRect screen[2];
    s32 screen_index;
    MovieRect strip;
    s32 ready;
    s32 done;
    s32 width,height;
} MovieState;
extern MovieState *D_80189390;
extern s32 D_801781D0, D_801781D4, D_801781D8, D_801781DC, D_801781E0;

extern s32 D_80086D8C;
extern void func_8006390C(void);
extern void func_800672D8(MovieRect *,void *);
extern void func_80067014(s32);
extern void func_801778C0(void *,s32);
void func_80176CA8(void) {
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
        func_801778C0(movie->output, (movie->strip.w * movie->strip.h) / 2);
    } else {
        movie->ready = 1;
        movie->screen_index = !movie->screen_index;
        movie->strip.x = movie->screen[movie->screen_index].x;
        movie->strip.y = movie->screen[movie->screen_index].y;
    }
}
