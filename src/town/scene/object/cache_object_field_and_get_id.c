#include "common.h"
#include "m2c_compat.h"
#include "town/scene/object.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 scene_registered_data_handle;
extern s32 D_80018BEC;

typedef struct S_806976E8_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
} S_806976E8_0;   /* D_80018BE8 in cache_object_field_and_get_id */

/* Cache the current object's field at 0x24 and return its field at 0x20. */
s32 cache_object_field_and_get_id(void) {
    D_80018BEC = ((S_806976E8_0 *)scene_registered_data_handle)->unk_24;
    return ((S_806976E8_0 *)scene_registered_data_handle)->unk_20;
}
