#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"

void func_8008D330();
void func_80098B38();
s32 func_800A56E0();
void func_800A5F38();
void func_800A63B8();
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
