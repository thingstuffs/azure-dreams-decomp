#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"

s32 func_8004383C();                 /* extern */
void func_8008D330(void *, void *, void *, void *); /* extern */
M2C_UNK func_80098B38();                         /* extern */
M2C_UNK func_800A5F38();                 /* extern */
M2C_UNK func_800A63B8();            /* extern */
s32 func_800AD6FC();            /* extern */
M2C_UNK func_800D4FC8();    /* extern */

/* Handles item use for an entity, updating its state and consuming the item. */
s32 func_800BFF00(void *entity, s32 item, s16 action_id) {
    if (entity == ((u8 *)D_800E3D7C)) {
        ((EntityRec *)entity)->unk_110 = item;
        func_8008D330(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }
    if ((u32) entity <= 0x9FFFFFFFU) {
        func_800A63B8(entity, item, action_id);
        if (func_800AD6FC(entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, item);
            return 1;
        }
    }
    if ((u8) (*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 1)) < 0x63U) {
        ((EntityRec *)entity)->unk_18 = func_8004383C(entity, 0);
        ((EntityRec *)entity)->unk_42 = 0;
        ((EntityRec *)entity)->unk_41 = 0;
        D_800E296C |= 0x100000;
    }
    func_800D4FC8(entity - 0x20, 0x20F0F0, 0x616);
    func_80098B38(item);
    dungeonStatus.unk_0A--;
    return 1;
}
