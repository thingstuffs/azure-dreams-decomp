#include "common.h"
#include "town/person.h"

extern s32 scene_object_payload_alias;
extern s32 town_position_callback_address[3];
extern void *town_target_record;

/* The selected contact is the word at +0x10 in the Town collision controller. */
s32 check_town_target_and_callback(const void *object) {
    s32 matches;

    matches = 0;
    if (town_target_record == object) {
        matches = scene_object_payload_alias == (s32) &town_position_callback_address;
    }
    return matches;
}
