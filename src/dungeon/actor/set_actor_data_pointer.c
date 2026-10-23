#include "common.h"

#include "dungeon/actor/state.h"
extern u8 actor_default_action_address;

typedef struct S_800D491C_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
} S_800D491C_0;   /* arg0 in set_actor_data_pointer */

/* Sets the object data pointer when the status check is positive. */
void set_actor_data_pointer(S_800D491C_0 *object, s32 context, void *source, void *target) {
    if (resolve_actor_floor_trap_once(object, context, source, target) > 0) {
        object->unk_8C = &actor_default_action_address;
    }
}
