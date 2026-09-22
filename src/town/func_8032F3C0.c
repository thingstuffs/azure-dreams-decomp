#include "common.h"
extern u8 D_80020000[];

extern u8 D_80016000[0x10];
extern s32 D_8001C370[3];
extern void func_8001ACE8(s32 value);

/* Play the sound id held at +0x18 of the current table entry. */
void func_80019BC0(void)
{
#ifndef NON_MATCHING
    u8 *page = (u8 *)D_80020000;
    s32 offset;
    s32 index;

    index = *(s32 *)(*(u8 **)D_80016000 + 0x14);
    offset = index * 0x1C;
    func_8001ACE8(*(s16 *)(offset + *(s32 *)(page - 0x3C90) + 0x18));
#else
    s32 index = *(s32 *)(*(u8 **)D_80016000 + 0x14);

    func_8001ACE8(*(s16 *)((u8 *)D_8001C370[0] + index * 0x1C + 0x18));
#endif
}
