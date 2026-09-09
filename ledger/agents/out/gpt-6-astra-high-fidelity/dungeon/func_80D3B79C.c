#include "common.h"

typedef struct S_80170F9C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80170F9C_0;   /* object in func_80170F9C */

typedef struct S_80170F9C_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_80170F9C_1;   /* work in func_80170F9C */

typedef struct S_80170F9C_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80170F9C_2;   /* part_a in func_80170F9C */

typedef struct S_80170F9C_3 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_80170F9C_3;   /* part_b in func_80170F9C */

typedef struct S_80170F9C_4 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x2];
    s16 unk_92;
    u8 pad_94[0x6];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x18];
    s8 unk_B5;
} S_80170F9C_4;   /* work_copy in func_80170F9C */



extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30(void);
extern void func_800A9C18();
extern void func_800AA36C();
extern void func_801708B8();

extern s32 D_80045340;
extern u8 D_80083498[];
extern u8 D_800E23E0[];
extern u8 D_800E2428[];
extern u8 D_801711B0[];
extern u8 D_80171A80[];

void *func_80170F9C(s16 arg0, s8 arg1, s8 arg2, s16 arg3)
{
    register s8 held_arg1 ASM_REG("$23") = arg1;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 held_arg3 = arg3;
    register s8 held_arg2 ASM_REG("$22") = arg2;   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s16 mode_copy;
    s32 kind;
    u16 saved_x;
    u16 saved_y;
    void *object;
    S_80170F9C_2 *part_a;
    S_80170F9C_3 *part_b;
    S_80170F9C_1 *work;
    S_80170F9C_4 *work_copy;

    work = 0;
    object = func_8003FD64(0x112, D_80083498);
    mode_copy = arg0;
    if (object != 0) {
        work = (u8 *)object + 0x20;
        ((S_80170F9C_0 *)object)->unk_10 = D_801711B0;
        work->unk_13 = 0x18;
        func_8004491C(object, &D_80045340);

        part_a = ((S_80170F9C_0 *)object)->unk_08;
        kind = arg0 & 3;
        part_a->unk_0A = held_arg3;
        part_b = ((S_80170F9C_0 *)object)->unk_0C;
        work_copy = work;
        part_b->unk_2C = D_800E23E0;
        part_b->unk_24 = held_arg1;
        part_b->unk_25 = held_arg2;

        if (kind == 1) {
            work->unk_14 |= 0x6000;
            work->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            work->unk_14 |= 0x2000;
            work->unk_1C |= 0x2000;
        } else if (((arg0 & -4) << 16) == 0) {
            if ((work->unk_14 & 0x200) == 0) {
                if (func_800A6D30() & 1) {
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    part_b->unk_2C = D_800E2428;
                }
            }
        }

        func_800A9C18(object, part_a, part_b, mode_copy);
        work_copy->unk_9A = 0xFF;
        work_copy->unk_9C = -1;
        work_copy->unk_8C = D_80171A80;
        work->unk_1C |= 0x40000;
        work_copy->unk_92 = -0x20;
        func_800AA36C(work_copy, part_a, part_b, work);

        work_copy->unk_B5 = 0;
        saved_x = part_b->unk_1C;
        saved_y = part_b->unk_1E;
        part_b->unk_1C = 0;
        part_b->unk_1E = 0;
        func_801708B8(work_copy, part_a, part_b);
        part_b->unk_1C = saved_x;
        part_b->unk_1E = saved_y;
    }

    return work;
}

/* MECHANISM: Ordered arg1/arg3/arg2 homes plus an s5 part_a base reproduce the 0x38 frame
   and retail save/hold set; ASM_USE keeps s6/s7 occupied so the mode copy takes fp.
   Both func_800A6D30 sites are zero-argument RNG calls, leaving their delay slots as nops. */
