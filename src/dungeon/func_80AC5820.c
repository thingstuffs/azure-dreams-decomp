#include "common.h"
#include "records/Rec_D_80082E80.h"


typedef struct S_80AC5820_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80AC5820_0;   /* arg1 in func_80AC5820 */

typedef struct S_80AC5820_1_pre {
    u16 unk_00;
} S_80AC5820_1_pre;   /* the 0x2 bytes before arg0 in func_80AC5820, addressed as arg0[-1] */

typedef struct S_80AC5820_1 {
    u8 pad_00[0x94];
    s16 unk_94;
    u16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
} S_80AC5820_1;   /* arg0 in func_80AC5820 */

typedef struct S_80AC5820_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80AC5820_2;   /* other in func_80AC5820 */




extern void func_800478B8();
extern s32 func_80065420(void *, void *, void *, void *);

extern s32 D_800814A0 __attribute__((section(".data")));
extern s16 D_80083228 __attribute__((section(".data")));
extern s8 D_800DCECC[8];

typedef struct StackWork {
    u16 xyz[3];
    u16 pad;
    s64 out18;
    s32 out20;
    s32 out24;
} StackWork;

void func_80AC5820(void *arg0, S_80AC5820_0 *arg1, Rec_D_80082E80 *arg2)
{
    StackWork work;
    s16 count;
    s32 first;
    s32 second;
    s8 *table_entry;
    u32 angle_page;
    S_80AC5820_2 *other;

    work.xyz[0] = arg1->unk_02;
    work.xyz[1] = arg1->unk_06;
    work.xyz[2] = arg1->unk_0A;
    first = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);

    other = ((S_80AC5820_1 *)arg0)->unk_A8;
    work.xyz[0] = other->unk_02;
    work.xyz[1] = other->unk_06;
    work.xyz[2] = other->unk_0A;
    second = func_80065420(work.xyz, &work.out18, &work.out20, &work.out24);
    angle_page = 0x80080000;
    ASM_KEEP(angle_page);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    table_entry = &D_800DCECC[
        ((*(s16 *)(angle_page + 0x3228) +
          ((S_80AC5820_1 *)arg0)->unk_94 + 0x100) >> 9) & 7];
    arg2->unk_06.as_s16 = first - second - *table_entry * 2;

    func_800478B8(arg2, table_entry);
    count = ((S_80AC5820_1 *)arg0)->unk_96 - 1;
    ((S_80AC5820_1 *)arg0)->unk_96 = count;
    if ((count << 16) <= 0) {
        register u32 flags_page ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        flags_page = 0x80080000;
        ASM_KEEP(flags_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        ((S_80AC5820_1_pre *)arg0)[-1].unk_00 |= 0x8000;
        *(s32 *)(flags_page + 0x14A0) |= 0x8000;
    }
}

/* MECHANISM: StackWork fixes the 0x40 frame and the s2/s1/s0 stack-output roles.
   A retained 0x80080000 page base yields the displaced angle/global accesses.
   The table pointer stays in a1; only the tail page live range is pinned to v1. */
