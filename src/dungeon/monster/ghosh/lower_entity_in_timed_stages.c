#include "shared/object_node_flags.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

typedef struct {
    u8 pad0[0x12];
    s16 state;
    u8 pad14[6];
    u16 timer;
} Entity;

typedef struct {
    u8 pad0[8];
    s32 y;
} Position;

extern u8 *ghosh_actor_node[];
extern u8 *D_80174CC8[];
extern void play_sound_if_enabled(s32);

/* Lowers the entity in two timed stages, then flags completion and clears the active pointer. */
void lower_entity_in_timed_stages(Entity *entity, Position *pos)
{
    u8 *context_base = ghosh_actor_node[0];
    s32 state = entity->state;
    s32 expected_state;
    u16 initial_state;
    u8 *context;

    initial_state = entity->state;
    context = context_base + 0x20;

    switch (state) {
    case 0:
        if (*(s16 *)(context + 0xAC) == 0x11) {
            entity->state = initial_state + 1;
            entity->timer = 0;
            return;
        }
        return;
    case 1:
        pos->y += 0xFFF80000;
        entity->timer++;
        if ((s16)entity->timer >= 11) {
            entity->timer = 0;
            entity->state++;
            play_sound_if_enabled(0x516);
            return;
        }
        return;
    case 2:
        pos->y += 0xFFFE0000;
        entity->timer++;
        if ((s16)entity->timer >= 20) {
            u8 *active_context = D_80174CC8[0] + 0x20;
            ((ObjectNodeHeader *)((u8 *)active_context - 0x20))->flags |= NODE_REMOVE;
            D_80174CC8[0] = 0;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }

        return;
    }
}
