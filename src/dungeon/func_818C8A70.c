#include "common.h"
#include "m2c_compat.h"

typedef struct S_818C8A70_0_pre {
    u16 unk_00;
} S_818C8A70_0_pre;   /* the 0x2 bytes before arg0 in func_818C8A70, addressed as arg0[-1] */

typedef struct S_818C8A70_0 {
    s16 unk_00;
    u16 unk_02;
    u8 pad_04[0x4];
    s16 unk_08;
    u8 pad_0A[0xB];
    u8 unk_15;
    u8 pad_16[0x16];
    void * unk_2C;
    void * unk_30;
    u8 pad_34[0x24];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_818C8A70_0;   /* arg0 in func_818C8A70 */

typedef struct S_818C8A70_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x54];
    s32 unk_58;
    s32 unk_5C;
    s32 unk_60;
} S_818C8A70_1;   /* temp_s4 in func_818C8A70 */

typedef struct S_818C8A70_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_818C8A70_2;   /* temp_v0 in func_818C8A70 */

typedef struct S_818C8A70_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818C8A70_3;   /* temp_s0 in func_818C8A70 */

typedef struct S_818C8A70_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_818C8A70_4;   /* arg1 in func_818C8A70 */

typedef struct S_818C8A70_5 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_818C8A70_5;   /* temp_s2 in func_818C8A70 */

typedef struct S_818C8A70_6 {
    u8 pad_00[0x60];
    s32 unk_60;
} S_818C8A70_6;   /* temp_s7 in func_818C8A70 */

typedef struct S_818C8A70_7_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_818C8A70_7_pre;   /* the 0x18 bytes before ((S_818C8A70_0 *)arg0)->unk_30 in func_818C8A70, addressed as ((S_818C8A70_0 *)arg0)->unk_30[-1] */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s16 D_80024D04;
extern u8 D_80045340[];
extern u8 D_800DE870[9];
extern s32 D_800814A0[3];
extern u8 D_800DEC00[];
void func_80024414(void) __attribute__((noreturn));                            /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
s32 func_80069EF8();                                /* extern */
s32 func_8009D218();            /* extern */
s32 func_800A4778();           /* extern */
M2C_UNK func_800A56E0();                     /* extern */
s32 func_800A6D30();                                /* extern */
M2C_UNK func_800C8CD8();        /* extern */
extern M2C_UNK D_80024024;
extern M2C_UNK D_80024124;
extern u8 D_800E3D68;

