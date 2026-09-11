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

/* Updates paired fields for the current countdown step and flags completion. */
void func_800245B8(void *object_data)
{
    s32 phase_index;
    s32 pair_offset;
    S_func_819A0DB8_0 *object = object_data;
    register u8 *global_page ASM_REG("$4") = (u8 *)0x80020000;   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    static void *const phase_labels[] = {
        &&L0, &&L1, &&L2, &&L3
    };

    (void)phase_labels;
    ASM_KEEP(global_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    phase_index = (s16)(object->unk_3A - 3);
    ((S_func_819A0DB8_1 *)global_page)->unk_61B0 = 1;
    if ((u32)phase_index < 11) {
        void **phase_table = jtbl_80024008;
        goto *phase_table[phase_index];
    }
    goto tail;

L0:
    object->unk_92 -= 0x60;
    object->unk_9E -= 0x60;
    object->unk_93 += 0x20;
    object->unk_9F += 0x20;
    goto tail;
L1:
    object->unk_92 += 0x20;
    object->unk_9E += 0x20;
    object->unk_8C -= 1;
    object->unk_98 += 1;
    goto tail;
L2:
    object->unk_95 = 24;
    do {
        object->unk_A1 = 24;
    } while (0);
     /* MATCH: keep each arm's stores before the shared tail. */
    pair_offset = -12;
    goto shared;
L3:
    object->unk_95 = 16;
    do {
        object->unk_A1 = 16;
    } while (0);
     /* MATCH: keep each arm's stores before the shared tail. */
    pair_offset = -8;
shared:
    object->unk_8D = pair_offset;
    object->unk_99 = pair_offset;
    object->unk_92 += 0x20;
    object->unk_9E += 0x20;

tail:
    {
        u16 remaining_steps = object->unk_3A - 1;
        object->unk_3A = remaining_steps;
        if ((s16)remaining_steps <= 0) {
            *(u16 *)((u8 *)object - 2) |= 0x8000;
            *(s32 *)((u8 *)D_80080000 + 0x14A0) |= 0x8000;
        }
    }
}
