#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AA258_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
} S_800AA258_0;   /* arg0 in func_800AA258 */

typedef struct S_800AA258_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x4A];
    u16 unk_6A;
} S_800AA258_1;   /* arg3 in func_800AA258 */

typedef struct S_800AA258_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    union { u8 s; volatile u8 u; } unk_25;   /* accessed as both */
} S_800AA258_2;   /* arg2 in func_800AA258 */


M2C_UNK func_8009A21C();                 /* extern */
M2C_UNK func_8009A3D0();                 /* extern */
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern struct {
    s8 pad0[10];
    u16 field_0x0A;
    s8 pad1[10];
} D_80083460;

/* Move the position one step in the actor's direction and update movement state. */
void func_800AA258(S_800AA258_0 *state, void *unused, S_800AA258_2 *position, S_800AA258_1 *actor) {
    register s32 next_x ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s32 direction_index;
    s32 tile_mask;
    s32 move_mask;

    state->unk_9A = 0xA;
    state->unk_9B = 0;
    state->unk_8C = 0;
    move_mask = 0x3000;
    if (actor->unk_1C & 0x2000) {
        move_mask = 0x300;
    }
    tile_mask = move_mask & 0xFFFF;
    func_8009A3D0(position->unk_24, position->unk_25.s, tile_mask);
    direction_index = ((u16) actor->unk_6A >> 8) & 0xE;
    next_x = position->unk_24;
    next_x = next_x + (u8) *(direction_index + &D_8006CCD8);
    position->unk_24 = (u8) next_x;
    position->unk_25.s = (u8) (position->unk_25.s + *(direction_index + &D_8006CCE8));
    func_8009A21C(position->unk_24, position->unk_25.u, tile_mask);
    actor->unk_1C = (s32) (actor->unk_1C & ~0x100);
    state->unk_96 = 0x21;
    state->unk_98 = (u16) (state->unk_98 | 8);
    D_80083460.field_0x0A = (u16)(D_80083460.field_0x0A + 1);
}

/* MECHANISM: Natural argument liveness yields the retail 0x28 frame and s2/s1/s3/s0 save order.
   Byte-scaled s8 tables plus an unsigned load preserve srl 8 / mask 0xE and select lbu.
   A guarded v0 sum accumulator and post-store schedule barrier reproduce the table roles and store order. */
