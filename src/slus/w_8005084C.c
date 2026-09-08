#include "common.h"

#include "common.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} S_8002E5D8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8002E5E8;

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} S_8005084C_A;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} S_8005084C_B;

typedef struct {
    s32 unk0;
    S_8005084C_A *unk4;
    S_8005084C_B *unk8;
} S_8005084C_Outer;

extern S_8002E5D8 D_8002E5D8;
extern S_8002E5E8 D_8002E5E8;
extern void func_80050550(S_8005084C_Outer *, s32, s32);

/* Initialize the object and its two data blocks from defaults, then apply starting settings. */
void func_8005084C(void *unused, S_8005084C_Outer *object,
                   S_8002E5D8 *primary_data, S_8005084C_B *secondary_data) {
    S_8002E5D8 *primary_defaults = &D_8002E5D8;
    S_8002E5E8 *secondary_defaults = &D_8002E5E8;
    s32 *secondary_first;

    primary_data->unk0 = primary_defaults->unk0;
    secondary_first = &secondary_defaults->unk0;
    primary_data->unk4 = primary_defaults->unk4;
    primary_data->unk8 = primary_defaults->unk8;
    primary_data->unkC = primary_defaults->unkC;

    ((S_8002E5E8 *)secondary_data)->unk0 = *secondary_first;
    ((S_8002E5E8 *)secondary_data)->unk4 = secondary_defaults->unk4;
    ((S_8002E5E8 *)secondary_data)->unk8 = secondary_defaults->unk8;

    object->unk4 = (S_8005084C_A *)primary_data;
    object->unk8 = secondary_data;
    object->unk0 = 0;

    object->unk4->unk8 = -0x6C;
    object->unk4->unkA = -0x10;
    object->unk4->unkF = 4;
    func_80050550(object, 0, 1);
}
