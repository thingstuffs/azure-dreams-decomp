#include "common.h"
#include "town/scene/entry_requests.h"

extern s32 D_80019170;
extern s32 D_80019174;

/* Store the supplied values in D_80019170 and D_80019174. */
void store_scene_value_pair(s32 first_value, s32 second_value) {
    D_80019170 = first_value;
    D_80019174 = second_value;
}
