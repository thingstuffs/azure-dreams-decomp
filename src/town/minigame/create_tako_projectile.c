#include "shared/object_node.h"
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
extern u8 D_800F7944[];

/* Creates object 0x136 with the supplied initial state and Y position. */
void create_tako_projectile(Copy20 *init_data, s32 pos_y)
{
    Object136 *obj;
    u8 *data;
    u8 *entity;

    obj = func_8003FC64(0x136);
    if (obj != 0) {
        obj->init = *init_data;
        obj->callback = D_8002614C;
        register_node(obj, project_sprite_chain);

        data = obj->data;
        entity = obj->entity;
        *(s32 *)(data + 0) = 0x05380000;
        *(s32 *)(data + 8) = 0xFFE00000;
        *(s32 *)(data + 4) = pos_y;
        ((SpriteFrameState *)entity)->scale_y = 0x1000;
        ((SpriteFrameState *)entity)->scale_x = 0x1000;
        ((SpriteFrameState *)entity)->source = (s32)D_800F7944;
        ((SpriteFrameState *)entity)->unk_04 = 0;
        ((SpriteFrameState *)entity)->unk_05 = 0;
        ((SpriteFrameState *)entity)->color.word = 0x00808080;
        ((SpriteFrameState *)entity)->flags |= 0x80;
    }
}
