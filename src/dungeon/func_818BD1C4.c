#include "common.h"
#include "m2c_compat.h"

typedef struct S_818BD1C4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818BD1C4_0;   /* temp_v0 in func_818BD1C4 */

typedef struct S_818BD1C4_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
} S_818BD1C4_1;   /* temp_v0_2 in func_818BD1C4 */

typedef struct S_818BD1C4_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818BD1C4_2;   /* temp_s0 in func_818BD1C4 */


typedef struct Copy24 {
    s32 words[6];
} Copy24;

extern void func_80024ABC(void) __attribute__((noreturn));
extern void func_80024AC0() __attribute__((noreturn));
extern void func_80024AC8() __attribute__((noreturn));
extern void func_80024B8C(void) __attribute__((noreturn));
M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64(s32);                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_80069EF8();                                /* extern */
extern M2C_UNK D_800248C0;
extern M2C_UNK D_80025E04;
extern M2C_UNK D_80045340;

s32 func_818BD1C4(s32 *arg0, void *arg1, s16 arg2, s32 arg3) {
    s16 temp_a0;
    u16 tail_y;
    s32 temp_v1;
    s32 var_v0;
    register void *tail_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    register u32 tail_page ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 tail_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *temp_a0_2;
    S_818BD1C4_2 *temp_s0;
    void *temp_v0;
    S_818BD1C4_1 *temp_v0_2;
    register s32 s3_arg ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    s3_arg = arg3;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        ((S_818BD1C4_0 *)temp_v0)->unk_10 = &D_800248C0;
        ((S_818BD1C4_0 *)temp_v0)->unk_20 = (s32) *arg0;
        temp_v0_2 = temp_v0 + 0x20;
        temp_v0_2->unk_06 = 0;
        temp_v0_2->unk_08 = 0;
        temp_s0 = ((S_818BD1C4_0 *)temp_v0)->unk_0C;
        temp_a0 = arg2 % 3;
        if (temp_a0 == 1) {
            goto case_1;
        }
        if (temp_a0 >= 2) {
            goto check_2;
        }
        if (temp_a0 == 0) {
            goto case_0;
        }
        tail_a0 = temp_s0;
        tail_page = 0x80020000;
        ASM_KEEP(tail_a0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        ASM_PAGEBASE_PIN(tail_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024AC8();

check_2:
        if (temp_a0 == 2) {
            goto case_2;
        }
        tail_a0 = temp_s0;
        tail_page = 0x80020000;
        ASM_PAGEBASE_PIN(tail_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_80024AC8();

case_0:
        temp_s0->unk_0C = 0x80;
        temp_s0->unk_0E = 0;
        temp_s0->unk_0D = 0;
        func_80024AC0();

case_1:
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0E = 0;
        func_80024ABC();

case_2:
        tail_a0 = temp_s0;
        ASM_KEEP(tail_a0);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0;
        temp_s0->unk_0C = 0;
        ASM_CLOBBER("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        tail_a0 = temp_s0;
        temp_s0->unk_12 = 0x7DCF;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        temp_s0->unk_10 = (u16) (temp_s0->unk_10 | 0x60);
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0x100);
        func_8003DB94(tail_a0, &D_80025E04, 0);
        var_v0 = func_80069EF8();
        temp_v1 = var_v0;
        if (temp_v1 < 0) {
            var_v0 = temp_v1 + 0xFFF;
        }
        temp_s0->unk_1A = (s16) (temp_v1 - ((var_v0 >> 0xC) << 0xC));
        temp_s0->unk_1E = 0x2000;
        temp_s0->unk_1C = 0x2000;
        func_8004491C(temp_v0, &D_80045340);
        tail_a0 = ((S_818BD1C4_0 *)temp_v0)->unk_08;
        (*(Copy24 *)((u8 *)tail_a0 + 0)) =
            (*(Copy24 *)((u8 *)arg1 + 0));
        tail_y = (*(u16 *)((u8 *)tail_a0 + 0xA));
        tail_result = (s32) temp_v0;
        tail_y -= s3_arg;
        ASM_KEEP(tail_result);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        (*(u16 *)((u8 *)tail_a0 + 0xA)) = tail_y;
        func_80024B8C();
    }
    return 0;
}
