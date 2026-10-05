#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern void func_8008D344(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 func_80098864(void *request, s32 record_data);
extern s32 func_80098B38(void *slot);
extern s32 func_800997FC(void *context, s32 first_input, s32 second_input);
extern s32 func_800A5F38(void *object_context, void *target);
extern s32 func_800A6480(void *actor, void *item, s32 buffer_arg2);
extern s32 func_800AD6FC(void *state, s32 mode, void *item);

typedef struct {
    s16 flags;
    u8 pad2[18];
} DungeonItem;

typedef struct {
    u8 pad0[12];
    DungeonItem *entries;
    u8 pad10[4];
} DungeonGroup;

extern DungeonGroup D_80073414[];
extern u8 D_800E101C;

/* Dispatch an item action using its category flags and target selector, then decrement the counter. */
s32 func_800BE360(void *target, void *item, s16 action_type, s32 action_value) {
    s32 item_index;
    s32 category_index;
    DungeonItem *item_entries;
    u16 *selector_table;
    s32 selector;
    s16 item_flags;
    u16 selector_bits;

    if (action_type == 0xD) {
        return func_80098864(item, action_value);
    }
    if ((s32) target == ((s32)D_800E3D7C)) {
        *(void **)((u8 *)target + 0x110) = item;
        func_8008D344(target, ((s32 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }
    if ((u32)target <= 0x9FFFFFFFU) {
        func_800A6480(target, item, action_type);
        category_index = *((u8 *)item + 1);
        item_index = *((u8 *)item + 0);
        item_entries = D_80073414[category_index].entries;
        item_flags = item_entries[item_index].flags;
        if (!(item_flags & 0x8000)) {
            selector = D_800DDE84[*((u8 *)target + 0x13)] & 3;
        } else {
            selector_table = D_800DDE84;
            selector_bits = selector_table[*((u8 *)target + 0x13)];
            selector = (selector_bits >> 4) & 3;
        }
        if (func_800AD6FC(target, selector, item) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
        func_80098B38(item);
    } else {
        func_800997FC((u8 *)&D_800E101C, action_value, action_type);
    }
    dungeonStatus.unk_0A = ((u16)dungeonStatus.unk_0A) - 1;
    return 1;
}
