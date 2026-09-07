#include "common.h"

typedef struct S_800BFD80_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 pad_02[0x11];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0xF];
    u8 unk_27;
    u8 pad_28[0x41];
    u8 unk_69;
    u8 pad_6A[0xA6];
    s32 unk_110;
} S_800BFD80_0;   /* arg0 in func_800BFD80 */



typedef struct {
    u8 pad[0xA];
    u16 counter;
} DungeonState;

extern void func_80041E70(void *);
extern void func_8008D330(void *, void *, void *, void *);
extern void func_80098B38(u32);
extern void func_80099844(void *, void *);
extern void func_800A5F38(void *, s32);
extern void func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern void func_800D4FC8(void *, s32, s32);

extern u8 D_80082E80[];
extern DungeonState D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E2056[];
extern void *D_800E3D7C[];

/* Updates entity state and progress counters, then triggers the associated effects. */
s32 func_800BFD80(void *entity, s32 update_value, s16 update_mode)
{
    u32 progress_value;
    u8 progress;
    u8 completion_count;

    if (entity == D_800E3D7C[0]) {
        ((S_800BFD80_0 *)entity)->unk_110 = update_value;
        func_8008D330(entity, D_80083780, D_80082E80, entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, update_value, update_mode);
        if (func_800AD6FC(
                entity, (D_800DDE84[((S_800BFD80_0 *)entity)->unk_13] >> 6) & 3, 0) == 0) {
            func_800A5F38(entity, update_value);
            return 1;
        }
    }

    if (((S_800BFD80_0 *)entity)->unk_27 == ((S_800BFD80_0 *)entity)->unk_69) {
        completion_count = ((S_800BFD80_0 *)entity)->unk_01;
        if (completion_count < 0xFF) {
            ((S_800BFD80_0 *)entity)->unk_01 = completion_count + 1;
            func_80041E70(entity);
        }
    }

    progress = ((S_800BFD80_0 *)entity)->unk_27;
    progress_value = progress & 0xFF;
    if (progress_value < 0xFF && progress_value < ((S_800BFD80_0 *)entity)->unk_69) {
        ((S_800BFD80_0 *)entity)->unk_27 = progress + 1;
    }

    if (((S_800BFD80_0 *)entity)->unk_14 & 0x4000) {
        func_80099844(entity, D_800E2056);
    }
    func_800D4FC8((u8 *)entity - 0x20, 0x20F020, 0x616);
    func_80098B38(update_value);
    D_80083460.counter--;
    return 1;
}
