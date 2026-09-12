#include "common.h"

typedef struct S_800DAEF4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800DAEF4_0;   /* object in func_800DAEF4 */

typedef struct S_800DAEF4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_800DAEF4_1;   /* part in func_800DAEF4 */

typedef struct S_800DAEF4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800DAEF4_2;   /* params in func_800DAEF4 */

typedef struct S_800DAEF4_3_pre {
    u16 unk_00;
} S_800DAEF4_3_pre;   /* the 0x2 bytes before owner in func_800DAEF4, addressed as owner[-1] */

typedef struct S_800DAEF4_3 {
    u8 pad_00[0x10];
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    u8 pad_12[0x36];
    u16 unk_48;
} S_800DAEF4_3;   /* owner in func_800DAEF4 */

typedef struct S_800DAEF4_4 {
    u8 pad_00[0x10];
    u16 unk_10;
    u8 pad_12[0x36];
    u16 unk_48;
} S_800DAEF4_4;   /* work in func_800DAEF4 */

typedef struct S_800DAEF4_5 {
    void * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} S_800DAEF4_5;   /* node in func_800DAEF4 */

typedef struct S_800DAEF4_6 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_800DAEF4_6;   /* link in func_800DAEF4 */

typedef struct S_800DAEF4_7 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_800DAEF4_7;   /* ((S_800DAEF4_0 *)object)->unk_08 in func_800DAEF4 */



extern void *func_8003FD64();
extern void func_8004491C();
extern s32 func_80069EF8(void);
extern u8 D_80045340[0x10];
extern s32 D_800814A0[3];
extern u8 D_80083498[];
extern s32 D_800DB164;
extern s32 D_800DEA68;

/* Spawns up to 13 scattered objects and marks the owner finished when its timer expires. */
void func_800DAEF4(void *source_owner, void *spawn_params)
{
    s32 remaining;
    u8 *link;
    void *object;
    void *node;
    u8 *work;
    s32 offset_roll_a;
    s32 spread_roll_b;
    s32 spread_roll_a;
    s32 divisor;
    s32 height_delta;
    s32 link_value;
    u16 timer;
    u16 target_height;
    void *part;

    remaining = 12;
    link = (u8 *)&D_800DEA68;
    do {
        object = func_8003FD64(0x312, D_80083498);
        if (object != 0) {
            ((S_800DAEF4_0 *)object)->unk_10 = &D_800DB164;
            func_8004491C(object, D_80045340);
            node = ((S_800DAEF4_0 *)object)->unk_0C;
            work = (u8 *)object + 0x20;

            offset_roll_a = func_80069EF8();
            {
                const s32 offset_roll_b = func_80069EF8();
                register s32 roll_remainder ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                s32 biased_roll;
                register s32 offset_sum ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

                part = ((S_800DAEF4_0 *)object)->unk_08;
                roll_remainder = offset_roll_a;
                if (offset_roll_a < 0) {
                    roll_remainder = offset_roll_a + 63;
                }
                biased_roll = offset_roll_b;
                offset_sum = (roll_remainder >> 6) << 6;
                roll_remainder = offset_roll_a - offset_sum;
                if (offset_roll_b < 0) {
                    biased_roll = offset_roll_b + 63;
                }
                offset_sum = (biased_roll >> 6) << 6;
                offset_sum = roll_remainder + (offset_roll_b - offset_sum) - 64;
                   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                ((S_800DAEF4_1 *)part)->unk_02 = ((S_800DAEF4_2 *)spawn_params)->unk_02 + offset_sum / 2;
            }

            spread_roll_a = func_80069EF8();
            spread_roll_b = func_80069EF8();
            ((S_800DAEF4_7 *)(((S_800DAEF4_0 *)object)->unk_08))->unk_06 = ((S_800DAEF4_2 *)spawn_params)->unk_06 + (spread_roll_a % 64 + spread_roll_b % 64 - 64) / 2;

            ((S_800DAEF4_7 *)(((S_800DAEF4_0 *)object)->unk_08))->unk_0A = ((S_800DAEF4_3 *)source_owner)->unk_10.s;
            ((S_800DAEF4_4 *)work)->unk_10 = ((S_800DAEF4_2 *)spawn_params)->unk_08.at02.v;

            divisor = (func_80069EF8() & 3) + 4;
            height_delta = ((S_800DAEF4_2 *)spawn_params)->unk_08.at00.v;
            height_delta -= ((S_800DAEF4_3 *)source_owner)->unk_10.u << 16;
            ((S_800DAEF4_7 *)(((S_800DAEF4_0 *)object)->unk_08))->unk_14 = height_delta / divisor;

            ((S_800DAEF4_5 *)node)->unk_14 |= 0xC;
            ((S_800DAEF4_5 *)node)->unk_1C = 0x1000;
            ((S_800DAEF4_5 *)node)->unk_1E = 0x200;
            if (func_80069EF8() & 1) {
                ((S_800DAEF4_5 *)node)->unk_14 |= 1;
            }
            ((S_800DAEF4_5 *)node)->unk_10 = 0x60;
            ((S_800DAEF4_5 *)node)->unk_0C = 0xC06060;
            ((S_800DAEF4_5 *)node)->unk_00 = link;
            link_value = ((S_800DAEF4_6 *)link)->unk_04;
            ((S_800DAEF4_5 *)node)->unk_04 = 0;
            ((S_800DAEF4_5 *)node)->unk_05 = 0;
            ((S_800DAEF4_5 *)node)->unk_08 = link_value;
            target_height = ((S_800DAEF4_2 *)spawn_params)->unk_08.at02.v;
            ((S_800DAEF4_4 *)work)->unk_48 = 4;
            ((S_800DAEF4_4 *)work)->unk_10 = target_height;
        }
        remaining--;
    } while (remaining >= 0);

    timer = ((S_800DAEF4_3 *)source_owner)->unk_48 - 1;
    ((S_800DAEF4_3 *)source_owner)->unk_48 = timer;
    if ((timer << 16) <= 0) {
        ((S_800DAEF4_3_pre *)source_owner)[-1].unk_00 |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

}
