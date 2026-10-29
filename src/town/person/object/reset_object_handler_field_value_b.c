/* Reset object handler field 72 value 400. */
#include "common.h"
#include "shared/object_index_slots.h"

extern s32 person_reset_handler_address;
#include "town/person/object/object_entries_aliases.h"
#include "town/person/object.h"


void reset_object_handler_field_72_value_400(void *object, s32 unused, SpriteFrameState *updateValue) {
    void *objectData;

    objectData = *(void **)((u8 *)object + 0x80);
    func_800C2E84(object, updateValue, (s32 *)(*(s32 *)((u8 *)objectData + 0x14)));
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = &person_reset_handler_address;
    *(s16 *)((u8 *)object + 0x72) = 0x400;
}
