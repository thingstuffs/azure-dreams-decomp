#include "common.h"

extern void func_800213C4(s32 value);
extern void func_800214A4(void);
extern void _card_wait(s32 value);
extern s32 D_800287CC[3];

void func_80020924(void *arg0)
{
    s32 *page;

    func_800214A4();
    _card_wait(0);
    _card_wait(1);

    page = (s32 *)0x80030000;
    if (arg0 != 0) {
        page[-0x1E0D] = 16;
    } else {
        page[-0x1E0D] = 0;
    }

    func_800213C4(D_800287CC[0]);
}
