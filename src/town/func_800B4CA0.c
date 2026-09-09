/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B1DCC_arg0.h"

typedef struct S_800B2400_8 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B2400_8;   /* ((temp_v1 * 4) + arg0) in func_800B2400 */

typedef struct S_800B2400_9 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B2400_9;   /* ((((Rec_func_800B1DCC_arg0 *)arg0)->unk_18 * 4) + arg0) in func_800B2400 */

typedef struct S_800B2400_10 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B2400_10;   /* ((temp_v1_2 * 4) + arg0) in func_800B2400 */

typedef struct S_800B2400_11 {
    s32 unk_00;
} S_800B2400_11;   /* (temp_a0->unk_24 * 4) + ((S_800B2400_8 *)(((temp_v1 * 4) + arg0)))->unk_3C in func_800B2400 */




typedef struct {
    s32 value;
} __attribute__((packed)) M2C_UNALIGNED_WORD;

s32 func_800B2130();
M2C_UNK func_800B2190();
M2C_UNK *func_800B2280();
M2C_UNK func_800B23C0();
s32 func_800B29A4();


typedef struct S_800B2400_1 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800B2400_1;   /* temp_v1_5 in func_800B2400 */

typedef struct S_800B2400_2 {
    u8 pad_00[0x24];
    s32 unk_24;
    s32 unk_28;
} S_800B2400_2;   /* temp_a0 in func_800B2400 */

typedef struct S_800B2400_3 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800B2400_3;   /* temp_s2 in func_800B2400 */

typedef struct S_800B2400_4 {
    M2C_UNK * unk_00;
    s32 unk_04;
} S_800B2400_4;   /* temp_s0 in func_800B2400 */

typedef struct S_800B2400_5 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_800B2400_5;   /* temp_sp in func_800B2400 */

typedef struct S_800B2400_6 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800B2400_6;   /* temp_v1_3 in func_800B2400 */

typedef struct S_800B2400_7 {
    u8 pad_00[0x28];
    s32 unk_28;
} S_800B2400_7;   /* temp_v1_4 in func_800B2400 */

/* Move the selected item to the destination list and return a status code. */
s32 func_800B2400(void *state) {
    M2C_UNK *new_item;
    s32 dest_capacity;
    s32 source_index;
    s32 remove_index;
    s32 result;
    u8 item_type;
    S_800B2400_2 *source_list;
    S_800B2400_4 *dest_slot;
    S_800B2400_3 *selected_item;
    S_800B2400_1 *dest_list;
    S_800B2400_6 *source_count;
    S_800B2400_7 *dest_count;
    S_800B2400_5 *source_selection;

    dest_capacity = func_800B2130(((Rec_func_800B1DCC_arg0 *)state)->unk_18);
    dest_list = state + (((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 0x10);
    if (dest_list->unk_28 >= dest_capacity) {
        result = 1;
        if (((Rec_func_800B1DCC_arg0 *)state)->unk_0C == 0) {
            result = 2;
            goto done;
        }
        goto done;
    }
    source_index = ((Rec_func_800B1DCC_arg0 *)state)->unk_14;
    source_list = state + (source_index * 0x10);
    if (source_list->unk_28 == 0) {
        result = 4;
        goto done;
    }
    selected_item = ((S_800B2400_11 *)((source_list->unk_24 * 4) + ((S_800B2400_8 *)(((source_index * 4) + state)))->unk_3C))->unk_00;
    if (((Rec_func_800B1DCC_arg0 *)state)->unk_0C == 0) {
        item_type = selected_item->unk_01;
        if (item_type == 0x13) {
            result = 3;
            goto done;
        }
    }
    {
        dest_slot = ((S_800B2400_9 *)(((((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 4) + state)))->unk_3C + (func_800B29A4(((S_800B2400_9 *)(((((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 4) + state)))->unk_3C) * 4);
        new_item = func_800B2280(((S_800B2400_9 *)(((((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 4) + state)))->unk_3C, ((Rec_func_800B1DCC_arg0 *)state)->unk_18, dest_capacity);
        *(M2C_UNALIGNED_WORD *)new_item = *(M2C_UNALIGNED_WORD *)selected_item;
        dest_slot->unk_00 = new_item;
        dest_slot->unk_04 = 0;
        remove_index = ((Rec_func_800B1DCC_arg0 *)state)->unk_14;
        func_800B2190(((S_800B2400_10 *)(((remove_index * 4) + state)))->unk_3C, (source_selection = state + (remove_index * 0x10), source_selection->unk_24));
        source_count = (((Rec_func_800B1DCC_arg0 *)state)->unk_14 * 0x10) + state;
        source_count->unk_28 = (s32) (source_count->unk_28 - 1);
        func_800B23C0(state + ((((Rec_func_800B1DCC_arg0 *)state)->unk_14 * 0x10) + 0x1C));
        dest_count = state + (((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 0x10);
        dest_count->unk_28 = (s32) (dest_count->unk_28 + 1);
        func_800B23C0(state + ((((Rec_func_800B1DCC_arg0 *)state)->unk_18 * 0x10) + 0x1C));
        result = 0;
    }
done:
    return result;
}
