#include "common.h"

/* Allocates a new entity node via func_8003FC64(0). On success, links the new
 * node's sub-object slot (offset 0x20) to point back at a0, clears bit 0x2000
 * in both the new node's and a0's flags word, sets the new node's self-pointer
 * (offset 0x24) and clears its byte flag (offset 0x2C), and installs
 * func_80051164 as the new node's callback (offset 0x10). Returns the new
 * node, or NULL if allocation failed. */
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

void *func_800511B4(S_800511B4_entity *a0)
{
    S_800511B4_entity *v1 = func_8003FC64(0);
    S_800511B4_sub *sub;

    if (v1 != 0) {
        v1->sub.unk0 = a0;
        v1->flags &= 0xDFFF;
        a0->flags &= 0xDFFF;
        sub = &v1->sub;
        sub->self = v1;
        sub->flag = 0;
        v1->field_0x10 = func_80051164;
    }
    return v1;
}
