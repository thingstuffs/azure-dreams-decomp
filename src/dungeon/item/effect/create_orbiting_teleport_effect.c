#include "shared/entity.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/item/effect.h"
#include "dungeon/system.h"
#include "engine/node.h"
#include "sdk/libc.h"
#include "dungeon/effect/mesh_callbacks_api.h"

#ifndef NULL
#define NULL 0
#endif

extern u8 D_800DF630[];

/* Creates and initializes a display object linked to its owner. */
void *create_orbiting_teleport_effect(void *owner, s16 effect_value, s16 direction, s16 effect_mode)
{
    ObjectNodeHeader *object;
    SpriteFrameState *display;
    ObjectPosition *source;
    ObjectPosition *target;
    OrbitingTeleportEffectBody *record;
    void *callback;
    s16 saved_mode;
    s16 initial_state;
    s32 direction_fixed;
    SpriteFrameState *parent;

    object = allocate_flagged_object_node(0x12);
    saved_mode = effect_mode;
    if (object != NULL) {
        callback = update_orbiting_teleport_effect;
        object->update_callback = callback;
        register_node(object, draw_linked_mesh_chain);

        display = object->sprite;
        display->color.word = 0x808080;
        display->source = D_800DF630;
        display->depth_bias = 0xC;

        source = NODE_HEADER(owner)->position;
        target = object->position;
        target->x.w.i = source->x.unsigned_parts.integer;
        target->y.w.i = source->y.unsigned_parts.integer;
        record = NODE_BODY(object);
        target->z.w.i = source->z.unsigned_parts.integer;

        record->effect_value = effect_value;
        direction_fixed = direction << 0x10;
        record->owner_position = source;
        parent = NODE_HEADER(owner)->sprite;
        record->orbit_angle = (s16)(direction_fixed >> 5);
        record->owner = owner;
        record->owner_sprite = parent;
        display->offset_x = 0x2000;
        record->size_offset = 0x400;
        record->orbit_offset_phase = rand();

        if (effect_mode == 1) {
            record->phase_ticks = 0;
        } else {
            if (effect_mode == 0) {
                play_sound_if_enabled(0x802);
                initial_state = 0x10;
            } else {
                play_sound_if_enabled(0x802);
                initial_state = 0x20;
            }
            record->phase_ticks = initial_state;
        }

        record->exit_mode = saved_mode;
        ((Rec_D_80082E80 *)owner)->unk_14.at00_s32.v |= 0x100000;
    }
    return object;
}

/* MECHANISM: The true rowbase function uses a 0x30 frame with s2/s4/s5/s3
   holding the four arguments, a post-call s6 copy, and s1/s0 object bases.
   The 800C5558/800C555C targets are local mode-store joins, not tail calls. */
