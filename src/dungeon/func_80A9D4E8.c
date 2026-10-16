#include "modules/dungeon_resource08_slot0.h"

void func_80172CE8(void *action, EntityRec *motion, void *actor, EntityRec *object) {
    u16 position[3];
    s16 is_special;
    u8 *item_slot;
    void *node;
    u8 state;

    is_special = 0;
    state = ((R08_80172CE8_S_80172CE8_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if ((((u32)object->flags1C)) & 0x2000) {
            u32 kind = ((object->unk_46) & 0x3FFF) - 1;
            switch (kind) {
            case 6: is_special = 1;
            case 2: item_slot = (u8 *)object + 0xE; break;
            case 5: is_special = 1;
            case 1: item_slot = (u8 *)object + 0xB; break;
            case 4: is_special = 1;
            case 0: item_slot = (u8 *)object + 8; break;
            default: item_slot = 0; break;
            }
        } else {
            s32 kind = (object->unk_46) & 0x3FFF;
            switch (kind) {
            case 3: item_slot = (u8 *)object + 0xE; break;
            case 2: item_slot = (u8 *)object + 0xB; break;
            case 1: item_slot = (u8 *)object + 8; break;
            default: item_slot = 0; break;
            }
        }

        if (*item_slot != 0) {

            ((R08_80172CE8_S_80172CE8_0 *)action)->unk_98 &= 0xFF7F;
            {
                s32 use_existing;
                u32 item_def;

                use_existing = is_special;
                if (use_existing) {
                    node = D_800814A8;
                    (object->target) = node;
                    {
                        item_def = (u32)((R08_80172CE8_S_80172CE8_1_pre *)node)[-1].unk_00;
                        (((u8)object->unk_72)) = ((R08_80172CE8_S_80172CE8_2 *)item_def)->unk_24;
                        (((u8)object->unk_73)) = ((R08_80172CE8_S_80172CE8_2 *)item_def)->unk_25;
                    }
                } else {
                    u8 *item_defs = D_8006DE24;
                    u8 item_id = *item_slot;
                    item_def = (item_id * 20 + item_defs)[0x12];
                    if (item_def == 2) {
                        node = (object->target);
                        if (node != 0) {
                            {
                                item_def = (u32)((R08_80172CE8_S_80172CE8_1_pre *)node)[-1].unk_00;
                                (((u8)object->unk_72)) = ((R08_80172CE8_S_80172CE8_2 *)item_def)->unk_24;
                                (((u8)object->unk_73)) = ((R08_80172CE8_S_80172CE8_2 *)item_def)->unk_25;
                            }

                        }
                    } else {



                        (object->target) = func_800A05A4(
                            object,
                            ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_24,
                            ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_25,
                            (object->facing),
                            0x10);
                        object->unk_72 = abs(object->unk_72);
                        object->unk_73 = abs(object->unk_73);
                    }
                }

            }

            position[0] = ((u16)motion->x.w.i);
            position[1] = ((u16)motion->y.w.i);
            position[2] = ((u16)motion->z.w.i);
            if (func_800A94A0(object, item_slot, is_special, (u8 *)action + 0x98)) {
                ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
                func_800A56E0(0x703);
                func_800DA840(position, (s16)((*item_slot - 1) % 3));
                ((R08_80172CE8_S_80172CE8_0 *)action)->unk_9B++;
                return;
            }
            return;

        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_24, ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_25);
        dungeonStatus.unk_0C = 0;
        {
            u8 *active_object = (u8 *)D_800814A8;
            (*(u16 *)((u8 *)active_object + 0xA6))--;
        }
        func_800A4ACC(object);
        (((u8)object->unk_6D))--;
        ((R08_80172CE8_S_80172CE8_0 *)action)->unk_8C = ((void *)func_80170E7C);
        (((u8)object->unk_73)) = 0;
        (((u8)object->unk_72)) = 0;
        (object->unk_46) &= 0x7FFF;
        return;

    case 1:
        if (!(((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            return;
        }
        (*(void * *)((u8 *)actor + 0x2C)) = ((u8 *)D_80174C7C);
        func_80047784(
            actor,
            ((u8 *)D_80174C7C)[((gameWork.view.viewAngle + (object->facing) + 0x100) >> 9) & 7],
            0);
        ((R08_80172CE8_S_80172CE8_0 *)action)->unk_9B++;
        return;

    case 2:
        if (func_8003F270()) {
            ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 |= 0x800;
            return;
        }
        ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
        ((R08_80172CE8_S_80172CE8_0 *)action)->unk_9B++;
                        /* fall through */

    case 3:
        if ((((R08_80172CE8_S_80172CE8_3 *)actor)->unk_04 == 5 &&
            (((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 & 0x1000)) ||
            (((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 |= 0x800;
            ((R08_80172CE8_S_80172CE8_0 *)action)->unk_96 = 0x10;
            ((R08_80172CE8_S_80172CE8_0 *)action)->unk_98 |= 0x80;
        }

        {
            u16 timer = ((R08_80172CE8_S_80172CE8_0 *)action)->unk_96 - 1;
            ((R08_80172CE8_S_80172CE8_0 *)action)->unk_96 = timer;
            if ((s16)timer <= 0) {
                ((R08_80172CE8_S_80172CE8_0 *)action)->unk_96 = 0;
                ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
            }
        }

        if (!(((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 & 0xE000)) {
            return;
        }

        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_24, ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_25);

        if (((R08_80172CE8_S_80172CE8_3 *)actor)->unk_2C != ((u8 *)D_80174C3C)) {
            (*(void * *)((u8 *)actor + 0x2C)) = ((u8 *)D_80174C3C);
            func_80047784(
                actor,
                ((u8 *)D_80174C3C)[((gameWork.view.viewAngle + (object->facing) + 0x100) >> 9) & 7],
                0);
        }

        {
            if (((s32)dungeonStatus.unk_0C) != 0) {
                return;
            }
            dungeonStatus.unk_0A--;
        }
        ((R08_80172CE8_S_80172CE8_3 *)actor)->unk_14 &= 0xF7FF;
        ((R08_80172CE8_S_80172CE8_0 *)action)->unk_8C = ((void *)func_80170E7C);
        func_800A4ACC(object);
        if ((object->unk_6D) > 0) {
            (((u8)object->unk_6D))--;
        }
        (((u8)object->unk_73)) = 0;
        (((u8)object->unk_72)) = 0;
        (object->unk_46) &= 0x7FFF;
        func_800A56E0(0xB4);
        break;

    default:
        break;
    }

    return;
}
