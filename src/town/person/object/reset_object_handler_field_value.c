/* Reset object handler field 72 value 800. */
#include "common.h"
#include "shared/object_index_slots.h"

extern s32 D_800C3C5C;
#include "town/person/object/object_entries_aliases.h"


void reset_object_handler_field_72_value_800(void *object, s32 unused, s32 updateValue) {
    void *objectData;

    objectData = *(void **)((u8 *)object + 0x80);
    func_800C2E84(object, (s8 *)(updateValue), (s32 *)(*(s32 *)((u8 *)objectData + 0x14)));
    object_index_slots[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = &D_800C3C5C;
    *(s16 *)((u8 *)object + 0x72) = 0x800;
}
