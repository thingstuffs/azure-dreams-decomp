#include "common.h"

typedef struct {
    u8 pad0[0x48];
    s16 active;
    u8 pad4A[2];
    u16 timer;
} DungeonState;

typedef struct {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 height;
} DungeonOrigin;

typedef struct {
    u8 pad0[0x10];
    u8 red;
    u8 green;
    u8 blue;
} FadeColor;

typedef struct {
    void *ptr;
    u8 pad[8];
} DungeonPage;

extern u16 D_80027330;
extern u8 D_80027334[];
extern FadeColor D_80027398;
extern u16 D_8002745C[];
extern void *D_8002732C;
extern u8 D_800273BE;
extern s32 D_800273C0;
extern DungeonPage D_800E3D7C;
extern s32 D_800814A0;

extern void func_80024C08(void) __attribute__((noreturn));
extern void func_8002592C(s16, s16, s16, s16, s32);
extern void func_80026BA8(s32, s32, DungeonOrigin *);
extern void func_800419EC(s32, s32);
extern s32 func_80069EF8(void);
extern s16 func_800A07D0(s32, s32, s32, s32);
extern void func_8009CE1C(void *, s32, s32, s32, s32, s32, s32);
extern void *func_8009B4B0();

/* Animate nearby tile heights and fade the color, then finalize the dungeon transition. */
void func_8195F0BC(DungeonState *state, DungeonOrigin *origin) {
    FadeColor *fade_color;
    s32 grid_x;
    register s32 grid_y ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    s32 tile_x;
    s32 grid_y_fixed;
    s32 tile_y;
    s32 page_base;
    s32 unused_x;
    s32 grid_x_fixed;
    register s32 scratch ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 *height_ptr;
    register u16 *height_row ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *tile;
    s32 height;
    u16 timer;
    register s32 lookup_x ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 lookup_y ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    void *page;
    u8 *delta_ptr;
    u8 height_delta;
    register s32 hard_zero ASM_REG("$0");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */

#ifdef NON_MATCHING
    hard_zero = 0;
#endif

    D_80027330++;
    if (state->active == 0) {
        fade_color = (FadeColor *)0x80020000;
        if (!(state->timer & 3)) {
            func_800419EC(8, 16);
        }
        fade_color = (FadeColor *)&D_80027398;
        fade_color->red += (0xF0 - fade_color->red) / (s16)state->timer;
        fade_color->green += (0x40 - fade_color->green) / (s16)state->timer;
        fade_color->blue += (0x20 - fade_color->blue) / (s16)state->timer;

        grid_y = 1;
        scratch = (s32)D_8002745C;
        height_row = (u16 *)scratch + 8;
        do {
            grid_x = 1;
            height_ptr = height_row + 1;
            scratch = (u16)origin->y >> 6;
            scratch -= 3;
            tile_y = scratch + grid_y;
            do {
                scratch = (u16)origin->x >> 6;
                scratch -= 3;
                tile_x = scratch + grid_x;
                scratch = func_80069EF8();
                lookup_x = tile_x & 0xFFFF;
                lookup_y = tile_y & 0xFFFF;
                delta_ptr = D_80027334 + (grid_y << 3);
                delta_ptr += grid_x;
                page = (void *)0x800e0000;
                scratch &= 7;
                height_delta = *delta_ptr;
                ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                page = *(void **)((u8 *)page + 0x3D7C);
                height = *height_ptr;
                height += (s8)height_delta - scratch;
                *height_ptr = height;
                tile = func_8009B4B0(page, lookup_x, lookup_y, height);
                if (tile != 0 && tile != D_8002732C) {
                    *(u16 *)(*(u8 **)((u8 *)tile - 0x18) + 0xA) =
                        *height_ptr + origin->height;
                }
                if (!(func_80069EF8() & 7)) {
                    func_8002592C((s16)(tile_x << 6), (s16)(tile_y << 6),
                                   *(s16 *)height_ptr, (s16)grid_x,
                                   (s16)grid_y);
                }
                grid_x++;
                height_ptr++;
            } while (grid_x < 7);
            grid_y++;
            height_row += 8;
        } while (grid_y < 7);

        timer = state->timer - 1;
        state->timer = timer;
        grid_y = 0;
        if ((timer << 16) <= 0) {
            page_base = (s32)0x800e0000;
            grid_x = hard_zero;
            do {
                grid_y_fixed = grid_y << 16;
                grid_x_fixed = grid_x;
                do {
                    scratch = grid_x - 3;
                    lookup_x = (u16)origin->x;
                    page = *(void **)((u8 *)page_base + 0x3D7C);
                    lookup_y = (u16)origin->y;
                    lookup_x = (((u32)lookup_x >> 6) + scratch) & 0xFFFF;
                    lookup_y >>= 6;
                    scratch = grid_y - 3;
                       /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                    lookup_y += scratch;
                    lookup_y &= 0xFFFF;
                    tile = func_8009B4B0(page, lookup_x, lookup_y);
                    if (tile != 0 && tile != D_8002732C) {
                        func_8009CE1C(
                            tile, 16, D_800273BE, 9,
                            (s16)func_800A07D0(grid_x_fixed >> 16,
                                               grid_y_fixed >> 16, 3, 3),
                            D_800273C0, 2);
                        *(s32 *)((u8 *)tile + 0x14) &= 0xFFEFFFFF;
                    }
                    func_80026BA8(grid_x_fixed >> 16, grid_y_fixed >> 16, origin);
                    grid_x_fixed += 0x10000;
                    grid_x++;
                } while (grid_x < 7);
                grid_y++;
                grid_x = 0;
            } while (grid_y < 7);
            state->timer = 8;
            state->active++;
            func_80024C08();
        }
    } else {
        timer = state->timer - 1;
        state->timer = timer;
        if ((timer << 16) <= 0) {
            *((u16 *)state - 1) |= 0x8000;
            D_800814A0 |= 0x8000;
        }
    }
}
