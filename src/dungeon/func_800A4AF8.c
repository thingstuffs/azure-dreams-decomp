#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"



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
void func_800AA258(Rec_func_800A9E70_arg0 *state, void *unused, S_800AA258_2 *position, Rec_D_800E3D7C *actor) {
    s32 next_x;
    s32 direction_index;
    s32 tile_mask;
    s32 move_mask;

    state->unk_9A.as_s8 = 0xA;
    state->unk_9B.as_s8 = 0;
    state->unk_8C = 0;
    move_mask = 0x3000;
    if (actor->unk_1C.as_s32 & 0x2000) {
        move_mask = 0x300;
    }
    tile_mask = move_mask & 0xFFFF;
    func_8009A3D0(position->unk_24, position->unk_25.s, tile_mask);
    direction_index = ((u16) actor->unk_6A.as_u16 >> 8) & 0xE;
    next_x = (position->unk_24 + (u8) *(direction_index + &D_8006CCD8)) + direction_index;
    next_x -= direction_index;
    position->unk_24 = (u8) next_x;
    position->unk_25.s = (u8) (position->unk_25.s + *(direction_index + &D_8006CCE8));
    func_8009A21C(position->unk_24, position->unk_25.u, tile_mask);
    actor->unk_1C.as_s32 = (s32) (actor->unk_1C.as_s32 & ~0x100);
    state->unk_96.as_s16 = 0x21;
    state->unk_98 = (u16) (state->unk_98 | 8);
    D_80083460.field_0x0A = (u16)(D_80083460.field_0x0A + 1);
}

/* MECHANISM: Natural argument liveness yields the retail 0x28 frame and s2/s1/s3/s0 save order.
   Byte-scaled s8 tables plus an unsigned load preserve srl 8 / mask 0xE and select lbu.
   A guarded v0 sum accumulator and post-store schedule barrier reproduce the table roles and store order. */
