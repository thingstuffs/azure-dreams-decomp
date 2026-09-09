#include "common.h"

typedef struct {
    u8 pad00[0x7C];
    s32 unk7C;
    s32 unk80;
} S_80011A50;

extern u8 D_80083E98;
extern void func_80024390(S_80011A50 *arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80024818(S_80011A50 *arg0);
extern void func_800249B4(S_80011A50 *arg0);

void func_80024A50(S_80011A50 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u8 *base;
    register s32 unk80 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    base = &D_80083E98;
    if (*(s32 *)(base + (arg0->unk7C << 7)) != 0) {
        func_80024390(arg0, arg1, arg2, arg3);
        return;
    }
    unk80 = arg0->unk80;
    if ((unk80 != 0) && (unk80 != 2)) {
        func_80024818(arg0);
        return;
    }
    func_800249B4(arg0);
}
