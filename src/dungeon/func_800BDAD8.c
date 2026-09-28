#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
M2C_UNK func_8008D330();
M2C_UNK func_80098B38();
M2C_UNK func_800A56E0();
M2C_UNK func_800A5F38();
M2C_UNK func_800A63B8();
s32 func_800AD6FC();
s32 func_800C8900();
extern u16 D_800DDE84[];

/* Handle item use on a target, deferring the player action or consuming the item. */
s32 func_800C3238(EntityRec *target, s32 item, s16 use_type) {
    if (target == D_800E3D7C) {
        target->unk_110 = item;
        func_8008D330(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }
    if ((s32)target <= 0x9FFFFFFFU) {
        func_800A63B8(target, item, use_type);
        if (func_800AD6FC(target,
                         (D_800DDE84[(*(u8 *)((u8 *)&target->unk_10 + 3))] >> 6) & 3,
                         0) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
    }
    if (func_800C8900(target, 0x400, 8) != 0) {
        func_800A56E0(0x612);
    }
    func_80098B38(item);
    dungeonStatus.unk_0A--;
    return 1;
}
