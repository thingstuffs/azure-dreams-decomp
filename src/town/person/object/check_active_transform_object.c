#include "common.h"
#include "town/person/object.h"

extern s32 scene_object_payload_alias;
extern s32 town_position_callback_address;
extern void *town_target_record;

/* True when the active object shares its 0x60 field with `other` and the global hook is the default. */
s32 check_active_transform_object(void *other) {
    s32 result;

    if (town_target_record != 0) {
        result = 0;
        if (*(s32 *)((u8 *)town_target_record + 0x60) ==
            *(s32 *)((u8 *)other + 0x60)) {
            result = scene_object_payload_alias == (s32)&town_position_callback_address;
        }
        return result;
    }
    return 0;
}

