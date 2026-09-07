#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

s16 func_8008C758(); /* extern */
s16 func_8008CF48();                    /* extern */
extern M2C_UNK D_800CFD18;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
} Unk80091A10;


s32 func_8008F170(Rec_D_800E3D7C *arg0, s32 *arg1) {
    Unk80091A10 sp18;
    s32 sp30;
    s16 temp_v0;
    s16 var_s2;

    sp18.unk0 = arg0->unk_00.at00_s32.v;
    sp18.unk4 = arg0->unk_04.at00_s32.v;
    sp18.unk8 = arg0->unk_08.at00_s32.v - arg0->unk_14.as_s32;
    var_s2 = func_8008CF48(&sp18, &sp30);
    *arg1 = sp30;
    sp18.unk0 = arg0->unk_00.at00_s32.v;
    sp18.unk4 = arg0->unk_04.at00_s32.v;
    sp18.unk8 = arg0->unk_08.at00_s32.v - arg0->unk_14.as_s32;
    temp_v0 = func_8008C758(&sp18, &D_800CFD18, 4, &sp30, (s32) var_s2, *arg1);
    if (temp_v0 < var_s2) {
        var_s2 = temp_v0;
        *arg1 = sp30;
    }
    if (var_s2 >= 0x80) {
        var_s2 = 0x80;
    }
    return var_s2;
}

/* MECHANISM: A 24-byte escaped record plus the separate sp30 output force the retail
   0x50 frame, stack offsets, and complete six-store copy sequence. Direct s16 CFG
   expressions remove shifted-temporary residue; 2.7.2-cdk-G0 supplies the exact schedule. */
