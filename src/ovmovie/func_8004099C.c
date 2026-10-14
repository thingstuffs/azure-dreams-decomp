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

#include "shared/game_work.h"
typedef struct { MovieRect viewport,screen; u8 interlaced,rgb24,pad[6]; } MovieDisplayEnv;
typedef struct { u8 bytes[96]; } MovieDrawEnv;
extern u8 D_80082E6B;
extern u8 D_801C9E40[],D_80189398[];
extern s32 D_801B8EBC;
extern s32 func_8003E240(s32);
extern void func_8006124C(s32,void *);
extern void func_80063538(void);
extern void func_8006636C(void *,s32,s32,s32,s32);
extern void func_80066424(void *,s32,s32,s32,s32);
extern void func_80066F78(s32);
extern void func_80067688(void *);
extern void func_800678E0(void *);
extern void func_8005FE18(s32);
extern void func_8005A56C(s32,s16,s16);
extern void func_8005A4E8(s32,s32,s32);
extern void func_80176CA8(void);
extern void func_80176BEC(void *,s32,s32,s32,s32);
extern void func_80176B60(void *,void (*)(void));
extern s32 func_80176E90(void *);
extern void func_801770BC(void *,s32);
extern void func_80177844(void *,s32);
extern void func_801778C0(void *,s32);

static inline s32 movie_skip_requested(s32 buttons,s32 previous) {
    s32 requested = 0;
    if (D_80082E6B == 30 || D_80082E6B == 32 || D_80082E6B == 1) {
        if (buttons) requested = 1;
    } else if (~previous & buttons & 0x9F0) requested = 1;
    return requested;
}

s32 func_8017719C(s32 unused,s32 frame_limit,s32 stream,s32 mode) {
    MovieDisplayEnv display;
    MovieDrawEnv draw;
    s32 fade_started = 0;
    s32 fade_step = 1;
    s32 frames = 0;
    s32 previous_buttons;
    u8 **screen_slot = (u8 **)&gameWork;

    D_801781D4 = frame_limit - 8;
    D_801781D0 = 0;
    D_80189390 = (MovieState *)D_80189398;
    func_8006124C(stream,D_80189398);
    if (mode) func_80176BEC((u8 *)D_80189390 + 4,0,0,0,240);
    else func_80176BEC((u8 *)D_80189390 + 4,0,0,0,224);
    func_80176B60(D_80189390,func_80176CA8);
    if (func_80176E90((u8 *)D_80189390 + 4)) {
        func_80066F78(1);
        if (D_80189390->height >= 225) {
            func_80066424(&display,D_80189390->screen[1].x,D_80189390->screen[1].y,D_80189390->screen[1].w,D_80189390->screen[1].h);
            func_8006636C(&draw,D_80189390->screen[1].x,D_80189390->screen[1].y,D_80189390->screen[1].w,D_80189390->screen[1].h);
        }
        if (D_801781E0 & 1) {
            display.rgb24 = 1;
            display.viewport.w = (display.viewport.w * 2) / 3;
        }
        if (D_80189390->height >= 225) {
            func_800678E0(&display);
            func_80067688(&draw);
        } else {
            func_800678E0(*screen_slot + 0x5C);
            func_80067688(*screen_slot);
        }
        previous_buttons = 0;
        while (1) {
            func_80177844(D_80189390->frame_buffers[D_80189390->frame_buffer_index],(D_801781E0 & 1) | 2);
            func_801778C0(D_80189390->output,(D_80189390->strip.w * D_80189390->strip.h) / 2);
            if (!func_80176E90((u8 *)D_80189390 + 4)) break;
            func_801770BC((u8 *)D_80189390 + 4,0);
            func_8005FE18(2);
            if (D_80189390->height >= 225) {
                s32 index = !D_80189390->screen_index;
                func_80066424(&display,D_80189390->screen[index].x,D_80189390->screen[index].y,D_80189390->screen[index].w,D_80189390->screen[index].h);
                func_8006636C(&draw,D_80189390->screen[index].x,D_80189390->screen[index].y,D_80189390->screen[index].w,D_80189390->screen[index].h);
            } else {
                u8 *buffer = D_801C9E40;
                if (D_80189390->screen_index) buffer += 0x108D4;
                *screen_slot = buffer;
            }
            if (D_801781E0 & 1) {
                display.rgb24 = 1;
                display.viewport.w = (display.viewport.w * 2) / 3;
            }
            if (D_80189390->height >= 225) {
                func_800678E0(&display);
                func_80067688(&draw);
            } else {
                func_800678E0(*screen_slot + 0x5C);
                func_80067688(*screen_slot);
            }
            if (D_801781D0 >= frame_limit - 8 || frames >= frame_limit - 3) break;
            ++frames;
            if (D_80189390->done == 1) break;
            if (!fade_started) {
                s32 old_buttons = previous_buttons;
                s32 skip;
                previous_buttons = func_8003E240(1);
                skip = 0;
                skip = movie_skip_requested(previous_buttons,old_buttons);
                if (skip) {
                    fade_started = 1;
                    fade_step = (D_801B8EBC + 9) / 10;
                } else if (D_801781D0 >= frame_limit - 20) {
                    fade_started = 1;
                    {
                        s32 brightness = D_801B8EBC;
                        s32 rounded = brightness + 7;
                        if (rounded < 0) rounded = brightness + 14;
                        fade_step = (u32)rounded >> 3;
                    }
                }
                if (!fade_started) continue;
            }
            D_801B8EBC -= (s16)fade_step;
            if (D_801B8EBC < 0) D_801B8EBC = 0;
            func_8005A56C(0,(s16)D_801B8EBC,(s16)D_801B8EBC);
            if (!D_801B8EBC) {
                func_8005A4E8(0,0,0);
                break;
            }
        }
    }
    display.rgb24 = 0;
    /* The integer ratio truncates to one. This compiler retains the width
       read (retail word 310) while deleting the redundant store. */
    display.viewport.w *= 3 / 2;
    if (D_80189390->height >= 225) func_800678E0(&display);
    else func_800678E0(*screen_slot + 0x5C);
    func_80063538();
    return 0;
}
