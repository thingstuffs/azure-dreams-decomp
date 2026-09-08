#include "common.h"

extern void func_8008F134(void *);
extern void func_80033D08(void *arg0);
extern struct { s32 v; s32 pad[2]; } D_800814A0;

void func_8009C340(void *arg0) {
    func_8008F134(arg0);
    func_80033D08(arg0);
    *((u16 *)arg0 - 1) |= 0x8000;
    { s32 t = D_800814A0.v; D_800814A0.v = t | 0x8000; }
}
