#include "common.h"
#include "m2c_compat.h"

typedef struct S_80090210_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    M2C_UNK * unk_14;
    u8 pad_18[0x2];
    s16 unk_1A;
    u8 pad_1C[0xA];
    s16 unk_26;
} S_80090210_0;   /* base_834B8 in func_80090210; pointer addresses record offset 0x10 */

typedef struct S_80090210_1 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_80090210_1;   /* base_82E80 in func_80090210 */

typedef struct S_80090210_2 {
    u8 pad_00[0x438];
    union { M2C_UNK (*s)(); s32 u; } unk_438;   /* accessed as both */
} S_80090210_2;   /* callback_page in func_80090210 */


M2C_UNK func_80033AA8();                     /* extern */
M2C_UNK func_80033AE8();                     /* extern */
s32 func_80033B2C();                         /* extern */
M2C_UNK func_80048D20();                            /* extern */
s32 func_80048D40();                                /* extern */
M2C_UNK func_80094984(); /* extern */
M2C_UNK func_80098868(); /* extern */
M2C_UNK func_80098928(); /* extern */
M2C_UNK func_80099764();                   /* extern */
extern s32 D_80080A80;
extern u8 D_80082E80[];
extern s32 D_800834B8;
extern s32 D_80083780;
extern u8 D_8008FFC0[];
extern M2C_UNK D_80097D54;
extern u8 D_800D0078[];
extern s32 D_800D0438;

/* Synchronizes the mode flag, updates state, and runs the pending callback. */
void func_80090210(void) {
    s32 disabled_flag;
    s32 enabled_flag;
    s32 mode_result; /* MATCH: Keep the merged call result in v0 for the shared stores. */
    u8 *work_state = (u8 *)&D_80083780;
    u8 *update_state = D_80082E80;
    u8 *handler_state = (u8 *)&D_800834B8;
    u8 *callback_page;
    M2C_UNK (*callback)();

    if (((S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_00 != D_8008FFC0) {
        if (func_80033B2C(0x1202) == 0) {
            ((S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_26 = 0;
            disabled_flag = func_80033B2C(0x1202);
            if (disabled_flag != func_80033B2C(0x9D)) {
                mode_result = func_80048D20();
                D_80080A80 = mode_result;
                ((S_80090210_1 *)update_state)->unk_28 = mode_result;
            }
            goto sync_mode_flag;
        }
        ((S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_26 = 1;
        enabled_flag = func_80033B2C(0x1202);
        if (enabled_flag != func_80033B2C(0x9D)) {
            s32 mode_result;
            mode_result = func_80048D40();
            D_80080A80 = mode_result;
            ((S_80090210_1 *)update_state)->unk_28 = mode_result;
        }
sync_mode_flag:
        if (func_80033B2C(0x1202) != 0) {
            func_80033AA8(0x9D);
        } else {
            func_80033AE8(0x9D);
        }
        func_80094984(D_800D0078, handler_state, update_state);
        func_80099764(handler_state);
        func_80098868(handler_state, work_state, update_state);
        func_80098928(handler_state, work_state, update_state);
        {
            u8 *handler_page;

            handler_page = (u8 *)0x80090000;
            ASM_KEEP(handler_page);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
            callback_page = (u8 *)0x800D0000;
            callback = ((S_80090210_2 *)callback_page)->unk_438.s;
            ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
            ((S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_14 =
                (M2C_UNK *)(handler_page + 0x7D54);
            ((S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_1A = 0x10;
            if (callback != NULL) {
                callback();
                ((S_80090210_2 *)callback_page)->unk_438.u = 0;
            }
        }
    }
}
