#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"

typedef struct {
    ObjectNodeHeader header;
    u8 pad20[0x2C];
    GhoshSpriteTemplate data;
} Object;


extern u8 D_8016E300[];

/* Creates and initializes a sprite object offset from the first source position. */
void create_sprite_object_offset(void) {
    ObjectPosition *source_pos;
    Object *obj;
    ObjectPosition *position;
    SpriteFrameState *sprite;

    source_pos = ghosh_actor_node->position;
    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->header.update_callback = D_8016E300;
        register_node(&obj->header, project_sprite_chain);
        position = obj->header.position;
        position->x.v = source_pos->x.v + (s32)0xFFC00000;
        position->y.v = source_pos->y.v;
        position->z.v = source_pos->z.v;
        sprite = obj->header.sprite;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        obj->data = ghosh_sprite_payload_template;
        sprite->source = &obj->data;
        D_80174CC8 = &obj->header;
    }
}
