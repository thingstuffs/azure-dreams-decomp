/* Entry queue (G00564). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A2B1C, CL:town/func_800A2CA4, CL:town/func_800A2D54, PD:town/engine:80100AA0. */
#include "town/shop/entry_queue_g00564.h"

/* Clears all 20 entries in D_80100AA0. */
void clear_entry_table(void) {
    s32 *entry;
    s32 index;

    index = 19;
    entry = (s32 *)D_80100AA0;
    entry += 19;
    do {
        *entry = 0;
        index--;
        entry--;
    } while (index >= 0);
}

/* Inserts a record into the first free slot, discarding the first record if full. */
void handle_inserts_first_free_slot_discarding_first_full(TownRecord *record) {
    TownRecord *dst;
    s32 slot;

    slot = 0;
    dst = D_80100AA0;
    while (slot < 20) {
        if (dst->bytes.unk1 == 0) {
            break;
        }
        slot++;
        dst++;
    }

    if (slot == 20) {
        for (slot = 0; slot < 19; slot++) {
            D_80100AA0[slot] = D_80100AA0[slot + 1];
        }
    }

    D_80100AA0[slot].bytes.unk0 = record->bytes.unk0;
    D_80100AA0[slot].bytes.unk1 = record->bytes.unk1;
    D_80100AA0[slot].bytes.unk2 = record->bytes.unk2;
    D_80100AA0[slot].bytes.unk3 = record->bytes.unk3;
}

/* Returns the address of D_80100AA0. */
s32 *get_address_global_80100_aa_0(void) {
    return (s32 *)&D_80100AA0;
}

/* Shift entries left until a free entry or the limit, then clear the tail. */
void handle_shift_entries_left_until_free_entry_limit_clear_tail(void) {
    s32 entry_index;
    s32 *entries = (s32 *)&D_80100AA0[0];
    s32 *write_entry;
    s32 *src;

    entry_index = 0;
    write_entry = entries;
    src = entries + 1;
    while (entry_index < 19) {
        if (((u8 *)write_entry)[1] == 0) {
            break;
        }
        *write_entry = *src;
        src++;
        entry_index++;
        write_entry++;
    }
    entries[entry_index] = 0;
}

/* Run the follow-up action when the current record has an eligible type and passes the check. */
void run_the_follow_up_action_has_eligible_type_passes_check(s32 check_value) {
    u8 record_type;
    S_800A0504_0 *record;

    record = (S_800A0504_0 *)get_address_global_80100_aa_0();
    record_type = record->unk_01;
    if ((record_type != 0) && (record_type != 0x13) && (create_an_position_initializes_graphics_state(record, check_value) != 0)) {
        handle_shift_entries_left_until_free_entry_limit_clear_tail();
    }
}
