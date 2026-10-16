#include "modules/dungeon_ovl_f8f070.h"

/* Allocate an object, initialize its parts and kind flags, and return its work area. */
void *func_8015E870(s16 spawn_flags, s16 value_24, s16 value_25, s16 value_0a)
{
    s32 kind;
    void *obj;
    S_8015E870_2 *part_a;
    S_8015E870_3 *part_b;
    S_8015E870_1 *work;
    S_8015E870_4 *actor;
    register s32 flags_14;
    register s32 flags_1c;
    s8 saved_value_24;
    s16 saved_value_0a;
    s8 saved_value_25;
    register void *init_obj;
    register void *init_part_a;

    work = 0;
    saved_value_24 = value_24;
    saved_value_0a = value_0a;
    saved_value_25 = value_25;
    obj = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8015E870_0 *)obj)->unk_10 = func_8015EA3C;
        work->unk_13 = 0x25;
        func_8004491C(obj, func_80045340);

        part_a = ((S_8015E870_0 *)obj)->unk_08;
        part_a->unk_0A = saved_value_0a;
        part_b = ((S_8015E870_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_25 = saved_value_25;
        actor = work;
        part_b->unk_2C = D_80162194;
        part_b->unk_24 = saved_value_24;

        if (kind == 1) {
            flags_14 = work->unk_14 | 0x6000;
            flags_1c = work->unk_1C | 0x6000;
            work->unk_14 = flags_14;
            work->unk_1C = flags_1c;
        } else if (kind >= 2) {
            flags_14 = work->unk_14 | 0x2000;
            flags_1c = work->unk_1C | 0x2000;
            work->unk_14 = flags_14;
            work->unk_1C = flags_1c;
        } else {
            init_obj = obj;
            if (((spawn_flags & ~3) << 16) == 0 && !(work->unk_14 & 0x200)) {
                init_part_a = part_a;
                work->unk_1C |= 0x200;
                func_800A48F0(work, 1,
                              (func_800A6D30() & 0x3F) | 0x20);
                part_b->unk_2C = D_801621DC;
            } else {
                goto init_actor;
            }
        }
        init_obj = obj;
init_actor:
        func_800A9C18(init_obj, part_a, part_b, spawn_flags);
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &func_8015EE68;
        part_b->unk_14 |= 0xC;
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
