#include "common.h"

#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FF2C(s32, void *, s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80033C1C(void *, s32);
extern void func_800375C0(void *, void *);
extern void func_800350B0(void *, void *);

extern void func_80033D54(void);
extern void func_800359FC(void);
extern void func_80035AAC(void);
extern void func_80037714(void);

extern u8 D_80082BC0[12];
extern u8 D_8006A9E8[12];
extern s16 D_8006A90C[];
extern u8 D_8007386C[12];
extern s32 D_800809B8;
extern s32 D_800809BC;

void func_80035888(void *arg0, void *arg1, s32 *arg2, s16 arg3, void *arg4)
{
    void *node;
    void *object;
    void *part8;
    void *partC;

    node = func_8003FF2C(0x11, arg0, 0x49, D_80082BC0);
    FIELD(node, void *, 0x10) = func_800359FC;
    func_8004491C(node, func_80033D54);

    object = (u8 *)node + 0x20;
    part8 = FIELD(node, void *, 8);
    partC = FIELD(node, void *, 0xC);
    FIELD(object, void *, 0x44) = arg2;
    FIELD(object, u8, 0x48) = 1;
    FIELD(object, s16, 0x4A) = arg3;

    func_80033C1C(arg1, *arg2);

    FIELD(node, void *, 0x20) = arg1;
    FIELD(object, s32, 4) = 0;
    FIELD(object, void *, 8) = func_80037714;
    func_800375C0(object, D_8006A9E8);
    func_800350B0(arg4, object);

    {
    s32 color;
    s32 first;
    s32 second;

    color = 0x800000;
    first = D_800809B8;
    FIELD(object, void *, 0x68) = func_80035AAC;
    FIELD(object, s32, 0x14) = first;
    second = D_800809BC;
    color |= second ? 0x8080 : 0x8080;
    FIELD(object, s32, 0x18) = second;
    FIELD(part8, s16, 2) = 0;
    FIELD(partC, s32, 0xC) = color;
    FIELD(partC, void *, 8) = D_8007386C;
    FIELD(partC, s32, 0) = 0;
    FIELD(partC, u8, 4) = 0;
    FIELD(partC, u8, 5) = 0;
    FIELD(object, void *, 0x74) = arg4;
    FIELD(object, u8, 0x78) = FIELD(arg4, u8, 1);
    FIELD(FIELD(node, void *, 0x20), s32, 0x34) =
        D_8006A90C[FIELD(FIELD(object, void *, 0x74), u8, 2)];
    }
}