void func_818C8A70(void *arg0, S_818C8A70_4 *arg1) {
    M2C_UNK var_a1;
    s16 temp_v1;
    s32 temp_a2;
    s32 temp_random;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_6;
    S_818C8A70_3 *temp_s0;
    S_818C8A70_5 *temp_s2;
    register S_818C8A70_1 *temp_s4 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    S_818C8A70_6 *temp_s7;
    void *temp_v0;

    D_80024D04 = 1;
    temp_s7 = ((S_818C8A70_0 *)arg0)->unk_2C;
    if (((S_818C8A70_0 *)arg0)->unk_00 == 0) {
        temp_v0 = func_8003FC64(0x212);
        temp_s4 = temp_v0 + 0x20;
        if (temp_v0 != NULL) {
            temp_s4->unk_02 = 0x1A;
            ((S_818C8A70_2 *)temp_v0)->unk_10 = &D_80024124;
            func_8004491C(temp_v0, D_80045340);
            temp_s0 = ((S_818C8A70_2 *)temp_v0)->unk_0C;
            temp_s0->unk_10 = 0x60;
            temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
            temp_s2 = ((S_818C8A70_2 *)temp_v0)->unk_08;
            temp_random = func_80069EF8();
            temp_v1 = arg1->unk_00.at02.v;
            temp_v1 -= 8;
            temp_v1 += temp_random & 0xF;
            temp_s2->unk_02 = temp_v1;
            temp_random = func_80069EF8();
            temp_v1 = arg1->unk_04.at02.v;
            temp_v1 -= 8;
            temp_v1 += temp_random & 0xF;
            temp_s2->unk_06 = temp_v1;
            temp_random = func_80069EF8();
            temp_v1 = arg1->unk_08.at02.v;
            temp_v1 -= 4;
            temp_v1 += temp_random & 7;
            temp_s2->unk_0A = temp_v1;
            temp_s4->unk_60 = (s32) (func_80069EF8() + 0xFFFE0000);
            temp_s0 = ((S_818C8A70_2 *)temp_v0)->unk_0C;
            temp_s0->unk_1C = 0x1000;
            temp_s0->unk_1E = 0x1000;
            temp_s0->unk_0E = 0x80;
            temp_s0->unk_0D = 0x80;
            temp_s0->unk_0C = 0x80;
            temp_s0->unk_12 = 0x7DCF;
            temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x100);
            func_8003DB94(temp_s0, D_800DE870, 0);
        }
        temp_v0_2 = ((S_818C8A70_0 *)arg0)->unk_02 - 1;
        ((S_818C8A70_0 *)arg0)->unk_02 = temp_v0_2;
        if ((temp_v0_2 << 0x10) <= 0) {
            if (((S_818C8A70_0 *)arg0)->unk_08 != 0) {
                ((S_818C8A70_0 *)arg0)->unk_00 = 1;
                ((S_818C8A70_0 *)arg0)->unk_02 = 0U;
                func_800A56E0(0x300);
                func_80024414();
                return;
            }
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            ((S_818C8A70_0_pre *)arg0)[-1].unk_00 = (u16) (((S_818C8A70_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
            goto block_8;
        }
block_8:
        if ((func_800A4778(arg1->unk_00.at02.v, arg1->unk_04.at02.v, (s16) arg1->unk_08.at02.v, ((S_818C8A70_0 *)arg0)->unk_30) << 0x10) == 0) {
            arg1->unk_00.at00.v = (s32) (arg1->unk_00.at00.v + ((S_818C8A70_0 *)arg0)->unk_58);
            arg1->unk_04.at00.v = (s32) (arg1->unk_04.at00.v + ((S_818C8A70_0 *)arg0)->unk_5C);
            arg1->unk_08.at00.v = (s32) (arg1->unk_08.at00.v + ((S_818C8A70_0 *)arg0)->unk_60);
            goto block_10;
        }
        goto block_25;
    }
block_10:
    temp_v1 = ((S_818C8A70_0 *)arg0)->unk_00;
    if (temp_v1 == 1) {
        temp_v0_3 = ((S_818C8A70_0 *)arg0)->unk_02 + 1;
        ((S_818C8A70_0 *)arg0)->unk_02 = temp_v0_3;
        if ((temp_v0_3 & 3) == temp_v1) {
            temp_v0 = func_8003FC64(0x212);
            temp_s4 = temp_v0 + 0x20;
            if (temp_v0 != NULL) {
                register s16 temp_z ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                temp_s4->unk_02 = 0x1A;
                ((S_818C8A70_2 *)temp_v0)->unk_10 = &D_80024124;
                func_8004491C(temp_v0, D_80045340);
                temp_s0 = ((S_818C8A70_2 *)temp_v0)->unk_0C;
                temp_s0->unk_10 = 0x60;
                temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
                temp_s2 = ((S_818C8A70_2 *)temp_v0)->unk_08;
                temp_s0 = ((S_818C8A70_7_pre *)(((S_818C8A70_0 *)arg0)->unk_30))[-1].unk_00;
                temp_random = func_80069EF8();
                temp_v1 = temp_s0->unk_02;
                temp_v1 -= 0x10;
                temp_v1 += temp_random & 0x1F;
                temp_s2->unk_02 = temp_v1;
                temp_random = func_80069EF8();
                temp_v1 = temp_s0->unk_06;
                temp_v1 -= 0x10;
                temp_v1 += temp_random & 0x1F;
                temp_s2->unk_06 = temp_v1;
                temp_random = func_80069EF8();
                temp_random &= 0x1F;
                temp_v1 = temp_s0->unk_0A;
                temp_random += 0x10;
                temp_z = temp_v1 - temp_random;
                temp_s2->unk_0A = temp_z;
                temp_s4->unk_58 = (s32) (func_80069EF8() - 0x8000);
                temp_s4->unk_5C = (s32) (func_80069EF8() - 0x8000);
                temp_s4->unk_60 = (s32) ((func_80069EF8() + 0xFFFC0000) * 2);
                temp_s0 = ((S_818C8A70_2 *)temp_v0)->unk_0C;
                temp_s0->unk_1C = 0x1000;
                temp_s0->unk_1E = 0x1000;
                temp_s0->unk_0E = 0x80;
                temp_s0->unk_0D = 0x80;
                temp_s0->unk_0C = 0x80;
                temp_s0->unk_12 = 0x7DCF;
                temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x100);
                func_8003DB94(temp_s0, D_800DE870, 0);
            }
        }
        if ((((S_818C8A70_0 *)arg0)->unk_02 & 3) == 2) {
            temp_v0 = func_8003FC64(0x212);
            temp_s4 = temp_v0 + 0x20;
            if (temp_v0 != NULL) {
                register s16 temp_z ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                temp_s4->unk_02 = 0x14;
                ((S_818C8A70_2 *)temp_v0)->unk_10 = &D_80024024;
                func_8004491C(temp_v0, D_80045340);
                temp_s0 = ((S_818C8A70_2 *)temp_v0)->unk_0C;
                temp_s0->unk_10 = 0;
                temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
                temp_s2 = ((S_818C8A70_2 *)temp_v0)->unk_08;
                temp_s0 = ((S_818C8A70_7_pre *)(((S_818C8A70_0 *)arg0)->unk_30))[-1].unk_00;
                temp_random = func_80069EF8();
                temp_v1 = temp_s0->unk_02;
                temp_v1 -= 0x10;
                temp_v1 += temp_random & 0x1F;
                temp_s2->unk_02 = temp_v1;
                temp_random = func_80069EF8();
                temp_v1 = temp_s0->unk_06;
                temp_v1 -= 0x10;
                temp_v1 += temp_random & 0x1F;
                temp_s2->unk_06 = temp_v1;
                temp_random = func_80069EF8();
                temp_random &= 0x3F;
                temp_v1 = temp_s0->unk_0A;
                temp_random += 0x20;
                temp_z = temp_v1 - temp_random;
                temp_s2->unk_0A = temp_z;
                temp_s0 = ((S_818C8A70_2 *)temp_v0)->unk_0C;
                temp_s0->unk_1C = 0x800;
                temp_s0->unk_1E = 0x800;
                temp_s4->unk_60 = (s32) (func_80069EF8() + 0xFFFE0000);
                temp_s0->unk_0E = 0x80;
                temp_s0->unk_0D = 0x80;
                temp_s0->unk_0C = 0x80;
                temp_s0->unk_12 = 0x7DC0;
                temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x100);
                func_8003DB94(temp_s0, D_800DEC00, 0);
            }
        }
        if ((s16) ((S_818C8A70_0 *)arg0)->unk_02 >= 0x29) {
            ((S_818C8A70_0 *)arg0)->unk_00 = 2;
            ((S_818C8A70_0 *)arg0)->unk_02 = 0U;
            if (func_8009D218(temp_s7->unk_60, 1, temp_s7) == 0) {
                s32 final_random;
                u32 final_field;
                final_random = func_800A6D30();
                final_random &= 3;
                final_field = ((S_818C8A70_0 *)arg0)->unk_15;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                final_random += 2;
                final_field >>= 2;
                temp_a2 = final_field + final_random;
                var_a1 = 0x10;
                if (D_800E3D68 == 0xFF) {
                    var_a1 = 0xFF;
                }
                func_800C8CD8(((S_818C8A70_0 *)arg0)->unk_30, var_a1, temp_a2);
            }
        }
    }
    if (((S_818C8A70_0 *)arg0)->unk_00 == 2) {
        temp_v0_6 = ((S_818C8A70_0 *)arg0)->unk_02 + 1;
        ((S_818C8A70_0 *)arg0)->unk_02 = temp_v0_6;
        if ((s16) temp_v0_6 >= 0x15) {
block_25:
            ((S_818C8A70_0_pre *)arg0)[-1].unk_00 = (u16) (((S_818C8A70_0_pre *)arg0)[-1].unk_00 | 0x8000);
            D_800814A0[0] = D_800814A0[0] | 0x8000;
        }
    }
}
