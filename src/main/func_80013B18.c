#include "common.h"

extern void func_800269B4(void *arg0);
extern void func_8004CBFC(void *arg0, s32 arg1, s32 *arg2);

/* Updates or clears active records, then refreshes the object if any were active. */
void func_80026B18(void *object, s32 *enable_flags, s32 *active_flags)
{
    s32 *slot_value;
    s32 *active_flag;
    s32 *enable_flag;
    s32 record_offset;
    s32 slot_index;
    s32 updated;
    u8 *value_slot;
    u8 *record;
    u8 *destination;
    u8 *global_data;

    slot_value = active_flags;
    updated = 0;
    if (object != 0) {
        slot_index = updated;
    } else {
        slot_index = updated;
    }
    record = object;
    record_offset = 4;
    enable_flag = enable_flags;
    value_slot = object;
    active_flag = slot_value;
    do {
        if (*active_flag != 0) {
            slot_value = *(s32 **)(value_slot + 0x68);
            updated = 1;
            if (*enable_flag != 0) {
                destination = (u8 *)object + record_offset;
                do {
                    global_data = (u8 *)0x80020000;
                } while (0);
                ASM_KEEP_DEP_NV(global_data, destination);
                global_data -= -0x7E68;
                func_8004CBFC(destination,
                              (s32)(unsigned long)global_data, slot_value);
            } else {
                *slot_value = 0;
                *(s32 *)(record + 8) = 0;
            }
        }
        record += 0xC;
        record_offset += 0xC;
        enable_flag++;
        value_slot += 4;
        slot_index++;
        active_flag++;
    } while (slot_index < 2);
    updated++;
    if (updated != 1) {
        func_800269B4(object);
    }
}
