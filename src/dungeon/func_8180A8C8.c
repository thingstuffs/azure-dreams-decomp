#include "modules/dungeon_ovl_1829800.h"

void switch_active_object_index(void *object, s16 new_index) {
    s16 old_index;
    s32 entry_index;
    s32 direction;
    S_800260C8_2 *entry_offsets;
    S_800260C8_3 *linked_state;
    S_800260C8_0 *index_state;
    void *entries;
    ResidentPage *resident_page;

    index_state = object + 0x20;
    old_index = index_state->unk_26;
    if (old_index != new_index) {
        entries = ((S_800260C8_1 *)object)->unk_20;
        if (entries != NULL) {
            ((S_800260C8_6 *)(((S_800260C8_4 *)(((old_index * 4) + entries)))->unk_0C))->unk_B6 = 4;
            resident_page = (ResidentPage *)0x80010000;
            entry_index = index_state->unk_26;
            entry_offsets = ((S_800260C8_7 *)(((S_800260C8_5 *)(((entry_index * 4)
                + ((S_800260C8_1 *)object)->unk_20)))->unk_0C))->unk_0C;
            direction = (resident_page->table[entry_index] + 2) & 7;
            entry_offsets->unk_24 = (s8) (dir_step_x[direction] + 1);
            entry_offsets->unk_25 = (s8) (dir_step_y[direction] + 1);
        }
        index_state->unk_26 = new_index;
        linked_state = ((S_800260C8_1 *)object)->unk_20;
        if (linked_state != NULL) {
            linked_state->unk_26 = new_index;
        }
    }
}
