#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void *func_8003FD64();
extern void func_8004491C();
extern void func_800A48F0();
extern s32 func_800A6D30();
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
    register s8 held_arg1 ASM_REG("$23") = arg1;
    register s16 held_arg3 ASM_REG("$17") = arg3;
    register s8 held_arg2 ASM_REG("$22") = arg2;
    s16 mode_copy;
    s32 kind;
    u16 saved_x;
    u16 saved_y;
    void *object;
    register void *part_a ASM_REG("$21");
    void *part_b;
    void *work;
    void *work_copy;

    work = 0;
    object = func_8003FD64(0x112, D_80083498);
    mode_copy = arg0;
    if (object != 0) {
        work = (u8 *)object + 0x20;
        FIELD(object, void *, 0x10) = D_801711B0;
        FIELD(work, s8, 0x13) = 0x18;
        func_8004491C(object, &D_80045340);

        part_a = FIELD(object, void *, 8);
        kind = arg0 & 3;
        FIELD(part_a, s16, 0xA) = held_arg3;
        part_b = FIELD(object, void *, 0xC);
        work_copy = work;
        FIELD(part_b, void *, 0x2C) = D_800E23E0;
        FIELD(part_b, s8, 0x24) = held_arg1;
        FIELD(part_b, s8, 0x25) = held_arg2;

        if (kind == 1) {
            FIELD(work, u32, 0x14) |= 0x6000;
            FIELD(work, u32, 0x1C) |= 0x6000;
        } else if (kind >= 2) {
            FIELD(work, u32, 0x14) |= 0x2000;
            FIELD(work, u32, 0x1C) |= 0x2000;
        } else if (((arg0 & -4) << 16) == 0) {
            if ((FIELD(work, u32, 0x14) & 0x200) == 0) {
                if (func_800A6D30() & 1) {
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    FIELD(part_b, void *, 0x2C) = D_800E2428;
                }
            }
        }

        func_800A9C18(object, part_a, part_b, mode_copy);
        ASM_USE(held_arg1);
        ASM_USE(held_arg2);
        FIELD(work_copy, u8, 0x9A) = 0xFF;
        FIELD(work_copy, s8, 0x9C) = -1;
        FIELD(work_copy, void *, 0x8C) = D_80171A80;
        FIELD(work, u32, 0x1C) |= 0x40000;
        FIELD(work_copy, s16, 0x92) = -0x20;
        func_800AA36C(work_copy, part_a, part_b, work);

        FIELD(work_copy, s8, 0xB5) = 0;
        saved_x = FIELD(part_b, u16, 0x1C);
        saved_y = FIELD(part_b, u16, 0x1E);
        FIELD(part_b, u16, 0x1C) = 0;
        FIELD(part_b, u16, 0x1E) = 0;
        func_801708B8(work_copy, part_a, part_b);
        FIELD(part_b, u16, 0x1C) = saved_x;
        FIELD(part_b, u16, 0x1E) = saved_y;
    }

    return work;
}

/* MECHANISM: Ordered arg1/arg3/arg2 homes plus an s5 part_a base reproduce the 0x38 frame
   and retail save/hold set; ASM_USE keeps s6/s7 occupied so the mode copy takes fp.
   Both func_800A6D30 sites are zero-argument RNG calls, leaving their delay slots as nops. */
