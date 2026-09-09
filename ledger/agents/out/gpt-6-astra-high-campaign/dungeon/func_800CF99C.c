#include "common.h"
#include "m2c_compat.h"

typedef struct S_800D50FC_0 {
    u16 unk_00;
    u8 pad_02[0xC];
    u8 unk_0E;
    u8 unk_0F;
    u8 unk_10;
    u8 pad_11[0xF];
    u16 unk_20;
    s16 unk_22;
} S_800D50FC_0;   /* arg0 in func_800D50FC; pointer addresses record offset 0x2 */

typedef struct S_800D50FC_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_800D50FC_1;   /* arg1 in func_800D50FC */

typedef struct S_800D50FC_2 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_800D50FC_2;   /* arg2 in func_800D50FC */

typedef struct S_800D50FC_3 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800D50FC_3;   /* page in func_800D50FC */


s32 rand();                                /* extern */
extern M2C_UNK D_800814A0;

/* Updates effect motion and color, then marks it inactive when its lifetime expires. */
void func_800D50FC(void *effect, S_800D50FC_1 *motion, S_800D50FC_2 *color) {
    s32 y_speed;
    u16 life_left;
    u32 phase;

    phase = ((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_20 & 7;
    switch (phase) {
    case 1:
    case 2:
    case 5:
    case 6:
        break;
    case 0:
    case 4:
        motion->unk_0C = (s32) (((rand() & 0x3FFF) - 0x2000) << 5);
        y_speed = (s32) (((rand() & 0x3FFF) - 0x2000) << 5);
        motion->unk_10 = y_speed;
        break;
    case 3:
    case 7:
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        break;
    }
    motion->unk_00 = (s32) (motion->unk_00 + motion->unk_0C);
    motion->unk_04 = (s32) (motion->unk_04 + motion->unk_10);
    motion->unk_08 = (s32) (motion->unk_08 + motion->unk_14);
    color->unk_0C = (s8) ((s32) (((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_0E * (s16) ((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_20) / (s16) ((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_22);
    color->unk_0D = (s8) ((s32) (((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_0F * (s16) ((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_20) / (s16) ((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_22);
    color->unk_0E = (s8) ((s32) (((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_10 * (s16) ((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_20) / (s16) ((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_22);
    life_left = ((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_20 - 1;
    ((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_20 = life_left;
    if ((life_left << 0x10) <= 0) {
        register u32 page ASM_REG("$3");

        page = 0x80080000;
        ASM_KEEP(page);
        ((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_00 = (u16) (((S_800D50FC_0 *)((u8 *)effect - 0x2))->unk_00 | 0x8000);
        ((S_800D50FC_3 *)page)->unk_14A0 = ((S_800D50FC_3 *)page)->unk_14A0 | 0x8000;
    }
}
