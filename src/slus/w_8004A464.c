#include "common.h"

#include "common.h"

typedef struct InnerA464 {
    u8 pad0[0x8];
    s32 field_8;
    u8 padC[0x18 - 0xC];
    s32 field_18;
} InnerA464;

typedef struct ObjA464 {
    u8 pad0[0x1E];
    u16 flags;
    InnerA464 inner;
} ObjA464;

extern void func_8004B530(s32 arg0);
extern s32 D_800814A0[3];
extern s32 D_800814A0_store;
__asm__(".set D_800814A0_store, 0x800814A0");

/* Sets object and global flags and processes the object's two inner values. */
void func_8004A464(ObjA464 *obj)
{
    InnerA464 *inner;

    if (obj != 0) {
        obj->flags |= 0x8000;
        inner = &obj->inner;
        D_800814A0_store = D_800814A0[0] | 0x8000;
        func_8004B530(inner->field_8);
        func_8004B530(inner->field_18);
    }
}
