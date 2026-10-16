#include "modules/dungeon_resource03_slot0.h"

void *func_80170854(s16 kind_flags, s16 byte_24, s16 byte_25, s16 value_0a)
{
    s32 kind;
    void *obj;
    R03_80170854_S_8016A854_2 *part_a;
    R03_80170854_S_8016A854_3 *part_b;
    R03_80170854_S_8016A854_1 *work;
    R03_80170854_S_8016A854_4 *actor;
    s32 primary_bits;
    s32 secondary_flags;
    s8 saved_byte_24;
    s16 saved_value_0a;
    s8 saved_byte_25;

    work = 0;
    saved_byte_24 = byte_24;
    saved_value_0a = value_0a;
    saved_byte_25 = byte_25;
    obj = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((R03_80170854_S_8016A854_0 *)obj)->unk_10 = ((u8 *)func_80170A28);
        work->unk_13 = 0x3;
        func_8004491C(obj, func_80045340);

        part_a = ((R03_80170854_S_8016A854_0 *)obj)->unk_08;
        part_a->unk_0A = saved_value_0a;
        part_b = ((R03_80170854_S_8016A854_0 *)obj)->unk_0C;
        kind = kind_flags & 3;
        part_b->unk_25 = saved_byte_25;
        actor = work;
        part_b->unk_2C = ((u8 *)D_80173C7C);
        part_b->unk_24 = saved_byte_24;

        if (kind == 1) {
            primary_bits = work->unk_14 | 0x6000;
            secondary_flags = work->unk_1C | 0x6000;
            work->unk_14 = primary_bits;
            work->unk_1C = secondary_flags;
        } else if (kind >= 2) {
            primary_bits = work->unk_14 | 0x2000;
            secondary_flags = work->unk_1C | 0x2000;
            work->unk_14 = primary_bits;
            work->unk_1C = secondary_flags;
        } else if (((kind_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                if (func_800A6D30() & 1) {
                    work->unk_1C |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    part_b->unk_2C = ((u8 *)D_80173CDC);
                }
            }
        }
        func_800A9C18(obj, part_a, part_b, kind_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = ((void *)func_80170E54);
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
