#include "common.h"
#include "shared/tile_object.h"
#include "m2c_compat.h"
#include "records/Rec_func_8008ACDC_arg0.h"

typedef struct S_80094270_3 {
    u8 pad_00[0xFA];
    u8 unk_FA;
} S_80094270_3;   /* (actor + (s16) slot) in func_80094270 */

typedef struct S_80094270_4 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_80094270_4;   /* entry in func_80094270 */

typedef struct S_80094270_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80094270_5;   /* ((S_80094270_4 *)entry)->unk_AC in func_80094270 */


/* cfail-repair: tf7-phase1-cache-v3 */
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
} S_80094270_1;   /* entry in func_80094270 */

typedef struct S_80094270_2 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_80094270_2;   /* item in func_80094270 */

/* Use or equip the item in the given slot: build the result message for the outcome, or fall through to the failure path. */
s32 func_80094270(void *actor, M2C_UNK param_a, M2C_UNK param_b, S_80094270_2 *item, s32 slot) {
    s16 out_a;
    s16 out_b;
    s16 kind;
    s32 text;
    u8 bits;
    s32 msg;
    s32 call_result;
    S_80094270_1 *entry;
    M2C_UNK *hdr;
    M2C_UNK *hdr3;

    ((Rec_func_8008ACDC_arg0 *)actor)->unk_8A = (s16) slot;
    if (func_80094208(0) == 0) {
        if (((S_80094270_3 *)((actor + (s16) slot)))->unk_FA == 2) {
            func_800997FC(&D_800E0633);
            return 1;
        }
        entry = (void *) ((((Rec_func_8008ACDC_arg0 *)actor)->unk_8A * 4) + (u32) actor);
        if (entry->unk_D0 == item) {
            if (!(((S_80094270_5 *)(((S_80094270_4 *)entry)->unk_AC))->unk_1C & 0x20000)) {
                /* Format the selected outcome, then terminate the message. */
                msg = func_800990FC();
                text = func_80099194(&D_800E0726, msg);
                if (((Rec_func_8008ACDC_arg0 *)actor)->unk_8A != 0) {
                    hdr = &D_800E05F0;
                } else {
                    hdr = &D_800E05E1;
                }
                text = func_80099194(hdr, text);
                call_result = func_80099194(&D_800E0739, text - 3);
                func_80099290(call_result);
                goto finish;
            }
            func_80094E34();
            D_80082E80.unk_030 = 0;
            func_8008DB0C(actor, param_a, param_b, 0, 0);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_60 = 0;
            goto return_zero;
        }
        kind = func_8009402C(actor, param_a, param_b, &out_a, &out_b, item);
        hdr3 = (M2C_UNK *)((s32) actor);
        if (kind != 0) {
            msg = func_800990FC();
            if (kind == 1) {
                kind = item->unk_03 & 0x1F;
                text = func_80099194(&D_800E0747, msg);
                text = func_8009929C(0xA, text);
                call_result = func_80099734(D_800E3DF0[kind], text);
                text = func_80099194(&D_800E0766, call_result);
            } else if (kind == 2) {
                text = func_80099194(&D_800E0769, msg);
                if ((s16)slot != 0)
                    hdr = &D_800E05F0;
                else
                    hdr = &D_800E05E1;
                text = func_80099194(hdr, text);
                text = func_80099194(&D_800E077C, text - 3);
            } else {
                bits = item->unk_03 & 0x1F;
                call_result = func_80099734(D_800E3DF0[bits], msg);
                text = func_80099194(&D_800E078A, call_result);
            }

            /* The three outcomes share the termination and display tail. */
            func_80099290(text);
finish:
            func_800A5720(msg);
            func_800A56E0(0x506);
            return 1;
        }
        ((Rec_func_8008ACDC_arg0 *)hdr3)->unk_C8 = 0;
        D_80082E80.unk_030 = (s32) item;
        func_8008DB0C(actor, param_a, param_b, out_a, (s32) out_b);
        func_80094E34();
return_zero:
        return 0;
    }
    return 1;
}
