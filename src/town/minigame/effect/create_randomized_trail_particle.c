#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_source.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "sdk/libc.h"
#include "town/minigame/effect.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct S_800267DC_3 {
    void * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800267DC_3;


s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */

extern u8 D_800268DC[];
extern u8 D_800F1564[];

/* Creates a sprite effect offset from the source with randomized motion. */
void create_randomized_trail_particle(ObjectPosition *source) {
    S_800267DC_3 *sprite;
    ObjectPosition *motion;
    ProjectileObject *effect;

    effect = allocate_flagged_object_node(0x136);
    if (effect != NULL) {
        effect->update_callback = D_800268DC;
        register_node(effect, project_sprite_chain);
        motion = effect->position;
        sprite = effect->sprite;
        motion->x.v = source->x.v + 0xFFF90000;
        motion->y.v = source->y.v + 0xFFFD0000;
        motion->z.v = source->z.v;
        motion->velocity_x = source->velocity_x >> 1;
        motion->velocity_z = ((rand() & 0x1FF) - 0x100) << 10;
        sprite->unk_1E = 0x800;
        sprite->unk_1C = 0x800;
        sprite->unk_10 = 0x60;
        sprite->unk_00 = D_800F1564;
        sprite->unk_14 |= 0xD;
        sprite->unk_08 = ((SpriteSourceEntry *)D_800F1564)->source;
        sprite->unk_04 = 0;
        sprite->unk_05 = 0;
        sprite->unk_0C = 0x8080F0;
    }
}
