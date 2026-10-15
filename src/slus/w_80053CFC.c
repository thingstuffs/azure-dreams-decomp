#include "slus/command_words.h"

void func_80053CFC(S_80053CFC *source, s32 packed_value)
{
    s32 saved_value;
    s32 low_bits;
    s32 *command;

    saved_value = packed_value;
    *(S_80053CFC *)&D_80081568 = *source;
    low_bits = saved_value & 0x7FFFFF;
    command = (s32 *)&D_80081568;
    *command = ((((u32)*command + 0x7FF) >> 11) << 23) | low_bits;
    Control_CD(6, (void *)command, saved_value);
    func_8003F320();
}
