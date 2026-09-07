#include "common.h"

typedef struct SpuRegs {
    u16 pad[0xD5];
    volatile u16 control;
} SpuRegs;

extern void DeliverEvent(u32, u32);
extern void func_8005D730(void);
extern SpuRegs *D_80079958;
extern void (* volatile D_80079990)(u32);
extern s32 D_800799A8;

void func_8005D064(void)
{
    u32 count;
    SpuRegs *regs;

    if (D_800799A8 == 0) {
        func_8005D730();
    }

    regs = D_80079958;
    regs->control &= 0xFFCF;
    count = 0;
    if (regs->control & 0x30) {
loop:
        count++;
        if (count < 0xF01) {
            if (regs->control & 0x30) {
                goto loop;
            }
        }
    }

    if (D_80079990 != 0) {
        D_80079990(0xF0000000);
    } else {
        DeliverEvent(0xF0000009, 0x20);
    }
}
