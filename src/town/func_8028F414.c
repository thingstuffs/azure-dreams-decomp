/* Relink of matched town/func_8032F3C0; every changed retail word is a paired relocation. */
#define townSetScriptFlagBit townClearScriptFlagBit
#include "common.h"
#include "shared/record_ptrs.h"
extern u8 D_80020000[];

extern s32 D_8001C370[3];
extern void townClearScriptFlagBit(s32);

/* Play the sound id held at +0x18 of the current table entry. */
void func_80019C14(void)
{
    u8 *page = (u8 *)D_80020000;
    s32 offset;
    s32 index;

    index = *(s32 *)(*(u8 **)((u8 *)(&D_80016000)) + 0x14);
    offset = index * 0x1C;
    townClearScriptFlagBit(*(s16 *)(offset + *(s32 *)(page - 0x3C90) + 0x18));
}
