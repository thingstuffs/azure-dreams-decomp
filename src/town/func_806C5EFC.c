#include "common.h"

extern s8 D_80016000[];
extern s8 D_80018EBC[];
extern s32 D_800190B4;

extern void func_800182E4(void *, s32 *, s32, s32);
extern s32 func_80018D6C(s32);

/* Selects a table entry from flag 0xFCB or callback 4 and passes it to func_800182E4. */
void func_80016EFC(s32 forwarded_first, s32 unused, s32 forwarded_last)
{
    s32 entry_index;

    if (func_80018D6C(0xFCB) != 0) {
        entry_index = 8;
    } else {
        entry_index = ((*(s32 (**)(s32))((s8 *)*(void **)((s8 *)*(void **)D_80016000 + 0x20) + 0x54))(4) & 3) * 2;
    }
    func_800182E4(D_80018EBC + (entry_index * 8), &D_800190B4, forwarded_first, forwarded_last);
}
