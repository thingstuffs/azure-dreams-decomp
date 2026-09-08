#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"

typedef struct S_80094270_3 {
    u8 pad_00[0xFA];
    u8 unk_FA;
} S_80094270_3;   /* (arg0 + (s16) arg4) in func_80094270 */

typedef struct S_80094270_4 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80094270_4;   /* temp_v1 in func_80094270 */

typedef struct S_80094270_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80094270_5;   /* ((S_80094270_4 *)temp_v1)->unk_AC in func_80094270 */




/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80082EB0[];
extern s32 D_800E3DF0[];
s16 func_8009402C(); /* extern */
s32 func_80094208();                         /* extern */
M2C_UNK func_80094E34();                      /* extern */
s32 func_800990FC();                          /* extern */
s32 func_80099194();                  /* extern */
M2C_UNK func_80099290();                    /* extern */
s32 func_8009929C();                    /* extern */
s32 func_80099734();                        /* extern */
M2C_UNK func_800997FC();                   /* extern */
M2C_UNK func_800A56E0();                     /* extern */
M2C_UNK func_800A5720();                         /* extern */
extern M2C_UNK D_800E05E1;
extern M2C_UNK D_800E05F0;
extern M2C_UNK D_800E0633;
extern M2C_UNK D_800E0726;
extern M2C_UNK D_800E0739;
extern M2C_UNK D_800E0747;
extern M2C_UNK D_800E0766;
extern M2C_UNK D_800E0769;
extern M2C_UNK D_800E077C;
extern M2C_UNK D_800E078A;


typedef struct S_80094270_1 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_80094270_1;   /* temp_v1 in func_80094270 */

typedef struct S_80094270_2 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_80094270_2;   /* arg3 in func_80094270 */

s32 func_80094270(void *arg0, M2C_UNK arg1, M2C_UNK arg2, S_80094270_2 *arg3, s32 arg4) {
    s16 sp18;
    s16 sp1A;
    s16 temp_v0;
    s32 temp_a1;
    s32 temp_s0;
    s32 temp_s2;
    s32 call_result;
    S_80094270_1 *temp_v1;
    M2C_UNK *hdr;
    register M2C_UNK *hdr3 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    register s32 call_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    ((Rec_func_8008ACDC_arg0 *)arg0)->unk_8A = (s16) arg4;
    if (func_80094208(0) == 0) {
        if (((S_80094270_3 *)((arg0 + (s16) arg4)))->unk_FA == 2) {
            func_800997FC(&D_800E0633);
            return 1;
        }
        temp_v1 = (void *) ((((Rec_func_8008ACDC_arg0 *)arg0)->unk_8A * 4) + (u32) arg0);
        if (temp_v1->unk_D0 == arg3) {
            call_a0 = (s32) arg0;
            if (!(((S_80094270_5 *)(((S_80094270_4 *)temp_v1)->unk_AC))->unk_1C & 0x20000)) {
                /* retail: a single shared "jal func_80099194(hdr,.)" call is
                 * reached from BOTH arms of the (s16)arg4 check below (hdr
                 * chosen per arm, computed BEFORE the call, not two separate
                 * calls); the "-3" applies UNIFORMLY to the result regardless
                 * of which arm ran (it is the delay-slot arg-setup for the
                 * NEXT, D_800E0739 call, not part of either arm). This ending
                 * then jumps into the SAME shared func_80099290(temp_a1,
                 * temp_a1) / func_800A5720 / func_800A56E0 / "return 1" tail
                 * the temp_v0 dispatch below also reaches (retail has only
                 * ONE physical "jal func_80099290" instance for all four
                 * endings). Previously spelled as fake externs
                 * func_80094364()/func_800944CC() whose "return" never
                 * actually escaped the function -- the real control flow
                 * always ends in "return 1". */
                temp_s2 = func_800990FC(call_a0);
                temp_a1 = func_80099194(&D_800E0726, temp_s2);
                if (((Rec_func_8008ACDC_arg0 *)arg0)->unk_8A != 0) {
                    hdr = &D_800E05F0;
                } else {
                    hdr = &D_800E05E1;
                }
                temp_a1 = func_80099194(hdr, temp_a1);
                call_result = func_80099194(&D_800E0739, temp_a1 - 3);
                ASM_SET(temp_a1);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                call_a0 = call_result;
                goto call_290;
            }
            func_80094E34();
            *D_80082EB0 = 0;
            func_8008DB0C(arg0, arg1, arg2, 0, 0);
            ((Rec_func_8008ACDC_arg0 *)arg0)->unk_60 = 0;
            goto return_zero;
        }
        temp_v0 = func_8009402C(arg0, arg1, arg2, &sp18, &sp1A, arg3);
        call_a0 = (s32) arg0;
        if (temp_v0 != 0) {
            temp_s2 = func_800990FC(call_a0);
            if (temp_v0 == 1) {
                register s32 temp_bits ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 *table_base;
                register u32 table_entry ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                temp_bits = arg3->unk_03 & 0x1F;
                ASM_KEEP_NV(temp_bits);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                temp_s0 = temp_bits & 0xFF;
                temp_a1 = func_80099194(&D_800E0747, temp_s2);
                temp_a1 = func_8009929C(0xA, temp_a1);
                table_base = D_800E3DF0;
                table_entry = temp_s0;
                table_entry <<= 2;
                table_entry += (u32) table_base;
                call_result = func_80099734(*(s32 *) table_entry, temp_a1);
                hdr3 = &D_800E0766;
                goto use_result;
            }
            if (temp_v0 == 2) {
                temp_a1 = func_80099194(&D_800E0769, temp_s2);
                if ((s16) arg4 != 0) {
                    hdr = &D_800E05F0;
                } else {
                    hdr = &D_800E05E1;
                }
                temp_a1 = func_80099194(hdr, temp_a1);
                hdr3 = &D_800E077C;
                temp_a1 -= 3;
                goto call3;
            }
            call_result = func_80099734(D_800E3DF0[arg3->unk_03 & 0x1F], temp_s2);
            hdr3 = &D_800E078A;
        use_result:
            temp_a1 = call_result;
        call3:
            /* one physical "jal func_80099194(hdr3,.)" call shared by all
             * three arms above (each pre-selects hdr3 and temp_a1, then
             * merges here). */
            temp_a1 = func_80099194(hdr3, temp_a1);
            call_a0 = temp_a1;
        call_290:
            /* one physical "jal func_80099290(temp_a1,temp_a1)" call shared
             * by ALL FOUR endings (the single-arg I-block ending above jumps
             * straight here too), followed by the shared finish tail. */
            func_80099290(call_a0, temp_a1);
        finish:
            func_800A5720(temp_s2);
            func_800A56E0(0x506);
            return 1;
        }
        ((Rec_func_8008ACDC_arg0 *)arg0)->unk_C8 = 0;
        *D_80082EB0 = (s32) arg3;
        func_8008DB0C(arg0, arg1, arg2, sp18, (s32) sp1A);
        func_80094E34();
    return_zero:
        return 0;
    }
    return 1;
}
