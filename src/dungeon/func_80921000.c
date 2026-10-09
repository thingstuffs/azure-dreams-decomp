#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"


typedef struct {
    s8 a;
    s8 b;
    s8 c;
    s8 d;
} ByteBuf;

typedef struct {
    u8 x;
    u8 y;
} CoordBuf;

s32 func_80033BC0(s32);
void func_8003F80C(void *, s32, s32, s32);
s32 func_800A4E2C(u8 *, u8 *);
s32 func_800A7A38(u8 *item);
void func_800A7A7C(u8, u8, s16, s32, void *);
s16 func_800BCB04(s32, s32, s16);
s32 func_800F61BC(s32, s32);
s32 func_800F6208(s32, s32);
extern u8 D_80081484[];
extern u8 D_800F6D48[];

/* Advance the animation and handle delayed object spawning. */
void func_80921020(EntityRec *state) {
    ByteBuf spawn_data;
    CoordBuf spawn_tile;
    s16 spawn_height;
    s16 spawn_delay;
    s32 height_result;
    u16 anim_ticks;
    u16 anim_offset;

    M2C_ERROR(/* Read from unset register $at */) << 0;
    anim_ticks = ((u16)state->x.w.i) - 1;
    state->x.w.i = anim_ticks;
    if ((anim_ticks << 0x10) <= 0) {
        state->x.w.i = 1U;
        anim_offset = ((u16)state->y.w.i) + 8;
        state->y.w.i = anim_offset;
        if ((s16) anim_offset >= 0x70) {
            state->y.w.i = 0U;
        }
        func_8003F80C(D_800F6D48 + ((s16) ((u16)state->y.w.i) * 4), 0x7380, 1, 2);
    }
    if ((func_80033BC0(0xA2) != 0) && ((func_800F61BC(6, 3) << 0x10) == 0) && ((func_800F6208(6, 3) << 0x10) == 0)) {
        u8 *mode;
        mode = D_80081484;
        if ((mode[0] != 3) || (mode[1] != 6)) {
            if ((*(s16 *)&state->z) == 0) {
                (*(s16 *)&state->z) = 0x40;
            }
        }
    }
    if ((*(s16 *)&state->z) != 0) {
        spawn_delay = (u16) (*(s16 *)&state->z) - 1;
        (*(s16 *)&state->z) = spawn_delay;
        if ((spawn_delay << 0x10) == 0) {
            spawn_data.a = 3;
            spawn_data.b = 6;
            spawn_data.c = 0;
            spawn_data.d = 0;
            do {

            } while ((func_800A4E2C(&spawn_tile.x, &spawn_tile.y) << 0x10) < 0);
            height_result = func_800BCB04((spawn_tile.x << 6) | 0x20, (spawn_tile.y << 6) | 0x20, -0x400);
            spawn_height = height_result;
            func_800A7A7C(spawn_tile.x, spawn_tile.y, spawn_height, func_800A7A38(&spawn_data), &spawn_data);
        }
    }
}
