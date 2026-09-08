#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();      /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
extern M2C_UNK D_800246AC;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DEB28;

typedef struct S_80024790_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    u16 unk_20;
} S_80024790_0;   /* temp_v0 in func_80024790 */

typedef struct S_80024790_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024790_1;   /* arg0 in func_80024790 */

typedef struct S_80024790_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u16 unk_04;
    u8 pad_06[0x2];
    s16 unk_08;
} S_80024790_2;   /* temp_s3 in func_80024790 */

typedef struct S_80024790_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024790_3;   /* temp_s0 in func_80024790 */

typedef struct S_80024790_4 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80024790_4;   /* temp_s0_2 in func_80024790 */

s32 func_80024790(S_80024790_1 *arg0, s32 arg1) {
    s32 held_arg1 = arg1;
    register s32 temp_s2 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 sign_temp;
    register s32 return_value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s16 temp_v0_3;
    s32 var_a2;
    register s32 temp_s5 ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    s32 temp_v1;
    s32 var_a0;
    s32 final_value;
    s8 temp_v0_2;
    u8 *global_page;
    u8 *global_addr;
    S_80024790_3 *temp_s0;
    S_80024790_4 *temp_s0_2;
    S_80024790_2 *temp_s3;
    void *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_s5 = held_arg1;
        ASM_KEEP(temp_s5);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ASM_KEEP(held_arg1);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        ((S_80024790_0 *)temp_v0)->unk_10 = &D_800246AC;
        ((S_80024790_0 *)temp_v0)->unk_20 = (u16) arg0->unk_02;
        temp_s3 = temp_v0 + 0x20;
        temp_s3->unk_02 = (u16) arg0->unk_06;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        sign_temp = held_arg1 << 16;
        temp_s2 = sign_temp >> 16;
        ASM_KEEP(sign_temp);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        temp_v1 = temp_s2 << 8;
        var_a0 = temp_v1;
        temp_s3->unk_04 = (u16) arg0->unk_0A;
        if (temp_v1 < 0) {
            var_a0 = temp_v1 + 0xFFF;
        }
        var_a2 = temp_s2;
        temp_s3->unk_08 = (s16) (temp_v1 - ((var_a0 >> 0xC) << 0xC));
        temp_s0 = ((S_80024790_0 *)temp_v0)->unk_0C;
        temp_v0_2 = ~(temp_s5 * 8);
        temp_s0->unk_0E = temp_v0_2;
        temp_s0->unk_0D = temp_v0_2;
        temp_s0->unk_0C = temp_v0_2;
        ASM_KEEP(temp_s5);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        global_page = (u8 *) 0x800E0000;
        ASM_KEEP(global_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        global_addr = global_page - 0x14D8;
        if (temp_s2 < 0) {
            var_a2 = temp_s2 + 7;
        }
        func_8003DB94(temp_s0, global_addr, (s16) (7 - (temp_s2 - ((var_a2 >> 3) * 8))));
        temp_v0_3 = (temp_s2 << 6) + 0x1000;
        temp_s0->unk_1E = temp_v0_3;
        temp_s0->unk_1C = temp_v0_3;
        temp_s0->unk_10 = (u16) (temp_s0->unk_10 | 0x20);
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        func_8004491C(temp_v0, &D_80045340);
        ASM_KEEP(temp_s2);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        temp_s0_2 = ((S_80024790_0 *)temp_v0)->unk_08;
        temp_s0_2->unk_02 = (s16) (((S_80024790_0 *)temp_v0)->unk_20 + ((s32) (func_800644B8(temp_s3->unk_08) * 2) >> 8));
        temp_s0_2->unk_06 = (s16) (temp_s3->unk_02 + ((s32) (func_80064584(temp_s3->unk_08) * 2) >> 8));
        return_value = (s32) temp_v0;
        final_value = temp_s3->unk_04 - (held_arg1 * 8);
        ASM_KEEP(return_value);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
        temp_s0_2->unk_0A = (u16) final_value;
        return;
    }
    return 0;
}

/* MECHANISM: Distinct s4/s5/s2 runtime roles force the retail 0x30 frame; a split sign extension
   and held 0x800e page reproduce the v0 temporaries and branch-delay address formation.
   The noreturn tail contract plus a v0 return hold across named final_value forces v1 and the +0xA delay-slot store. */
