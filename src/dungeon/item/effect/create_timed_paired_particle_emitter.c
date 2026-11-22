#include "shared/entity.h"
#include "common.h"
#include "dungeon/item.h"
#include "shared/object_node.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/item/effect.h"
#include "dungeon/system.h"
#include "engine/node.h"

#ifndef NULL
#define NULL 0
#endif

   /* arg0 in create_timed_paired_particle_emitter */

   /* (void *)temp in create_timed_paired_particle_emitter */

#include "dungeon/effect/screen.h"
#include "dungeon/effect/screen/menu.h"
#include "dungeon/data.h"

/*
 * Draws the effect initialization ellipse and starts a 64-tick particle emitter at the source
 * position.
 */
void create_timed_paired_particle_emitter(ObjectPosition *source, s32 effect_param, void *state_param)
{
    GpuRectBuffer effect_init;
    ObjectNodeHeader *object;
    s32 init_value;
    ObjectPosition *components;
    DungeonGlobalStatus *status;
    PairedParticleEmitterState *state;
    s32 *color;
    u16 component_x;
    u16 component_y;
    u16 component_z;

    object = allocate_list_node(0x202, &scene_object_list_anchor.next);
    if (object == NULL) {
        return;
    }

    color = &dungeon_ellipse_parameters.center_color;
    *color = effect_param;
    effect_init.words[0] = 0x01000340;
    init_value = 0x00200020;
    effect_init.words[1] = init_value;
    draw_textured_ellipse(&dungeon_ellipse_parameters, &effect_init.rect, 1, 0);

    state = NODE_BODY(object);
    state->count = 0x40;
    object->update_callback = (void *)tick_paired_particle_emitter;
    components = object->position;
    component_x = (u16)source->x.w.i;
    components->x.w.i = component_x;
    state->source_x = component_x;
    component_y = (u16)source->y.w.i;
    components->y.w.i = component_y;
    state->source_y = component_y;
    component_z = (u16)source->z.w.i;
    components->z.w.i = component_z;
    state->source_z = component_z;
    state->data = source;
    state->meta = state_param;
    play_sound_if_enabled(0x702);
    status = &g_dungeon_status;
    (*(u16 *)&status->activity_counts.parts.pending_action_count)++;
}
