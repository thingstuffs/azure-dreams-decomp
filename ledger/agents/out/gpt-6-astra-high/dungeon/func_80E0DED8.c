#include "common.h"
#include "m2c_compat.h"

typedef struct S_801716D8_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    s8 unk_71;
    u8 pad_72[0x18];
    s16 unk_8A;
} S_801716D8_0;   /* state in func_801716D8 */

typedef struct S_801716D8_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_801716D8_1;   /* arg2 in func_801716D8 */

typedef struct S_801716D8_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801716D8_2;   /* temp_v0 in func_801716D8 */

typedef struct S_801716D8_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
} S_801716D8_3;   /* arg0 in func_801716D8 */

typedef struct S_801716D8_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801716D8_4;   /* (state + ((S_801716D8_0 *)state)->unk_8A) in func_801716D8 */


M2C_UNK func_80047784();         /* extern */
M2C_UNK func_8009A21C();             /* extern */
M2C_UNK func_8009A3D0();             /* extern */
M2C_UNK func_8009A66C(); /* extern */
s16 func_800A0818();             /* extern */
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80176460[8];

/* Advance the entity along its stored path and update its heading and movement timing. */
void func_801716D8(void *motion, void *unused, void *entity, void *path_state) {
    M2C_UNK old_cell_mask;
    M2C_UNK new_cell_mask;
    s16 heading;
    register s32 step_count ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    s32 old_x;
    s32 old_y;
    s32 next_x;
    s32 next_y;
    s32 move_flag;
    void *path_step;
    void *state = path_state;

    if ((((S_801716D8_0 *)state)->unk_71 > 0) && ((s32) (u8) ((S_801716D8_0 *)state)->unk_71 > ((S_801716D8_0 *)state)->unk_8A)) {
        if (((S_801716D8_1 *)entity)->unk_2C != D_80176460) {
            (*(void **)((u8 *)entity + 0x2C)) = D_80176460;
            func_80047784(entity, D_80176460[((D_80083228 + ((S_801716D8_0 *)state)->unk_2A + 0x100) >> 9) & 7], 0);
        }
        old_x = ((S_801716D8_1 *)entity)->unk_24;
        old_y = ((S_801716D8_1 *)entity)->unk_25;
        old_cell_mask = 0x3000;
        if (((S_801716D8_0 *)state)->unk_1C & 0x2000) {
            old_cell_mask = 0x300;
        }
        func_8009A3D0(old_x, old_y, old_cell_mask);
        path_step = state + ((S_801716D8_0 *)state)->unk_8A;
        heading = func_800A0818(old_x, old_y, ((S_801716D8_2 *)path_step)->unk_74, ((S_801716D8_2 *)path_step)->unk_7C, motion + 0x98);
        func_8009A66C(heading, entity, state, 0x20);
        ((S_801716D8_1 *)entity)->unk_24 = (u8) ((S_801716D8_4 *)((state + ((S_801716D8_0 *)state)->unk_8A)))->unk_74;
        ((S_801716D8_1 *)entity)->unk_25 = (u8) ((S_801716D8_4 *)((state + ((S_801716D8_0 *)state)->unk_8A)))->unk_7C;
        ((S_801716D8_0 *)state)->unk_8A = (s16) ((u16) ((S_801716D8_0 *)state)->unk_8A + 1);
        move_flag = ((S_801716D8_0 *)state)->unk_1C & 0x2000;
        next_x = ((S_801716D8_1 *)entity)->unk_24;
        next_y = ((S_801716D8_1 *)entity)->unk_25;
        new_cell_mask = 0x3000;
        if (move_flag) {
            new_cell_mask = 0x300;
        }
        func_8009A21C(next_x, next_y, new_cell_mask);
        ((S_801716D8_0 *)state)->unk_2A = heading;
        ((S_801716D8_3 *)motion)->unk_9A = 0xF;
        ((S_801716D8_3 *)motion)->unk_8C = 0;
        (*(s32 *)((u8 *)state + 0x1C)) = (s32) (((S_801716D8_0 *)state)->unk_1C | 0x40000000);
        if (D_80083462 & 0x80) {
            ((S_801716D8_3 *)motion)->unk_96 = 0;
            return;
        }
        ((S_801716D8_3 *)motion)->unk_96 = 8;
        step_count = (u8) ((S_801716D8_0 *)state)->unk_71;
        if ((s32) step_count > 0) {
            ((S_801716D8_3 *)motion)->unk_96 = (s16) (8 / (s32) step_count);
        }
    }
    ASM_KEEP(state);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
}

/* MECHANISM: A guarded $s0 state-base pin restores the retail 0x30 frame and
   saved-register roles; byte-table typing fixes the indexed lbu sequence.
   A cached flag plus schedule seam preserves the second-call order, while a
   widened $a2 divisor pin closes the lbu/blez/div tail live range. */
