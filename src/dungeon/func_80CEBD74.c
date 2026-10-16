#include "modules/dungeon_ovl_7f469800_p07.h"

/* Updates the actor's directional animation and advances its action state. */
void func_80175574(T_80175574_Obj0 *controller, void *context, T_80175574_Obj2 *animation, T_80175574_Obj3 *actor)
{
    unsigned long table_entry;


    switch (((T_80175574_S_80175574_0 *)controller)->unk_9B) {
    case 0:
        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *counter_base = &dungeonStatus;

            counter_base->unk_0A--;
        }
        {

            switch (((EntityRec *)actor)->unk_48) {
            default:
                break;
            case 13:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E54;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E54;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E5C;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E5C;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E64;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E64;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            }
        }
        ((T_80175574_S_80175574_0 *)controller)->unk_9B++;
        return;

    case 1:
    {
        u8 *dir_table;
        void *current_table;

        switch (((EntityRec *)actor)->unk_48) {
        default:
            break;
        case 13:
            current_table = ((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv;
            dir_table = D_80175E54;
            if (current_table != dir_table) {
                (*(void * *)((u8 *)animation + 0x2C)) = dir_table;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)dir_table;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
            }
            break;
        case 14:
            current_table = ((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv;
            dir_table = D_80175E5C;
            if (current_table != dir_table) {
                (*(void * *)((u8 *)animation + 0x2C)) = dir_table;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)dir_table;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
            }
            break;
        case 15:
            current_table = ((Rec_func_800AA258_arg2 *)animation)->unk_2C.as_pv;
            dir_table = D_80175E64;
            if (current_table != dir_table) {
                (*(void * *)((u8 *)animation + 0x2C)) = dir_table;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)dir_table;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
            }
            break;
        }
    }

        if (((EntityRec *)actor)->tileY != 0) {
            switch (((EntityRec *)actor)->unk_48) {
            case 13:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E6C;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E6C;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E74;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E74;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E7C;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E7C;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            }
        } else {
            if (dungeonStatus.flags & 0x1000) {
                return;
            }
            if (((EntityRec *)actor)->unk_64 != 0) {
                if (func_800AA6B4(controller, context, animation, 0) != 0) {
                    return;
                }
            }
            if ((func_800A2C34(actor) << 16) != 0) {
                return;
            }
            {
                s32 actor_flags = ((EntityRec *)actor)->flags1C;

                if (actor_flags & 0x100) {
                    func_800AA258(controller, context, animation, actor);
                    return;
                }
                if (actor_flags & 0x80000) {
                    func_800AA888(controller, context, animation, actor);
                    func_801759A0(controller, context, animation, actor);
                    return;
                }
            }
            if (((EntityRec *)actor)->unk_6D == 0) {
                return;
            }
            if ((func_800A2C34(actor) << 16) != 0) {
                if ((func_8009A180(actor,
                        (u8 *)D_800814A8->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            func_800A9A0C(actor);
            func_800A9A04(actor);
            if (((EntityRec *)actor)->tileY == 0) {
                return;
            }
            switch (((EntityRec *)actor)->unk_48) {
            case 13:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E6C;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E6C;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 14:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E74;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E74;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            case 15:
                (*(void * *)((u8 *)animation + 0x2C)) = D_80175E7C;
                table_entry = ((gameWork.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7;
                table_entry += (unsigned long)D_80175E7C;
                func_80047784(animation,
                    *(u8 *)table_entry,
                    0);
                break;
            }
        }

increment_counter:
        {
            DungeonGlobalStatus *counter_base = &dungeonStatus;

            counter_base->unk_0A++;
        }
increment_state:
        ((T_80175574_S_80175574_0 *)controller)->unk_9B++;
        return;

    case 2:
        if (!(((Rec_func_800AA258_arg2 *)animation)->unk_14 & 0xE000)) {
            return;
        }
        {
            DungeonGlobalStatus *counter_base = &dungeonStatus;

            counter_base->unk_0A--;
        }
        ((T_80175574_S_80175574_0 *)controller)->unk_8C = func_801724BC;
        return;

    default:
        return;
    }
}
