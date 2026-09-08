#include "common.h"
#include "records/Rec_func_800247B8_arg1.h"

typedef struct S_80024D34_0 {
    u8 pad_00[0x5A];
    s16 unk_5A;
    s16 unk_5C;
} S_80024D34_0;   /* sub in func_80024D34 */

typedef struct S_80024D34_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80024D34_1;   /* node in func_80024D34 */

typedef struct S_80024D34_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_80024D34_2;   /* control in func_80024D34 */

typedef struct S_80024D34_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80024D34_3;   /* position in func_80024D34 */


typedef struct S_80024D34_5 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80024D34_5;   /* control2 in func_80024D34 */


#define VFIELD(expr, type, offset) (*(volatile type *)((u8 *)(expr) + (offset)))

extern void *func_8003FC64(s32);
extern void func_8004491C();
extern s32 rand(void);
extern void func_8003DB94();

extern u8 D_80024C0C[16];
extern u8 D_80045340[16];
extern u8 D_800DE870[16];

void func_80024D34(void *arg0, Rec_func_800247B8_arg1 *arg1)
{
    u16 flags;
    S_80024D34_2 *control;
    S_80024D34_5 *control2;
    S_80024D34_3 *position;
    void *node;
    S_80024D34_0 *sub;
    s32 random;

    node = func_8003FC64(0x212);
    if (node != 0) {
        sub = (u8 *)node + 0x20;
        sub->unk_5A = 0xE;
        sub->unk_5C = 0xE;
        ((S_80024D34_1 *)node)->unk_10 = D_80024C0C;
        func_8004491C(node, D_80045340);

        control = ((S_80024D34_1 *)node)->unk_0C;
        control->unk_10 = 0x60;
        flags = control->unk_14 | 0xC;
        VFIELD(control, u16, 0x14) = flags;
        ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        control->unk_14 = flags | 2;

        position = ((S_80024D34_1 *)node)->unk_08;
        random = rand();
        position->unk_02 = arg1->unk_02
                                  + ((random & 0x1F) - 0x10);
        random = rand();
        position->unk_06 = arg1->unk_06
                                  + ((random & 0x1F) - 0x10);
        random = rand();
        position->unk_0A = arg1->unk_0A
                                    + ((random & 0x1F) - 0x10);

        control2 = ((S_80024D34_1 *)node)->unk_0C;
        control2->unk_1E = 0xC00;
        control2->unk_1C = 0xC00;
        control2->unk_0E = 0x80;
        control2->unk_0D = 0x80;
        control2->unk_0C = 0x80;
        control2->unk_12 = 0x7DCF;
        control2->unk_14 = control2->unk_14 | 0x100;
        func_8003DB94(control2, D_800DE870, 0);
    }
}

/* MECHANISM: Preserve the seed's exact 0x20 frame, s2/s1/s0 holds, and CFG.
   Unsigned byte fields keep the shared 0x80 store value as +128, matching
   retail's addiu before the three sb operations. */
