#include "modules/dungeon_resource06_slot0.h"

void *func_8017087C(s16 kind_flags, s16 tile_x, s16 tile_y, s16 part_id)
{
    s32 kind;
    void *obj;
    R06_8017087C_S_8017087C_2 *part_a;
    R06_8017087C_S_8017087C_5 *slot_base;
    R06_8017087C_S_8017087C_8 *child_slot;
    s32 entry_id_fixed;
    void *part_b;
    void *work;
    s8 saved_x;
    s16 saved_part_id;
    s8 saved_y;
    s32 setup_value;
    register s32 work_flags;
    void *alloc_or_entry;
    s32 entry_id;
    s32 entry_mode;
    s32 child_index;
    u8 *slot;
    s32 entry_index;

    work = 0;
    alloc_or_entry = (void *)274;
    saved_x = tile_x;
    saved_part_id = part_id;
    saved_y = tile_y;
    obj = func_8003FD64((s32)alloc_or_entry, ((u8 *)(&D_80083498)));
    if (obj != 0) {
        work = (u8 *)obj + 0x20;
        ((R06_8017087C_S_8017087C_0 *)obj)->unk_10 = dungeonCreateAnchoredDirectionalObject;
        ((R06_8017087C_S_8017087C_1 *)work)->unk_13 = 6;
        func_8004491C(obj, func_80045340);

        part_a = ((R06_8017087C_S_8017087C_0 *)obj)->unk_08;
        part_a->unk_0A = saved_part_id;
        part_b = ((R06_8017087C_S_8017087C_0 *)obj)->unk_0C;
        slot_base = work;
        kind = kind_flags & 3;
        ((R06_8017087C_S_8017087C_3 *)part_b)->unk_2C = ((u8 *)D_8017586C);
        ((R06_8017087C_S_8017087C_3 *)part_b)->unk_24 = saved_x;
        ((R06_8017087C_S_8017087C_3 *)part_b)->unk_25 = saved_y;

        if (kind == 1) {
            setup_value = ((R06_8017087C_S_8017087C_1 *)work)->unk_14 | 0x6000;
            work_flags = ((R06_8017087C_S_8017087C_1 *)work)->unk_1C | 0x6000;
            ((R06_8017087C_S_8017087C_1 *)work)->unk_14 = setup_value;
            ((R06_8017087C_S_8017087C_1 *)work)->unk_1C = work_flags;
        } else if (kind >= 2) {
            setup_value = ((R06_8017087C_S_8017087C_1 *)work)->unk_14 | 0x2000;
            work_flags = ((R06_8017087C_S_8017087C_1 *)work)->unk_1C | 0x2000;
            ((R06_8017087C_S_8017087C_1 *)work)->unk_14 = setup_value;
            ((R06_8017087C_S_8017087C_1 *)work)->unk_1C = work_flags;
        } else {
            if (((kind_flags & ~3) << 16) == 0) {
                if (!(((R06_8017087C_S_8017087C_1 *)work)->unk_14 & 0x200)) {
                    setup_value = func_800A6D30();
                    if (setup_value & 1) {
                        ((R06_8017087C_S_8017087C_1 *)work)->unk_1C |= 0x200;
                        func_800A48F0(work, 1,
                                      (func_800A6D30() & 0x3F) | 0x20);
                        ((R06_8017087C_S_8017087C_3 *)part_b)->unk_2C = ((u8 *)D_80175894);
                    }
                }
            }
        }

        func_800A9C18(obj, part_a, part_b,(s16)(kind_flags));

        child_index = 0;
        entry_id_fixed = 0x00190000;
        slot = (u8 *)slot_base;
        ((R06_8017087C_S_8017087C_4 *)slot)->unk_9A = 0xFF;
        slot_base->unk_9C = -1;
        slot_base->unk_8C = func_8017140C;
        ((R06_8017087C_S_8017087C_1 *)work)->unk_1C |= 0x40000;
        slot_base->unk_92 = -24;
        slot_base->unk_9E = 3;
        do {
            void *child_obj;

            child_obj = func_8003FD64(274, ((u8 *)(&D_80083498)));
            ((R06_8017087C_S_8017087C_4 *)slot)->unk_A4 = child_obj;
            if (child_obj != 0) {
                void *child_work = (u8 *)child_obj + 0x20;

                if (child_index != 0) {
                    ((R06_8017087C_S_8017087C_6 *)child_work)->unk_02 = 1;
                } else {
                    ((R06_8017087C_S_8017087C_6 *)child_work)->unk_02 = 2;
                }
                entry_index = 0;
                if (entry_index < ((R06_8017087C_S_8017087C_6 *)child_work)->unk_02) {
                    s32 entry_offset;
                    s32 child_id_fixed;

                    child_slot = slot;
                    child_id_fixed = entry_id_fixed;
                    entry_offset = 8;
                    do {
                        u8 *entry = (u8 *)child_work + entry_offset;
                        R06_8017087C_S_8017087C_9 *callback_obj;
                        s32 field_value;

                        field_value = ((R06_8017087C_S_8017087C_3 *)part_b)->unk_28;
                        ((R06_8017087C_S_8017087C_7 *)entry)->unk_0C = 0x00C0C0C0;
                        alloc_or_entry = entry;
                        entry_id = child_id_fixed >> 16;
                        ((R06_8017087C_S_8017087C_7 *)entry)->unk_28 = field_value;
                        entry_mode = 0;
                        callback_obj = child_slot->unk_A4;
                        callback_obj->unk_10 = dungeonProcessEffectBlockEntries;
                        setup_value = ((R06_8017087C_S_8017087C_7 *)entry)->unk_14;
                        setup_value |= 0xC;
                        ((R06_8017087C_S_8017087C_7 *)entry)->unk_14 = setup_value;
                        func_80047784(alloc_or_entry, entry_id, entry_mode);
                        entry_offset += 48;
                        ((R06_8017087C_S_8017087C_7 *)entry)->unk_10 = 96;
                        ((R06_8017087C_S_8017087C_7 *)entry)->unk_12 = ((R06_8017087C_S_8017087C_3 *)part_b)->unk_12 - 128;
                        ((R06_8017087C_S_8017087C_6 *)child_work)->unk_06 = child_index + 1;
                        textureSetTheActiveEntriesMatchingIDInTypeN2TableSlots(part_b, ((u8 *)D_800D71A8), ((R06_8017087C_S_8017087C_6 *)child_work)->unk_06);
                        ((R06_8017087C_S_8017087C_6 *)child_work)->unk_98 = (u8 *)obj + 30;
                    } while (++entry_index < ((R06_8017087C_S_8017087C_6 *)child_work)->unk_02);
                }
            }
            entry_id_fixed += 0x10000;
            slot += 4;
        } while (++child_index < slot_base->unk_9E);
        slot_base->unk_98 = slot_base->unk_98 | 0x2000;
        func_800AA36C(slot_base, part_a, part_b, work);
    }
    return work;
}
