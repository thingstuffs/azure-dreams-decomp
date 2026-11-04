#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_effect_views.h"


typedef struct S_800A782C_0_pre {
    void (*unk_00)(void *, s32, s32);
    u8 pad_04[0xC];
} S_800A782C_0_pre;   /* the 0x10 bytes before arg0 in initialize_timed_scale_object, addressed as arg0[-1] */

   /* arg1 in initialize_timed_scale_object */

#include "town/system/clear_object_status_and_dispatch_target_api.h"
#include "town/menu/object.h"
#include "engine/node.h"
#include "town/menu.h"

extern void run_record_handler_if_active(void *record, s32 context, s32 update_data);
extern M2C_UNK D_800F842C;

/* Initialize the object and reset its state before completing setup. */
void initialize_timed_scale_object(void *object, ObjectPosition *state, struct SpriteFrameState *context) {
    ((S_800A782C_0_pre *)object)[-1].unk_00 = &run_record_handler_if_active;
    clear_object_status_and_dispatch_target(object, context, (int)(&D_800F842C), 0);
    register_node_if_unregistered(object, project_sprite_chain);
    state->z.w.i = 0;
    initialize_randomized_scale_timer(object, state, context);
}
