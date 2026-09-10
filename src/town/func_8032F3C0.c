#include "common.h"

#ifdef NON_MATCHING
#define ASM_KEEP(value) ((void)0)
#elif __GNUC__ < 3
#define ASM_KEEP(value) __asm__ __volatile__("" : "=r"(value) : "0"(value))
#else
#define LEGACY_KEEP(value) ASM_KEEP(value)
#endif

extern u8 D_80016000[0x10];
extern s32 D_8001C370[3];
extern void func_8001ACE8(s32 arg0);

void func_80019BC0(void)
{
#ifndef NON_MATCHING
    u8 *page = (u8 *)0x80020000;
    s32 offset;
    s32 index;

    ASM_KEEP(page);
    index = *(s32 *)(*(u8 **)D_80016000 + 0x14);
    ASM_KEEP(index);
    offset = index * 0x1C;
    ASM_KEEP(offset);
    func_8001ACE8(*(s16 *)(offset + *(s32 *)(page - 0x3C90) + 0x18));
#else
    s32 index = *(s32 *)(*(u8 **)D_80016000 + 0x14);

    func_8001ACE8(*(s16 *)((u8 *)D_8001C370[0] + index * 0x1C + 0x18));
#endif
}
