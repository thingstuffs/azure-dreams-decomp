/* G00677: timed actor motion. */
/* Original-file evidence (G00677): inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D6268. */
#include "town/person/timed_actor_motion_g00677.h"
#include "town/person.h"

/* Decrement the object's countdown and advance its state when the countdown expires. */
void advance_object_after_timeout_variant_2(TownObjectRecord *object, s32 unused, void *updateContext) {
    u16 remainingTicks;

    remainingTicks = object->timer.as_u16 - 1;
    object->timer.as_u16 = remainingTicks;
    if ((remainingTicks << 0x10) <= 0) {
        initialize_object_entries((Struct800C5724 *)(object), updateContext, D_800D6268);
        object->unk_50.as_pm = &D_800C8FF0;
        object->heading.as_s16 = 0xC00;
        object->timer.as_u16 = (u16) (object->variant.as_u8 * 3);
    }
}

/* Decrement the entity's timer, updating motion until the next state begins. */
void decrement_entity_timer_updating_motion(TownObjectRecord *entity, ObjectPosition *motion, void *context) {
    u16 ticks_left;
    void *transition_context;

    ticks_left = entity->timer.as_u16 - 1;
    entity->timer.as_u16 = ticks_left;
    transition_context = context;
    if ((s16) ticks_left < 0) {
        initialize_object_entries((Struct800C5724 *)(entity), transition_context, D_800D6268);
        entity->timer.as_u16 = 3U;
        entity->unk_50.as_pm = &finish_countdown_and_set_flags;
        entity->heading.as_s16 = 0xC00;
        return;
    }
    entity->heading.as_s16 = 0x800;
    motion->y.v = (s32) (motion->y.v + 0xFFEAAAAB);
}
