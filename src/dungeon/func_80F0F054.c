#include "modules/dungeon_ovl_7f23b800.h"

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *func_8016A854(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    s32 variant;
    void *obj_alt;
    S_8016A854_3 *part_b;
    S_8016A854_2 *part_a;
    void *work_copy;
    void *object;
    S_8016A854_1 *work;

    work = 0;
    variant = 1;
    object = func_8003FD64(274, ((u8 *)(&D_80083498)));
    if (object != 0) {
        work = (u8 *)object + 0x20;
        ((S_8016A854_0 *)object)->unk_10 = func_8016AA8C;
        work->unk_13 = 0x23;
        func_8004491C(object, func_80045340);
        part_a = ((S_8016A854_0 *)object)->unk_08;
        part_a->unk_0A = attr_c;
        part_b = ((S_8016A854_0 *)object)->unk_0C;
        part_b->unk_25 = attr_b;
        work_copy = work;
        part_b->unk_2C = D_8016DD30;
        kind = spawn_flags & 3;
        part_b->unk_24 = attr_a;
        if (kind == 1) {
            work->unk_14 |= 0x6000;
            work->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            work->unk_14 |= 0x2000;
            work->unk_1C |= 0x2000;
        } else if (((spawn_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                if (func_800A6D30() & 1) {
                    work->unk_1C |= 0x200;
                    func_800A48F0(work, 1, (func_800A6D30() & 0x3F) | 0x20);
                    part_b->unk_2C = D_8016DD78;
                }
            }
            variant = func_800A6D30() & 3;
        }
        func_800A9C18(object, part_a, part_b, spawn_flags);
        ((S_8016A854_4 *)work_copy)->unk_9A = 0xFF;
        ((S_8016A854_4 *)work_copy)->unk_9C = -1;
        ((S_8016A854_4 *)work_copy)->unk_8C = func_8016AF74;
        ((S_8016A854_4 *)work_copy)->unk_A4 = -1;
        if (variant != 0) {
            ((S_8016A854_4 *)work_copy)->unk_A6 = 0;
        } else {
            obj_alt = (u8 *)work_copy - 0x20;
            ((S_8016A854_4 *)work_copy)->unk_A6 = 1;
            part_b->unk_10 = 0x60;
            part_b->unk_14 |= 0xC;
            part_b->unk_12 -= 0x80;
            func_80044A50(obj_alt);
            func_800BC318(obj_alt);
        }
        func_800AA36C(work_copy, part_a, part_b, work);
    }

    return work;
}
