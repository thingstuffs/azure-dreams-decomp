#include "shared/menu_display.h"
#include "shared/object_node.h"
#include "common.h"

#include "engine/menu.h"
#include "slus/data.h"

typedef struct S_8004F684 {
    /* 0x00 */ u32 unk00;
    /* 0x04 */ ObjectNodeHeader *entries[8];
    /* 0x24 */ s32 count;
    /* 0x28 */ s32 divisor;
    /* 0x2C */ s32 multiplier;
    /* 0x30 */ s32 idxB;
    /* 0x34 */ s32 idxA;
} S_8004F684;

/* Interpolate table values into each target's fields with scales of 30 and 12 and fixed offsets. */
void interpolate_selection_menu_entry_coordinates(S_8004F684 *state)
{
    S_8004F684 *settings;
    s32 entry_index;
    u8 *value_row;
    ObjectNodeHeader **entry_slot;
    s32 start_value;
    s32 value_delta;
    s32 scaled_weight;
    s32 offset;
    s32 offset2;
    s32 offset3;
    s32 target_value;
    ObjectNodeHeader *entry;
    MenuDisplayBlock *target;
    MenuDisplayNode *obj;

    settings = state;

    for (entry_index = 0; entry_index < settings->count; entry_index++) {
        entry_slot = (ObjectNodeHeader **)settings + entry_index;
        value_row = selection_menu_animation_keys + entry_index * 3;
        start_value = value_row[settings->idxA];
        value_delta = value_row[settings->idxB] - start_value;

        scaled_weight = settings->multiplier * 30;
        offset = (value_delta * scaled_weight) / settings->divisor;
        entry = entry_slot[1];
        obj = (MenuDisplayNode *)entry->sprite;
        target_value = start_value * 30;
        offset2 = offset + 0x200;
        target_value = target_value + offset2;
        obj->block->fields.depth = (s16)target_value;

        scaled_weight = settings->multiplier * 12;
        offset2 = (value_delta * scaled_weight) / settings->divisor;

        target = obj->block;
        target_value = start_value * 12;
        offset3 = offset2 - 0x40;
        target_value = target_value + offset3;
        target->fields.y = (s16)target_value;

    }
}
