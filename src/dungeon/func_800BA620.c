#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


extern void func_80041E70(void *);
extern void func_8008D330(void *, void *, void *, void *);
extern void func_80098B38(u32);
extern void func_80099844(void *, void *);
extern void func_800A5F38(void *, s32);
extern void func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800D4FC8(void *source, s32 color, unsigned short sound_id);

extern u8 D_800E2056[];

/* Updates entity state and progress counters, then triggers the associated effects. */
s32 func_800BFD80(void *entity, s32 update_value, s16 update_mode)
{
    u32 progress_value;
    u8 progress;
    u8 completion_count;

    if (entity == D_800E3D7C) {
        ((EntityRec *)entity)->unk_110 = update_value;
        func_8008D330(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, update_value, update_mode);
        if (func_800AD6FC(
                entity, (D_800DDE84[(*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3))] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, update_value);
            return 1;
        }
    }

    if (((EntityRec *)entity)->unk_27 == ((EntityRec *)entity)->unk_69) {
        completion_count = (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 1));
        if (completion_count < 0xFF) {
            (*(u8 *)((u8 *)&((EntityRec *)entity)->x + 1)) = completion_count + 1;
            func_80041E70(entity);
        }
    }

    progress = ((EntityRec *)entity)->unk_27;
    progress_value = progress & 0xFF;
    if (progress_value < 0xFF && progress_value < ((EntityRec *)entity)->unk_69) {
        ((EntityRec *)entity)->unk_27 = progress + 1;
    }

    if (((EntityRec *)entity)->flags14 & 0x4000) {
        func_80099844(entity, D_800E2056);
    }
    func_800D4FC8((u8 *)entity - 0x20, 0x20F020, 0x616);
    func_80098B38(update_value);
    dungeonStatus.unk_0A--;
    return 1;
}
