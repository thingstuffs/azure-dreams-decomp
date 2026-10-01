#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"

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

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
Body *func_8015E894(s16 spawn_flags, s32 attr_a, s32 attr_b, s32 attr_c) {
    s16 held_flags;
    register s16 held_a ASM_REG("$21");   /* UNRESOLVED C shape (pin): global.c must rank held_a above child_a (retail $s5 vs $s6); at cdk kind is 2 refs/live 20 vs position 4/77 - position live >= 81 flips it (duplicated actor callback stores in the default arms do that) but cse then folds actor into result and jump2 merges the stores */
    s32 held_c;
    s32 held_b;
    s16 arg0_copy;
    Body *body;
    Object *object;
    ChildA *child_a;
    ChildB *child_b;
    Body *body_alias;

    held_flags = spawn_flags;
    held_a = attr_a;
    held_c = attr_c;
    held_b = attr_b;
    body = 0;
    object = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    arg0_copy = held_flags;
    if (object != 0) {
        body = &object->body_20;
        body->field_13 = 14;
        func_8004491C(object, func_80045340);

        child_a = object->child_a_08;
        attr_b = held_flags & 3;
        child_a->field_0A = held_c;
        child_b = object->child_b_0C;
        child_b->field_24 = held_a;
        child_b->field_25 = held_b;
        body_alias = body;

        if (attr_b == 1) {
            body->callback_8C = D_8015EE9C;
            body->flags_14 |= 0x6000;
            body->flags_1C |= 0x6000;
            child_b->field_2C = D_80162ED8;
        } else if (attr_b >= 2) {
            body->callback_8C = D_8015EE9C;
            body->flags_14 |= 0x2000;
            body->flags_1C |= 0x2000;
            child_b->field_2C = D_80162ED8;
        } else {
            if (((held_flags & ~3) << 16) == 0) {
                if (!(body->flags_14 & 0x200) && (func_800A6D30() & 1)) {
                    func_800A48F0(body, 1, (func_800A6D30() & 0x3F) | 0x20);
                    child_b->field_2C = D_80162F00;
                }
                body_alias->callback_8C = D_8015EE9C;
            } else {
                body->callback_8C = D_8015EE9C;
            }
            child_b->field_2C = D_80162ED8;
        }
        object->field_10 = D_8015EA98;
        func_800A9C18(object, child_a, child_b, (s16)arg0_copy);
        body_alias->field_9A = 0xFF;
        body_alias->field_9C = -1;
        func_800AA36C(body_alias, child_a, child_b, body);
    }
    return body;
}
