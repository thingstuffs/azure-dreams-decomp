#include "common.h"

typedef struct S_800511B4_sub {
    void *unk0;                /* 0x00 (== entity offset 0x20): related entity */
    struct S_800511B4_entity *self; /* 0x04 (== entity offset 0x24) */
    u8 pad8[0x0C - 0x08];       /* 0x08 */
    u8 flag;                    /* 0x0C (== entity offset 0x2C) */
} S_800511B4_sub;

typedef struct S_800511B4_entity {
    u8 pad0[0x10];                      /* 0x00 */
    void (*field_0x10)(void *self);     /* 0x10 - callback */
    u8 pad14[0x1E - 0x14];              /* 0x14 */
    u16 flags;                          /* 0x1E */
    S_800511B4_sub sub;                 /* 0x20 */
    u8 pad2D[0x124 - 0x2D];             /* 0x2D */
} S_800511B4_entity;

extern void *func_8003FC64(s32 a0);
extern void func_80051164(void *a0);

/* Allocates and initializes a new entity linked to the related entity, or returns NULL. */
void *func_800511B4(S_800511B4_entity *related_entity)
{
    S_800511B4_entity *new_entity = func_8003FC64(0);
    S_800511B4_sub *sub;

    if (new_entity != 0) {
        new_entity->sub.unk0 = related_entity;
        new_entity->flags &= 0xDFFF;
        related_entity->flags &= 0xDFFF;
        sub = &new_entity->sub;
        sub->self = new_entity;
        sub->flag = 0;
        new_entity->field_0x10 = func_80051164;
    }
    return new_entity;
}
