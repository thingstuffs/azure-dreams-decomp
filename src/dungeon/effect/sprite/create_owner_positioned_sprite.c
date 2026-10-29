#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"

typedef struct Sprite {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Sprite;

typedef struct ObjectTail {
    u8 pad0[8];
    ObjectNodeHeader *owner;
    u8 padC[42];
    s16 angle;
} ObjectTail;

typedef struct Pair {
    s32 first;
    s32 second;
} Pair;

#include "engine/node/allocation.h"
#include "shared/entity.h"
#include "dungeon/effect/sprite.h"
#include "dungeon/effect/screen.h"
extern u8 D_80025AC4[12];
extern u8 screen_effect_sprite_entries[12];
extern u8 D_80028238[12];
extern u8 D_80028250[12];

/* Creates an object at its owner's position and initializes its sprite and angle. */
void create_owner_positioned_sprite(ObjectNodeHeader *owner, s16 angle) {
    GpuRectBuffer rect;
    ObjectNodeHeader *spawned;
    SpriteFrameState *node;
    ObjectTail *tail;

    spawned = allocate_list_node(0x212, &owner->next);
    if (spawned != 0) {
        spawned->update_callback = D_80025AC4;
        register_node(spawned, project_sprite_chain);
        (*(Sprite * *)&spawned->position)->x = (u16)owner->position->x.w.i;
        (*(Sprite * *)&spawned->position)->y = (u16)owner->position->y.w.i;
        (*(Sprite * *)&spawned->position)->z = (u16)owner->position->z.w.i;
        node = spawned->sprite;
        node->source = screen_effect_sprite_entries;
        node->scale_y = 0x2800;
        node->scale_x = 0x2800;
        node->depth_bias = 8;
        node->angle_z = angle + 0x400;
        tail = (ObjectTail *)((u8 *)spawned + 0x20);
        node->color.word = 0x808080;
        tail->owner = owner;
        tail->angle = angle;
        rect.words[0] = 0x01400340;
        rect.words[1] = 0x200020;
        draw_textured_ellipse(D_80028238, &rect.rect, 0, 0);
        draw_textured_ellipse(D_80028250, &rect.rect, 1, 0);
    }
}
