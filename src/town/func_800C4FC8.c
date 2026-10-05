#include "common.h"

extern s32 func_800352FC(void);
extern void func_8008F134(void *node);
extern struct { s32 v; s32 pad[2]; } D_800814A0;

/* On a zero result, process the object and set its flag and the global flag. */
void func_800C2728(void *object, s32 value, s32 options, s32 mode) {
    if (func_800352FC() == 0) {
        func_8008F134(object);
        *((u16 *)object - 1) |= 0x8000;
        D_800814A0.v |= 0x8000;
    }
}
