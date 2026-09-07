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
extern void func_800241B8() __attribute__((noreturn));

extern u8 D_80024024[];
extern u8 D_80024E88[];
extern u8 D_80045340[];

void *func_800240CC(void *arg0, Copy24 *arg1, s16 arg2)
{
    Object *obj;
    S_800240CC_0 *fields;
    Sprite *sprite;
    Copy24 *dst;
    s32 copy_a0;
    s32 copy_a1;
    s32 copy_a2;
    s32 copy_a3;
    s32 random_value;
    register Object *result ASM_REG("$2");   /* MATCH pin: retail keeps a computation the compiler would drop */
    register Object *call_obj ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = D_80024024;
        fields = (u8 *)obj + 0x20;
        do { fields->unk_0C = arg0; } while (0);
        fields->unk_10 = 0;
        fields->unk_12 = arg2;

        sprite = obj->sprite;
        sprite->color[2] = 0x80;
        sprite->color[1] = 0x80;
        sprite->color[0] = 0x80;
        sprite->callback = D_80024E88;
        random_value = rand();
        call_obj = obj;
        do { sprite->rotation = random_value % 0x1000; } while (0);
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;

        func_8004491C(call_obj, D_80045340);
        do { dst = obj->dst; } while (0);
        result = obj;
        ASM_KEEP(result);   /* MATCH pin: retail keeps a computation the compiler would drop */
        copy_a0 = arg1->word[0];
        copy_a1 = arg1->word[1];
        copy_a2 = arg1->word[2];
        copy_a3 = arg1->word[3];
        dst->word[0] = copy_a0;
        dst->word[1] = copy_a1;
        dst->word[2] = copy_a2;
        dst->word[3] = copy_a3;
        copy_a0 = arg1->word[4];
        copy_a1 = arg1->word[5];
        dst->word[4] = copy_a0;
        dst->word[5] = copy_a1;
        func_800241B8(copy_a0, copy_a1, copy_a2, copy_a3);
    }
    return 0;
}
