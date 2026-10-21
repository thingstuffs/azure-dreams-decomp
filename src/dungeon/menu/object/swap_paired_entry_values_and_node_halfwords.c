#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_801237A4_arg0.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void select_paired_value_tables();    /* extern */
typedef struct HalfValue {
    s32 pad[2];
    u16 value;
} HalfValue;

typedef struct ValueLink {
    s32 pad;
    HalfValue *next;
} ValueLink;

extern s32 * catalog_display_node_slots[28];


/* Swap paired slot values and linked halfwords, toggle the state flag, and update. */
void swap_paired_entry_values_and_node_halfwords(Rec_func_801237A4_arg0 *state) {
    s32 * *slots;
    s32 * *right_slot;
    s32 * *left_slot;
    s32 *left_word;
    s32 saved_word;
    s32 slot_index;
    u16 saved_half;
    ValueLink *right;
    ValueLink *left;
    HalfValue *right_value;
    HalfValue *left_value;

    slot_index = 2;
    slots = catalog_display_node_slots;
    right_slot = slots + 0x10;
    left_slot = slots + 2;
    do {
        left_word = *left_slot;
        left_slot += 1;
        saved_word = *left_word;
        slot_index += 1;
        *left_word = **right_slot;
        **right_slot = saved_word;
        right_slot += 1;
    } while (slot_index < 0xE);
    right = (ValueLink *) catalog_display_node_slots[22];
    left = (ValueLink *) catalog_display_node_slots[8];
    right_value = right->next;
    left_value = left->next;
    saved_half = left_value->value;
    left_value->value = right_value->value;
    ((ValueLink *) catalog_display_node_slots[22])->next->value = saved_half;
    state->unk_16 = (s8) (state->unk_16 ^ 1);
    select_paired_value_tables(state);
}
