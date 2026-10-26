#include "common.h"
#include "town/map/animation.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"

extern void *allocate_list_node(s32, void *);
extern s32 register_node(void *, void *);
extern u8 D_800BFF7C[9];
extern u8 map_animation_sprite_entries[9];

/* Moves the object through its animation states, spawns an effect, and marks completion. */
void advance_object_animation_and_effect(TownMapFallingObject *object)
{
    s32 state;
    ObjectNodeHeader *effect;
    SpriteFrameState *effect_sprite;

    state = object->state.s;
    object->timer.u = (u16) ((object->timer.u) - 1);
    switch (state) {
    case 0:
        object->timer.u = 3;
        object->motion.velocity_x.w.i = -4;
        object->motion.velocity_z.w.i = 0x14;
        object->state.u = (u16) ((object->state.u) + 1);

    case 1:
        object->motion.x.v += object->motion.velocity_x.v;
        object->motion.z.v += object->motion.velocity_z.v;
        if ((object->timer.s) > 0) {
            return;
        }
        object->state.u =
            (u16) ((object->state.u) + 1);
        return;

    case 2:
        object->unk_0C.u = (u16) ((object->unk_0C.u)
            + (((object->motion.velocity_x.w.i) * 3) >> 2));
        object->unk_10.u = (u16) ((object->unk_10.u)
            + (((object->motion.velocity_z.w.i) * 3) >> 2));
        object->motion.z.v += object->motion.velocity_z.v;
        object->motion.x.v += object->motion.velocity_x.v;
        if ((object->motion.z.w.i) <= 0) {
            return;
        }
        object->motion.z.w.i = 0;
        effect = allocate_list_node(0x312, &scene_object_list_anchor.next);
        if (effect != 0) {
            effect->update_callback = D_800BFF7C;
            register_node(effect, project_sprite_chain);
            effect_sprite = effect->sprite;
            effect->position->x.v = object->motion.x.v;
            effect->position->y.v = object->motion.y.v;
            effect->position->z.v = object->motion.z.v;
            *((s16 *) (((u8 *) effect_sprite) + 0x1E)) = 0xC00;
            *((s16 *) (((u8 *) effect_sprite) + 0x1C)) = 0xC00;
            *((s16 *) (((u8 *) effect_sprite) + 0x10)) = 0x60;
            *((s32 *) (((u8 *) effect_sprite) + 0xC)) = 0xA0A0A0;
            *((void **) (((u8 *) effect_sprite) + 0)) = map_animation_sprite_entries;
            *((u16 *) (((u8 *) effect_sprite) + 0x14)) |= 0xC;
            effect_sprite->source = *((s32 *) (map_animation_sprite_entries + 4));
            effect_sprite->unk_04 = 0;
            effect_sprite->frame_ticks = 0;
        }
        object->timer.u = 4;
        object->state.u =
            (u16) ((object->state.u) + 1);
        return;

    case 3:
        object->unk_0C.u = (u16) ((object->unk_0C.u)
            + (((object->motion.velocity_x.w.i) * 3) >> 2));
        object->unk_10.u = (u16) ((object->unk_10.u)
            + (((object->motion.velocity_z.w.i) * 3) >> 2));
        if ((object->timer.s) > 0) {
            return;
        }
        {
            u16 *state_field = &object->state.u;
            *state_field = 0xFF;
        }
        return;

    case 0xFF:
        *((u16 *) (((u8 *) object) + (-2))) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;

        return;
    default:
        return;
    }
}
