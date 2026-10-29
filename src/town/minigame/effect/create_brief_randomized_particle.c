#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "sdk/libc.h"
#include "engine/node.h"
#include "town/minigame/effect.h"

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

typedef struct S_80026978_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80026978_2;

typedef struct S_80026978_3 {
    u8 pad_00[0xE];
    s16 unk_0E;
} S_80026978_3;

typedef struct S_80026978_4 {
    u8 pad_00[0x4];
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80026978_4;


extern u8 D_80026B00[];
extern u8 tako_particle_sprite_data[];

/* Spawns a gray sprite effect at a randomized offset from the origin. */
void create_brief_randomized_particle(S_80026978_1 *origin)
{
    s32 spawn_x;
    s32 spawn_y;
    s32 spawn_z;
    s32 random_delta;
    s32 color;
    S_80026978_4 *sprite;
    S_80026978_2 *transform;
    S_80026978_3 *effect_state;
    void *effect;

    effect = allocate_flagged_object_node(0x136);
    if (effect != NULL) {
        ((ProjectileObject *)effect)->update_callback = D_80026B00;
        register_node(effect, project_sprite_chain);
        transform = ((ProjectileObject *)effect)->position;
        sprite = ((ProjectileObject *)effect)->sprite;
        effect_state = (S_80026978_3 *)((u8 *)effect + 0x20);
        spawn_x = (origin->unk_02 + (rand() % 40)) - 0x14;
        transform->unk_02 = spawn_x;
        spawn_y = (origin->unk_06 + (rand() % 40)) - 0x14;
        transform->unk_06 = spawn_y;
        spawn_z = (origin->unk_0A + (rand() % 40)) - 0x14;
        transform->unk_0A = spawn_z;
        transform->unk_0C = origin->unk_0C;
        random_delta = rand();
        color = 0x808080;
        random_delta = ((random_delta & 0x1FF) - 0x100) << 0xA;
        transform->unk_14 = random_delta;
        effect_state->unk_0E = 3;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_08 = tako_particle_sprite_data;
        sprite->unk_04 = 0;
        sprite->unk_05 = 0;
        sprite->unk_0C = color;
        sprite->unk_14 = sprite->unk_14 | 0xC;
    }
}
