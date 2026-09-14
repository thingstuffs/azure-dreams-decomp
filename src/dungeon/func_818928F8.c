#include "common.h"

typedef struct S_818928F8_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    s16 unk_10;
    s16 unk_12;
} S_818928F8_0;   /* fields in func_818928F8 */



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

extern u8 D_80024028[];
extern u8 D_80025308[];
extern u8 D_80045340[];

/* Create an object with a randomly rotated sprite and initialize its copied data. */
void *func_818928F8(void *context, Copy24 *src_data, s16 state_value)
{
    Object *obj;
    S_818928F8_0 *state;
    Sprite *sprite;
    Copy24 *dst_data;
    s32 random_rotation;
    Object *sprite_obj;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = D_80024028;
        state = (u8 *)obj + 0x20;
        do { state->unk_0C = context; } while (0);
        state->unk_10 = 0;
        state->unk_12 = state_value;

        sprite = obj->sprite;
        sprite->color[2] = 0x80;
        sprite->color[1] = 0x80;
        sprite->color[0] = 0x80;
        sprite->callback = D_80025308;
        random_rotation = rand();
        sprite_obj = obj;
        do { sprite->rotation = random_rotation % 0x1000; } while (0);
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;

        func_8004491C(sprite_obj, D_80045340);
        dst_data = obj->dst;
        *dst_data = *src_data;
        dst_data->word[5] = (s32)0xFFFF0000;
        return obj;
    }
    return 0;
}
