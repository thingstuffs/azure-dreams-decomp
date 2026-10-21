#ifndef SLUS_GP_ORDER_BYTES_OWNER_H
#define SLUS_GP_ORDER_BYTES_OWNER_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

typedef struct S_8002E5D8
{
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
}
S_8002E5D8;

typedef struct S_8002E5E8
{
    s32 f0;
    s32 f4;
    s32 f8;
}
S_8002E5E8;

typedef struct S_80049F68_Link
{
    s32 unk0;
    void *self;
    void *parent;
    struct S_80049F68_Link *next;
}
S_80049F68_Link;

typedef struct S_80049F68_Elem
{
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    S_80049F68_Link link;
}
S_80049F68_Elem;

typedef struct S_80049F68_Obj
{
    u8 pad00[0x20];
    S_80049F68_Elem elem[4];
    s32 unkA0;
    s32 unkA4;
    s32 unkA8;
}
S_80049F68_Obj;

extern S_8002E5D8 display_block_defaults;
extern S_8002E5E8 display_vector_defaults;
extern u8 menu_element_order[4];

/* Initialize element defaults and link elements in the configured order. */

void sound_initialize_ordered_elements(S_80049F68_Obj *obj);

#endif
