#include "common.h"

extern void func_8008F134(void *);
extern void func_80033D08(void *arg0);
extern struct { s32 v; s32 pad[2]; } D_800814A0;

/* Update the object and set the high bit in its header and the global flags. */
void func_8009C340(void *object) {
    func_8008F134(object);
    func_80033D08(object);
    *((u16 *)object - 1) |= 0x8000;
    { s32 global_flags = D_800814A0.v; D_800814A0.v = global_flags | 0x8000; }
}
