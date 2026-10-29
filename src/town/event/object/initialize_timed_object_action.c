#include "common.h"
#include "town/event/object_setup.h"
#include "town/event/object.h"

extern s32 D_800F8B6C[];

/* Initialize the record, clear its counter, and set its flags. */
void initialize_timed_object_action(void *context, void *source, void *record) {
    initialize_actor_action_with_defaults(context, source, record, &D_800F8B6C[0]);
    *(s16 *)((u8 *)record + 0x10) = 0;
    *(u16 *)((u8 *)record + 0x14) = *(u16 *)((u8 *)record + 0x14) | 0x1C;
}
