#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

void func_8008D330(); /* extern */
void func_80094E34();                            /* extern */
void func_80098B38();                         /* extern */
void func_800997FC();                   /* extern */
void func_80099844();           /* extern */
s32 func_800A56E0();                     /* extern */
void func_800A5F38();                 /* extern */
void func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
extern M2C_UNK D_800E17C6;
extern M2C_UNK D_800E17EF;
extern M2C_UNK D_800E180E;


typedef struct S_800C3900_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C3900_1;   /* var_v1 in func_800C3900 */

/* Processes an entity action, preserves its state flag, and updates the shared counter. */
s32 func_800C3900(EntityRec *entity, s32 action, s16 action_param) {
    void *counter_page;
    DungeonGlobalStatus *counter_base;
    s32 saved_flag;
    s32 flag_test;
    u32 flags;

    if (entity == ((s32)D_800E3D7C)) {
        entity->unk_110 = action;
        func_8008D330(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }
    if (((u32) ((*(u8 *)((u8 *)&entity->unk_10 + 3)) - 1) < 0x2EU) && ((u32) entity <= 0x9FFFFFFFU)) {
        func_800A63B8(entity, action, action_param);
        saved_flag = ((u32) ((u32)entity->flags1C) >> 3) & 1;
        if (func_800AD6FC(entity, (D_800DDE84[(*(u8 *)((u8 *)&entity->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, action);
            return 1;
        }
        flag_test = saved_flag;
        if (flag_test != 0) {
            entity->flags1C = (u32) (((u32)entity->flags1C) | 8);
        }
        flags = ((u32)entity->flags1C);
        (*(s16 *)&entity->tileX) = 0;
        if (!(flags & 8)) {
            flag_test = flags & 0x80000;
            counter_page = (void *)0x80080000;
            if (flag_test != 0) {
                func_80094E34();
                counter_page = (void *)0x80080000;
            }
            counter_page = &dungeonStatus.unk_00;
            ((S_800C3900_1 *)counter_page)->unk_0A = (u16) (((S_800C3900_1 *)counter_page)->unk_0A + 1);
        }
        func_800A56E0(0x51E);
        if (entity->flags14 & 0x4000) {
            func_80099844(entity, &D_800E17C6);
        }
        func_80098B38(action);
    } else if ((*(u8 *)((u8 *)&entity->unk_10 + 3)) == 0) {
        func_800997FC(&D_800E17EF);
        func_800A56E0(0x506);
    } else {
        func_80098B38(action);
        func_800997FC(&D_800E180E);
    }
    counter_base = &dungeonStatus;
    counter_base->unk_0A = (u16) (((u16)counter_base->unk_0A) - 1);
    return 1;
}
