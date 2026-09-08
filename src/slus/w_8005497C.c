#include "common.h"

extern void func_800558FC(s32 a0);
extern void func_80055BD8(s32 a0);

/* Reports the low-byte event code and forwards an index for events 0x11, 0x12, 0x14 and 0x18. */
void func_8005497C(s32 event)
{
    s32 event_code = event & 0xFF;
    s32 event_index;

    func_800558FC(event_code);

    switch (event_code) {
    case 0x11:
        event_index = 0;
        break;
    case 0x12:
        event_index = 1;
        break;
    case 0x14:
        event_index = 2;
        break;
    case 0x18:
        event_index = 3;
        break;
    default:
        return;
    }

    func_80055BD8(event_index);
}
