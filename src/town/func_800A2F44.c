#include "modules/town_door.h"

/* Initialize the record and select its handler according to its variant. */
void initialize_door_variant(void *record_data, s32 initial_value) {
    u32 variant;

    variant = ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_A4;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_00 = &handle_door_check_result;
    {
        union { s32 *pointer; s32 value; } handler;

        if (variant == 1) {
            handler.value = 2;
            ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_A0 = handler.value;
            handler.pointer = &advance_door_step;
            ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_7E = 0;
        } else if (variant == 0) {
            handler.pointer = &trigger_door_interaction_effect;
        } else {
            handler.pointer = &install_next_door_handler;
            ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_7E = 0;
        }
        ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_60 = handler.pointer;
    }
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_18 = initial_value;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_1C = &D_800D09E0;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_78 = 0;
}
