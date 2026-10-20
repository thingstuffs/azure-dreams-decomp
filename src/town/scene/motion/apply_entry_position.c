#include "common.h"

typedef struct {
    s16 unk0;
    s16 selector;
    s32 result;
} Entry;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 unk6;
} Position;

extern s32 find_entry_8_index_or_assert();
extern void update_dependent_entry_ids();
extern s32 all_entries_pass_check();
extern void set_script_flag_bit();

/* Applies the selected entry's position and returns its result. */
s32 apply_entry_position(Entry *entries, s32 object, void *context, s32 selection)
{
    s32 saved_object;
    s32 entry_index;
    Position *position;
    s32 selector;
    s32 table;

    saved_object = object;

    entry_index = find_entry_8_index_or_assert(entries, selection);
    selector = entries[entry_index].selector;
    table = *(s32 *)((u8 *)context + 0x14);
    position = (Position *)(selector * 8 + table);
    update_dependent_entry_ids(position->x, position->y, position->z);

    if (saved_object != 0 && all_entries_pass_check(saved_object) != 0) {
        set_script_flag_bit(*(s16 *)((u8 *)context + 0x18));
    }

    return entries[entry_index].result;
}
