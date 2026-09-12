#include "common.h"

extern u8 *D_800E3D7C;
extern u16 D_8008347E;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u16 D_800DCE6C[];
extern u16 D_800DCE8C[];

extern void func_8003DB4C(void *, s32);
extern s32 func_80065F90(s32, s32);
extern s32 func_8009A350(s32, s32, s32, u16 *);
extern s32 func_800A0134(void *, void *);
extern s32 func_800A0548(s32, s32);
extern s32 func_800BCB04(s32, s32, s32);

/* Find an unoccupied valid position at the target or within two tiles. */
s32 func_8009B88C(u8 *entry, s32 target_x, s32 target_y, s16 *out_x, s16 *out_y) {
    u16 tile_flags;
    u8 *occupied;
    u16 search_seed;
    u8 *actor;
    s32 near_x;
    u8 *object;
    s32 object_x;
    s32 object_y;
    u16 *near_dx;
    u16 *near_dy;
    u16 *far_dx;
    u16 *far_dy;
    s32 result_dx;
    s32 result_dy;
    s32 near_offset_x;
    s32 near_offset_y;
    s32 far_offset_x;
    s32 far_offset_y;
    s32 tile_offset_x;
    s32 tile_offset_y;
    s32 delta_x;
    s32 delta_y;
    s32 tile_distance;
    s32 separation;
    s32 y_distance;
    s16 slot;
    s32 near_dir;
    s32 far_dir;
    s16 attempts;
    s32 center_x;
    s32 center_y;
    s32 near_y;
    s32 far_x;
    s32 far_y;
    s32 wrap_pending;
    s16 wrap_check;

    occupied = (u8 *)0x1F800000;
    if (entry != 0) {
        actor = entry;
        wrap_pending = 0;
    } else {
        actor = D_800E3D7C;
        wrap_pending = 1;
        entry = *(u8 **)(actor + 88) + 32;
    }
    func_8003DB4C(occupied, 7);
    goto next_entry;

    do {
        object = *(u8 **)(entry - 20);
        object_x = *(u8 *)(object + 36);
        object_y = *(u8 *)(object + 37);
        delta_x = (s16)target_x - object_x;
        tile_distance = __builtin_abs(delta_x);
        delta_y = (s16)target_y - object_y;
        y_distance = __builtin_abs(delta_y);
        wrap_pending = 0;
        if (tile_distance < y_distance) {
            tile_distance = y_distance;
        }
        if (tile_distance < 3) {
            if (tile_distance == 0) {
                slot = 0;
            } else if (tile_distance == 1) {
                slot = (((func_80065F90(object_y - (s16)target_y, object_x - (s16)target_x) + 256) >> 9) & 7) + 1;
            } else {
                slot = (((func_80065F90(object_y - (s16)target_y, object_x - (s16)target_x) + 128) >> 8) & 15) + 9;
            }
            separation = (s16)func_800A0134(actor, entry);
            if (separation < 0) {
                separation = -separation;
            }
            if (separation < 64) {
                *(u8 *)((u32)slot | (u32)occupied) = 1;
            }
        }

    next_entry:
        entry = *(u8 **)(entry + 92) + 32;
    } while (entry != actor || (wrap_check = wrap_pending) != 0);
    ASM_KEEP_NV(entry);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if (occupied[0] != 0) {
        goto search_nearby;
    }
    center_x = (s16)target_x;
    center_y = (s16)target_y;
    if (func_800A0548(center_x, center_y) != 0) {
        goto search_nearby;
    }
    if ((func_8009A350((s16)(target_x - 1), center_y, 0, &tile_flags) << 16) == 0) {
        goto search_nearby;
    }
    if ((tile_flags & 0x8000) != 0) {
        goto search_nearby;
    }
    if ((tile_flags & 0x400) != 0 && (*(u32 *)(entry + 28) & 0x40000) == 0) {
        goto search_nearby;
    }
    if ((s16)func_800BCB04((((center_x << 6) + 32) & 0xffe0), (((center_y << 6) + 32) & 0xffe0),
                           (s16)(*(u16 *)(actor + 136) - 32)) >= 512) {
        goto search_nearby;
    }
    *out_x = target_x;
    *out_y = target_y;
    return 1;

found_near:
    result_dx = near_dx[0];
    *out_x = target_x + result_dx;
    result_dy = near_dy[0];
    *out_y = target_y + result_dy;
    return 1;

found_far:
    result_dx = far_dx[0];
    *out_x = target_x + result_dx;
    result_dy = far_dy[0];
    *out_y = target_y + result_dy;
    return 1;

search_nearby:
    attempts = 0;
    near_x = (s16)target_x;
    do {
        search_seed = D_8008347E;
    } while (0);
    near_y = (s16)target_y;
    ASM_USE(near_y);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    slot = search_seed & 7;
    do {
        near_dir = slot;
        ASM_USE2(target_x, target_x);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_USE2(target_x, target_x);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_USE2(target_y, target_y);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        if (*(occupied + near_dir + 1) == 0) {
            near_dx = D_8006CCD8 + near_dir;
            near_dy = D_8006CCE8 + near_dir;
            ASM_USE(near_dy);   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if ((near_offset_x = near_dx[0], near_offset_y = near_dy[0],
                 func_800A0548((s16)(target_x + near_offset_x), (s16)(target_y + near_offset_y))) == 0 &&
                (func_8009A350(near_x, near_y, near_dir, &tile_flags) << 16) != 0 &&
                (tile_flags & 0x8000) == 0 &&
                ((tile_flags & 0x400) == 0 || (*(u32 *)(entry + 28) & 0x40000) != 0) &&
                (s16)func_800BCB04((((near_x + (s16)near_dx[0]) << 6) + 32) & 0xffe0,
                                   (((near_y + (s16)near_dy[0]) << 6) + 32) & 0xffe0,
                                   (s16)(*(u16 *)(actor + 136) - 32)) < 512) {
                goto found_near;
            }
        }
        attempts++;
        slot = (slot + 1) & 7;
    } while (attempts < 8);

    attempts = 0;
    far_x = (s16)target_x;
    search_seed = D_8008347E;
    far_y = (s16)target_y;
    slot = search_seed & 15;
    do {
        far_dir = slot;
        ASM_USE2(target_x, target_x);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        ASM_USE2(target_y, target_y);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
        if (*(occupied + far_dir + 9) == 0) {
            far_dx = D_800DCE6C + far_dir;
            far_dy = D_800DCE8C + far_dir;
               /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
            if ((far_offset_x = far_dx[0], far_offset_y = far_dy[0],
                 func_800A0548((s16)(target_x + far_offset_x), (s16)(target_y + far_offset_y))) == 0 &&
                ((tile_offset_x = far_dx[0], tile_offset_y = far_dy[0],
                  func_8009A350((s16)(target_x + tile_offset_x - 1), (s16)(target_y + tile_offset_y), 0, &tile_flags)) << 16) != 0 &&
                (tile_flags & 0x8000) == 0 &&
                ((tile_flags & 0x400) == 0 || (*(u32 *)(entry + 28) & 0x40000) != 0) &&
                (s16)func_800BCB04((((far_x + (s16)far_dx[0]) << 6) + 32) & 0xffe0,
                                   (((far_y + (s16)far_dy[0]) << 6) + 32) & 0xffe0,
                                   (s16)(*(u16 *)(actor + 136) - 32)) < 512) {
                goto found_far;
            }
        }
        attempts++;
        slot = (slot + 1) & 15;
    } while (attempts < 16);
    ASM_USE_NV(entry);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    return 0;
}
