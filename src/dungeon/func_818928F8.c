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
extern void func_800241EC() __attribute__((noreturn));

extern u8 D_80024028[];
extern u8 D_80025308[];
extern u8 D_80045340[];

void *func_818928F8(void *arg0, Copy24 *arg1, s16 arg2)
{
    Object *obj;
    S_818928F8_0 *fields;
    Sprite *sprite;
    Copy24 *dst;
    s32 call_a1;
    s32 call_a2;
    s32 call_a3;
    s32 copy_v1;
    s32 random_value;
    Object *result;
    register Object *call_obj ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        obj->callback = D_80024028;
        fields = (u8 *)obj + 0x20;
        do { fields->unk_0C = arg0; } while (0);
        fields->unk_10 = 0;
        fields->unk_12 = arg2;

        sprite = obj->sprite;
        sprite->color[2] = 0x80;
        sprite->color[1] = 0x80;
        sprite->color[0] = 0x80;
        sprite->callback = D_80025308;
        random_value = rand();
        call_obj = obj;
        do { sprite->rotation = random_value % 0x1000; } while (0);
        sprite->scale_y = 0x800;
        sprite->scale_x = 0x800;

        func_8004491C(call_obj, D_80045340);
        do { dst = obj->dst; } while (0);
        result = obj;
        ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        copy_v1 = arg1->word[0];
        call_a1 = arg1->word[1];
        call_a2 = arg1->word[2];
        call_a3 = arg1->word[3];
        dst->word[0] = copy_v1;
        dst->word[1] = call_a1;
        dst->word[2] = call_a2;
        dst->word[3] = call_a3;
        copy_v1 = arg1->word[4];
        call_a1 = arg1->word[5];
        dst->word[4] = copy_v1;
        *(volatile s32 *)&dst->word[5] = call_a1;
        ASM_USE(result);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        copy_v1 = (s32)0xFFFF0000;
        dst->word[5] = copy_v1;
        func_800241EC(dst, call_a1, call_a2, call_a3);
    }
    return 0;
}
