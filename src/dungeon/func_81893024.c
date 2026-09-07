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

void *func_81893024(s32 arg0, void *arg1, s16 arg2, s16 arg3) {
    M2C_BLOCK *src;
    M2C_OBJECT *temp_v0;
    s32 *temp_v0_2;
    M2C_BLOCK *temp_v1;
    void *var_v0;

    temp_v0 = func_8003FC64(0x212);
    do { var_v0 = NULL; } while (0);
    if (temp_v0 != NULL) {
        src = (M2C_BLOCK *)arg1;
        temp_v0->callback = &D_800243F8;
        temp_v0_2 = &temp_v0->arg0;
        temp_v0->arg0 = arg0;
        ((s16 *)temp_v0_2)[2] = 0;
        ((s16 *)temp_v0_2)[3] = arg2;
        temp_v1 = temp_v0->data;
        *temp_v1 = *src;
        ((S_81893024_0 *)temp_v1)->unk_0A = (s16) (((S_81893024_0 *)temp_v1)->unk_0A + arg3);
        func_8004491C(temp_v0, D_8002445C);
        var_v0 = temp_v0;
    }
    return var_v0;
}
