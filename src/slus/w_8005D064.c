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

/* Clears the SPU transfer mode, waits for it to clear, and signals completion. */
void func_8005D064(void)
{
    u32 poll_count;
    u32 event_class;
    SpuRegs *spu_regs;

    if (D_800799A8 == 0) {
        func_8005D730();
    }

    spu_regs = D_80079958;
    spu_regs->control &= 0xFFCF;
    poll_count = 0;
    while (spu_regs->control & 0x30) {
        poll_count++;
        if (poll_count >= 0xF01) {
            break;
        }
    }

    event_class = 0xF0000000 + (u32)spu_regs;
    event_class -= (u32)spu_regs;
    if (D_80079990 != 0) {
        D_80079990(event_class);
    } else {
        DeliverEvent(event_class | 9, 0x20);
    }
}
