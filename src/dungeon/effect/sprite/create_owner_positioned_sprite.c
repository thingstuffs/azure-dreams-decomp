#include "common.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"

typedef struct Sprite {
    u8 pad0[2];
    u16 x;
    u8 pad4[2];
    u16 y;
    u8 pad8[2];
    u16 z;
} Sprite;

typedef struct Node {
    u8 pad0[6];
    s16 field6;
    void *field8;
    s32 fieldC;
    u8 pad10[10];
    s16 field1A;
    s16 field1C;
    s16 field1E;
} Node;

typedef struct Object {
    u8 pad0[8];
    Sprite *sprite;
    Node *node;
    void *field10;
} Object;

typedef struct ObjectTail {
    u8 pad0[8];
    Object *owner;
    u8 padC[42];
    s16 angle;
} ObjectTail;

typedef struct Pair {
    s32 first;
    s32 second;
} Pair;

void *allocate_list_node();
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
void draw_textured_ellipse();
extern u8 D_80025AC4[12];
extern u8 screen_effect_sprite_entries[12];
extern u8 D_80028238[12];
extern u8 D_80028250[12];

/* Creates an object at its owner's position and initializes its sprite and angle. */
void create_owner_positioned_sprite(Object *owner, s16 angle) {
    Pair rect;
    ObjectNodeHeader *spawned;
    SpriteFrameState *node;
    ObjectTail *tail;

    spawned = allocate_list_node(0x212, owner);
    if (spawned != 0) {
        spawned->update_callback = D_80025AC4;
        register_node(spawned, project_sprite_chain);
        (*(Sprite * *)&spawned->position)->x = owner->sprite->x;
        (*(Sprite * *)&spawned->position)->y = owner->sprite->y;
        (*(Sprite * *)&spawned->position)->z = owner->sprite->z;
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
        rect.first = 0x01400340;
        rect.second = 0x200020;
        draw_textured_ellipse(D_80028238, &rect, 0, 0);
        draw_textured_ellipse(D_80028250, &rect, 1, 0);
    }
}
