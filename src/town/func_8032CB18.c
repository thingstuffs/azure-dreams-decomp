#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s32 M2C_UNK;
M2C_UNK func_80019B54();
M2C_UNK func_80019C68();
M2C_UNK func_8001ACE8();
s32 func_8001ADE0();
/* Update the context flag and dispatch the selected entry according to active flags. */
void func_80017318(void *context, M2C_UNK entry_index)
{
    if (func_8001ADE0(0x1459) != 0) {
        func_8001ACE8(*((s16 *) (((s8 *) context) + 0x18)));
        func_80019C68(context, entry_index);
        return;
    }
    if (func_8001ADE0(0x1458) != 0) {
        func_8001ACE8(*((s16 *) (((s8 *) context) + 0x18)));
    }
    func_80019B54(context, entry_index);
}
