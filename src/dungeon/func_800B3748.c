#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
typedef struct {
    u16 unk0;
    u16 unk2;
    u16 unk4;
} FuncInput;

typedef struct {
    u8 pad0[2];
    u16 unk2;
    u8 pad4[2];
    u16 unk6;
    u8 pad8[2];
    u16 unkA;
    u8 padC[2];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
} FuncChild;

typedef struct {
    u8 pad0[8];
    s32 unk8;
    s32 unkC;
    s16 unk10;
    u8 pad12[2];
    u16 unk14;
    u8 pad16[6];
    s16 unk1C;
    s16 unk1E;
    u8 pad20[2];
    s16 unk22;
} FuncMeta;

typedef struct {
    u8 pad0[8];
    FuncChild *child;
    FuncMeta *meta;
    void *unk10;
    u8 pad14[14];
    s16 unk22;
} FuncObject;

extern s32 D_800CEEFC[3];
extern s32 D_800B8E18;
extern void *func_8003FD64(s16, s32);
extern s32 func_8004491C(void *, s32 *);

void func_800B8EA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3,
                   FuncInput *arg4, s32 arg5, s16 arg6, s32 arg7, s16 arg8) {
    FuncMeta *temp_a1;
    FuncObject *temp_v0;
    FuncChild volatile *temp_v1;
    u16 input4;
    s32 count;

    temp_v0 = func_8003FD64(0x12, arg0);
    if (temp_v0 != NULL) {
        temp_v0->unk10 = &D_800B8E18;
        func_8004491C(temp_v0, D_800CEEFC);
        temp_v1 = temp_v0->child;
        temp_v1->unk2 = arg4->unk0;
        temp_v1->unk6 = arg4->unk2;
        input4 = arg4->unk4;
        temp_v1->unkE = arg1;
        temp_v1->unk12 = arg2;
        temp_v1->unk16 = arg3;
        temp_v1->unkA = input4;
        temp_a1 = temp_v0->meta;
        temp_a1->unk8 = arg5;
        temp_a1->unk1E = arg7;
        temp_a1->unk1C = arg7;
        temp_a1->unkC = 0x808080;
        count = ((s32) arg6 << 16) >> 16;
        if (count != 0) {
            temp_a1->unk10 = (s16) ((count - 1) << 5);
            temp_a1->unk14 = (u16) (temp_a1->unk14 | 0xC);
        }
        temp_v0->unk22 = arg8;
    }
}
