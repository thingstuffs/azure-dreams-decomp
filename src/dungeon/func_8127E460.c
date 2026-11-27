/* Relink of matched dungeon/reset_and_release_beldo_effect_slots at file 0x1274460; imports and data use paired retail relocations. */
#include "common.h"
#include "dungeon/stale_bank_imports.h"
#include "shared/game_state.h"
extern s32 beldo_effect_stream_stale_bank;
extern s32 beldo_active_entity_stale_bank;
extern s16 beldo_command_ticks_stale_bank;
extern u8 *D_80172F90;
extern s32 beldo_effect_scripts_stale_bank;

typedef struct FlagsPage {
    u8 pad_00[0x3714];
    u16 system_update_flags;
    s16 monster_special_entry_index;
    s16 unk_3718;
    s16 sequence_step;
    s32 unk_371C;
} FlagsPage;

typedef struct ActiveState {
    u8 pad_00[0xB8];
    s16 script_index;
    s8 script_active;
} ActiveState;

/* Resets state and processes occupied entries in the two-slot object table. */
void reset_state_occupied_entries(void) {
    s16 slot_index;
    s16 next_slot;
    s32 object_addr;
    s32 slot_offset;
    u8 *saved_state;
    s32 saved_value;
    ActiveState *active_state;
    void *object_header;
    u8 *table_page;
    u32 high_bit;
    FlagsPage *flags_base;
    u16 state_flags;

    slot_index = 0;
    table_page = (u8 *)0x800E0000;
    high_bit = 0x80000000;
    flags_base = (FlagsPage *)0x80010000;
    active_state = (ActiveState *)(beldo_active_entity_stale_bank + 0x20);
    active_state->script_active = 1;
    state_flags = flags_base->system_update_flags;
    beldo_command_ticks_stale_bank = 0;
    *(s16 *)((u8 *)flags_base + 0x371A) = 0;
    *(s16 *)((u8 *)flags_base + 0x3718) = 0;
    *(s16 *)((u8 *)flags_base + 0x3716) = 0;
    state_flags = (state_flags | 9) & 0xFFEF;
    flags_base->system_update_flags = state_flags;
    saved_state = D_80172F90;
    GAME_STATE->log.data = saved_state;
    saved_value = beldo_effect_scripts_stale_bank;
    active_state->script_index = 0;
    beldo_effect_stream_stale_bank = saved_value;

    do {
        slot_offset = (slot_index << 16) >> 14;
        object_addr = *(s32 *)(slot_offset + *(s32 *)(table_page + 0x397C) + 0xAC);
        if (object_addr != 0) {
            func_80098E28(object_addr);
            object_header = (void *)(*(s32 *)(slot_offset + *(s32 *)(table_page + 0x397C) + 0xAC) - 0x20);
            *(u32 *)((u8 *)object_header + 0x10) |= high_bit;
        }
        next_slot = slot_index + 1;
        slot_index = next_slot;
    } while (next_slot < 2);
}
