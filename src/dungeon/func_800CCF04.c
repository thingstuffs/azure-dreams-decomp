#include "common.h"


typedef void (*DungeonCallback)(void *, void *, void *, void *);

extern u16 D_80083462;
extern DungeonCallback D_800E2228[];

extern s16 func_800BCB04(u16, u16, s16);


typedef struct S_800D2664_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D2664_0;   /* pos in func_800D2664 */

typedef struct S_800D2664_1 {
    u8 pad_00[0x90];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_90;   /* overlapping accesses */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 pad_9A[0x3];
    u8 unk_9D;
} S_800D2664_1;   /* obj in func_800D2664 */

typedef struct S_800D2664_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800D2664_2;   /* ent in func_800D2664 */

/* Runs object callbacks, applies movement and gravity, and updates ground height. */
void func_800D2664(void *object, void *motion, void *entity) {
    void *ent = entity;
    void *update_obj = object;
    DungeonCallback callback;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 fall_offset;
    s32 fall_speed;
    u16 fall_flags;
    s16 ground_height;
    s16 base_height;
    s32 base_height_u;

    if (D_80083462 & 0x2000) {
        (*(u8 *)((u8 *)update_obj + (0x71))) &= 0x7F;
        return;
    }


    callback = (*(DungeonCallback *)((u8 *)update_obj + (0x8C)));
    if (callback != 0) {
        callback(update_obj, motion, ent, update_obj);
    }
    D_800E2228[(*(u8 *)((u8 *)update_obj + (0x9A)))](update_obj, motion, ent, update_obj);

    x = ((S_800D2664_0 *)motion)->unk_00.at00.v;
    dx = ((S_800D2664_0 *)motion)->unk_0C;
    y = ((S_800D2664_0 *)motion)->unk_04.at00.v;
    dy = ((S_800D2664_0 *)motion)->unk_10;
    ((S_800D2664_0 *)motion)->unk_00.at00.v = x + dx;
    ((S_800D2664_0 *)motion)->unk_04.at00.v = y + dy;

    if ((*(u16 *)((u8 *)update_obj + (0x98))) & 8) {
        (*(u8 *)((u8 *)update_obj + (0x9D))) = 0;
    } else {
        ((S_800D2664_0 *)motion)->unk_14 += (*(s8 *)((u8 *)update_obj + (0x9D))) * 0x14000;
        (*(u8 *)((u8 *)update_obj + (0x9D)))++;
    }
    fall_offset = ((S_800D2664_1 *)object)->unk_90.at00.v;
    fall_speed = ((S_800D2664_0 *)motion)->unk_14;
    fall_flags = ((S_800D2664_1 *)object)->unk_98;
    ((S_800D2664_1 *)object)->unk_90.at00.v = fall_offset + fall_speed;

    if (fall_flags & 4) {
        goto clear_fall_flag;
    }

    ground_height = func_800BCB04(
        ((S_800D2664_0 *)motion)->unk_00.at02.v,
        ((S_800D2664_0 *)motion)->unk_04.at02.v,
        (s16)((*(u16 *)((u8 *)update_obj + (0x88))) - 0x20));
    if (ground_height >= 0x200) {
        goto clear_fall_flag;
    }

    base_height_u = (*(u16 *)((u8 *)update_obj + (0x88)));
    base_height = (*(s16 *)((u8 *)update_obj + (0x88)));
    if (((S_800D2664_1 *)object)->unk_90.at02.v + base_height < ground_height) {
        u16 object_flags = ((S_800D2664_1 *)object)->unk_98;
        ASM_KEEP(object_flags);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    } else {
        if (ground_height >= base_height) {
            ((S_800D2664_1 *)object)->unk_90.at00.v = 0;
        } else {
            ((S_800D2664_1 *)object)->unk_90.at02.v = ground_height - base_height_u;
        }
        ((S_800D2664_0 *)motion)->unk_14 = 0;
        (*(u32 *)((u8 *)update_obj + (0x1C))) |= 0x08000000;
        ((S_800D2664_1 *)object)->unk_9D = 0;
    }

    if ((*(u32 *)((u8 *)update_obj + (0x1C))) & 0x40000000) {
        s32 tile_x;
        s32 tile_y;
        (*(u32 *)((u8 *)update_obj + (0x1C))) &= ~0x40000000;
        tile_x = (((S_800D2664_2 *)ent)->unk_24 << 6) | 0x20;
        tile_y = (((S_800D2664_2 *)ent)->unk_25 << 6) | 0x20;
        ground_height = func_800BCB04(
            tile_x, tile_y, (s16)((*(u16 *)((u8 *)update_obj + (0x88))) - 0x20));
        ((S_800D2664_1 *)object)->unk_90.at02.v += (*(u16 *)((u8 *)update_obj + (0x88))) - ground_height;
        (*(s16 *)((u8 *)update_obj + (0x88))) = ground_height;
    }
    goto finish;

clear_fall_flag:
    (*(u32 *)((u8 *)update_obj + (0x1C))) &= ~0x08000000;

finish:
    ((S_800D2664_0 *)motion)->unk_0A = (*(u16 *)((u8 *)update_obj + (0x88))) + ((S_800D2664_1 *)object)->unk_90.at02u.v;
    ((S_800D2664_2 *)ent)->unk_14 |= 0x40;
    (*(u32 *)((u8 *)update_obj + (0x1C))) |= 0x200;
}
