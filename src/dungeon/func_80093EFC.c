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

/* Processes an eligible object in two stages and returns the resulting value. */
s32 func_8009965C(Object *object, s32 input_value) {
    s32 result = input_value;

    if (!(D_800E3D7C[0]->flags & 0x10)) {
        if ((object->flags & 0x80) || func_80042A80(object)) {
            result = func_80099194(
                D_800E18C0,
                func_80099368(object, func_8009929C(10, result)));
            object->flags &= 0x7F;
            func_800A90E8(object);
            result = func_80099194(
                D_80088CA8,
                func_80099368(object, result));
            func_800A90E8(object);
        }
    }

    return result;
}
