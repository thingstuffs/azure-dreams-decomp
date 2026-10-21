/* Item menu cursor transition (G00601). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B0FD4, CL:town/func_800B10F4. */
#include "town/shop/item_menu_cursor_transition_g00601.h"

/* Sets fixed values and color bytes on each item's linked records. */
void style_item_menu_entry_records(S_800AE734_0 *collection) {
    s32 entry_offset;
    s32 entry_index;

    entry_index = 0;
    if (collection->unk_28 > 0) {
        do {
            entry_offset = entry_index * 4;
            ((S_800AE734_6 *)(((S_800AE734_2 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_38))->unk_04.s))->unk_08 = 0x20;
            *((S_800AE734_2 *)(((S_800AE734_1 *)((entry_offset + collection->unk_D8)))->unk_38))->unk_04.u = 0x68;
            ((S_800AE734_6 *)(((S_800AE734_2 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_38))->unk_04.s))->unk_01 = 0x68;
            ((S_800AE734_6 *)(((S_800AE734_2 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_38))->unk_04.s))->unk_02 = 0x60;
            ((S_800AE734_7 *)(((S_800AE734_3 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_08))->unk_04))->unk_08 = 9;
            ((S_800AE734_8 *)(((S_800AE734_4 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_20))->unk_04))->unk_08 = 0x39;
            ((S_800AE734_9 *)(((S_800AE734_5 *)(((S_800AE734_1 *)((entry_offset
                + collection->unk_D8)))->unk_50))->unk_04))->unk_08 = 0x8F;
            entry_index += 1;
        } while (entry_index < collection->unk_28);
    }
}

/* Animate the cursor position, row offsets, and colors during a row transition. */
void animate_item_menu_cursor_transition(void *state) {
    s32 start_row;
    s32 start_r_duration;
    s32 start_g_duration;
    s32 end_r_duration;
    s32 end_g_duration;
    s32 slide_offset;
    s32 cursor_offset;
    s32 start_b_duration;
    s32 row_delta;
    s32 scaled_progress;
    s32 end_b_duration;
    void *cursor_prim;

    style_item_menu_entry_records((S_800AE734_0 *)state);
    start_row = F(state, s32, 0x20);
    row_delta = F(state, s32, 0x1C) - start_row;
    scaled_progress = F(state, s32, 8) * 0x10;
    cursor_offset = row_delta * scaled_progress / F(state, s32, 4) + 0xA;
    cursor_prim = F(F(F(state, void *, 0xD8), void *, 4), void *, 4);
    F(cursor_prim, s16, 0xA) = (s16)(start_row * 0x10 + cursor_offset);
    slide_offset = (F(state, s32, 8) * 8) / F(state, s32, 4);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s16, 8) =
        (s16)(0x28 - slide_offset);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s16, 8) =
        (s16)(slide_offset + 0x20);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x50), void *, 4), s16, 8) =
        (s16)(0x97 - slide_offset);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x50), void *, 4), s16, 8) =
        (s16)(slide_offset + 0x8F);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 8), void *, 4), s16, 8) =
        (s16)(0x11 - slide_offset);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 8), void *, 4), s16, 8) = (s16)(slide_offset + 9);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x20), void *, 4), s16, 8) =
        (s16)(0x41 - slide_offset);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x20), void *, 4), s16, 8) =
        (s16)(slide_offset + 0x39);
    start_r_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 0) =
        (s8)(((start_r_duration - F(state, s32, 8)) * 0x18) / start_r_duration + 0x68);
    start_g_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 1) =
        (s8)(((start_g_duration - F(state, s32, 8)) * 0x18) / start_g_duration + 0x68);
    start_b_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x20) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 2) =
        (s8)(((start_b_duration - F(state, s32, 8)) << 5) / start_b_duration + 0x60);
    end_r_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 0) =
        (s8)(-0x80 - ((end_r_duration - F(state, s32, 8)) * 0x18) / end_r_duration);
    end_g_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 1) =
        (s8)(-0x80 - ((end_g_duration - F(state, s32, 8)) * 0x18) / end_g_duration);
    end_b_duration = F(state, s32, 4);
    F(F(F(F(state, s32, 0x1C) * 4 + F(state, void *, 0xD8), void *, 0x38), void *, 4), s8, 2) =
        (s8)(-0x80 - ((end_b_duration - F(state, s32, 8)) << 5) / end_b_duration);
}
