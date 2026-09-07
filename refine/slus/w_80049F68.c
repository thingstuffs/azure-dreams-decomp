#include "common.h"

typedef struct S_8002E5D8
{
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
} S_8002E5D8;

typedef struct S_8002E5E8
{
    s32 f0;
    s32 f4;
    s32 f8;
} S_8002E5E8;

typedef struct S_80049F68_Link
{
    s32 unk0;
    void *self;
    void *parent;
    struct S_80049F68_Link *next;
} S_80049F68_Link;

typedef struct S_80049F68_Elem
{
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    S_80049F68_Link link;
} S_80049F68_Elem;

typedef struct S_80049F68_Obj
{
    u8 pad00[0x20];
    S_80049F68_Elem elem[4];
    s32 unkA0;
    s32 unkA4;
    s32 unkA8;
} S_80049F68_Obj;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;
extern u8 D_80080B30;
extern u8 D_80080B2C[16];

/* Initialize element defaults and link elements in the configured order. */
void func_80049F68(S_80049F68_Obj *obj_input)
{
    register S_80049F68_Obj *obj ASM_REG("$4") = obj_input;   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    register s32 init_index ASM_REG("$7");   /* MATCH pin: slus-diff */
    register s32 elem_offset ASM_REG("$6");   /* MATCH pin: slus-diff */
    register u8 *cursor ASM_REG("$5");   /* MATCH pin: slus-diff */
    register S_8002E5D8 *defaults ASM_REG("$8");   /* MATCH pin: slus-diff */
    void *parent;
    s32 default_fc;
    void *elem_ptr;
    S_80049F68_Link *tail;
    S_80049F68_Link *next;
    u8 elem_index;
    s32 end_marker;

    init_index = 0;
    defaults = &D_8002E5D8;
    parent = &obj->unkA0;
    obj->unkA0 = D_8002E5E8.f0;
    ASM_KEEP(defaults);   /* MATCH pin: slus-diff */
    obj->unkA4 = D_8002E5E8.f4;
    obj->unkA8 = D_8002E5E8.f8;
    elem_offset = 0x20;
    cursor = (u8 *)obj;
    do {
        *((s32 *)(cursor + 0x20)) = D_8002E5D8.f0;
        elem_ptr = ((u8 *)obj) + elem_offset;
        *((s32 *)(cursor + 0x24)) = defaults->f4;
        elem_offset += 0x20;
        *((s32 *)(cursor + 0x28)) = defaults->f8;
        default_fc = defaults->fC;
        init_index += 1;
        *((void **)(cursor + 0x34)) = elem_ptr;
        *((void **)(cursor + 0x38)) = parent;
        *((s32 *)(cursor + 0x2C)) = default_fc;
        cursor += 0x20;
    } while (init_index < 4);

    tail = &obj->elem[0].link;
    end_marker = 4;
    if (D_80080B30 != end_marker) {
        s32 expected_marker;
        register u8 *order_ptr ASM_REG("$5");   /* MATCH pin: slus-diff */

        expected_marker = end_marker;
        order_ptr = &D_80080B2C[4];
        do {
            elem_index = *(order_ptr++);
            next = &obj->elem[elem_index].link;
            tail->next = next;
            tail = next;
        } while (*order_ptr != expected_marker);
    }
    tail->next = 0;
}
