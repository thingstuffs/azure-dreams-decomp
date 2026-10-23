#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 scene_registered_entry_handle;
extern s32 D_80019544;

typedef struct S_80480444_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
} S_80480444_0;   /* D_80019540 in prepare_scene_request_state */

/* Save the referenced object's unk_24 in D_80019544 and return its unk_20. */
s32 prepare_scene_request_state(void) {
    D_80019544 = ((S_80480444_0 *)scene_registered_entry_handle)->unk_24;
    return ((S_80480444_0 *)scene_registered_entry_handle)->unk_20;
}
