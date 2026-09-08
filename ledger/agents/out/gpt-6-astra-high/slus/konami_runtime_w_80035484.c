#include "common.h"

#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef void (*Callback)(void *);

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
void func_80035484(s32 object_id, void *model, void *config) {
    void *state;
    void *transform;
    void *appearance;
    void *object;

    object = func_8003FF2C(0x11, object_id, 0x49, &D_80082BC0[0]);
    D_80081440 = object;
    FIELD(object, Callback, 0x10) = func_800355EC;
    func_8004491C(object, &func_80033D54);
    transform = FIELD(object, void *, 8);
    appearance = FIELD(object, void *, 0xC);
    func_80033C1C(model, 0);
    FIELD(object, void *, 0x20) = model;
    FIELD(model, s32, 0x60) = 6;
    state = (u8 *)object + 0x20;
    FIELD(FIELD(object, void *, 0x20), s32, 0x10) = 0;
    FIELD(FIELD(object, void *, 0x20), u16, 8) = 0x400;
    FIELD(state, s32, 4) = 0;
    FIELD(state, s32, 8) = 0;
    func_800350B0(config, state);
    FIELD(state, Callback, 0x68) = func_80035614;
    FIELD(transform, s16, 2) = -0x86;
    FIELD(transform, s16, 6) = 0x78;
    FIELD(transform, s16, 0xA) = 0x200;
    FIELD(appearance, s32, 0xC) = 0x808080;
    FIELD(appearance, void *, 8) = &D_80073B54[0];
    FIELD(appearance, s32, 0) = 0;
    FIELD(appearance, s8, 4) = 0;
    FIELD(appearance, s8, 5) = 0;
    FIELD(state, void *, 0x74) = config;
    FIELD(FIELD(object, void *, 0x20), s32, 0x14) =
        *(s16 *)((u8 *)&D_8006A93C[0] + FIELD(config, u8, 2) * 2);
    FIELD(appearance, void *, 8) =
        *(void **)((u8 *)&D_8006A8F0[0] + FIELD(FIELD(state, void *, 0x74), u8, 2) * 4);
}
