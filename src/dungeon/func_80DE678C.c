#include "common.h"

extern void func_800478B8(void *arg);
extern void func_80174068(void) __attribute__((noreturn));
extern s32 D_800814A0[3];

typedef struct {
    u8 pad14[0x14];
    u16 flags;
    u8 pad16[6];
    u16 field1c;
    u16 field1e;
} Func80DE678C_Obj;

/* Update object motion unless its flags trigger termination. */
void func_80DE678C(void *state_data, s32 *motion, Func80DE678C_Obj *object) {
    func_800478B8(object);
    if (object->flags & 0x6000) {
        *(u16 *)((u8 *)state_data - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_80174068();
        return;
    }

    object->field1e += 0x200;
    object->field1c = object->field1e;
    motion[3] /= 2;
    motion[4] /= 2;
    motion[5] -= 20000;
    motion[0] += motion[3];
    motion[1] += motion[4];
    motion[2] += motion[5];
}
