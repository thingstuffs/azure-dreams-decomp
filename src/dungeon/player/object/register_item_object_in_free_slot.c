#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "dungeon/item.h"
#include "dungeon/player/object.h"

extern s32 get_bounded_stride_index(void *, void *, s32, s32);
extern s32 find_last_zero_entry_run_start(void);
extern s32 find_and_clear_empty_item_slot(void);
extern void *get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern s32 write_text_byte_and_advance(s8 value, s8 *dest);
extern s32 append_typed_formatted_value(void *, s32);
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void play_sound_if_enabled(s32);
extern void display_text_with_fullwidth_adjustment(s8 *text);

extern u8 temporary_item_record[];
extern void *held_item_record;
extern u8 D_800E07EF[];
extern u8 dungeon_ground_item_positions[];

/* Moves a held or selected ground item into free inventory slots, or displays a failure message when full. */
void *register_item_object_in_free_slot(void *target, void *ptr1, void *ptr2, s16 flag)
{
    s16 held_flag = flag;
    s32 first;
    s32 second;
    s32 index;
    void *object;
    s32 found;
    s32 narrowed;
    s32 address;
    u32 flags;
    u8 *entry;
    u8 *entry_base;
    s32 entry_base_s;
    void *global_object;
    void **slot;

    if (target == (void *)&held_item_record ||
        target == (void *)temporary_item_record ||
        target == *(void **)((u8 *)primary_actor_record + 0xF0)) {
    first = find_last_zero_entry_run_start();
    second = find_and_clear_empty_item_slot();
    index = (s16)first;

    if (index < 0 || (s16)second < 0) {
        object = get_unused_text_buffer();
        clear_byte_and_advance(expand_text_control_codes(ptr2,
            apply_type_based_entry_adjustments(target,
                expand_text_control_codes(ptr1, write_text_byte_and_advance(8, object)))));
        display_text_with_fullwidth_adjustment(object);
        return 0;
    }

    object = get_unused_text_buffer();
    clear_byte_and_advance(expand_text_control_codes(D_800E07EF,
        append_typed_formatted_value(target, object)));
    if (held_flag != 0) {
        display_text_with_fullwidth_adjustment(object);
    }
    play_sound_if_enabled(0x508);

    if (target == (void *)&held_item_record) {
        slot = &((void **)0x80010248)[index];
        *slot = held_item_record;
        global_object = primary_actor_record;
        flags = *(u32 *)((u8 *)global_object + 0x1C);
        held_item_record = 0;
        *(s32 *)((u8 *)global_object + 0x124) = 0;
        *(u32 *)((u8 *)global_object + 0x1C) = flags & 0xFFEFFFFF;
    } else {

        found = (s16)get_bounded_stride_index(*(void **)(((u8 *)dungeon_actor_ring_anchor) + 0xF0),
                                 ((u8 *)dungeon_ground_items), 4, 0x40);
        if (found >= 0) {
            entry_base_s = (s32)dungeon_ground_item_positions;
            entry = (u8 *)(found * 12);
            entry += entry_base_s;
            update_map_cell_flags_with_item_limit(entry[0], entry[1], 0x800);
            ((void **)0x80010248)[index] = *(void **)temporary_item_record;
        } else {
            ((void **)0x80010248)[index] = *(void **)temporary_item_record;
        }
        *(s32 *)*(void **)((u8 *)primary_actor_record + 0xF0) = 0;
    }
    entry_base = (u8 *)0x80010248;
    narrowed = first << 16;
    narrowed >>= 14;
    address = narrowed + (s32)entry_base;
    narrowed = (u16)second;
    *(s32 *)target = 0;
    target = (void *)address;
    entry_base = (u8 *)0x80010000;
    address = narrowed << 16;
    address >>= 14;
    address += (s32)entry_base;
    *(void **)(address + 0x29c) = target;
    }
    return target;
}
