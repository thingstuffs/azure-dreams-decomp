/* Reset object handler field 6c value 15. */
#include "common.h"
#include "shared/object_index_slots.h"

extern s32 D_800C3B7C;
extern void func_800C2E84();


void reset_object_handler_field_6c_value_15(void *object, s32 unused, s32 updateValue) {
    void *objectData;

    objectData = *(void **)((u8 *)object + 0x80);
    func_800C2E84(object, updateValue, *(s32 *)((u8 *)objectData + 0x10));
    D_80082660[*(s32 *)((u8 *)object + 0x60)].unk_00 = 0;
    *(void **)((u8 *)object + 0x54) = &D_800C3B7C;
    *(s16 *)((u8 *)object + 0x6C) = 0x15;
}
