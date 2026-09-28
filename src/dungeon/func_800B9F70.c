#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_800E3D7C.h"




extern u16 D_800DDE84[];
extern u8 D_800E12A9[];
extern s32 D_800E296C;

extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern void func_800997FC(void *, s32, s16);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);

/* Applies a value according to the target and mode, then updates bookkeeping. */
s32 func_800BF6D0(EntityRec *target, s32 value, s16 mode, s32 context)
{
    if (mode == 13) {
        return func_80098864(value, context);
    }

    if (target == ((u8 *)D_800E3D7C)) {
        target->unk_110 = value;
        func_8008D344(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        func_800A6480(target, value, mode);
        if (func_800AD6FC(target,
                         D_800DDE84[(*(u8 *)((u8 *)&target->unk_10 + 3))] & 3,
                         value) == 0) {
            func_800A5F38(target, value);
            return 1;
        }
    } else {
        func_800997FC(D_800E12A9, context, mode);
        D_800E296C |= 0x200;
    }

    dungeonStatus.unk_0A--;
    func_80098B38(value);
    return 1;
}
