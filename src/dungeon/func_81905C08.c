#include "common.h"

typedef struct {
    u8 bytes[0x20];
} LocalPoints;

typedef struct {
    u16 x;
    u16 y;
    u16 w;
    u16 h;
} Box __attribute__((packed));

typedef struct {
    u16 x;
    u16 y;
    u16 z;
    u16 pad;
} PackedVector __attribute__((packed));

typedef struct {
    u16 x;
    u16 y;
} Point __attribute__((packed));

extern void func_80024B6C(void *, Box *, Point *, s32, s32);
extern s32 func_80067014(s32);
extern void func_800672D8(Box *, u8 *);
extern void func_8006733C(Box *, u8 *);
extern void func_800B8FC8(void *, Box *, Point *, s32, s32);
extern LocalPoints D_80024004;
extern PackedVector D_8002400C;
extern s16 D_800267B8;
extern u8 D_80026820[];
extern s32 D_800814A0;

/* Builds an inverted pixel mask and updates a timed fade effect. */
void func_80025408(void *context, void *unused, void *effect_data) {
    Box image_rect;
    Box mask_rect;
    Point center;
    s32 state;
    s32 tile_column;
    s32 tile_row;
    s32 tile_x;
    s32 mask_x;
    s32 tile_y;
    register u16 mask_pixel ASM_REG("$23");
    s16 frame;
    s32 pixel_index;
    s32 one;
    s32 image_width;
    u16 *pixel;
    void *effect;
    u8 *pixel_page;
    Box *rect_template;

    effect = effect_data;
    rect_template = (Box *)(void *)&D_80024004;
    image_rect = *rect_template;
#ifdef NON_MATCHING
    rect_template = (Box *)(void *)&D_8002400C;
#else
    rect_template = (Box *)((u8 *)&D_8002400C);
#endif
    mask_rect = *rect_template;
    state = *(s16 *)context;
    D_800267B8 = 1;
    if (state != 0) {
        if (state == 1) {
            goto update_fade;
        }
        goto update_visibility;
    }

    tile_column = 0;
    pixel_page = (u8 *)0x80020000;
    mask_pixel = -1;
    tile_x = 0x340;
    do {
        tile_row = 0;
        mask_x = tile_x;
        tile_y = 0x154;
        do {
            mask_rect.w = 0x18;
            mask_rect.x = mask_x;
            mask_rect.y = tile_y;
            mask_rect.h = 0x15;
            func_8006733C(&mask_rect, pixel_page + 0x6820);
            do {
            } while (func_80067014(1) != 0);
            pixel = (u16 *)(pixel_page + 0x6820);
            pixel_index = 0;
            do {
                if (*pixel == 0) {
                    *pixel = mask_pixel;
                } else {
                    *pixel = 0;
                }
                pixel_index += 1;
                pixel += 1;
            } while (pixel_index < 0x1f8);
            func_800672D8(&mask_rect, pixel_page + 0x6820);
            tile_row += 1;
            tile_y += 0x15;
        } while (tile_row < 4);
        tile_column += 1;
        tile_x += 0x18;
    } while (tile_column < 4);
    *(s16 *)context = (u16)*(s16 *)context + 1;
    *(u16 *)((u8 *)effect + 0x14) &= 0xff7f;
update_fade:
    {
        Box *call_rect;
        register Point *call_center ASM_REG("$6");

        call_rect = &mask_rect;
        tile_column = &center;
        call_center = tile_column;
        tile_x = 0x340;
        pixel_page = (u8 *)0x100;
        ASM_KEEP_NV(call_rect);
        ASM_KEEP_NV(call_center);
        image_width = 0x60;
        mask_rect.w = image_width;
        mask_rect.x = tile_x;
        mask_rect.y = (s32)pixel_page;
        mask_rect.h = 0x54;
        center.x = 0x370;
        center.y = 0x148;
        one = 1;
        func_800B8FC8(*(void **)((u8 *)context + 0x44), call_rect, call_center, 0, one);
    }
    {
        Box *call_rect;
        Point *call_center;

        call_rect = &image_rect;
        call_center = tile_column;
        image_rect.w = 0x60;
        image_rect.x = tile_x;
        image_rect.y = (s32)pixel_page;
        image_rect.h = 0x54;
        center.x = 0x370;
        center.y = 0x12a;
        func_80024B6C(*(void **)((u8 *)context + 0x48), call_rect, call_center, one, one);
    }
    frame = *(s16 *)((u8 *)context + 2);
    if (frame < 0x15) {
        *(s8 *)((u8 *)effect + 0xe) = (frame << 7) / 20;
        *(s8 *)((u8 *)effect + 0xd) = (*(s16 *)((u8 *)context + 2) << 7) / 20;
        *(s8 *)((u8 *)effect + 0xc) = (*(s16 *)((u8 *)context + 2) << 7) / 20;
    }
    if (*(s16 *)((u8 *)context + 2) >= 0x51) {
        *(s8 *)((u8 *)effect + 0xe) = ((0x64 - *(s16 *)((u8 *)context + 2)) << 7) / 20;
        *(s8 *)((u8 *)effect + 0xd) = ((0x64 - *(s16 *)((u8 *)context + 2)) << 7) / 20;
        *(s8 *)((u8 *)effect + 0xc) = ((0x64 - *(s16 *)((u8 *)context + 2)) << 7) / 20;
    }
    frame = (u16)*(s16 *)((u8 *)context + 2) + 1;
    *(s16 *)((u8 *)context + 2) = frame;
    if (frame >= 0x65) {
        *(s16 *)((u8 *)context + 2) = 0;
        *(s16 *)context = (u16)*(s16 *)context + 1;
        *(s16 *)(*(u8 **)((u8 *)context + 0x40) + 0x9c) = one;
        *(u16 *)((u8 *)context - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
update_visibility:
    if ((u32)(*(u8 *)(*(u8 **)((u8 *)context + 0x3c) + 0x13) - 0x33) < 4U) {
        *(u16 *)((u8 *)effect + 0x14) |= 0x80;
    }
    return;
}
