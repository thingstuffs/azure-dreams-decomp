#include "common.h"

typedef struct S_80024E80_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_80024E80_0;   /* obj in func_80024E80 */

typedef struct S_80024E80_1 {
    s32 unk_00;
    u8 pad_04[0x1C];
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
} S_80024E80_1;   /* arg0 in func_80024E80 */

typedef struct S_80024E80_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x8];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} S_80024E80_2;   /* work in func_80024E80 */

typedef struct S_80024E80_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_80024E80_3;   /* control in func_80024E80 */

typedef struct S_80024E80_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80024E80_4;   /* points in func_80024E80 */

typedef struct S_80024E80_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80024E80_5;   /* arg1 in func_80024E80 */

typedef struct S_80024E80_6 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80024E80_6;   /* slot in func_80024E80 */


typedef struct SixWords {
    s32 word[6];
} SixWords;

extern s32 func_80024804();
extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 func_800647A0();
extern s16 func_80065F90();
extern s32 rand();

extern u8 D_80024C0C[];
extern s32 D_80045340;
extern u8 D_800DE39C[];


/* Creates an oriented effect between the supplied position and its owner. */
void *func_80024E80(void *owner, S_80024E80_5 *start_pos) {
    void *effect;
    S_80024E80_2 *state;
    S_80024E80_3 *render;
    S_80024E80_4 *endpoints;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 slot_index;
    u8 *slot_ptr;
    s32 random_angle;

    effect = func_8003FD64(0x212, (u8 *)owner - 0x20);
    if (effect != 0) {
        ((S_80024E80_0 *)effect)->unk_10 = D_80024C0C;
        state = (u8 *)effect + 0x20;
        ((S_80024E80_0 *)effect)->unk_20 = ((S_80024E80_1 *)owner)->unk_00;
        state->unk_04 = 0;

        render = ((S_80024E80_0 *)effect)->unk_0C;
        render->unk_0E = 0x80;
        render->unk_0D = 0x80;
        render->unk_0C = 0x80;
        render->unk_12 = 0x7DCF;
        render->unk_08 = D_800DE39C;
        render->unk_14 |= 0x100;

        random_angle = rand();
        render->unk_1A = random_angle % 0x1000;
        render->unk_1E = 0x400;
        render->unk_1C = 0x400;

        func_8004491C(effect, &D_80045340);

        endpoints = ((S_80024E80_0 *)effect)->unk_08;
        *(SixWords *)endpoints = *(SixWords *)start_pos;
        endpoints->unk_0C = ((S_80024E80_1 *)owner)->unk_20;
        endpoints->unk_10 = ((S_80024E80_1 *)owner)->unk_24;
        endpoints->unk_14 = ((S_80024E80_1 *)owner)->unk_28;

        dx = ((S_80024E80_1 *)owner)->unk_20 - start_pos->unk_00;
        dy = ((S_80024E80_1 *)owner)->unk_24 - start_pos->unk_04;
        dz = ((S_80024E80_1 *)owner)->unk_28 - start_pos->unk_08;

        state->unk_0E = func_80065F90(
            func_800647A0((((dx >> 12) * (dx >> 12)) +
                           ((dy >> 12) * (dy >> 12))) << 4),
            dz >> 4);
        state->unk_10 = func_80065F90(dx >> 4, dy >> 4);

        if (dx < 0) {
            state->unk_12 = 1;
        }

        slot_index = 0;
        slot_ptr = state;
        do {
            ((S_80024E80_6 *)slot_ptr)->unk_14 = func_80024804(state, endpoints, (s16)slot_index);
            slot_index++;
            slot_ptr += 4;
        } while (slot_index < 3);

        return effect;
    }
    return 0;
}
