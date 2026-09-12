#include "common.h"

typedef struct ChildA {
    u8 pad_00[10];
    s16 field_0A;
} ChildA;

typedef struct ChildB {
    u8 pad_00[36];
    u8 field_24;
    u8 field_25;
    u8 pad_26[6];
    void *field_2C;
} ChildB;

typedef struct Body {
    u8 pad_00[19];
    u8 field_13;
    u32 flags_14;
    u8 pad_18[4];
    u32 flags_1C;
    u8 pad_20[108];
    void *callback_8C;
    u8 pad_90[10];
    u8 field_9A;
    u8 pad_9B;
    s8 field_9C;
} Body;

typedef struct Object {
    u8 pad_00[8];
    ChildA *child_a_08;
    ChildB *child_b_0C;
    void *field_10;
    u8 pad_14[12];
    Body body_20;
} Object;

extern u8 D_80083498[9];
extern u8 D_80045340[9];
extern u8 D_8015EE9C[9];
extern u8 D_80162ED8[9];
extern u8 D_80162F00[9];
extern u8 D_8015EA98[9];

extern Object *func_8003FD64(s32, void *);
extern void func_8004491C(Object *, void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(Body *, s32, s32);
extern void func_800A9C18(Object *, ChildA *, ChildB *, s16);
extern void func_800AA36C(Body *, ChildA *, ChildB *, Body *);

Body *func_8015E894(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 saved_arg0 = arg0;
    s16 saved_arg1 = arg1;
    s32 saved_arg3 = arg3;
    register s32 saved_arg2 ASM_REG("$20") = arg2;   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register Body *body ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    register Object *object ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    ChildA *child_a;
    s32 arg0_copy;
    ChildB *child_b;
    Body *body_alias;
    s32 mode;

    body = 0;
    object = func_8003FD64(0x112, D_80083498);
    if (object != 0) {
        arg0_copy = saved_arg0;
        ASM_KEEP(arg0_copy);   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
        body = &object->body_20;
        body->field_13 = 14;
        func_8004491C(object, D_80045340);

        child_a = object->child_a_08;
        mode = saved_arg0 & 3;
        child_a->field_0A = saved_arg3;
        child_b = object->child_b_0C;
        child_b->field_25 = saved_arg2;
        body_alias = body;
        child_b->field_24 = saved_arg1;

        if (mode == 1) {
            body->callback_8C = D_8015EE9C;
            body->flags_14 |= 0x6000;
            body->flags_1C |= 0x6000;
            child_b->field_2C = D_80162ED8;
            goto after_child_value;
        }
        if (mode >= 2) {
            body->callback_8C = D_8015EE9C;
            body->flags_14 |= 0x2000;
            body->flags_1C |= 0x2000;
            child_b->field_2C = D_80162ED8;
            goto after_child_value;
        }
        if ((s16)(saved_arg0 & ~3) != 0) {
            goto callback_on_body;
        }
        if (body->flags_14 & 0x200) {
            body_alias->callback_8C = D_8015EE9C;
            goto load_child_value;
        }
        if (!(func_800A6D30() & 1)) {
            body_alias->callback_8C = D_8015EE9C;
            goto load_child_value;
        }
        func_800A48F0(body, 1, (func_800A6D30() & 0x3F) | 0x20);
        child_b->field_2C = D_80162F00;
        body_alias->callback_8C = D_8015EE9C;
        goto load_child_value;

callback_on_body:
        body->callback_8C = D_8015EE9C;
load_child_value:
        child_b->field_2C = D_80162ED8;
after_child_value:
        object->field_10 = D_8015EA98;
        func_800A9C18(object, child_a, child_b, (s16)arg0_copy);

        body_alias->field_9A = 0xFF;
        body_alias->field_9C = -1;
        func_800AA36C(body_alias, child_a, child_b, body);
    }
    return body;
}
