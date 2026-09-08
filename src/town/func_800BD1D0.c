#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800BA930_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_800BA930_0_pre;   /* the 0x10 bytes before arg0 in func_800BA930, addressed as arg0[-1] */

typedef struct S_800BA930_1 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_800BA930_1;   /* particlePrim in func_800BA930 */



typedef struct Position {
    s32 x;
    s32 y;
    s32 z;
} Position;

typedef struct Primitive {
    u8 pad0[8];
    void *image;
    u8 red;
    u8 green;
    u8 blue;
    u8 padF;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 angle;
    s16 scaleX;
    s16 scaleY;
    s16 scaleZ;
} Primitive;

typedef struct Core {
    u8 pad0[0x66];
    u16 angle;
    u8 pad68[0x2F];
    s8 index;
    s32 value;
    struct Core *parent;
} Core;

typedef struct Object {
    u8 pad0[8];
    Position *position;
    Primitive *primitive;
    void *update;
} Object;

extern Object *func_8003FD64();
extern void func_8004491C();
extern s32 rand(void);
extern void func_8008F104(Core *, Position *, void *);

extern u8 D_80045C34[];
extern u8 D_80046398[];
extern u8 D_80083160[];
extern u8 D_800B9CB8[];
extern u8 D_800B9EDC[];
extern u8 D_800B9F74[];
extern u8 D_800BA8C4[];
extern void *D_800D1BCC[];
extern u8 D_800F8A1C[];
extern u8 D_800F8A28[];

/* Initialize an effect with a random angle and spawn its particle and textured children. */
void func_800BA930(Core *effect, Position *origin) {
    s32 random_angle;
    s32 biased_angle;
    s32 child_index;
    s32 child_value;
    s32 particle_y;
    s32 sprite_y;
    s32 overlay_y;
    s32 center_y;
    u8 particle_blue;
    Object *child_obj;
    Core *child_core;
    void *parent_obj;
    Primitive *particle_prim;
    Primitive *texture_prim;
    Position *child_pos;

    ((S_800BA930_0_pre *)effect)[-1].unk_00 = D_800B9CB8;
    random_angle = rand();
    biased_angle = random_angle;
    if (random_angle < 0) {
        biased_angle = random_angle + 0xFFF;
    }

    child_index = 0;
    effect->angle = random_angle - ((biased_angle >> 12) << 12);
    effect->index = 0;
    do {
        child_obj = func_8003FD64(0x136, (u8 *)effect - 0x20);
        if (child_obj != NULL) {
            child_obj->update = D_800BA8C4;
            func_8004491C(child_obj, D_80046398);
            child_value = effect->value;
            child_core = (Core *)((u8 *)child_obj + 0x20);
            child_core->parent = effect;
            child_core->angle = 0;
            child_core->index = child_index;
            child_core->value = child_value;
            particle_prim = child_obj->primitive;
            particle_prim->scaleX = 0x1000;
            particle_prim->scaleY = 0x1000;
            particle_prim->scaleZ = 0xAAA;
            particle_prim->red = D_80083160[0xA8];
            particle_prim->green = D_80083160[0xA9];
            particle_blue = D_80083160[0xAA];
            ((S_800BA930_1 *)particle_prim)->unk_08 = child_index + 0x1A;
            particle_prim->blue = particle_blue;
            child_pos = child_obj->position;
            child_pos->x = origin->x;
            particle_y = origin->y;
            child_pos->z = 0;
            child_pos->y = particle_y;
            func_8008F104(child_core, child_pos, D_800D1BCC[child_index]);
        }
        child_index += 1;
    } while (child_index < 4);

    child_index = 0;
    do {
        child_obj = func_8003FD64(0x36, (u8 *)effect - 0x20);
        if (child_obj != NULL) {
            child_obj->update = D_800B9EDC;
            func_8004491C(child_obj, D_80045C34);
            child_value = effect->value;
            child_core = (Core *)((u8 *)child_obj + 0x20);
            child_core->parent = effect;
            child_core->index = child_index;
            child_core->value = child_value;
            texture_prim = child_obj->primitive;
            texture_prim->image = D_800F8A1C;
            texture_prim->blue = 0x80;
            texture_prim->green = 0x80;
            texture_prim->red = 0x80;
            texture_prim->unk16 = 0x370;
            texture_prim->unk18 = 0;
            texture_prim->angle = effect->angle + (child_index << 10);
            texture_prim->scaleY = 0x1000;
            texture_prim->scaleX = 0x1000;
            child_pos = child_obj->position;
            child_pos->x = origin->x;
            sprite_y = origin->y;
            child_pos->z = 0xFF2C0000;
            sprite_y += 0x200000;
            child_pos->y = sprite_y;
        }
        child_index += 1;
    } while (child_index < 4);

    parent_obj = (u8 *)effect - 0x20;
    child_obj = func_8003FD64(0x36, parent_obj);
    if (child_obj != NULL) {
        child_obj->update = D_800B9EDC;
        func_8004491C(child_obj, D_80045C34);
        child_value = effect->value;
        child_core = (Core *)((u8 *)child_obj + 0x20);
        child_core->parent = effect;
        child_core->value = child_value;
        texture_prim = child_obj->primitive;
        texture_prim->image = D_800F8A28;
        texture_prim->blue = 0x80;
        texture_prim->green = 0x80;
        texture_prim->red = 0x80;
        texture_prim->unk16 = 0x370;
        texture_prim->unk18 = 0;
        texture_prim->angle = effect->angle;
        texture_prim->scaleY = 0x1000;
        texture_prim->scaleX = 0x1000;
        child_pos = child_obj->position;
        child_pos->x = origin->x;
        overlay_y = origin->y;
        child_pos->z = 0xFF2C0000;
        overlay_y += 0x200000;
        child_pos->y = overlay_y;
    }

    child_obj = func_8003FD64(0x136, parent_obj);
    if (child_obj != NULL) {
        child_obj->update = D_800B9F74;
        func_8004491C(child_obj, D_80046398);
        child_value = effect->value;
        child_core = (Core *)((u8 *)child_obj + 0x20);
        child_core->parent = effect;
        child_core->value = child_value;
        particle_prim = child_obj->primitive;
        particle_prim->scaleX = 0x1000;
        particle_prim->scaleY = 0x1000;
        particle_prim->scaleZ = 0x1000;
        particle_prim->angle = effect->angle;
        particle_prim->red = D_80083160[0xA8];
        particle_prim->green = D_80083160[0xA9];
        particle_prim->blue = D_80083160[0xAA];
        child_pos = child_obj->position;
        ((S_800BA930_1 *)particle_prim)->unk_08 = 0x19;
        child_pos->x = origin->x;
        center_y = origin->y;
        child_pos->z = 0;
        child_pos->y = center_y;
    }
}
