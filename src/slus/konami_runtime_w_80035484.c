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

void func_80035484(s32 arg0, void *arg1, void *arg2) {
    void *temp_s1;
    void *temp_s2;
    void *temp_s3;
    void *temp_v0;

    temp_v0 = func_8003FF2C(0x11, arg0, 0x49, &D_80082BC0[0]);
    D_80081440 = temp_v0;
    FIELD(temp_v0, Callback, 0x10) = func_800355EC;
    func_8004491C(temp_v0, &func_80033D54);
    temp_s2 = FIELD(temp_v0, void *, 8);
    temp_s3 = FIELD(temp_v0, void *, 0xC);
    func_80033C1C(arg1, 0);
    FIELD(temp_v0, void *, 0x20) = arg1;
    FIELD(arg1, s32, 0x60) = 6;
    temp_s1 = (u8 *)temp_v0 + 0x20;
    FIELD(FIELD(temp_v0, void *, 0x20), s32, 0x10) = 0;
    FIELD(FIELD(temp_v0, void *, 0x20), u16, 8) = 0x400;
    FIELD(temp_s1, s32, 4) = 0;
    FIELD(temp_s1, s32, 8) = 0;
    func_800350B0(arg2, temp_s1);
    FIELD(temp_s1, Callback, 0x68) = func_80035614;
    FIELD(temp_s2, s16, 2) = -0x86;
    FIELD(temp_s2, s16, 6) = 0x78;
    FIELD(temp_s2, s16, 0xA) = 0x200;
    FIELD(temp_s3, s32, 0xC) = 0x808080;
    FIELD(temp_s3, void *, 8) = &D_80073B54[0];
    FIELD(temp_s3, s32, 0) = 0;
    FIELD(temp_s3, s8, 4) = 0;
    FIELD(temp_s3, s8, 5) = 0;
    FIELD(temp_s1, void *, 0x74) = arg2;
    FIELD(FIELD(temp_v0, void *, 0x20), s32, 0x14) =
        *(s16 *)((u8 *)&D_8006A93C[0] + FIELD(arg2, u8, 2) * 2);
    FIELD(temp_s3, void *, 8) =
        *(void **)((u8 *)&D_8006A8F0[0] + FIELD(FIELD(temp_s1, void *, 0x74), u8, 2) * 4);
}
