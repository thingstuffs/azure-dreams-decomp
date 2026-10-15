#include "modules/town_door.h"

/* Initialize the record and select its handler according to its variant. */
void func_800A06A4(void *record_data, s32 initial_value) {
    u32 variant;

    variant = ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_A4;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_00 = &func_800A0708;
    {
        union { s32 *pointer; s32 value; } handler;

        if (variant == 1) {
            handler.value = 2;
            ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_A0 = handler.value;
            handler.pointer = &func_800A0BE4;
            ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_7E = 0;
        } else if (variant == 0) {
            handler.pointer = &func_800A0AC8;
        } else {
            handler.pointer = &func_800A07A4;
            ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_7E = 0;
        }
        ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_60 = handler.pointer;
    }
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_18 = initial_value;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_1C = &D_800D09E0;
    ((S_800A06A4_0 *)((u8 *)record_data - 0x10))->unk_78 = 0;
}
