#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_effect_views.h"


typedef struct S_800A782C_0_pre {
    void (*unk_00)(void *, s32, s32);
    u8 pad_04[0xC];
} S_800A782C_0_pre;   /* the 0x10 bytes before arg0 in initialize_timed_scale_object, addressed as arg0[-1] */

   /* arg1 in initialize_timed_scale_object */


void register_node_if_unregistered(void *block_data, void *registration_id);
void initialize_randomized_scale_timer(); /* Unprototyped: retail call passes more arguments than the callee reads */
#include "town/system/clear_object_status_and_dispatch_target_api.h"
#include "town/menu/object.h"
extern void D_800A78AC(void *record, s32 context, s32 update_data);
extern M2C_UNK D_800F842C;

/* Initialize the object and reset its state before completing setup. */
void initialize_timed_scale_object(void *object, ScaleStateHalfView *state, void *context) {
    ((S_800A782C_0_pre *)object)[-1].unk_00 = &D_800A78AC;
    clear_object_status_and_dispatch_target(object, context, (int)(&D_800F842C), 0);
    register_node_if_unregistered(object, project_sprite_chain);
    state->unk_0A = 0;
    initialize_randomized_scale_timer(object, state, context);
}
