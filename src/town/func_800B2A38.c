#include "common.h"

extern s32 *reallocField0Buffer(s32 *buffer_slot, s32 entry_count, s32 clear_words);
extern void textureSetTheFieldOffsetHex8InEachEntryPointerArray(void *entries, s32 value, s32 count);

extern s32 D_8002E5E8[];


s32 load_actor_display_resource(void *object, s32 entry_count) {
    s32 success = 0;
    s32 *handle = reallocField0Buffer((s32 *)((u8 *)object + 0xAC), entry_count, 12);

    *(s32 **)((u8 *)object + 0xA8) = handle;
    if (handle != 0) {
        *(s32 *)((u8 *)object + 0x8C) = D_8002E5E8[0];
        *(s32 *)((u8 *)object + 0x90) = D_8002E5E8[1];
        *(s32 *)((u8 *)object + 0x94) = D_8002E5E8[2];
        textureSetTheFieldOffsetHex8InEachEntryPointerArray(handle, (s32)((u8 *)object + 0x8C), 40);
        success = 1;
    }
    return success;
}
