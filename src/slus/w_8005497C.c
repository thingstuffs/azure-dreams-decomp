#include "common.h"

extern void func_800558FC(s32 a0);
extern void func_80055BD8(s32 a0);

/* Reports the low-byte event code and forwards a secondary code for selected events. */
void func_8005497C(s32 event)
{
    s32 event_code = event & 0xFF;
    s32 secondary_code;

    func_800558FC(event_code);

    switch (event_code) {
    case 0x11:
        secondary_code = 0;
        break;
    case 0x12:
        secondary_code = 1;
        break;
    case 0x14:
        secondary_code = 2;
        break;
    case 0x18:
        secondary_code = 3;
        break;
    default:
        return;
    }

    func_80055BD8(secondary_code);
}
