#include "common.h"

#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef void (*Callback)(void *);

typedef struct S_func_80035484_0 {
    u8 pad_00[8];
    void *unk_08;
    void *unk_0C;
    Callback unk_10;
    u8 pad_14[0xC];
    void *unk_20;
} S_func_80035484_0;

typedef struct S_func_80035484_1 {
    u8 pad_00[4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x5C];
    Callback unk_68;
    u8 pad_6C[8];
    void *unk_74;
} S_func_80035484_1;

typedef struct S_func_80035484_2 {
    u8 pad_00[2];
    s16 unk_02;
    u8 pad_04[2];
    s16 unk_06;
    u8 pad_08[2];
    s16 unk_0A;
} S_func_80035484_2;

typedef struct S_func_80035484_3 {
    s32 unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[2];
    void *unk_08;
    s32 unk_0C;
} S_func_80035484_3;

typedef struct S_func_80035484_4 {
    u8 pad_00[8];
    u16 unk_08;
    u8 pad_0A[6];
    s32 unk_10;
    s32 unk_14;
    u8 pad_18[0x48];
    s32 unk_60;
} S_func_80035484_4;

typedef struct S_func_80035484_5 {
    u8 pad_00[2];
    u8 unk_02;
} S_func_80035484_5;


extern void func_80033C1C(void *arg0, s32 arg1);
extern void func_800350B0(void *arg0, void *arg1);
extern void *func_8003FF2C(s32 arg0, s32 arg1, s32 arg2, void **arg3);
extern s32 func_8004491C(void *arg0, void (*arg1)(void));

extern void func_80033D54(void);
extern void func_800355EC(void *arg0);
extern void func_80035614(void *arg0);

extern s16 D_8006A93C[];
extern void *D_8006A8F0[];
extern u8 D_80073B54[];
extern void *D_80081440;
extern void *D_80082BC0[3];

/* Creates a runtime object and initializes its model, transform, and appearance. */
void func_80035484(s32 object_addr, S_func_80035484_4 *model, S_func_80035484_5 *config) {
    S_func_80035484_1 *state;
    S_func_80035484_2 *transform;
    S_func_80035484_3 *appearance;
    S_func_80035484_0 *object;

    object = func_8003FF2C(0x11, object_addr, 0x49, &D_80082BC0[0]);
    D_80081440 = object;
    object->unk_10 = func_800355EC;
    func_8004491C(object, &func_80033D54);
    transform = object->unk_08;
    appearance = object->unk_0C;
    func_80033C1C(model, 0);
    object->unk_20 = model;
    model->unk_60 = 6;
    state = (S_func_80035484_1 *)((u8 *)object + 0x20);
    ((S_func_80035484_4 *)object->unk_20)->unk_10 = 0;
    ((S_func_80035484_4 *)object->unk_20)->unk_08 = 0x400;
    state->unk_04 = 0;
    state->unk_08 = 0;
    func_800350B0(config, state);
    state->unk_68 = func_80035614;
    transform->unk_02 = -0x86;
    transform->unk_06 = 0x78;
    transform->unk_0A = 0x200;
    appearance->unk_0C = 0x808080;
    appearance->unk_08 = &D_80073B54[0];
    appearance->unk_00 = 0;
    appearance->unk_04 = 0;
    appearance->unk_05 = 0;
    state->unk_74 = config;
    ((S_func_80035484_4 *)object->unk_20)->unk_14 =
        *(s16 *)((u8 *)&D_8006A93C[0] + config->unk_02 * 2);
    appearance->unk_08 =
        *(void **)((u8 *)&D_8006A8F0[0] + ((S_func_80035484_5 *)state->unk_74)->unk_02 * 4);
}
