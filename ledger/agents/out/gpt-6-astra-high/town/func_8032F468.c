#include "common.h"

extern void func_8001ACE8(s32 arg0);
extern void func_8001AD60(s32 arg0);
extern s32 func_8001ADE0(s32 arg0);

// Processes the selected entry if the object's handle passes its status check.
s32 func_80019C68(void *object, s32 entryIndex)
{
    s32 processed;

    if (func_8001ADE0(*(s16 *)((s8 *)object + 0x18)) != 0) {
        goto success;
    }
    processed = 0;
    goto done;

success:
    func_8001ACE8(*(s16 *)(*(s32 *)((s8 *)object + 0x10) + entryIndex * 0x10 + 0xC));
    func_8001AD60(*(s16 *)((s8 *)object + 0x18));
    processed = 1;

done:
    return processed;
}
