#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

extern s16 D_800261B0[];
extern s32 D_800814A0[];
extern u8 D_80020000[];
extern u8 D_80080000[];
extern void *jtbl_80024008[];
__asm__(".set jtbl_80024008, 0x80024008");

void func_800245B8(void *arg0)
{
    s32 index;
    s32 tail_value;
    void *self = arg0;
    register u8 *page ASM_REG("$4") = (u8 *)0x80020000;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    static void *const keepalive[] = {
        &&L0, &&L1, &&L2, &&L3
    };

    (void)keepalive;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    index = (s16)(FIELD(self, u16 *, 0x3A) - 3);
    FIELD(page, s16 *, 0x61B0) = 1;
    if ((u32)index < 11) {
        void **table = jtbl_80024008;
        goto *table[index];
    }
    goto tail;

L0:
    FIELD(self, u8 *, 0x92) -= 0x60;
    FIELD(self, u8 *, 0x9E) -= 0x60;
    FIELD(self, u8 *, 0x93) += 0x20;
    FIELD(self, u8 *, 0x9F) += 0x20;
    goto tail;
L1:
    FIELD(self, u8 *, 0x92) += 0x20;
    FIELD(self, u8 *, 0x9E) += 0x20;
    FIELD(self, u8 *, 0x8C) -= 1;
    FIELD(self, u8 *, 0x98) += 1;
    goto tail;
L2:
    FIELD(self, u8 *, 0x95) = 24;
    FIELD(self, u8 *, 0xA1) = 24;
    ASM_SCHED_BARRIER(); /* MATCH: keep each arm's stores before the shared tail. */
    tail_value = -12;
    goto shared;
L3:
    FIELD(self, u8 *, 0x95) = 16;
    FIELD(self, u8 *, 0xA1) = 16;
    ASM_SCHED_BARRIER(); /* MATCH: keep each arm's stores before the shared tail. */
    tail_value = -8;
shared:
    FIELD(self, s8 *, 0x8D) = tail_value;
    FIELD(self, s8 *, 0x99) = tail_value;
    FIELD(self, u8 *, 0x92) += 0x20;
    FIELD(self, u8 *, 0x9E) += 0x20;

tail:
    {
        u16 state = FIELD(self, u16 *, 0x3A) - 1;
        FIELD(self, u16 *, 0x3A) = state;
        if ((s16)state <= 0) {
            FIELD(self, u16 *, -2) |= 0x8000;
            FIELD(D_80080000, s32 *, 0x14A0) |= 0x8000;
        }
    }
}
