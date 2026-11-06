#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "sdk/libc.h"
#include "engine/node.h"
#include "town/minigame/effect.h"
#include "town/minigame/brief_random_particle_body.h"
#include "town/data.h"

#ifndef NULL
#define NULL 0
#endif



typedef struct S_80026978_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
} S_80026978_1;   /* arg0 in create_brief_randomized_particle */

extern u8 D_80026B00[];

/* Spawns a gray sprite effect at a randomized offset from the origin. */
void create_brief_randomized_particle(S_80026978_1 *origin)
{
    s32 spawn_x;
    s32 spawn_y;
    s32 spawn_z;
    s32 random_delta;
    s32 color;
    SpriteFrameState *sprite;
    ObjectPosition *transform;
    BriefRandomParticleBody *effect_state;
    void *effect;

    effect = allocate_flagged_object_node(0x136);
    if (effect != NULL) {
        ((ProjectileObject *)effect)->update_callback = D_80026B00;
        register_node(effect, project_sprite_chain);
        transform = ((ProjectileObject *)effect)->position;
        sprite = ((ProjectileObject *)effect)->sprite;
        effect_state = NODE_BODY(effect);
        spawn_x = (origin->unk_02 + (rand() % 40)) - 0x14;
        transform->x.w.i = spawn_x;
        spawn_y = (origin->unk_06 + (rand() % 40)) - 0x14;
        transform->y.w.i = spawn_y;
        spawn_z = (origin->unk_0A + (rand() % 40)) - 0x14;
        transform->z.w.i = spawn_z;
        transform->velocity_x = origin->unk_0C;
        random_delta = rand();
        color = 0x808080;
        random_delta = ((random_delta & 0x1FF) - 0x100) << 0xA;
        transform->velocity_z = random_delta;
        effect_state->ticks_left = 3;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->source = tako_particle_sprite_data;
        sprite->unk_04 = 0;
        sprite->frame_ticks = 0;
        sprite->color.word = color;
        sprite->flags = sprite->flags | 0xC;
    }
}
