#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/sprite_source.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_projectile_views.h"
#include "sdk/libc.h"
#include "town/minigame/effect.h"

#ifndef NULL
#define NULL 0
#endif


s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */

extern u8 D_800268DC[];
extern u8 D_800F1564[];

/* Creates a sprite effect offset from the source with randomized motion. */
void create_randomized_trail_particle(ObjectPosition *source) {
    SpriteFrameState *sprite;
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
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;
        sprite->tpage_abr = 0x60;
        sprite->unk_00 = D_800F1564;
        sprite->flags |= 0xD;
        sprite->source = ((SpriteSourceEntry *)D_800F1564)->source;
        sprite->unk_04 = 0;
        sprite->frame_ticks = 0;
        sprite->color.word = 0x8080F0;
    }
}
