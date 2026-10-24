#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/slus_callbacks.h"
typedef signed char s8;
typedef unsigned char u8;
typedef short s16;
typedef unsigned short u16;
typedef int s32;
typedef unsigned int u32;

typedef struct Copy20 {
    s32 word[5];
} Copy20;

typedef struct Object136 {
    u8 pad0[8];
    void *data;
    void *entity;
    void *callback;
    u8 pad14[12];
    Copy20 init;
} Object136;

extern void register_node();
extern u8 D_8002614C[];
extern u8 tako_particle_sprite_data[];

/* Creates object 0x136 with the supplied initial state and Y position. */
void create_tako_projectile(Copy20 *init_data, s32 pos_y)
{
    Object136 *obj;
    ObjectPosition *data;
    SpriteFrameState *entity;

    obj = allocate_flagged_object_node(0x136);
    if (obj != 0) {
        obj->init = *init_data;
        obj->callback = D_8002614C;
        register_node(obj, project_sprite_chain);

        data = obj->data;
        entity = obj->entity;
        data->x.v = 0x05380000;
        data->z.v = 0xFFE00000;
        data->y.v = pos_y;
        entity->scale_y = 0x1000;
        entity->scale_x = 0x1000;
        entity->source = (s32)tako_particle_sprite_data;
        entity->unk_04 = 0;
        entity->frame_ticks = 0;
        entity->color.word = 0x00808080;
        entity->flags |= 0x80;
    }
}
