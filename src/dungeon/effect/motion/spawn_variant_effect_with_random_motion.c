#include "shared/object_node.h"
#include "dungeon/effect.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "dungeon/effect/motion.h"


typedef struct S_800B7D74_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_800B7D74_2;

/* cfail-repair: tf7-phase1-cache-v3 */
struct S_80083178__jr {
    /* 0x00 */ char pad0[0xB0];
    /* 0xB0 */ s16 unkB0;                           /* inferred */
    /* 0xB2 */ char padB2[2];
    /* 0xB4 */ void (*callback)();
    /* 0xB8 */ void *field_B8;
    /* 0xBC */ char padBC[0x1C];                    /* maybe part of field_B8[8]? */
    /* 0xD8 */ void *ptr;
};                                                  /* size = 0xDC */

void select_record_entry_and_value();  /* extern */
s32 register_node();           /* extern */
s32 rsin();                             /* extern */
s32 rcos();                             /* extern */
s32 rand();                                /* extern */
extern M2C_UNK D_8006E24C;
extern M2C_UNK D_8006E258;
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_8006E51C[];
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_8006E57C[];
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_8006E5D4[];


/* Spawns an effect at the given position with variant-specific graphics and randomized motion. */
void spawn_variant_effect_with_random_motion(s32 pos_x, s32 pos_y, s32 pos_z, u32 variant) {
    GameView *game_state = &g_game_work.view;
    s32 velocity_y;
    SpriteFrameState *sprite;
    ObjectPosition *motion;
    S_800B7D74_2 *effect_data;
    ObjectNodeHeader *effect;

    effect = allocate_flagged_object_node(0x212);
    if (effect == NULL) {
        return;
    }
    effect->unk_10 = &advance_effect_fade_and_remove;
    register_node(effect, project_sprite_chain);
    motion = effect->position;
    motion->x.w.i = pos_x;
    effect_data = ((void *)effect) + 0x20;
    motion->y.w.i = pos_y;
    motion->z.w.i = pos_z;
    sprite = effect->sprite;
    switch (variant) {
    case 0:
        *((s16 *)&motion->velocity_x + 1) = (s16) ((rand() & 0x1F) - 0x10);
        *((s16 *)&motion->velocity_y + 1) = (s16) ((rand() & 0x1F) - 0x10);
        *((s16 *)&motion->velocity_z + 1) = (s16) (-8 - (rand() & 0x1F));
        effect_data->unk_08 = &D_8006E5D4;
        select_record_entry_and_value(sprite, &D_8006E5D4, 0);
        break;
    case 1:
        sprite->source = &D_8006E24C;
        *((s16 *)&motion->velocity_z + 1) = (s16) (-0x10 - (rand() & 0xF));
        motion->velocity_x = (s32) (rcos(game_state->camera_rotation.parts.viewAngle - 0x300) << 7);
        motion->velocity_y = (s32) (rsin(game_state->camera_rotation.parts.viewAngle - 0x300) << 7);
        effect_data->unk_12 = 1;
        break;
    case 2:
        sprite->source = &D_8006E258;
        *((s16 *)&motion->velocity_z + 1) = (s16) (-8 - (rand() & 0xF));
        motion->velocity_x = (s32) (rcos(game_state->camera_rotation.parts.viewAngle + 0x500) << 7);
        motion->velocity_y = (s32) (rsin(game_state->camera_rotation.parts.viewAngle + 0x500) << 7);
        effect_data->unk_12 = 1;
        break;
    case 3:
        effect_data->unk_08 = &D_8006E51C;
        select_record_entry_and_value(sprite, &D_8006E51C, 0);
        motion->velocity_x = (s32) (rcos(game_state->camera_rotation.parts.viewAngle) << 7);
        velocity_y = rsin(game_state->camera_rotation.parts.viewAngle) << 7;
        motion->velocity_y = velocity_y;
        *((s16 *)&motion->velocity_z + 1) = (s16) (-0xC - (rand() & 0xF));
        break;
    case 4:
        effect_data->unk_08 = &D_8006E57C;
        select_record_entry_and_value(sprite, &D_8006E57C, 0);
        motion->velocity_x = (s32) ((0 - rcos(game_state->camera_rotation.parts.viewAngle)) << 7);
        velocity_y = (0 - rsin(game_state->camera_rotation.parts.viewAngle)) << 7;
        motion->velocity_y = velocity_y;
        *((s16 *)&motion->velocity_z + 1) = (s16) (-0xC - (rand() & 0xF));
    }
    sprite->color.c.b = 0x80;
    sprite->color.c.g = 0x80;
    sprite->color.c.r = 0x80;
    sprite->scale_y = 0x1000;
    sprite->scale_x = 0x1000;
    effect_data->unk_14 = (s16) ((rand() & 0x1FF) - 0x100);
    effect_data->unk_16 = (s16) ((rand() & 0x1FF) - 0x100);
    effect_data->unk_10 = (s16) ((rand() & 0x1F) + 0x20);
    return;
}
