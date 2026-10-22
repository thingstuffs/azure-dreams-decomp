/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/item_ids.h"
#include "records/Rec_func_800B1DCC_arg0.h"

typedef struct S_800B2400_8 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B2400_8;

typedef struct S_800B2400_9 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B2400_9;   /* ((((Rec_func_800B1DCC_arg0 *)arg0)->unk_18 * 4) + arg0) in move_item_to_list */

typedef struct S_800B2400_10 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B2400_10;

typedef struct S_800B2400_11 {
    s32 unk_00;
} S_800B2400_11;


typedef struct {
    s32 value;
} __attribute__((packed)) PackedItemWord;

s32 get_mode_value_or_default(s32);
void remove_selected_entry_from_list(s32, s32);
u32 find_unused_pool_slot(s32 *, s32, s32);
struct TownB4C60; void get_zero_based_group_index(struct TownB4C60 *);
s32 count_nonzero_entries(s32 *);


typedef struct S_800B2400_1 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800B2400_1;

typedef struct S_800B2400_2 {
    u8 pad_00[0x24];
    s32 unk_24;
    s32 unk_28;
} S_800B2400_2;

typedef struct S_800B2400_3 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2400_3;

typedef struct S_800B2400_4 {
    s32 * unk_00;
    s32 unk_04;
} S_800B2400_4;

typedef struct S_800B2400_5 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_800B2400_5;

typedef struct S_800B2400_6 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800B2400_6;

typedef struct S_800B2400_7 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800B2400_7;

/* Move the selected item to the destination list and return a status code. */
s32 move_item_to_list(void *state) {
    s32 *new_item;
    s32 dest_capacity;
    s32 source_index;
    s32 remove_index;
    s32 result;
    S_800B2400_2 *source_list;
    S_800B2400_4 *dest_slot;
    S_800B2400_3 *selected_item;
    S_800B2400_1 *dest_list;
    S_800B2400_6 *source_count;
    S_800B2400_7 *dest_count;
    S_800B2400_5 *source_selection;

    dest_capacity = get_mode_value_or_default(((Rec_func_800B1DCC_arg0 *)state)->unk_18);
    dest_list = state + (((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 0x10);
    if (dest_list->unk_28 >= dest_capacity) {
        result = 1;
        if (((Rec_func_800B1DCC_arg0 *)state)->unk_0C == 0) {
            result = 2;
        }
    } else {
        source_index = ((Rec_func_800B1DCC_arg0 *)state)->unk_14;
        source_list = state + (source_index * 0x10);
        if (source_list->unk_28 == 0) {
            result = 4;
        } else {
            selected_item = ((S_800B2400_11 *)((source_list->unk_24 * 4) + ((S_800B2400_8 *)(((source_index * 4)
                + state)))->unk_3C))->unk_00;
            if (((Rec_func_800B1DCC_arg0 *)state)->unk_0C == 0 && selected_item->unk_01 == ITEM_KIND_FAMILIAR) {
                result = 3;
            } else {
                dest_slot = ((S_800B2400_9 *)(((((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 4) + state)))->unk_3C
                    + (count_nonzero_entries((s32 *)(((S_800B2400_9 *)(((((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 4)
                    + state)))->unk_3C)) * 4);
                new_item = find_unused_pool_slot((s32 *)(((S_800B2400_9 *)(((((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 4)
                    + state)))->unk_3C), ((Rec_func_800B1DCC_arg0 *)state)->unk_18, dest_capacity);
                *(PackedItemWord *)new_item = *(PackedItemWord *)selected_item;
                dest_slot->unk_00 = new_item;
                dest_slot->unk_04 = 0;
                remove_index = ((Rec_func_800B1DCC_arg0 *)state)->unk_14;
                remove_selected_entry_from_list(((S_800B2400_10 *)(((remove_index * 4) + state)))->unk_3C,
                    (source_selection = state + (remove_index * 0x10), source_selection->unk_24));
                source_count = (((Rec_func_800B1DCC_arg0 *)state)->unk_14 * 0x10) + state;
                source_count->unk_28 = (s32) (source_count->unk_28 - 1);
                get_zero_based_group_index(state + ((((Rec_func_800B1DCC_arg0 *)state)->unk_14 * 0x10) + 0x1C));
                dest_count = state + (((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 0x10);
                dest_count->unk_28 = (s32) (dest_count->unk_28 + 1);
                get_zero_based_group_index(state + ((((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 0x10) + 0x1C));
                result = 0;
            }
        }
    }
    return result;
}
