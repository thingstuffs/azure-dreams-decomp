#include "common.h"

typedef struct {
    u8 pad0[0x6C];
    u16 timer;
    u16 value;
    u16 pad70;
    u16 output;
} TownObject;

extern void func_800C4174(TownObject *obj, s32 arg1, s32 arg2);

void func_800C9F58(TownObject *obj, s32 arg1, s32 arg2) {
    u16 timer;

    timer = obj->timer - 1;
    obj->timer = timer;
    if ((timer << 16) <= 0) {
        func_800C4174(obj, arg1, arg2);
        obj->output = obj->value;
        return;
    }
    obj->output -= 0x400;
}
