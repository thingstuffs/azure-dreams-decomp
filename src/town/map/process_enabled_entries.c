#include "script_symbols.h"
#include "common.h"
#include "m2c_compat.h"



void set_resident_bitmap_bit(s32);
void clear_resident_bitmap_bit(s32);
s32 Control_CD(s32 event_code, void *event_data, s32 payload);
void drain_cd_command_queue(void);
void apply_building_tile_entry(s16, s16, u8);
extern M2C_UNK D_800D1BF4;
extern u8 D_800D2644[];
extern u8 D_800D2EA4[];

typedef struct S_800B98B4_0 {
    u8 unk_00;
    u8 unk_01;
} S_800B98B4_0;

typedef struct S_800B98B4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B98B4_1;

typedef struct S_800B98B4_2 {
    u8 unk_00;
} S_800B98B4_2;

typedef struct S_800B98B4_3 {
    u8 pad_00[0x33A4];
    u8 unk_33A4;
} S_800B98B4_3;

/* Processes enabled entries across 33 slots and handles entries of type 1. */
void process_enabled_entries(void) {
    S_800B98B4_3 *state_base;
    u8 *slot_data;
    u8 *entry_table;
    s32 slot_index;
    u8 entry_id;
    S_800B98B4_0 *entry;
    S_800B98B4_2 *reloaded_entry;

    Control_CD(6, &D_800D1BF4, 0);
    slot_index = 0;
    drain_cd_command_queue();
    clear_resident_bitmap_bit(F_funsui_sound);
    entry_table = D_800D2644;
    slot_data = D_800D2EA4;
    state_base = (S_800B98B4_3 *)0x80010000;
    do {
        entry_id = ((S_800B98B4_3 *)((u8 *)state_base + (slot_index * 2)))->unk_33A4;
        if (entry_id != 0) {
            entry = (void *)((u32)(entry_id << 5) + (u32)entry_table);
            if (entry->unk_01 != 0) {
                apply_building_tile_entry(((S_800B98B4_1 *)slot_data)->unk_00, ((S_800B98B4_1 *)slot_data)->unk_01, entry->unk_00);
            }
            reloaded_entry = (void *)((u32)(((S_800B98B4_3 *)((u8 *)state_base + (slot_index * 2)))->unk_33A4 << 5)
                + (u32)entry_table);
            if (reloaded_entry->unk_00 == 1) {
                set_resident_bitmap_bit(F_funsui_sound);
            }
        }
        slot_data += 8;
        slot_index += 1;
    } while (slot_index < 0x21);
}
