#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s32 func_800644B8();                             /* extern */
s32 func_80064584();                             /* extern */
s32 func_80065F90();             /* extern */
extern M2C_UNK D_80000001;


void func_80095094(Rec_D_800E3D7C *arg0) {
    s32 var_a0;
    s32 var_a1;
    s32 var_a2;
    s32 temp_v0;
    register s32 temp_v0_2 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 temp_v0_3 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 var_a0_2;
    s32 var_s0;

    temp_v1 = arg0->unk_0C.as_s32;
    if ((temp_v1 != 0) || (arg0->unk_10.at00_s32.v != 0)) {
        var_a2 = 0x80000001;
        ASM_KEEP(var_a2);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
        var_a0 = 0x80000001;
        if (var_a2 < temp_v1) {
            var_a0 = temp_v1;
        }
        temp_v1_2 = arg0->unk_10.at00_s32.v;
        var_a1 = 0x80000001;
        if (var_a2 < temp_v1_2) {
            var_a1 = temp_v1_2;
        }
        var_s0 = func_80065F90(var_a0, var_a1, var_a2);
        temp_v0_2 = func_800644B8(var_s0);
        var_a0_2 = var_s0;
        temp_v0_2 = temp_v0_2 << 5;
        var_s0 = temp_v0_2;
        if (temp_v0_2 < 0) {
            var_s0 = 0 - var_s0;
        }
        temp_v0_3 = func_80064584(var_a0_2);
        temp_v1_3 = arg0->unk_0C.as_s32;
        temp_v0_3 = temp_v0_3 << 5;
        var_a0_2 = temp_v0_3;
        if (temp_v0_3 < 0) {
            var_a0_2 = 0 - var_a0_2;
        }
        temp_v0_4 = temp_v1_3 - var_s0;
        if (temp_v1_3 < 0) {
            temp_v0_5 = temp_v1_3 + var_s0;
            arg0->unk_0C.as_s32 = temp_v0_5;
            if (temp_v0_5 > 0) {
                arg0->unk_0C.as_s32 = 0;
            }
        } else {
            arg0->unk_0C.as_s32 = temp_v0_4;
            if (temp_v0_4 < 0) {
                arg0->unk_0C.as_s32 = 0;
            }
        }
        temp_v0_6 = arg0->unk_10.at00_s32.v;
        if (temp_v0_6 < 0) {
            temp_v0_7 = temp_v0_6 + var_a0_2;
            arg0->unk_10.at00_s32.v = temp_v0_7;
            if (temp_v0_7 > 0) {
                arg0->unk_10.at00_s32.v = 0;
                return;
            }
        } else {
            temp_v0_8 = temp_v0_6 - var_a0_2;
            arg0->unk_10.at00_s32.v = temp_v0_8;
            if (temp_v0_8 < 0) {
                arg0->unk_10.at00_s32.v = 0;
            }
        }
    }
}

/* MECHANISM: Signed shifted-result lifetimes give the 0x20 frame with s1=arg0 and s0=the held delta.
   Guarded v0 result holds and an a2 sentinel hold reproduce both absolute-value and constant-split slots.
   Explicit field clears before the two sibcalls supply retail's store-filled tail-jump delay slots. */
