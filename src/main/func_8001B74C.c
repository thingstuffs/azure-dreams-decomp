#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 index;
} Struct8001B74C_arg0;

extern u8 D_80408ADD[][4];
extern s32 D_80408B2C[][4];

extern void func_80402508(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 *arg4);
extern void func_80402670(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* Resolve and apply the last table entry when the object's table is enabled. */
void func_8001B74C(Struct8001B74C_arg0 *object) {
    s32 resolved_a;
    s32 resolved_b;
    s32 resolved_c;
    s32 table_index = object->index;
    s32 last_index = D_80408ADD[table_index][0] - 1;

    if (D_80408ADD[table_index][1] != 0) {
        func_80402508(D_80408B2C[table_index][last_index], object->unk0, &resolved_a, &resolved_b, &resolved_c);
        func_80402670(object, resolved_a, resolved_b, last_index, resolved_c);
    }
}
