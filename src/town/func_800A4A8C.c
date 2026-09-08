#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800A21EC_0 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
} S_800A21EC_0;   /* arg2 in func_800A21EC */

typedef struct S_800A21EC_1 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    s32 unk_04;
    s32 unk_08;
} S_800A21EC_1;   /* arg1 in func_800A21EC */

typedef struct S_800A21EC_2 {
    M2C_UNK * unk_00;
    u8 pad_04[0x10];
    void * unk_14;
    u8 pad_18[0x8];
    s16 unk_20;
} S_800A21EC_2;   /* arg0 in func_800A21EC */

typedef struct S_800A21EC_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800A21EC_3;   /* ((S_800A21EC_2 *)arg0)->unk_14 in func_800A21EC */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004491C();
extern void func_800A22AC(void);
extern M2C_UNK D_80046398;
extern M2C_UNK D_800A22D0;

s32 func_800A21EC(void *arg0, S_800A21EC_1 *arg1, S_800A21EC_0 *arg2) {
    arg2->unk_00 = 0;
    arg2->unk_04 = 0;
    arg2->unk_05 = 0;
    func_8004491C(arg0 - 0x20, &D_80046398);
    arg1->unk_00.at00.v = (s32) ((S_800A21EC_3 *)(((S_800A21EC_2 *)arg0)->unk_14))->unk_00;
    arg1->unk_04 = (s32) ((S_800A21EC_3 *)(((S_800A21EC_2 *)arg0)->unk_14))->unk_04;
    arg1->unk_08 = (s32) ((S_800A21EC_3 *)(((S_800A21EC_2 *)arg0)->unk_14))->unk_08;
    ((S_800A21EC_2 *)arg0)->unk_00 = &D_800A22D0;
    if (((S_800A21EC_2 *)arg0)->unk_20 == 0) {
        register s32 dead ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
        dead = 1;
        arg2->unk_08 = dead;
        dead = (u16) arg1->unk_00.at02.v;
        ASM_KEEP(dead);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        func_800A22AC();
        return dead + 0x90;
    }
    {
        s32 flags = (u16) arg2->unk_14;
        s32 one = 1;
        arg2->unk_08 = one;
        ASM_KEEP(one);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        arg2->unk_14 = (u16) (flags | 1);
        arg1->unk_00.at02.v = (u16) (arg1->unk_00.at02.v - 0x90);
        arg2->unk_1A = 0;
    }
}
