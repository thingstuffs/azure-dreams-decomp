#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern u8 D_800E11FD[];

extern void func_8008D344(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern void func_800997FC(void *, s32, s16);
extern void func_8009D8A4(void);
extern void func_800A56E0(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);

/* Applies an item to the target and removes it when consumed. */
s32 func_800BF210(EntityRec *target, s32 item, s16 target_kind, s32 target_data)
{
    if (target_kind == 13) {
        return func_80098864(item, target_data);
    }

    if (target == ((u8 *)D_800E3D7C)) {
        target->unk_110 = item;
        func_8008D344(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A6480(target, item, target_kind);
        if (func_800AD6FC(target,
                          D_800DDE84[(*(u8 *)((u8 *)&target->unk_10 + 3))] & 3,
                          item) == 0) {
            func_800A5F38(target, item);
            return 1;
        }
    } else {
        func_800997FC(D_800E11FD, target_data, target_kind);
        func_8009D8A4();
        D_800E296C |= 0x800000;
        func_800A56E0(0x80F);
    }

    dungeonStatus.unk_0A--;
    func_80098B38(item);
    return 1;
}
