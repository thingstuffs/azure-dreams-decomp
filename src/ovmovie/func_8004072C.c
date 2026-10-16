#include "modules/ovmovie_game.h"

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
