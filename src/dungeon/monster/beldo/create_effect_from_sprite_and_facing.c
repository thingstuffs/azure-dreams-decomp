#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct {
    s32 word0;
    s32 word1;
    s32 word2;
    s32 word3;
} Block16;

void *allocate_list_node();
s32 register_node();
void select_sprite_entry();
extern M2C_UNK D_80170D44;
extern u8 beldo_frame_set_3[8];

typedef struct S_80170E18_0 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    s16 unk_A8;
    u8 pad_AA[0x2];
    void * unk_AC;
} S_80170E18_0;

typedef struct S_80170E18_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80170E18_3;   /* arg3 in create_effect_from_sprite_and_facing */

   /* arg1 in create_effect_from_sprite_and_facing */

/* Creates an effect using the supplied sprite data, transform, and facing. */
void create_effect_from_sprite_and_facing(void *unused, MovingPosition *source_transform, void *sprite_template, S_80170E18_3 *facing_source) {
    SpriteFrameState *sprite;
    ObjectNodeHeader *effect;
    S_80170E18_0 *effect_state;
    MovingPosition *transform;
    void *sprite_data;
    Block16 *src;
    Block16 *dst;
    Block16 *end;

    effect = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
    sprite_data = sprite_template;
    if (effect != NULL) {
        effect_state = ((void *)effect) + 0x20;
        effect_state->unk_96 = 7;
        effect_state->unk_A8 = 7;
        effect->update_callback = &D_80170D44;
        effect_state->unk_AC = source_transform;
        sprite = effect->sprite;
        src = (Block16 *)sprite_data;
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
        transform->x = (u16) source_transform->x;
        transform->y = (u16) source_transform->y;
        transform->z = (u16) source_transform->z;
    }
}
