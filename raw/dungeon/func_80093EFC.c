#include "common.h"

typedef struct DungeonState {
    u8 pad[0x1C];
    u32 flags;
} DungeonState;

typedef struct Object {
    u8 pad[3];
    u8 flags;
} Object;

extern DungeonState *D_800E3D7C[3];
extern u8 D_800E18C0[];
extern u8 D_80088CA8[];

extern s32 func_80042A80(Object *arg0);
extern s32 func_80099194(void *arg0, s32 arg1);
extern s32 func_8009929C(s32 arg0, s32 arg1);
extern s32 func_80099368(void *arg0, s32 arg1);
extern void func_800A90E8(void *arg0);

s32 func_8009965C(Object *arg0, s32 arg1) {
    s32 result = arg1;

    if (!(D_800E3D7C[0]->flags & 0x10)) {
        if ((arg0->flags & 0x80) || func_80042A80(arg0)) {
            result = func_80099194(
                D_800E18C0,
                func_80099368(arg0, func_8009929C(10, result)));
            arg0->flags &= 0x7F;
            func_800A90E8(arg0);
            result = func_80099194(
                D_80088CA8,
                func_80099368(arg0, result));
            func_800A90E8(arg0);
        }
    }

    return result;
}
