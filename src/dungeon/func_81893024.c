#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s32 f14;
} M2C_BLOCK;

typedef struct {
    s8 unk0[8];
    M2C_BLOCK *data;
    s8 unkC[4];
    void *callback;
    s8 unk14[12];
    s32 arg0;
} M2C_OBJECT;

extern s32 D_8002445C[];
void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800243F8;

typedef struct S_81893024_0 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_81893024_0;   /* temp_v1 in func_81893024 */

/* Creates an object with copied data, an adjusted field, and initialized arguments. */
void *func_81893024(s32 object_arg, void *source_data, s16 initial_value, s16 field_delta) {
    M2C_BLOCK *src;
    M2C_OBJECT *object;
    s32 *object_args;
    M2C_BLOCK *data;
    void *result;

    object = func_8003FC64(0x212);
    do { result = NULL; } while (0);
    if (object != NULL) {
        src = (M2C_BLOCK *)source_data;
        object->callback = &D_800243F8;
        object_args = &object->arg0;
        object->arg0 = object_arg;
        ((s16 *)object_args)[2] = 0;
        ((s16 *)object_args)[3] = initial_value;
        data = object->data;
        *data = *src;
        ((S_81893024_0 *)data)->unk_0A = (s16) (((S_81893024_0 *)data)->unk_0A + field_delta);
        func_8004491C(object, D_8002445C);
        result = object;
    }
    return result;
}
