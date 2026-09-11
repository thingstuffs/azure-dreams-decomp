#include "common.h"

typedef struct S_800240CC_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s16 unk_10;
    s16 unk_12;
} S_800240CC_0;   /* fields in func_800240CC */



typedef struct Copy24 {
    s32 word[6];
} Copy24;

typedef struct Sprite {
    u8 pad0[8];
    void *callback;
    u8 color[3];
    u8 padF[11];
    s16 rotation;
    s16 scale_x;
    s16 scale_y;
} Sprite;

typedef struct Object {
    u8 pad0[8];
    Copy24 *dst;
    Sprite *sprite;
    void *callback;
} Object;

extern Object *func_8003FC64(s32);
extern s32 rand(void);
extern void func_8004491C(void *, void *);

extern u8 D_80024024[];
extern u8 D_80024E88[];
extern u8 D_80045340[];

/* Creates a sprite object with random rotation and copies its initial data. */
void *func_800240CC(void *context, Copy24 *copy_src, s16 initial_value)
{
    Object *obj;
    S_800240CC_0 *fields;
    Sprite *sprite;
    Copy24 *dst;
    s32 random_value;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = D_80024024;
        fields = (u8 *)obj + 0x20;
        fields->unk_0C = context;
        fields->unk_10 = 0;
        fields->unk_12 = initial_value;

        sprite = obj->sprite;
        sprite->color[2] = 0x80;
        sprite->color[1] = 0x80;
        sprite->color[0] = 0x80;
        sprite->callback = D_80024E88;
        random_value = rand();
        sprite->rotation = random_value % 0x1000;
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;

        func_8004491C(obj, D_80045340);
        dst = obj->dst;
        *dst = *copy_src;
        return obj;
    }
    return 0;
}
