/* callback object reset. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CEC24. */
#include "town/person/callback_object_reset_g00688.h"
#include "town/person.h"
#include "town/person/object.h"

/* Prepare the context and forward the arguments to the next handler. */
void create_object_and_brighten(TownObjectRecord *object, void *context, SpriteFrameState *callback_arg) {
    create_burst_particle_spawner(context);
    reset_object_entry_and_brighten(object, context, callback_arg);
}

/* Reset the object's table entry and brighten the packet to a clamped grayscale intensity. */
void reset_object_entry_and_brighten(TownObjectRecord *object, void *draw_arg, SpriteFrameState *packet) {
    u32 intensity;

    initialize_object_entries(object, packet, (s32 *)D_800D6CA8);
    object_index_slots[object->slot].unk_00 = 0;

    intensity = packet->color.c.r;
    intensity += 0x20;
    if (intensity >= 0x100) {
        intensity = 0xFF;
    }

    packet->color.c.b = intensity;
    packet->color.c.g = intensity;
    packet->color.c.r = intensity;
    apply_object_setup_and_update(object, draw_arg, packet);
}
