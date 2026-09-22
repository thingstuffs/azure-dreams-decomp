#include "common.h"
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
    s16 index;
    s32 msg;
    s32 call_result;
    S_80094270_1 *entry;
    M2C_UNK *hdr;
    register M2C_UNK *hdr3 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */

    ((Rec_func_8008ACDC_arg0 *)actor)->unk_8A = (s16) slot;
    if (func_80094208(0) == 0) {
        if (((S_80094270_3 *)((actor + (s16) slot)))->unk_FA == 2) {
            func_800997FC(&D_800E0633);
            return 1;
        }
        entry = (void *) ((((Rec_func_8008ACDC_arg0 *)actor)->unk_8A * 4) + (u32) actor);
        if (entry->unk_D0 == item) {
            hdr3 = (M2C_UNK *)((s32) actor);
            if (!(((S_80094270_5 *)(((S_80094270_4 *)entry)->unk_AC))->unk_1C & 0x20000)) {
                /* retail: a single shared "jal func_80099194(hdr,.)" call is
                 * reached from BOTH arms of the (s16)slot check below (hdr
                 * chosen per arm, computed BEFORE the call, not two separate
                 * calls); the "-3" applies UNIFORMLY to the result regardless
                 * of which arm ran (it is the delay-slot arg-setup for the
                 * NEXT, D_800E0739 call, not part of either arm). This ending
                 * then jumps into the SAME shared func_80099290(text,
                 * text) / func_800A5720 / func_800A56E0 / "return 1" tail
                 * the kind dispatch below also reaches (retail has only
                 * ONE physical "jal func_80099290" instance for all four
                 * endings). Previously spelled as fake externs
                 * func_80094364()/func_800944CC() whose "return" never
                 * actually escaped the function -- the real control flow
                 * always ends in "return 1". */
                msg = func_800990FC((s32)hdr3);
                text = func_80099194(&D_800E0726, msg);
                if (((Rec_func_8008ACDC_arg0 *)actor)->unk_8A != 0) {
                    hdr = &D_800E05F0;
                } else {
                    hdr = &D_800E05E1;
                }
                text = func_80099194(hdr, text);
                call_result = func_80099194(&D_800E0739, text - 3);
                ASM_SET(text);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
                hdr3 = (M2C_UNK *)(call_result);
                goto call_290;
            }
            func_80094E34();
            *D_80082EB0 = 0;
            func_8008DB0C(actor, param_a, param_b, 0, 0);
            ((Rec_func_8008ACDC_arg0 *)actor)->unk_60 = 0;
            goto return_zero;
        }
        kind = func_8009402C(actor, param_a, param_b, &out_a, &out_b, item);
        hdr3 = (M2C_UNK *)((s32) actor);
        if (kind != 0) {
            msg = func_800990FC((s32)hdr3);
            if (kind == 1) {
                register s32 bits ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                s32 *table_base;
                register u32 table_entry ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

                bits = item->unk_03 & 0x1F;
                index = bits & 0xFF;
                text = func_80099194(&D_800E0747, msg);
                text = func_8009929C(0xA, text);
                table_base = D_800E3DF0;
                table_entry = index;
                table_entry <<= 2;
                table_entry += (u32) table_base;
                call_result = func_80099734(*(s32 *) table_entry, text);
                hdr3 = &D_800E0766;
                goto use_result;
            }
            if (kind == 2) {
                text = func_80099194(&D_800E0769, msg);
                if ((s16) slot != 0) {
                    hdr = &D_800E05F0;
                } else {
                    hdr = &D_800E05E1;
                }
                text = func_80099194(hdr, text);
                hdr3 = &D_800E077C;
                text -= 3;
                goto call3;
            }
            call_result = func_80099734(D_800E3DF0[item->unk_03 & 0x1F], msg);
            hdr3 = &D_800E078A;
        use_result:
            text = call_result;
        call3:
            /* one physical "jal func_80099194(hdr3,.)" call shared by all
             * three arms above (each pre-selects hdr3 and text, then
             * merges here). */
            text = func_80099194(hdr3, text);
            hdr3 = (M2C_UNK *)(text);
        call_290:
            /* one physical "jal func_80099290(text,text)" call shared
             * by ALL FOUR endings (the single-arg I-block ending above jumps
             * straight here too), followed by the shared finish tail. */
            func_80099290((s32)hdr3, text);
        finish:
            func_800A5720(msg);
            func_800A56E0(0x506);
            return 1;
        }
        ((Rec_func_8008ACDC_arg0 *)actor)->unk_C8 = 0;
        *D_80082EB0 = (s32) item;
        func_8008DB0C(actor, param_a, param_b, out_a, (s32) out_b);
        func_80094E34();
    return_zero:
        return 0;
    }
    return 1;
}
