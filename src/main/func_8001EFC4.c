#include "common.h"

typedef struct S_8001EFC4_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_8001EFC4_0_pre;   /* the 0x10 bytes before root in func_8001EFC4, addressed as root[-1] */

typedef struct S_8001EFC4_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
} S_8001EFC4_0;   /* root in func_8001EFC4 */


extern void func_80063FF8(s32 code);
extern void advance_indexed_object_operation(void *obj);
extern s32 func_80058FF0(s32 current, s32 direction, s32 amount);
extern void card_devkit_refresh_save_slot_pair_highlights(void *obj);
extern s32 card_devkit_poll_stable_slot_state(void);
extern void submit_stored_and_queried_boot_values(void);
extern void propagate_object_high_bit_flags(void *obj);
extern void allocate_or_reuse_effect_and_install_callback(s32 current, s32 mode);
extern volatile s32 D_801379A8;
extern volatile s32 D_801379B0;
extern u8 D_80405AB4[];

/* Per-frame menu step: handle the pad's edge/repeat flags, move the cursor and run the post-step hooks. */
void func_8001EFC4(u8 *root)
{
    s32 action = 0;
    s32 entry_flags;
    s32 flags8;
    s32 flags10;
    s32 value;
    s32 side;
    s32 result;

    entry_flags = D_801379A8;
    if (entry_flags != 0) {
        s32 flags20;
        s32 flags5000;

        flags20 = D_801379B0;
        if (flags20 & 0x40) {
            func_80063FF8(0x515);
            ((S_8001EFC4_0_pre *)root)[-1].unk_00 = D_80405AB4;
        }
        flags10 = D_801379B0;
        if (flags10 & 0x20) {
            func_80063FF8(0x514);
            advance_indexed_object_operation(root);
        } else {
            flags5000 = D_801379A8;
            if (flags5000 & 0x5000) {
                side = flags10 & 0x5000;
                if (side != 0) {
                    (*(s32 *)((u8 *)root + 0x30)) = 0;
                    flags10 = D_801379B0;
                    if (flags10 & 0x1000) {
                        action = -1;
                    } else if (flags10 & 0x4000) {
                        action = 1;
                    }
                } else {
                    value = ((S_8001EFC4_0 *)root)->unk_30;
                    if (value >= 13) {
                        side = value - 2;
                        (*(s32 *)((u8 *)root + 0x30)) = side;
                        flags8 = D_801379A8;
                        if (flags8 & 0x1000) {
                            action = -1;
                        } else if (flags8 & 0x4000) {
                            action = 1;
                        }
                    } else {
                        side = value + 1;
                        ((S_8001EFC4_0 *)root)->unk_30 = side;
                    }
                }
            }
        }

        if (action != 0) {
            func_80063FF8(0x502);
            value = func_80058FF0(((S_8001EFC4_0 *)root)->unk_28, action, 5);
            ((S_8001EFC4_0 *)root)->unk_28 = value;
            card_devkit_refresh_save_slot_pair_highlights(root);
        }
    }

    result = card_devkit_poll_stable_slot_state();
    submit_stored_and_queried_boot_values();
    if (result == 0) {
        return;
    }
    if (result == 1) {
        return;
    }
    propagate_object_high_bit_flags(root - 0x20);
    allocate_or_reuse_effect_and_install_callback(((S_8001EFC4_0 *)root)->unk_20, 0);

    return;
}
