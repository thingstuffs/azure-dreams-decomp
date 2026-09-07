#include "common.h"

extern s32 D_80083D98[32];
extern s32 D_80081554;
extern s32 D_80081558;

extern void func_8004DCA8(void *arg);
extern void func_8003528C(void *arg);

/* Build and submit a command buffer using the supplied data. */
void func_8004DDE4(void *data)
{
    s32 packet_index;
    s32 word_or_index;
    s32 initial_index;
    s32 header_or_index;
    s32 buffer_index;
    s32 command_offset;
    s32 value_offset;
    s32 packet_offset;
    s32 *command_ptr;
    s32 *value_ptr;

    buffer_index = D_80081554 & 0xF;
    word_or_index = buffer_index;
    header_or_index = 0x15080707;
    D_80081554 = buffer_index;
    D_80081558 = word_or_index;
    initial_index = buffer_index;
    word_or_index = header_or_index;
    D_80083D98[buffer_index] = word_or_index;
    D_80081554 = initial_index + 1;
    func_8004DCA8(data);

    word_or_index = 0x20C11;
    header_or_index = D_80081554;
    packet_index = D_80081558;
    command_offset = header_or_index * 4;
    header_or_index += 1;
    packet_offset = packet_index * 4;
    command_ptr = (s32 *)((u8 *)D_80083D98 + command_offset);
    *command_ptr = word_or_index;
    value_offset = header_or_index * 4;
    value_ptr = (s32 *)((u8 *)D_80083D98 + value_offset);
    word_or_index = 1;
    D_80081554 = header_or_index;
    header_or_index += 1;
    *value_ptr = word_or_index;
    D_80081554 = header_or_index;
    func_8003528C((s32 *)((u8 *)D_80083D98 + packet_offset));
}
