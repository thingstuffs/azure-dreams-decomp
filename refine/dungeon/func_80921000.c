#include "common.h"
#include "m2c_compat.h"

typedef struct S_80921000_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    s16 unk_08;
} S_80921000_0;   /* arg0 in BODY_NAME */


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
s32 func_800A7A38(void *);
void func_800A7A7C(u8, u8, s16, s32, void *);
s16 func_800BCB04(s32, s32, s16);
s32 func_800F61BC(s32, s32);
s32 func_800F6208(s32, s32);
extern u8 D_80081484[];
extern u8 D_800F6D48[];

#ifdef __mips__
static const u32 split_prefix[] __asm__("func_80921000")
    __attribute__((section(".text.func_80921000"), aligned(4))) = {
    0x00000001, 0x00010001, 0x00010000, 0x0001FFFF,
    0x0000FFFF, 0xFFFFFFFF, 0xFFFF0000, 0xFFFF0001,
};
__asm__(".globl func_80921000\n"
        ".size func_80921000, 444");
#define BODY_NAME func_80921020
#else
#define BODY_NAME func_80921000
#endif

/* Advance the animation and handle delayed object spawning. */
void BODY_NAME(S_80921000_0 *state) {
    ByteBuf spawn_data;
    CoordBuf spawn_tile;
    s16 spawn_height;
    s16 spawn_delay;
    s32 height_result;
    u16 anim_ticks;
    u16 anim_offset;

    M2C_ERROR(/* Read from unset register $at */) << 0;
    anim_ticks = state->unk_02 - 1;
    state->unk_02 = anim_ticks;
    if ((anim_ticks << 0x10) <= 0) {
        state->unk_02 = 1U;
        anim_offset = state->unk_06 + 8;
        state->unk_06 = anim_offset;
        if ((s16) anim_offset >= 0x70) {
            state->unk_06 = 0U;
        }
        func_8003F80C(D_800F6D48 + ((s16) state->unk_06 * 4), 0x7380, 1, 2);
    }
    if ((func_80033BC0(0xA2) != 0) && ((func_800F61BC(6, 3) << 0x10) == 0) && ((func_800F6208(6, 3) << 0x10) == 0)) {
        u8 *mode;
        mode = D_80081484;
        if ((mode[0] != 3) || (mode[1] != 6)) {
            if (state->unk_08 == 0) {
                state->unk_08 = 0x40;
                goto check_spawn_delay;
            }
            goto decrement_spawn_delay;
        }
    }
check_spawn_delay:
    if (state->unk_08 != 0) {
decrement_spawn_delay:
        spawn_delay = (u16) state->unk_08 - 1;
        state->unk_08 = spawn_delay;
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
