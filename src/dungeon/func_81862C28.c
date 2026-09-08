#include "common.h"

typedef struct S_81862C28_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} S_81862C28_0;   /* temp_v0 in func_81862C28 */

typedef struct S_81862C28_1 {
    u8 unk_00;
    u8 pad_01[0x1];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81862C28_1;   /* temp_s0 in func_81862C28 */

typedef struct S_81862C28_2 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_81862C28_2;   /* held_arg1 in func_81862C28 */



extern void *func_8003FC64(s32);
extern void func_8003DB94(void *, void *, s32);
extern void func_8004491C(void *, void *);
extern void func_80024694(void) __attribute__((noreturn));
extern void func_800246A4(void) __attribute__((noreturn));
extern s32 func_800A45D8(s32, s32, s16);
extern u16 func_800BCAD0(void *);

extern void func_80024374(void);
extern u8 D_80045340[];
extern u8 D_800DE9D0[];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];

void func_81862C28(s32 arg0, void *arg1, s32 arg2, u8 *arg3) {
    register void *held_arg1 ASM_REG("$22");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 held_arg2;
    s16 temp_s3;
    s16 temp_s4;
    s32 var_a1;
    s32 var_v1;
    register s32 temp_a2 ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 var_s2;
    register void *var_s5 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *page_8007 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_81862C28_1 *temp_s0;
    S_81862C28_0 *temp_v0;
    s32 xSum;
    s32 yProduct;
    s32 yOffset;
    s16 zValue;

    held_arg1 = arg1;
    ASM_KEEP_NV(held_arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    held_arg2 = temp_a2;
    temp_a2 <<= 0x10;
    if (temp_a2 == 0) {
        temp_v0 = func_8003FC64(0x212);
        if (temp_v0 != 0) {
            temp_s0 = temp_v0->unk_0C;
            temp_v0->unk_10 = func_80024374;
            temp_v0->unk_20 = arg0;
            temp_v0->unk_24 = 0;
            temp_s0->unk_0E = 0x80;
            temp_s0->unk_0D = 0x80;
            temp_s0->unk_0C = 0x80;
            func_8003DB94(temp_s0, D_800DE9D0, 0);
            temp_s0->unk_1C = 0x1000;
            temp_s0->unk_1E = 0x3000;
            temp_s0->unk_12 = 0x7E0B;
            temp_s0->unk_10 |= 0x20;
            temp_s0->unk_14 |= 0x10C;
            func_8004491C(temp_v0, D_80045340);
            temp_s0 = temp_v0->unk_08;
            temp_s0->unk_02.s = ((S_81862C28_2 *)held_arg1)->unk_02.s;
            temp_s0->unk_06.s = ((S_81862C28_2 *)held_arg1)->unk_06.s;
            temp_s0->unk_0A = ((S_81862C28_2 *)held_arg1)->unk_0A.s;
            func_800246A4();
        }
    } else {
        var_s2 = 0;
        page_8007 = (u8 *)0x80070000;
        ASM_KEEP(page_8007);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        var_s5 = page_8007 - 0x3328;
loop_5:
        temp_s0 = arg3 + var_s2;
        if (temp_s0->unk_00 == 0) {
            var_v1 = ((S_81862C28_2 *)held_arg1)->unk_02.u;
            if (var_v1 < 0) {
                var_v1 += 0x3F;
            }
            xSum = (var_v1 >> 6) + (*(u16 *)var_s5 * held_arg2);
            yOffset = var_s2 << 1;
            var_a1 = ((S_81862C28_2 *)held_arg1)->unk_06.u;
            if (var_a1 < 0) {
                var_a1 += 0x3F;
            }
            yProduct = *(u16 *)((u8 *)D_8006CCE8 + yOffset) * held_arg2;
            zValue = ((S_81862C28_2 *)held_arg1)->unk_0A.u;
            temp_s4 = ((xSum << 0x10) >> 0xA) + 0x20;
            temp_s3 = ((((var_a1 >> 6) + yProduct) << 0x10) >> 0xA) + 0x20;
            if ((func_800A45D8(temp_s4 & 0xFFE0, temp_s3 & 0xFFE0, zValue) << 0x10) != 0) {
                temp_s0->unk_00 = 1;
                func_80024694();
            }
            temp_v0 = func_8003FC64(0x212);
            if (temp_v0 != 0) {
                temp_s0 = temp_v0->unk_0C;
                temp_v0->unk_10 = func_80024374;
                temp_v0->unk_20 = arg0;
                temp_v0->unk_24 = 0;
                temp_s0->unk_0E = 0x40;
                temp_s0->unk_0D = 0x40;
                temp_s0->unk_0C = 0x40;
                func_8003DB94(temp_s0, D_800DE9D0, 0);
                temp_s0->unk_1C = 0x1000;
                temp_s0->unk_1E = 0x1800;
                temp_s0->unk_12 = 0x7E0B;
                temp_s0->unk_10 |= 0x20;
                temp_s0->unk_14 |= 0x10C;
                func_8004491C(temp_v0, D_80045340);
                temp_s0 = temp_v0->unk_08;
                temp_s0->unk_02.u = temp_s4;
                temp_s0->unk_06.u = temp_s3;
                temp_s0->unk_0A = ((S_81862C28_2 *)held_arg1)->unk_0A.s;
                temp_s0->unk_0A = func_800BCAD0(temp_s0);
            }
        }
        var_s2 += 1;
        var_s5 += 2;
        if (var_s2 < 8) {
            goto loop_5;
        }
    }
}
