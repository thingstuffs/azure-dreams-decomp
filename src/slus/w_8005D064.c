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
    register u32 event ASM_REG("$4");   /* MATCH pin: slus-diff */
    SpuRegs *regs;

    if (D_800799A8 == 0) {
        func_8005D730();
    }

    regs = D_80079958;
    regs->control &= 0xFFCF;
    count = 0;
    while (regs->control & 0x30) {
        count++;
        if (count >= 0xF01) {
            break;
        }
    }

    event = 0xF0000000;
    if (D_80079990 != 0) {
        D_80079990(event);
    } else {
        DeliverEvent(event | 9, 0x20);
    }
}
