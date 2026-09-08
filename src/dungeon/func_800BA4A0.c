#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u8 pad[0xA];
    u16 counter;
} DungeonState;

extern void func_80041E70(void *);
extern void func_8008D330(void *, void *, void *, void *);
extern void func_80098B38(s32);
extern void func_80099844(void *, void *);
extern void func_800A5F38(void *, s32);
extern void func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800D4FC8(void *, s32, s32);

extern u8 D_80082E80[];
extern DungeonState D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E1350[];
extern void *D_800E3D7C[];



/* Handles an entity action, advancing capped counters and updating dungeon state. */
s32 func_800BFC00(void *entity, s32 action_id, s16 action_param)
{
    u32 progress_value;
    u8 progress;
    u8 completion_count;

    if (entity == D_800E3D7C[0]) {
        ((Rec_D_800E3D7C *)entity)->unk_110 = action_id;
        func_8008D330(entity, D_80083780, D_80082E80, entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, action_id, action_param);
        if (func_800AD6FC(
                entity, (D_800DDE84[((Rec_D_800E3D7C *)entity)->unk_10.at03_u8.v] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, action_id);
            return 1;
        }
    }

    if (((Rec_D_800E3D7C *)entity)->unk_26 == ((Rec_D_800E3D7C *)entity)->unk_68) {
        completion_count = ((Rec_D_800E3D7C *)entity)->unk_00.at00_u8.v;
        if (completion_count < 0xFF) {
            ((Rec_D_800E3D7C *)entity)->unk_00.at00_u8.v = completion_count + 1;
            func_80041E70(entity);
        }
    }

    progress = ((Rec_D_800E3D7C *)entity)->unk_26;
    progress_value = progress & 0xFF;
    if (progress_value < 0xFF && progress_value < ((Rec_D_800E3D7C *)entity)->unk_68) {
        ((Rec_D_800E3D7C *)entity)->unk_26 = progress + 1;
    }

    if (((Rec_D_800E3D7C *)entity)->unk_14.as_s32 & 0x4000) {
        func_80099844(entity, D_800E1350);
    }
    func_800D4FC8((u8 *)entity - 0x20, 0x2020F0, 0x616);
    func_80098B38(action_id);
    D_80083460.counter--;
    return 1;
}
