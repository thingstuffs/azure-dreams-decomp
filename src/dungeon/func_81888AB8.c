#include "modules/dungeon_ovl_18a6800.h"
#include "modules/dungeon_native_abi.h"
#include "common.h"

extern s32 try_trigger_target_record_effect(s32, s32);
extern s32 set_or_clear_actor_status_slot(s32, s32, s32);
extern void adjust_source_value_and_finalize(s32, void *);
extern u8 D_800E1D01[9];

/* Checks the target using a scaled low-byte value and conditionally applies D_800E1D01. */
void check_the_target_using_scaled_low_byte_conditionally_applies_global_800_e_1_d_01(s32 target, s32 value, void *unused) {
    u8 pinnedValue = value;
    if (try_trigger_target_record_effect(target, 2) == 0) {
        u32 scaledLowByte = pinnedValue;
        scaledLowByte >>= 2;
        if ((set_or_clear_actor_status_slot(target, 0x16, scaledLowByte + 4) << 16) != 0) {
            adjust_source_value_and_finalize(target, D_800E1D01);
        }
    }
}
