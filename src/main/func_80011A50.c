#include "common.h"

typedef struct {
    u8 pad00[0x7C];
    s32 unk7C;
    s32 unk80;
} S_80011A50;

extern u8 D_80083E98;
extern void func_80024390(void);
extern void func_80024818(void);
extern void func_800249B4(void);

void func_80024A50(S_80011A50 *arg0)
{
    u8 *base;
    register s32 unk80 ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    base = &D_80083E98;
    if (*(s32 *)(base + (arg0->unk7C << 7)) != 0) {
        func_80024390();
        return;
    }
    unk80 = arg0->unk80;
    if ((unk80 != 0) && (unk80 != 2)) {
        func_80024818();
        return;
    }
    func_800249B4();
}
