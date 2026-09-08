#include "common.h"

#define FIELD(expr, type, offset) (*(type)((u8 *)(expr) + (offset)))

extern s16 D_800261B0[];
extern s32 D_800814A0[];
extern u8 D_80020000[];
extern u8 D_80080000[];
extern void *jtbl_80024008[];
__asm__(".set jtbl_80024008, 0x80024008");

extern void func_8002468C(void) __attribute__((noreturn));
extern void func_800246AC(void) __attribute__((noreturn));

void func_800245B8(void *arg0)
{
    s32 index;
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
    func_800246AC();
L1:
    FIELD(self, u8 *, 0x92) += 0x20;
    FIELD(self, u8 *, 0x9E) += 0x20;
    FIELD(self, u8 *, 0x8C) -= 1;
    FIELD(self, u8 *, 0x98) += 1;
    func_800246AC();
L2:
    FIELD(self, u8 *, 0x95) = 24;
    FIELD(self, u8 *, 0xA1) = 24;
    {
        s32 tail_value;
        tail_value = -12;
        ASM_TAILSLOT_PIN_TIED(tail_value);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    }
    func_8002468C();
L3:
    FIELD(self, u8 *, 0x95) = 16;
    FIELD(self, u8 *, 0xA1) = 16;
    FIELD(self, s8 *, 0x8D) = -8;
    FIELD(self, s8 *, 0x99) = -8;
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
