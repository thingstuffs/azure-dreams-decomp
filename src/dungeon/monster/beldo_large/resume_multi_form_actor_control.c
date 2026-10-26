#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

extern u8 encounter_transition_pool_script[];

extern void enqueue_runtime_pool_script(void *);
extern void func_80164BA4(void *);
void update_multi_form_actor_control(ActorRecord *actor, ObjectPosition *context, SpriteFrameState *sprite, ActorRecord *entity);

/* Update shared state and the controller callback, then process and mark linked objects. */
void resume_multi_form_actor_control(void *controller, void *unused_1, void *unused_2, u8 *active_object)
{
    s32 object_index;
    u16 update_count;
    u16 state_flags;
    u8 *object_header;
    u8 *object;
    u8 *flags_page;
    DungeonGlobalStatus *state;

    flags_page = (u8 *)0x80010000;
    state = &g_dungeon_status;

    state_flags = *(u16 *)(flags_page + 0x3714);
    update_count = ((u16)state->activity_counts.parts.pending_action_count);
    *(u16 *)(flags_page + 0x3714) = state_flags | 8;
    state->activity_counts.parts.pending_action_count = update_count + 1;
    if ((state->pending_display_owner) == active_object - 0x20) {
        *(u32 *)&state->pending_display_owner &= 0x7FFFFFFF;
    }

    enqueue_runtime_pool_script(encounter_transition_pool_script);
    object_index = 0;
    active_object[0x6D] = 0;
    ((u8 *)controller)[0x9B] = 0;
    *(void **)((u8 *)controller + 0x8C) = (void *)update_multi_form_actor_control;

    do {
        object = *(u8 **)(((u8 *)dungeon_actor_ring_anchor) + (object_index * 4) + 0xAC);
        if (object != 0) {
            func_80164BA4(object);
            object_header = *(u8 **)(((u8 *)dungeon_actor_ring_anchor) + (object_index * 4) + 0xAC) - 0x20;
            *(u32 *)(object_header + 0x10) |= 0x80000000;
        }
        object_index++;
    } while (object_index < 2);
}
