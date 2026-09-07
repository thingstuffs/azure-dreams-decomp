#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern volatile s16 D_80013714[8];
extern s32 D_80083460[3];
M2C_UNK __attribute__((noreturn)) func_80017344();  /* extern */
M2C_UNK __attribute__((noreturn)) func_80017390();  /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_800C7B38;

typedef struct S_800172A0_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800172A0_0;   /* arg0 in func_800172A0 */

typedef struct S_800172A0_1 {
    u8 pad_00[0x98];
    s16 unk_98;
    u8 pad_9A[0xA];
    s16 unk_A4;
    s16 unk_A6;
    s16 unk_A8;
    u8 pad_AA[0x2];
    s16 unk_AC;
    u8 pad_AE[0x2];
    s16 unk_B0;
    u8 pad_B2[0x2];
    M2C_UNK * unk_B4;
} S_800172A0_1;   /* state in func_800172A0 */

typedef struct S_800172A0_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_800172A0_2;   /* temp_s5 in func_800172A0 */

typedef struct S_800172A0_3 {
    void * unk_00;
    u8 pad_04[0x8];
    void * unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x8];
    s16 unk_24;
    s16 unk_26;
} S_800172A0_3;   /* temp_s1 in func_800172A0 */

typedef struct S_800172A0_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800172A0_4;   /* counter in func_800172A0 */

void func_800172A0(S_800172A0_0 *arg0, s16 arg1) {
    s16 temp_v0;
    s16 temp_v1;
    s16 temp_v1_2;
    u8 *state;
    void *temp_s1;
    s32 temp_s2;
    S_800172A0_2 *temp_s5;
    u16 *counter;
    s16 direction;
    s32 temp_rand;

    state = (u8 *)&D_80083178;
    temp_s5 = state + 0x1C4;
    temp_s1 = state + 0xB8;
    temp_s2 = (rand() & 0x1FFF) - 0x1000;
    if (!((u16) *D_80013714 & 2)) {
        temp_v1 = arg0->unk_02 + (func_80064584(temp_s2) * 2);
        ((S_800172A0_1 *)state)->unk_A4 = temp_v1;
        if (temp_v1 < 0) {
            ((S_800172A0_1 *)state)->unk_A4 = 0;
            func_80017344();
        }
        if (temp_v1 >= temp_s5->unk_1C) {
            ((S_800172A0_1 *)state)->unk_A4 = (s16) ((u16) temp_s5->unk_1C - 1);
        }
        temp_v1_2 = arg0->unk_06 + (func_800644B8(temp_s2) * 2);
        ((S_800172A0_1 *)state)->unk_A6 = temp_v1_2;
        if (temp_v1_2 < 0) {
            ((S_800172A0_1 *)state)->unk_A6 = 0;
            func_80017390();
        }
        if (temp_v1_2 >= temp_s5->unk_1E) {
            ((S_800172A0_1 *)state)->unk_A6 = (s16) ((u16) temp_s5->unk_1E - 1);
        }
        temp_v0 = (s16) (arg0->unk_0A - 0x400);
        ((S_800172A0_1 *)state)->unk_AC = 0;
        ((S_800172A0_1 *)state)->unk_A8 = temp_v0;
        temp_rand = rand();
        direction = -0x800;
        if (temp_rand & 1) {
            direction = 0x800;
        }
        ((S_800172A0_1 *)state)->unk_B0 = direction;
        ((S_800172A0_3 *)temp_s1)->unk_00 = (void *) (temp_s1 + 4);
        ((S_800172A0_3 *)temp_s1)->unk_14 = 1;
        ((S_800172A0_3 *)temp_s1)->unk_24 = 0x40;
        ((S_800172A0_3 *)temp_s1)->unk_0C = arg0;
        ((S_800172A0_3 *)temp_s1)->unk_18 = 0;
        ((S_800172A0_3 *)temp_s1)->unk_26 = arg1;
        ((S_800172A0_1 *)state)->unk_B4 = &D_800C7B38;
        temp_v0 = arg1 + ((((S_800172A0_3 *)temp_s1)->unk_24 + 1) * 0x30);
        ((S_800172A0_1 *)state)->unk_98 = temp_v0;
        ((S_800172A0_3 *)temp_s1)->unk_10 = (s32) temp_v0;
        counter = (u16 *)D_80083460;
        ((S_800172A0_4 *)counter)->unk_0A = (u16) (((S_800172A0_4 *)counter)->unk_0A + 1);
    }
}
/* Warning: struct S_80083178 is not defined (only forward-declared) */
