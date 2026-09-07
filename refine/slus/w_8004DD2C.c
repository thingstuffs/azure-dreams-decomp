#include "common.h"

extern s32 D_80083D98[32];
extern s32 D_80081554;
extern s32 D_80081558;

extern void func_8004DCA8(void *arg);
extern void func_8003528C(void *arg);

/* Build a command sequence with a header and terminator, then submit it. */
void func_8004DD2C(void *context)
{
    s32 submit_index;
    s32 entry_value;
    s32 header_index;
    s32 buffer_value;
    s32 write_index;

    write_index = D_80081554 & 0xF;
    entry_value = write_index;
    buffer_value = 0x15080707;
    D_80081554 = write_index;
    D_80081558 = entry_value;
    header_index = write_index;
    entry_value = buffer_value;
    D_80083D98[write_index] = entry_value;
    D_80081554 = header_index + 1;
    func_8004DCA8(context);

    buffer_value = D_80081554;
    write_index = buffer_value;
    entry_value = write_index;
    D_80083D98[entry_value] = 0x23;
    buffer_value = write_index + 1;
    D_80081554 = buffer_value;
    submit_index = D_80081558;
    func_8003528C(&D_80083D98[submit_index]);
}
