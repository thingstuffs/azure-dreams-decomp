#include "common.h"


typedef void (*DungeonCallback)(void *, void *, void *, void *);

extern u16 D_80083462;
extern DungeonCallback D_800E2228[];

extern s16 func_800BCB04(u16, u16, s16);
extern void func_800D276C(s32, s32);
extern void func_800D27F8();
extern void func_800D2810();
extern void func_800D2890();
extern void func_800D28C4();


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

void func_800D2664(void *arg0, void *arg1, void *arg2) {
    S_800D2664_1 *obj = arg0;
    S_800D2664_0 *pos = arg1;
    S_800D2664_2 *ent = arg2;
    register void *work ASM_REG("$16") = obj;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    DungeonCallback callback;
    s32 x;
    s32 y;
    s32 dx;
    s32 dy;
    s32 fall_accum;
    s32 fall_delta;
    u16 fall_flags;
    s16 result;
    s16 height;
    s32 uheight;

    if (D_80083462 & 0x2000) {
        (*(u8 *)((u8 *)work + 0x71)) &= 0x7F;
        return;
    }

    ASM_KEEP(obj);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(pos);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(ent);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(work);   /* MATCH pin: retail basic-block layout depends on it */

    callback = (*(DungeonCallback *)((u8 *)work + 0x8C));
    if (callback != 0) {
        callback(work, pos, ent, work);
    }
    D_800E2228[(*(u8 *)((u8 *)work + 0x9A))](work, pos, ent, work);

    x = pos->unk_00.at00.v;
    dx = pos->unk_0C;
    y = pos->unk_04.at00.v;
    dy = pos->unk_10;
    pos->unk_00.at00.v = x + dx;
    pos->unk_04.at00.v = y + dy;

    if ((*(u16 *)((u8 *)work + 0x98)) & 8) {
        (*(u8 *)((u8 *)work + 0x9D)) = 0;
        func_800D276C(dx, dy);
        return;
    }

    pos->unk_14 += (*(s8 *)((u8 *)work + 0x9D)) * 0x14000;
    (*(u8 *)((u8 *)work + 0x9D))++;
    fall_accum = obj->unk_90.at00.v;
    fall_delta = pos->unk_14;
    fall_flags = obj->unk_98;
    obj->unk_90.at00.v = fall_accum + fall_delta;

    if (fall_flags & 4) {
        goto clear_fall_flag;
    }

    result = func_800BCB04(
        pos->unk_00.at02.v,
        pos->unk_04.at02.v,
        (s16)((*(u16 *)((u8 *)work + 0x88)) - 0x20));
    if (result >= 0x200) {
        goto clear_fall_flag;
    }

    uheight = (*(u16 *)((u8 *)work + 0x88));
    height = (*(s16 *)((u8 *)work + 0x88));
    if (obj->unk_90.at02.v + height < result) {
        u16 tail_flags = obj->unk_98;
        ASM_KEEP(tail_flags);   /* MATCH pin: retail basic-block layout depends on it */
        func_800D2810();
        return;
    }
    if (result >= height) {
        obj->unk_90.at00.v = 0;
        func_800D27F8();
        return;
    }

    obj->unk_90.at02.v = result - uheight;
    pos->unk_14 = 0;
    (*(u32 *)((u8 *)work + 0x1C)) |= 0x08000000;
    obj->unk_9D = 0;

    if ((*(u32 *)((u8 *)work + 0x1C)) & 0x40000000) {
        s32 tile_x;
        s32 tile_y;
        (*(u32 *)((u8 *)work + 0x1C)) &= ~0x40000000;
        tile_x = (ent->unk_24 << 6) | 0x20;
        tile_y = (ent->unk_25 << 6) | 0x20;
        result = func_800BCB04(
            tile_x, tile_y, (s16)((*(u16 *)((u8 *)work + 0x88)) - 0x20));
        obj->unk_90.at02.v += (*(u16 *)((u8 *)work + 0x88)) - result;
        (*(s16 *)((u8 *)work + 0x88)) = result;
        func_800D2890();
        return;
    }
    goto finish;

clear_fall_flag:
    (*(u32 *)((u8 *)work + 0x1C)) &= ~0x08000000;

finish:
    pos->unk_0A = (*(u16 *)((u8 *)work + 0x88)) + obj->unk_90.at02u.v;
    ent->unk_14 |= 0x40;
    (*(u32 *)((u8 *)work + 0x1C)) |= 0x200;
}
