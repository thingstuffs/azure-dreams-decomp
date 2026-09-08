#include "common.h"

typedef struct S_80171590_0 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171590_0;   /* state in func_80171590 */

typedef struct S_80171590_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171590_1;   /* arg2 in func_80171590 */

typedef struct S_80171590_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    u8 pad_9B[0x9];
    s16 unk_A4;
} S_80171590_2;   /* arg0 in func_80171590 */

typedef struct S_80171590_3 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_80171590_3;   /* (u8 *)state + ((S_80171590_0 *)state)->unk_8A.s in func_80171590 */



extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_8009A66C();
extern s16 func_800A0818();
extern s32 func_80171F58();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801752AC[];

/* Advances the entity along its stored path and updates movement state. */
void func_80171590(void *motion_arg, s32 update_arg, void *entity_arg, void *state_arg) {
    void *motion = motion_arg;
    s32 update_param = update_arg;
    void *entity = entity_arg;
    void *state = state_arg;
    s32 tile_mask;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    register s16 heading ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s16 move_result ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    if (((S_80171590_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (!((s32)((S_80171590_0 *)state)->unk_71.u > ((S_80171590_0 *)state)->unk_8A.s)) {
        return;
    }

    if (((S_80171590_1 *)entity)->unk_2C != D_801752AC) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_801752AC;
        func_80047784(
            entity,
            D_801752AC[((D_80083228 + ((S_80171590_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    old_x = ((S_80171590_1 *)entity)->unk_24;
    old_y = ((S_80171590_1 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((S_80171590_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A3D0(old_x, old_y, tile_mask);

    heading = func_800A0818(
        old_x,
        old_y,
        ((S_80171590_3 *)((u8 *)state + ((S_80171590_0 *)state)->unk_8A.s))->unk_74,
        ((S_80171590_3 *)((u8 *)state + ((S_80171590_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)motion + 0x98);
    move_result = func_8009A66C(heading, entity, state, 0x20);

    ((S_80171590_1 *)entity)->unk_24 =
        ((S_80171590_3 *)((u8 *)state + ((S_80171590_0 *)state)->unk_8A.s))->unk_74;
    ((S_80171590_1 *)entity)->unk_25 =
        ((S_80171590_3 *)((u8 *)state + ((S_80171590_0 *)state)->unk_8A.s))->unk_7C;
    ((S_80171590_0 *)state)->unk_8A.u++;

    new_x = ((S_80171590_1 *)entity)->unk_24;
    new_y = ((S_80171590_1 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((S_80171590_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A21C(new_x, new_y, tile_mask);
    ((S_80171590_0 *)state)->unk_2A = heading;

    if (move_result == 2) {
        if (D_80083462 & 0x80) {
            goto failure;
        }
        if (((S_80171590_1 *)entity)->unk_14 & 0x8000) {
            ((S_80171590_2 *)motion)->unk_9A = 15;
            goto finish_step;
        }
    } else {
        if (move_result != 3) {
            goto failure;
        }
        if (D_80083462 & 0x80) {
            goto failure;
        }
        if (((S_80171590_1 *)entity)->unk_14 & 0x8000) {
            goto failure;
        }
    }

    func_80171F58(motion, update_param, entity, state);
    ((S_80171590_2 *)motion)->unk_A4 = move_result;
    goto finish_step;

failure:
    ((S_80171590_2 *)motion)->unk_9A = 15;
finish_step:
    ((S_80171590_2 *)motion)->unk_8C = 0;
    (*(u32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (D_80083462 & 0x80) {
        ((S_80171590_2 *)motion)->unk_96 = 0;
        return;
    }
    ((S_80171590_2 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((S_80171590_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((S_80171590_2 *)motion)->unk_96 = 8 / step_count;
        }
    }
    return;
}
