#include "common.h"

#include "common.h"

typedef void (*Callback)(void *);

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern void *func_8003FF2C(s32, s32, s32, void *);
extern void func_8004491C(void *, Callback);
extern void ClearImage(void *, s32, s32, s32);
extern void func_80033C1C(void *, s32);
extern void func_800350B0(void *, void *);
extern void func_80036988(void *, void *);
extern void func_800375C0(void *, void *);

extern void func_80033D54(void *);
extern void func_8003605C(void *);
extern void func_80036110(void *);
extern void func_80037714(void *);

extern u8 D_80082BC0[];
extern u8 D_8006AA3C[];
extern u8 D_80073AAC[];
extern u16 D_8006A91C[];
extern u16 D_8006A924[];
extern u16 D_8006A92C[];
extern u32 D_8006A8FC[];
extern s16 D_8006A914[];

void func_80035E58(s32 arg0, void *arg1, u8 *arg2, s32 *arg3,
                   s32 arg4, u8 *arg5) {
    u8 *obj;
    u8 *sub;
    u8 *child;
    u8 *actor;

    obj = func_8003FF2C(0x11, arg0, 0x49, D_80082BC0);
    FIELD(obj, Callback, 0x10) = func_8003605C;
    func_8004491C(obj, func_80033D54);

    sub = obj + 0x20;
    child = FIELD(obj, u8 *, 0xC);
    FIELD(sub, s32 *, 0x44) = arg3;
    FIELD(sub, u8, 0x48) = 1;
    FIELD(sub, s16, 0x4A) = (s16)arg4;
    ClearImage(arg2 + 4, 0, 0, 0);

    func_80033C1C(arg1, *arg3);
    FIELD(obj, void *, 0x20) = arg1;
    FIELD(sub, void *, 0x4) = arg2;
    FIELD(sub, Callback, 0x8) = func_80037714;
    func_800375C0(sub, D_8006AA3C);
    func_800350B0(arg5, sub);

    FIELD(sub, Callback, 0x68) = func_80036110;
    actor = arg5 + 0x8C;
    FIELD(child, u32, 0xC) = 0x808080;
    FIELD(child, void *, 0x8) = D_80073AAC;
    FIELD(child, s32, 0x0) = 0;
    FIELD(child, u8, 0x4) = 0;
    FIELD(child, u8, 0x5) = 0;
    FIELD(sub, void *, 0x74) = actor;

    FIELD(sub, u16, 0x12) = D_8006A91C[FIELD(FIELD(actor, u8 *, 0x80), u8, 2)];
    FIELD(sub, u16, 0x2E) = D_8006A924[FIELD(FIELD(actor, u8 *, 0x80), u8, 2)];
    FIELD(sub, u16, 0x36) = D_8006A92C[FIELD(FIELD(actor, u8 *, 0x80), u8, 2)];
    func_80036988(obj + 0x2C, FIELD(sub, void *, 0x74));
    FIELD(child, u32, 0x8) = D_8006A8FC[FIELD(FIELD(actor, u8 *, 0x80), u8, 2)];
    FIELD(FIELD(obj, u8 *, 0x20), s32, 0x34) =
        D_8006A914[FIELD(FIELD(actor, u8 *, 0x80), u8, 2)];
}
