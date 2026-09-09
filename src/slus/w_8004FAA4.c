/* first_pass: swept 49 configs, best 2.7.2-cdk '-fno-delayed-branch' 89 words off — do NOT re-sweep by hand */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8004FAA4_0 {
    u8 pad_00[0x8];
    union { s32 s; volatile s32 u; } unk_08;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
} S_8004FAA4_0;   /* input in func_8004FAA4 */

typedef struct S_8004FAA4_1 {
    u8 pad_00[0x24];
    s32 unk_24;
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    u8 pad_34[0x4];
    s32 unk_38;
} S_8004FAA4_1;   /* arg0 in func_8004FAA4 */

typedef struct S_8004FAA4_2 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    s32 unk_B0;
} S_8004FAA4_2;   /* D_800814A8[0] in func_8004FAA4 */


M2C_UNK func_8004FA2C();
s32 func_8004FD78();
M2C_UNK SD_Call();
extern void *D_800814A8[];
extern M2C_UNK D_80083160[8];

/* Update menu selection from directional and side-switch input, with key repeat and sound. */
void func_8004FAA4(S_8004FAA4_1 *menu) {
    M2C_UNK target_side;
    M2C_UNK *input;
    void *target_menu;
    s32 next_index;
    s32 repeat_ticks;
    s32 held_buttons;
    s32 index_delta;

    input = D_80083160;
    index_delta = 0;
    if ((((S_8004FAA4_0 *)input)->unk_08.s != 0) && (menu->unk_24 >= 2)) {
        if (((S_8004FAA4_0 *)input)->unk_08.s & 0xA000) {
            if (((S_8004FAA4_0 *)input)->unk_10 & 0x2000) {
                index_delta = 1;
                goto start_repeat;
            }
            if (((S_8004FAA4_0 *)input)->unk_10 & 0x8000) {
                index_delta = -1;
start_repeat:
                menu->unk_38 = 0;
                menu->unk_28 = 4;
            } else {
                repeat_ticks = menu->unk_38;
                if (repeat_ticks >= 9) {
                    menu->unk_38 = (s32) (repeat_ticks - 2);
                    held_buttons = ((S_8004FAA4_0 *)input)->unk_08.u;
                    if (held_buttons & 0x2000) {
                        index_delta = 1;
                        goto repeat_move;
                    }
                    if (held_buttons & 0x8000) {
                        index_delta = -1;
repeat_move:
                        menu->unk_28 = 3;
                    }
                } else {
                    menu->unk_38 = (s32) (repeat_ticks + 1);
                }
            }
        }
        if (index_delta == 0) {
            if (((S_8004FAA4_0 *)input)->unk_10 & 1) {
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                if (((S_8004FAA4_2 *)(D_800814A8[0]))->unk_B0 != 0) {
                    target_menu = menu;
                    target_side = 1;
                    goto select_target;
                }
            } else if (((S_8004FAA4_0 *)input)->unk_10 & 2) {
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the compiled object of the TU; the source shape that makes it unnecessary has not been found */
                if (((S_8004FAA4_2 *)(D_800814A8[0]))->unk_AC != 0) {
                    target_menu = menu;
                    target_side = 0;
select_target:
                    next_index = func_8004FD78(target_menu, target_side);
                    menu->unk_28 = 4;
                    index_delta = next_index - menu->unk_30;
                }
            }
            if (index_delta != 0) {
                goto apply_move;
            }
        } else {
apply_move:
            SD_Call(0x504);
            func_8004FA2C(menu, index_delta);
        }
    }
}
