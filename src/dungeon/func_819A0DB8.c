#include "common.h"

typedef struct S_func_819A0DB8_0 {
    u8 pad_00[0x3A];
    u16 unk_3A;
    u8 pad_3C[0x50];
    u8 unk_8C;
    s8 unk_8D;
    u8 pad_8E[0x4];
    u8 unk_92;
    u8 unk_93;
    u8 pad_94[0x1];
    u8 unk_95;
    u8 pad_96[0x2];
    u8 unk_98;
    s8 unk_99;
    u8 pad_9A[0x4];
    u8 unk_9E;
    u8 unk_9F;
    u8 pad_A0[0x1];
    u8 unk_A1;
} S_func_819A0DB8_0;

typedef struct S_func_819A0DB8_1 {
    u8 pad_00[0x61B0];
    s16 unk_61B0;
} S_func_819A0DB8_1;

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
    S_func_819A0DB8_0 *self = arg0;
    register u8 *page ASM_REG("$4") = (u8 *)0x80020000;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    static void *const keepalive[] = {
        &&L0, &&L1, &&L2, &&L3
    };

    (void)keepalive;
    ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    index = (s16)(self->unk_3A - 3);
    ((S_func_819A0DB8_1 *)page)->unk_61B0 = 1;
    if ((u32)index < 11) {
        void **table = jtbl_80024008;
        goto *table[index];
    }
    goto tail;

L0:
    self->unk_92 -= 0x60;
    self->unk_9E -= 0x60;
    self->unk_93 += 0x20;
    self->unk_9F += 0x20;
    goto tail;
L1:
    self->unk_92 += 0x20;
    self->unk_9E += 0x20;
    self->unk_8C -= 1;
    self->unk_98 += 1;
    goto tail;
L2:
    self->unk_95 = 24;
    self->unk_A1 = 24;
    ASM_SCHED_BARRIER(); /* MATCH: keep each arm's stores before the shared tail. */
    tail_value = -12;
    goto shared;
L3:
    self->unk_95 = 16;
    self->unk_A1 = 16;
    ASM_SCHED_BARRIER(); /* MATCH: keep each arm's stores before the shared tail. */
    tail_value = -8;
shared:
    self->unk_8D = tail_value;
    self->unk_99 = tail_value;
    self->unk_92 += 0x20;
    self->unk_9E += 0x20;

tail:
    {
        u16 state = self->unk_3A - 1;
        self->unk_3A = state;
        if ((s16)state <= 0) {
            *(u16 *)((u8 *)self - 2) |= 0x8000;
            *(s32 *)((u8 *)D_80080000 + 0x14A0) |= 0x8000;
        }
    }
}
