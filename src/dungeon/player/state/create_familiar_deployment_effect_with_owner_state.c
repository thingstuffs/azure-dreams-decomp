#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/player/state.h"
#include "engine/graphics.h"
#include "engine/node.h"

typedef struct S_80093C70_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void (*unk_10)(void *, void *, void *);
    u8 pad_14[0xC];
    void * unk_20;
} S_80093C70_0;

typedef struct S_80093C70_5 {
    u8 pad_00[0x6];
    s16 unk_06;
    s16 unk_08;
} S_80093C70_5;

#include "engine/node/allocation.h"                  /* extern */
extern void dungeon_familiar_deploy_update_address(void *object_data, void *unused, void *state_data);

/* Creates a sprite effect at the supplied position and links it to its owner. */
void create_familiar_deployment_effect_with_owner_state(void *owner_body, EntityRec *source_pos, SpriteFrameState *owner) {
    ObjectNodeHeader *owner_node = owner_body - 0x20;
    SpriteFrameState *sprite;
    ObjectNodeHeader *effect;
    ObjectPosition *position;
    S_80093C70_5 *effect_state;
    u16 flags;

    effect = allocate_list_node(0x310, &owner_node->next);
    if (effect != NULL) {
        position = effect->position;
        effect->update_callback = &dungeon_familiar_deploy_update_address;
        position->x.w.i = (u16)source_pos->x.w.i;
        position->y.w.i = (u16)source_pos->y.w.i;
        position->z.w.i = (u16)source_pos->z.w.i;
        sprite = effect->sprite;
        sprite->animation_resource = owner->animation_resource;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        flags = sprite->flags;
        sprite->flags = (u16) (flags | 0x200);
        sprite->depth_bias = 4;
        if (reference_tile_object.sprite_flags & 1) {
            sprite->flags = (u16) (sprite->flags | 1);
        }
        set_sprite_animation_frame(sprite, 0xCE, 0, 3);
        register_node(effect, project_sprite_chain);
        effect_state = ((void *)effect) + 0x20;
        ((S_80093C70_0 *)effect)->unk_20 = owner;
        effect_state->unk_06 = 0x10;
        sprite->color.word = 0x2C808080;
        effect_state->unk_08 = 1;
    }
}
/* MECHANISM: The natural three-pointer lifetimes reproduce retail's 0x20 frame and s0/s2/s1 save
   contract. A volatile first flags read fixes load placement. */
