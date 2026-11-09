#include "shared/entity.h"
#include "engine/node/registration.h"
#include "common.h"
#include "dungeon/monster/beldo/expanding_fade.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/monster/beldo.h"
#include "engine/node.h"
#include "dungeon/data.h"

typedef struct {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
} Block16;

void select_sprite_entry();
extern M2C_UNK D_80170D44;


typedef struct S_80170E18_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80170E18_3;   /* arg3 in create_effect_from_sprite_and_facing */

   /* arg1 in create_effect_from_sprite_and_facing */

/* Creates an effect using the supplied sprite data, transform, and facing. */
void create_effect_from_sprite_and_facing(void *unused, MovingPosition *source_transform, void *sprite_template, S_80170E18_3 *facing_source) {
    SpriteFrameState *sprite;
    ObjectNodeHeader *effect;
    BeldoExpandingFadeBody *effect_state;
    ObjectPosition *transform;
    Block16 *sprite_data;
    Block16 *src;
    Block16 *dst;
    Block16 *end;

    effect = allocate_list_node(0x112, &scene_object_list_anchor.next);
    sprite_data = sprite_template;
    if (effect != NULL) {
        effect_state = NODE_BODY(effect);
        effect_state->ticks_left = 7;
        effect_state->duration = 7;
        effect->update_callback = &D_80170D44;
        effect_state->source_position = source_transform;
        sprite = effect->sprite;
        src = sprite_data;
        dst = (Block16 *)sprite;
        end = src + 3;
        do {
            *dst = *src;
            src++;
            dst++;
        } while (src != end);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x50;
        sprite->color.c.g = 0x50;
        sprite->color.c.r = 0x50;
        sprite->tpage_abr = 0x20;
        sprite->clut = 0xFF80;
        sprite->offset_y = 0xFFF1;
        sprite->flags = (u16) (sprite->flags | 0xC);
        register_node(effect, project_sprite_chain);
        sprite->frameTable = &beldo_frame_set_3;
        select_sprite_entry(sprite, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + facing_source->unk_2A + 0x100) >> 9) & 7)
            + beldo_frame_set_3), 0);
        transform = effect->position;
        transform->x.w.i = (u16) source_transform->x;
        transform->y.w.i = (u16) source_transform->y;
        transform->z.w.i = (u16) source_transform->z;
    }
}
