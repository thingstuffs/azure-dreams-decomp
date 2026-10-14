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

typedef struct { u8 pad00[8]; u32 frame; u8 pad0C[4]; u16 width,height; } FrameInfo;
typedef struct { u8 pad00[0x14]; s16 w0,h0; u8 pad18[4]; s16 w1,h1; u8 pad20[10]; s16 rounded_height; } FrameDisplay;
extern u8 D_80189388[8];
extern s32 func_80063828(s32 *,FrameInfo **);
extern void func_80060D90(s32,u8 *);
s32 func_80176F2C(u8 *display) {
    s32 data;
    FrameInfo *info;
    s32 polls_left = 0x800000;
    s32 width;
    s32 rounded;
    MovieState *movie;
    MovieState *dimensions;
    while (func_80063828(&data,&info)) {
        func_80060D90(1,D_80189388);
        if (D_80189388[0] & 0x10) return 1;
        if (--polls_left == 0) return 0;
    }
    if (info->frame >= (u32)D_801781D4) D_80189390->done = 1;
    movie = D_80189390;
    D_801781D0 = info->frame;
    if (movie->width != info->width || movie->height != info->height) {
        movie->width = info->width;
        movie->height = info->height;
    }
    if (D_801781E0 & 1) width = (D_80189390->width * 3) / 2;
    else width = (u16)D_80189390->width;
    *(s16 *)(display + 0x1C) = width;
    *(s16 *)(display + 0x14) = width;
    dimensions = D_80189390;
    *(s16 *)(display + 0x16) = *(s16 *)(display + 0x1E) = dimensions->height;
    rounded = dimensions->height + 15;
    if (rounded < 0) rounded = dimensions->height + 30;
    ((FrameDisplay *)display)->rounded_height = rounded & 0xFFF0;
    return data;
}
