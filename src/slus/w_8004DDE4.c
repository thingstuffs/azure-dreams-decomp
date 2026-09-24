#include "slus/command_slots_81554.h"

/* Build and submit a command buffer using the supplied data. */
void func_8004DDE4(void *data)
{
    D_80081554 &= 0xF;
    D_80081558 = D_80081554;
    D_80083D98[D_80081554++] = 0x15080707;
    func_8004DCA8(data);
    D_80083D98[D_80081554++] = 0x20C11;
    D_80083D98[D_80081554++] = 1;
    func_8003528C((s32)&D_80083D98[D_80081558]);
}
