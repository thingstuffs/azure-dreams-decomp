#include "common.h"

extern void func_8001ACE8(s32 arg0);
extern void func_8001AD60(s32 arg0);
extern s32 func_8001ADE0(s32 arg0);

s32 func_80019C68(void *arg0, s32 arg1)
{
    s32 result;

    if (func_8001ADE0(*(s16 *)((s8 *)arg0 + 0x18)) != 0) {
        goto success;
    }
    result = 0;
    goto done;

success:
    func_8001ACE8(*(s16 *)(*(s32 *)((s8 *)arg0 + 0x10) + arg1 * 0x10 + 0xC));
    func_8001AD60(*(s16 *)((s8 *)arg0 + 0x18));
    result = 1;

done:
    return result;
}
