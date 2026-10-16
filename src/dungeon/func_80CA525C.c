#include "modules/dungeon_ovl_cc5000.h"

void *func_8015EA5C(s16 spawn_flags, s16 attr_a, s16 attr_b, s32 attr_c)
{
    s32 kind;
    s32 flags0;
    s32 flags1;
    void *result;
    void *object;
    CL_CC5000_80170A5C_S_80170A5C_2 *part0;
    CL_CC5000_80170A5C_S_80170A5C_3 *part1;
    CL_CC5000_80170A5C_S_80170A5C_4 *result_copy;

    result = 0;
    object = func_8003FD64(0x112, ((s32 *)&D_80083498.next));
    if (object != 0) {
        result = (u8 *)object;
        result += 0x20;
        ((CL_CC5000_80170A5C_S_80170A5C_0 *)object)->unk_10 = func_8015EC24;
        ((CL_CC5000_80170A5C_S_80170A5C_1 *)result)->unk_13 = 20;
        func_8004491C(object, func_80045340);

        {
            void *handler;

            part0 = ((CL_CC5000_80170A5C_S_80170A5C_0 *)object)->unk_08;
            handler = D_801632B4;
            part0->unk_0A = attr_c;
            part1 = ((CL_CC5000_80170A5C_S_80170A5C_0 *)object)->unk_0C;
            kind = spawn_flags & 3;
            part1->unk_25 = attr_b;
            result_copy = result;
            part1->unk_2C = handler;
        }
        part1->unk_24 = attr_a;

        if (kind == 1) {
            flags0 = ((CL_CC5000_80170A5C_S_80170A5C_1 *)result)->unk_14;
            flags1 = ((CL_CC5000_80170A5C_S_80170A5C_1 *)result)->unk_1C;
            flags0 |= 0x6000;
            flags1 |= 0x6000;
            ((CL_CC5000_80170A5C_S_80170A5C_1 *)result)->unk_14 = flags0;
            ((CL_CC5000_80170A5C_S_80170A5C_1 *)result)->unk_1C = flags1;
        } else if (kind >= 2) {
            flags0 = ((CL_CC5000_80170A5C_S_80170A5C_1 *)result)->unk_14;
            flags1 = ((CL_CC5000_80170A5C_S_80170A5C_1 *)result)->unk_1C;
            flags0 |= 0x2000;
            flags1 |= 0x2000;
            ((CL_CC5000_80170A5C_S_80170A5C_1 *)result)->unk_14 = flags0;
            ((CL_CC5000_80170A5C_S_80170A5C_1 *)result)->unk_1C = flags1;
        } else if (((spawn_flags & -4) << 16) == 0 &&
                   (((CL_CC5000_80170A5C_S_80170A5C_1 *)result)->unk_14 & 0x200) == 0 &&
                   (func_800A6D30() & 1) != 0) {
            func_800A48F0(result, 1, (func_800A6D30() & 0x3F) | 0x20);
            part1->unk_2C = D_801632FC;
        }

        func_800A9C18(object, part0, part1, spawn_flags);
        result_copy->unk_9A = 0xFF;
        result_copy->unk_9C = -1;
        result_copy->unk_8C = func_8015F02C;
        func_800AA36C(result_copy, part0, part1, result);
    }
    return result;
}

/* MECHANISM: 2.7.2-cdk-G0 (retail shows the compiler's HIGH/LO_SUM address split: lui / lw / addiu).
   The two byte parameters arrive as s16: their narrowing copies survive cse, combine folds the a1/a2
   temps into them, so sched1 schedules the parameter copies and the entry order is retail's. */
