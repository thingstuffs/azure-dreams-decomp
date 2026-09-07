#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_81977B40_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_81977B40_0;   /* object in func_81977B40 */

typedef struct S_81977B40_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    u8 pad_0C[0x14];
    s32 unk_20;
    u8 pad_24[0x22];
    s16 unk_46;
    u8 pad_48[0x3A];
    s16 unk_82;
} S_81977B40_1;   /* base in func_81977B40 */



extern void *func_8003FD64();
extern void func_8004491C();
extern s32 rand();

extern u8 D_80024D84[9];
extern u8 D_800251E8[9];
extern u8 D_80083498[9];

void func_81977B40(void *arg0)
{
    s16 angle;
    s32 random;
    s32 random2;
    s32 parent;
    s32 i;
    void *object;
    u8 *base;
    u8 *new_base;

    base = arg0;
    object = func_8003FD64(0x212, D_80083498);
    i = 0;
    if (object != NULL) {
        do { ((S_81977B40_0 *)object)->unk_10 = D_800251E8; } while (0);
        new_base = (u8 *)object + 0x20;
        ASM_KEEP(new_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        parent = ((S_81977B40_1 *)base)->unk_20;
        base = new_base;
        ((S_81977B40_0 *)object)->unk_20 = parent;
        ((S_81977B40_1 *)base)->unk_04 = 0;
        ((S_81977B40_1 *)base)->unk_06 = 0;
        ((S_81977B40_1 *)base)->unk_08 = 0;
        do {
            ((S_81977B40_1 *)base)->unk_0A = 0;
            random = rand();
            angle = ((i % 6) * 0x2AA) + (random % 33) - 0x10;
            ((S_81977B40_1 *)base)->unk_46 = angle;
            random2 = rand();
            i++;
            ((S_81977B40_1 *)base)->unk_82 = (random2 % 9) - 4;
            base += 2;
        } while (i < 0x1E);
        func_8004491C(object, D_80024D84);
    }
}
