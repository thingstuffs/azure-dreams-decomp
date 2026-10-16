#include "modules/dungeon_ovl_ee706c.h"

/* Spawn this overlay's effect object: allocate it, fill its two parts from the attributes and arm its handlers. */
void *dungeonCreateActorChildDisplayC(s16 spawn_flags, s16 attr_a, s16 attr_b, s16 attr_c)
{
    s32 kind;
    void *work;
    s8 held_a;
    s8 held_b;
    void *obj;
    S_8015E86C_2 *part_a;
    S_8015E86C_3 *part_b;
    S_8015E86C_4 *actor;
    s32 left;
    s32 right;
    s16 held_flags;
    void *current;
    S_8015E86C_8 *base;
    void *child_obj;
    S_8015E86C_7 *elem;
    s32 count;
    register s32 i;
    u32 elem_offset;
    s32 child_arg;
    u16 flags;
    u16 child_flags;
    u16 elem_flags;

    work = 0;
    held_b = attr_b;
    held_flags = spawn_flags;
    obj = func_8003FD64(0x112, (held_a = attr_a, ((u8 *)(&D_80083498))));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((S_8015E86C_0 *)obj)->unk_10 = func_8015EB64;
        ((S_8015E86C_1 *)work)->unk_13 = 0x21;
        func_8004491C(obj, func_80045340);
        actor = work;

        part_a = ((S_8015E86C_0 *)obj)->unk_08;
        part_a->unk_0A = attr_c;
        part_b = ((S_8015E86C_0 *)obj)->unk_0C;
        kind = spawn_flags & 3;
        part_b->unk_2C = D_8016218C;
        part_b->unk_24 = held_a;
        part_b->unk_25 = held_b;

        if (kind == 1) {
            left = ((S_8015E86C_1 *)work)->unk_14 | 0x6000;
            right = ((S_8015E86C_1 *)work)->unk_1C | 0x6000;
            ((S_8015E86C_1 *)work)->unk_14 = left;
            ((S_8015E86C_1 *)work)->unk_1C = right;
        } else if (kind >= 2) {
            left = ((S_8015E86C_1 *)work)->unk_14 | 0x2000;
            right = ((S_8015E86C_1 *)work)->unk_1C | 0x2000;
            ((S_8015E86C_1 *)work)->unk_14 = left;
            ((S_8015E86C_1 *)work)->unk_1C = right;
        } else {
            if (((spawn_flags & ~3) << 16) == 0) {
                if (!(((S_8015E86C_1 *)work)->unk_14 & 0x200)) {
                    left = func_800A6D30();
                    if (left & 1) {
                        ((S_8015E86C_1 *)work)->unk_1C |= 0x200;
                        right = func_800A6D30();
                        func_800A48F0(work, 1, (right & 0x3F) | 0x20);
                        part_b->unk_2C = D_801621CC;
                    }
                }
            }
        }

        func_800A9C18(obj, part_a, part_b, held_flags);

        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = func_8015F1A4;
        ((S_8015E86C_1 *)work)->unk_1C |= 0x00040000;
        actor->unk_92 = -16;
        flags = actor->unk_98;
        actor->unk_A8 = 0;
        actor->unk_9E = 1;
        actor->unk_98 = flags | 0x4000;

        current = actor;
        count = 0;
        do {
            child_obj = func_8003FD64(0x112, ((u8 *)(&D_80083498)));
            ((S_8015E86C_5 *)current)->unk_A4 = child_obj;
            if (child_obj != 0) {
                void *child;

                child = (u8 *)child_obj + 0x20;

                ((S_8015E86C_6 *)child)->unk_02 = 1;
                i = 0;
                base = current;
                elem_offset = 8;
                while (i < ((S_8015E86C_6 *)child)->unk_02) {
                    elem = (u8 *)child + elem_offset;
                    child_flags = ((S_8015E86C_6 *)child)->unk_04;
                    ((S_8015E86C_6 *)child)->unk_04 = child_flags | 0x8000;
                    child_arg = part_b->unk_28;
                    elem_flags = elem->unk_14;
                    elem->unk_10 = 96;
                    elem->unk_28 = child_arg;
                    elem->unk_14 = elem_flags | 0xC;

                    elem->unk_12 = part_b->unk_12 - 128;
                    elem->unk_0C = ((u32)(0x00C0C0C0));
                    ((S_8015E86C_9 *)(base->unk_A4))->unk_10 = dungeonProcessEffectBlockEntries;

                    func_80047784(elem, 39, 0);
                    elem_offset += 48;
                    i++;
                    ((S_8015E86C_6 *)child)->unk_06 = 0;
                    textureSetTheActiveEntriesMatchingIDInTypeN2TableSlots(part_b, dungeonDrawSpriteEffectQuads, 0);
                    ((S_8015E86C_6 *)child)->unk_98 = (u8 *)obj + 30;
                }
            }
            current = (u8 *)current + 4;
            count++;
        } while (count < actor->unk_9E);
        func_800AA36C(actor, part_a, part_b, work);
    }
    return work;
}
