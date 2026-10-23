#include "common.h"

typedef struct S_func_800B361C_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xAC];
    void *unk_CC;
} S_func_800B361C_0;

typedef struct S_func_800B361C_1 {
    u8 pad_00[0x74];
    void *unk_74;
    void *unk_78;
} S_func_800B361C_1;

extern s32 item_menu_primary_page_data[];
extern s32 card_selection_display_data[];

/* Update status flags and state pointers from the current value and its limit. */
void update_shop_state_flags(S_func_800B361C_0 *object) {
    if (object->unk_10 > 0) {
        S_func_800B361C_1 *state;
        s32 branch_flags;

        state = object->unk_CC;
        *(void **)state->unk_74 = item_menu_primary_page_data;
        branch_flags = object->unk_1C;
        branch_flags &= ~2;
        object->unk_1C = branch_flags;
    } else {
        s32 branch_flags;

        branch_flags = object->unk_1C;
        branch_flags |= 2;
        object->unk_1C = branch_flags;
    }

    if (object->unk_10 < object->unk_14) {
        s32 clear_mask;
        S_func_800B361C_1 *state;

        clear_mask = ~1;
        object->unk_1C &= clear_mask;

        state = object->unk_CC;
        *(void **)state->unk_78 = card_selection_display_data;
        return;
    }

    object->unk_1C |= 1;
}
