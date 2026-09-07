#include "common.h"

typedef s32 Callback(s32);

extern s32 func_8001E670(s32 id);
extern void func_800196A4(void);

extern void *D_80016000[];
extern s32 D_80018448[];
extern u8 *D_8001E950;

s32 func_8001947C(void)
{
    s32 index;

    if ((func_8001E670(0x1391) == 0) ||
        (func_8001E670(0xA2) != 0)) {
        index = (*(Callback **)((u8 *)*(void **)((u8 *)D_80016000[0] + 0x20) + 0x2D4))(0);
        return D_80018448[index];
    }

    func_800196A4();
    D_8001E950[0]++;
    return 0;
}

/* MECHANISM: The natural callback/table-return CFG preserves the retail
   24-byte frame with only $ra saved.  The callback field is a stored function
   pointer (Callback **), forcing retail's lw/load-delay/jalr sequence. */
