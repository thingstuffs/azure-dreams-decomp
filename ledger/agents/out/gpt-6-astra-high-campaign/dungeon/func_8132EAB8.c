#include "common.h"


extern s16 D_801760D8;
extern s32 D_800814A0;
extern void *D_80164808[];
extern s16 func_800BCB04(u16, u16, s16);


typedef struct S_80165AB8_0 {
    u8 pad_00[0x17];
    u8 unk_17;
    u8 pad_18[0x1A];
    union { s16 s; u16 u; } unk_32;   /* accessed as both */
    u8 pad_34[0x20];
    s32 unk_54;
    u8 pad_58[0x8];
    s32 unk_60;
} S_80165AB8_0;   /* arg0 in func_80165AB8 */

typedef struct S_80165AB8_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { s16 v; } at00u; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80165AB8_1;   /* arg1 in func_80165AB8 */

typedef struct S_80165AB8_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_80165AB8_2;   /* arg2 in func_80165AB8 */

/* Updates object motion, landing, and fading before marking it finished. */
void func_80165AB8(u8 *object, u8 *motion, u8 *sprite)
{
    static void *const keep_cases[] __attribute__((used)) = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4
    };
    s32 height;
    u32 state;
    s32 counter_check;
    s32 next_tick;

    state = ((S_80165AB8_0 *)object)->unk_17;
    if (state >= 5) {
        goto done;
    }
    goto *D_80164808[state];

case_0:
        ((S_80165AB8_1 *)motion)->unk_00.at00.v += ((S_80165AB8_1 *)motion)->unk_0C;
        ((S_80165AB8_1 *)motion)->unk_04.at00.v += ((S_80165AB8_1 *)motion)->unk_10;
        ((S_80165AB8_1 *)motion)->unk_08.at00.v += ((S_80165AB8_1 *)motion)->unk_14;

        height = ((S_80165AB8_1 *)motion)->unk_08.at02.v;
        ((S_80165AB8_1 *)motion)->unk_14 += ((S_80165AB8_0 *)object)->unk_60;
        if ((func_800BCB04(((S_80165AB8_1 *)motion)->unk_00.at02.v,
                           ((S_80165AB8_1 *)motion)->unk_04.at02.v,
                           (s16)(((S_80165AB8_1 *)motion)->unk_08.at02u.v - 4)) - 15) < height) {
            ((S_80165AB8_0 *)object)->unk_54 = 0;
            ((S_80165AB8_1 *)motion)->unk_08.at02.v =
                func_800BCB04(((S_80165AB8_1 *)motion)->unk_00.at02.v,
                              ((S_80165AB8_1 *)motion)->unk_04.at02.v,
                              (s16)(((S_80165AB8_1 *)motion)->unk_08.at02u.v - 4)) - 2;
            ((S_80165AB8_1 *)motion)->unk_08.at00u.v = 0;
            ((S_80165AB8_0 *)object)->unk_32.s = 0;
            ((S_80165AB8_0 *)object)->unk_17++;
        }
        counter_check = ((S_80165AB8_0 *)object)->unk_32.u;
        next_tick = counter_check + 1;
        counter_check = (s16)counter_check < 60;
        goto check_counter;

case_1: {
        register s32 tripled_size ASM_REG("$3");

        tripled_size = ((S_80165AB8_2 *)sprite)->unk_1E * 3;
        ((S_80165AB8_2 *)sprite)->unk_1E = tripled_size;
        ((S_80165AB8_2 *)sprite)->unk_1C = tripled_size;
        goto advance_state;
    }

case_2:
        if (D_801760D8 == 0) {
            goto done;
        }
        goto advance_state;

case_3:
        if ((s16)((S_80165AB8_0 *)object)->unk_32.u++ < 20) {
            goto done;
        }
        ((S_80165AB8_2 *)sprite)->unk_10 = 0;
        ((S_80165AB8_2 *)sprite)->unk_14 |= 0xC;

advance_state:
        ((S_80165AB8_0 *)object)->unk_32.s = 0;
        ((S_80165AB8_0 *)object)->unk_17++;
        return;

case_4:
        ((S_80165AB8_2 *)sprite)->unk_0C =
            ((10 - ((S_80165AB8_0 *)object)->unk_32.s) * 255) / 10;
        ((S_80165AB8_2 *)sprite)->unk_0D = ((S_80165AB8_2 *)sprite)->unk_0E =
            ((10 - ((S_80165AB8_0 *)object)->unk_32.s) * 32) / 10;
        counter_check = ((S_80165AB8_0 *)object)->unk_32.u;
        next_tick = counter_check + 1;
        counter_check = (s16)counter_check < 10;
check_counter:
        ((S_80165AB8_0 *)object)->unk_32.u = next_tick;
        if (counter_check) {
            goto done;
        }

finish:
    (*(u16 *)((u8 *)object + (-2))) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}
