#include "common.h"

extern void func_800558FC(s32 a0);
extern void func_80055BD8(s32 a0);

/* Reports an event type via func_800558FC, then translates it to a
 * secondary code and forwards it to func_80055BD8 for a small subset
 * of event codes. */
void func_8005497C(s32 a0)
{
    s32 v = a0 & 0xFF;
    s32 arg;

    func_800558FC(v);

    switch (v) {
    case 0x11:
        arg = 0;
        break;
    case 0x12:
        arg = 1;
        break;
    case 0x14:
        arg = 2;
        break;
    case 0x18:
        arg = 3;
        break;
    default:
        return;
    }

    func_80055BD8(arg);
}
