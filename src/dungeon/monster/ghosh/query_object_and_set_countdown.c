#include "common.h"
#include "dungeon/monster/ghosh.h"

struct EntityFields;
extern void *create_linked_actor_fade_effect(struct EntityFields *source);

/* Store the object query result and set an active flag and countdown when nonzero. */
s32 query_object_and_set_countdown(void) {
    void *result;
    void *source = ghosh_actor_node;
    s32 flag;
    void *status;

    status = (u8 *)source + 0x20;
    result = create_linked_actor_fade_effect(source);
    *(void **)((s8 *)status + 0xA4) = result;
    if (result == 0) {
        return 0;
    }
    flag = 1;
    *(s8 *)((s8 *)status + 0xB0) = flag;
    *(s8 *)((s8 *)status + 0xB1) = 60;
    return flag;
}
