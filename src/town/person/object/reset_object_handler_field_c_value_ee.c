/* Reset object handler field 6c value 15 46ee4. */
#include "common.h"
#include "shared/object_index_slots.h"

extern s32 D_800C3FC8;
#include "town/person/object/object_entries_aliases.h"
#include "town/person/object.h"


/*
 * Reinitializes entries from linked data offset 0x1C, clears the indexed object slot, and installs
 * D_800C3FC8 with count 0x15.
 */
void reset_object_handler_field_6c_value_15_46ee4(void *object, s32 unused, SpriteFrameState *updateValue) {
    void *objectData;

    objectData = *(void **)((u8 *)object + 0x80);
    func_800C2E84(object, updateValue, (s32 *)(*(s32 *)((u8 *)objectData + 0x1C)));
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = &D_800C3FC8;
    *(s16 *)((u8 *)object + 0x6C) = 0x15;
}
