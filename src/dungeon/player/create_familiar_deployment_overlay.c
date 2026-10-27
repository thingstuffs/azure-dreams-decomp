#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"
#include "engine/graphics.h"

#include "engine/node/allocation.h"                  /* extern */
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */           /* extern */
extern void dungeon_familiar_deploy_update_address(void *object_data, void *unused, void *state_data);

typedef struct S_80093D8C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void (*unk_10)(void *, void *, void *);
    u8 pad_14[0xC];
    void * unk_20;
    u8 pad_24[0x2];
    s16 unk_26;
} S_80093D8C_0;

/* Create a sprite effect at the supplied position and attach it to its owner. */
void create_familiar_deployment_overlay(void *owner_body, EntityRec *source_pos, SpriteFrameState *owner) {
    ObjectNodeHeader *owner_node = owner_body - 0x20;
    SpriteFrameState *sprite;
    S_80093D8C_0 *effect;
    MovingPosition *position;

    effect = allocate_list_node(0x310, &owner_node->next);
    if (effect != NULL) {
        position = effect->unk_08;
        effect->unk_10 = &dungeon_familiar_deploy_update_address;
        position->x = (u16)source_pos->x.w.i;
        position->y = (u16)source_pos->y.w.i;
        position->z = (u16)source_pos->z.w.i;
        sprite = effect->unk_0C;
        sprite->animation_resource = owner->animation_resource;
        sprite->scale_y = 0x1000;
        sprite->flags = 0xCU;
        sprite->tpage_abr = 0x20;
        sprite->color.word = 0xF8F8F8;
        sprite->scale_x = 0;
        sprite->depth_bias = 4;
        sprite->flags = (u16) (sprite->flags | 0x200);
        set_sprite_animation_frame(sprite, 0xD0, 0, 2);
        register_node(effect, project_sprite_chain);
        effect->unk_20 = owner;
        effect->unk_26 = 0x10;
    }
}
