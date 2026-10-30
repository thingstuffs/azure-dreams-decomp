#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "engine/node.h"

typedef struct S_800A7AC0_0 {
    void (*unk_00)(void *, void *, void *);
} S_800A7AC0_0;   /* arg0 in initialize_effect_object; pointer addresses record offset 0x10 */
#include "town/system/clear_object_status_and_dispatch_target_api.h" /* extern */
void finalize_checked_object_or_fallback(void *object, void *check_data, void *fallback_data);
extern M2C_UNK D_800F838C;

/* Initialize the object with its state, resource data, and callback. */
void initialize_effect_object(void *object, void *unused, struct SpriteFrameState *context) {
    ((S_800A7AC0_0 *)((u8 *)object - 0x10))->unk_00 = &finalize_checked_object_or_fallback;
    clear_object_status_and_dispatch_target(object, context, (int)(&D_800F838C), 0);
    register_node_if_unregistered(object, project_sprite_chain);
}
