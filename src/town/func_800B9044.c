#include "common.h"
#include "shared/types3a_types.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
} Template0;


typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    u8 unkE;
    u8 unkF;
} Instance0;


typedef struct {
    s32 unk0;
    Instance0 *unk4;
    DisplayPositionWords *unk8;
} Owner;

typedef union {
    s32 value;
} StackArg;

extern Template0 D_8002E5D8;
extern DisplayPositionWords D_8002E5E8;

/* Initialize the owner's instances from defaults and set their position. */
void func_800B67A4(Owner *owner, Template0 *instance_data, DisplayPositionWords *instance1,
                   s32 x, StackArg y_arg, StackArg z_arg) {
    s32 y = y_arg.value;
    s32 z = z_arg.value;
    Template0 *defaults0 = &D_8002E5D8;
    DisplayPositionWords *defaults1 = &D_8002E5E8;
    s32 *first_word;

    instance_data->unk0 = defaults0->unk0;
    first_word = &defaults1->unk0;
    instance_data->unk4 = defaults0->unk4;
    instance_data->unk8 = defaults0->unk8;
    instance_data->unkC = defaults0->unkC;

    instance1->unk0 = *first_word;
    instance1->unk4 = defaults1->unk4;
    instance1->unk8 = defaults1->unk8;

    owner->unk4 = (Instance0 *)instance_data;
    owner->unk8 = instance1;
    owner->unk0 = 0;

    owner->unk4->unk8 = x;
    owner->unk4->unkA = y;
    owner->unk4->unkC = z;
    owner->unk4->unkF = 4;
}
