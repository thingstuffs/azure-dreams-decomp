#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"

typedef s32 UnalignedS32 __attribute__((aligned(1)));

typedef struct {
    UnalignedS32 x;
    UnalignedS32 y;
    UnalignedS32 z;
} PackedVec;

typedef struct {
    ObjectNodeHeader header;
    u8 pad20[0x2C];
    PackedVec data;
} Object;

extern PackedVec ghosh_sprite_payload_template[];
extern s32 *ghosh_actor_node[3];
extern Object *D_80174CC8[3];
extern u8 D_8016E300[];

/* Creates and initializes a sprite object offset from the first source position. */
void create_sprite_object_offset(void) {
    s32 *source_pos;
    Object *obj;
    ObjectPosition *position;
    SpriteFrameState *sprite;

    source_pos = (s32 *)ghosh_actor_node[0][2];
    obj = allocate_flagged_object_node(0x212);
    if (obj != 0) {
        obj->header.update_callback = D_8016E300;
        register_node(&obj->header, project_sprite_chain);
        position = obj->header.position;
        position->x.v = source_pos[0] + (s32)0xFFC00000;
        position->y.v = source_pos[1];
        position->z.v = source_pos[2];
        sprite = obj->header.sprite;
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        obj->data = ghosh_sprite_payload_template[0];
        sprite->source = &obj->data;
        D_80174CC8[0] = obj;
    }
}
