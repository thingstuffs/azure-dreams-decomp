#include "modules/dungeon_ovl_a0d054.h"

void *func_8014C854(s16 spawn_flags, s16 tile_x, s16 tile_y, s16 part_id)
{
    s32 kind;
    void *obj;
    S_8014C854_2 *part_a;
    S_8014C854_3 *part_b;
    S_8014C854_1 *work;
    S_8014C854_4 *actor;
    s32 flags;
    s32 extra_flags;
    s8 saved_x;
    s16 saved_id;
    s8 saved_y;

    work = 0;
    saved_x = tile_x;
    saved_id = part_id;
    saved_y = tile_y;
    obj = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8014C854_0 *)obj)->unk_10 = D_8014CA28;
        work->unk_13 = 0x3;
        func_8004491C(obj, func_80045340);

        part_a = ((S_8014C854_0 *)obj)->unk_08;
        part_a->unk_0A = saved_id;
        part_b = ((S_8014C854_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_y;
        actor = work;
        part_b->unk_2C = D_8014FC7C;
        part_b->unk_24 = saved_x;

        if (kind == 1) {
            flags = work->unk_14 | 0x6000;
            extra_flags = work->unk_1C | 0x6000;
            work->unk_14 = flags;
            work->unk_1C = extra_flags;
        } else if (kind >= 2) {
            flags = work->unk_14 | 0x2000;
            extra_flags = work->unk_1C | 0x2000;
            work->unk_14 = flags;
            work->unk_1C = extra_flags;
        } else if (((spawn_flags & ~3) << 16) == 0) {
            if (!(work->unk_14 & 0x200)) {
                if (func_800A6D30() & 1) {
                    work->unk_1C |= 0x200;
                    func_800A48F0(work, 1,
                                  (func_800A6D30() & 0x3F) | 0x20);
                    part_b->unk_2C = D_8014FCDC;
                }
            }
        }
        func_800A9C18(obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014CE54;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
