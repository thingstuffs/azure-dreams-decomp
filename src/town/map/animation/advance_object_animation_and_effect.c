#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/object_flags.h"

extern void *allocate_list_node(s32, void *);
extern s32 register_node(void *, void *);
extern u8 D_800BFF7C[9];
extern u8 map_animation_sprite_entries[9];

/* Moves the object through its animation states, spawns an effect, and marks completion. */
void advance_object_animation_and_effect(void *object)
{
    s32 state;
    ObjectNodeHeader *effect;
    SpriteFrameState *effect_sprite;

    state = *((s16 *) (((u8 *) object) + 0x4C));
    *((u16 *) (((u8 *) object) + 0x48)) = (u16) ((*((u16 *) (((u8 *) object) + 0x48))) - 1);
    switch (state) {
    case 0:
        *((u16 *) (((u8 *) object) + 0x48)) = 3;
        *((s16 *) (((u8 *) object) + 0x2A)) = -4;
        *((s16 *) (((u8 *) object) + 0x32)) = 0x14;
        *((u16 *) (((u8 *) object) + 0x4C)) = (u16) ((*((u16 *) (((u8 *) object) + 0x4C))) + 1);

    case 1:
        *((s32 *) (((u8 *) object) + 0x1C)) += *((s32 *) (((u8 *) object) + 0x28));
        *((s32 *) (((u8 *) object) + 0x24)) += *((s32 *) (((u8 *) object) + 0x30));
        if ((*((s16 *) (((u8 *) object) + 0x48))) > 0) {
            return;
        }
        *((u16 *) (((u8 *) object) + 0x4C)) =
            (u16) ((*((u16 *) (((u8 *) object) + 0x4C))) + 1);
        return;

    case 2:
        *((u16 *) (((u8 *) object) + 0xC)) = (u16) ((*((u16 *) (((u8 *) object) + 0xC)))
            + (((*((s16 *) (((u8 *) object) + 0x2A))) * 3) >> 2));
        *((u16 *) (((u8 *) object) + 0x10)) = (u16) ((*((u16 *) (((u8 *) object) + 0x10)))
            + (((*((s16 *) (((u8 *) object) + 0x32))) * 3) >> 2));
        *((s32 *) (((u8 *) object) + 0x24)) += *((s32 *) (((u8 *) object) + 0x30));
        *((s32 *) (((u8 *) object) + 0x1C)) += *((s32 *) (((u8 *) object) + 0x28));
        if ((*((s16 *) (((u8 *) object) + 0x26))) <= 0) {
            return;
        }
        *((s16 *) (((u8 *) object) + 0x26)) = 0;
        effect = allocate_list_node(0x312, ((u8 *)(&scene_object_list_anchor)));
        if (effect != 0) {
            effect->unk_10 = D_800BFF7C;
            register_node(effect, project_sprite_chain);
            effect_sprite = effect->sprite;
            *((s32 *) (((u8 *) (effect->position)) + 0)) = *((s32 *) (((u8 *) object) + 0x1C));
            *((s32 *) (((u8 *) (effect->position)) + 4)) = *((s32 *) (((u8 *) object) + 0x20));
            *((s32 *) (((u8 *) (effect->position)) + 8)) = *((s32 *) (((u8 *) object) + 0x24));
            *((s16 *) (((u8 *) effect_sprite) + 0x1E)) = 0xC00;
            *((s16 *) (((u8 *) effect_sprite) + 0x1C)) = 0xC00;
            *((s16 *) (((u8 *) effect_sprite) + 0x10)) = 0x60;
            *((s32 *) (((u8 *) effect_sprite) + 0xC)) = 0xA0A0A0;
            *((void **) (((u8 *) effect_sprite) + 0)) = map_animation_sprite_entries;
            *((u16 *) (((u8 *) effect_sprite) + 0x14)) |= 0xC;
            effect_sprite->source = *((s32 *) (map_animation_sprite_entries + 4));
            effect_sprite->unk_04 = 0;
            effect_sprite->unk_05 = 0;
        }
        *((u16 *) (((u8 *) object) + 0x48)) = 4;
        *((u16 *) (((u8 *) object) + 0x4C)) =
            (u16) ((*((u16 *) (((u8 *) object) + 0x4C))) + 1);
        return;

    case 3:
        *((u16 *) (((u8 *) object) + 0xC)) = (u16) ((*((u16 *) (((u8 *) object) + 0xC)))
            + (((*((s16 *) (((u8 *) object) + 0x2A))) * 3) >> 2));
        *((u16 *) (((u8 *) object) + 0x10)) = (u16) ((*((u16 *) (((u8 *) object) + 0x10)))
            + (((*((s16 *) (((u8 *) object) + 0x32))) * 3) >> 2));
        if ((*((s16 *) (((u8 *) object) + 0x48))) > 0) {
            return;
        }
        {
            u16 *state_field = (u16 *) (((u8 *) object) + 0x4C);
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
