#include "dungeon/effect/sprite/fading_entries.h"
#include "shared/entity.h"
#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_800D4BD4_arg1.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/effect/shade.h"
#include "dungeon/effect/shade/emit_particles_until_expired.h"
#include "engine/node.h"
#include "slus.h"


/* Initialize object state and rendering data from the source and position. */
void initialize_effect_object_state(ObjectNodeHeader *object, Rec_func_800D4BD4_arg1 *source, ObjectPosition *position, s32 unused_spawn_context)
{
    SpriteFrameState *render_config;
    SpriteFrameState *render_data;
    ObjectPosition *object_position;
    FadingMotionParticleBody *state;
    s32 source_value;
    u16 flags;

    state = NODE_BODY(object);
    state->source_emitter = source;
    register_node(object, project_sprite_chain);
    render_config = object->sprite;
    render_config->tpage_abr = 0x20;
    render_config->flags = render_config->flags | 0xC;
    object_position = object->position;
    object_position->x.w.i = position->x.unsigned_parts.integer;
    object_position->y.w.i = position->y.unsigned_parts.integer;
    object_position->z.w.i = position->z.unsigned_parts.integer;
    render_data = object->sprite;
    render_data->scale_y = 0x800;
    render_data->scale_x = 0x800;
    state->color.word = source->unk_0C;
    source_value = source->unk_0C;
    flags = render_data->flags;
    render_data->clut = 0x7DCF;
    flags |= 0x100;
    render_data->color.word = source_value;
    render_data->flags = flags;
    select_record_entry_and_value(render_data, &fading_sprite_entries, 0);
}
