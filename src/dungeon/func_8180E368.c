#include "common.h"

typedef struct S_80027368_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80027368_0;   /* object in func_80027368 */

typedef struct S_80027368_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80027368_1;   /* part in func_80027368 */

typedef struct S_80027368_2 {
    u8 pad_00[0x13];
    u8 unk_13;
} S_80027368_2;   /* arg3 in func_80027368 */

typedef struct S_80027368_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
} S_80027368_3;   /* sprite in func_80027368 */

typedef struct S_80027368_4 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x5E];
    s16 unk_66;
} S_80027368_4;   /* work in func_80027368 */



extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);

extern s32 D_80027164;
extern s32 D_80028874;
extern s32 D_80045340;
extern s32 D_80083498;
extern u8 D_800DDC40[];

void *func_80027368(s16 arg0, s16 arg1, s16 arg2, S_80027368_2 *arg3)
{
    void *object;
    S_80027368_1 *part;
    S_80027368_3 *sprite;
    S_80027368_4 *work;

    object = func_8003FD64(0x12, &D_80083498);
    if (object != 0) {
        ((S_80027368_0 *)object)->unk_10 = &D_80027164;
        func_8004491C(object, &D_80045340);
        part = ((S_80027368_0 *)object)->unk_08;
        part->unk_02 = arg0;
        part->unk_06 = arg1;
        part->unk_0A =
            arg2 - (D_800DDC40[arg3->unk_13] >> 1);
        sprite = ((S_80027368_0 *)object)->unk_0C;
        sprite->unk_08 = &D_80028874;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        work = (u8 *)object + 0x20;
        work->unk_04 = arg3;
        work->unk_66 = 0x10;
    }
    return object;
}

/* MECHANISM: Four call-live arguments naturally occupy s1-s4 while the
   allocated object occupies s0; three distinct subrecord locals separate
   the a0 and v1 lifetimes while preserving the retail access widths. */
