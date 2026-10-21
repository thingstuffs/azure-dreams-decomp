#include "common.h"

extern s32 scene_object_payload_alias;
extern s32 D_80097D2C[3];
extern s32 town_target_record;

/* Check whether both the requested identifier and the global pointer match. */
s32 check_transform_identifier_and_hook(s32 requested_id) {
    s32 matches;

    matches = 0;
    if (town_target_record == requested_id) {
        matches = scene_object_payload_alias == (s32) &D_80097D2C;
    }
    return matches;
}
