#include "common.h"

typedef union S_800504B4_Val {
    s16 s;
    u16 u;
} S_800504B4_Val;

typedef struct S_800504B4_Sub {
    s8 pad0[2];
    S_800504B4_Val val;
} S_800504B4_Sub;

typedef struct S_800504B4_Elem {
    s8 pad0[8];
    S_800504B4_Sub *sub;
} S_800504B4_Elem;

typedef struct S_800504B4 {
    void (*func)(void *);
    s8 pad0[0x64];
    S_800504B4_Elem **arr;
} S_800504B4;

extern void forward_object_input_handler(void *a0);
extern void handle_object_input(void *a0);

/* Decays six counters, switches callbacks when the last reaches zero, and updates the object. */
void decay_gauge_counters(S_800504B4 *object)
{
    s32 elem_index;
    for (elem_index = 1; elem_index < 7; elem_index++) {
        S_800504B4_Elem *elem = object->arr[elem_index];
        S_800504B4_Sub *counter = elem->sub;
        if (counter->val.s > 0) {
            counter->val.u = counter->val.u - 0x100;
        } else {
            counter->val.s = 0;
        }
    }
    if (object->arr[6]->sub->val.s == 0) {
        object->func = forward_object_input_handler;
    }
    handle_object_input(object);
}
