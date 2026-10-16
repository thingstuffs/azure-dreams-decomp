#include "common.h"
#include "shared/record_ptrs.h"
extern u8 D_80020000[];

extern s32 D_8001C370[3];
extern void townSetScriptFlagBit(s32 value);

/* Play the sound id held at +0x18 of the current table entry. */
void townSetCurrentEntryScriptFlag(void)
{
    u8 *page = (u8 *)D_80020000;
    s32 offset;
    s32 index;

    index = *(s32 *)(*(u8 **)((u8 *)(&D_80016000)) + 0x14);
    offset = index * 0x1C;
    townSetScriptFlagBit(*(s16 *)(offset + *(s32 *)(page - 0x3C90) + 0x18));
}
