#include "common.h"

typedef u32 OT_TYPE;

typedef struct State16 {
    s32 field0;
    u8 pad4[12];
} State16;

typedef struct State12 {
    s32 field0;
    s32 pad4;
    s32 pad8;
} State12;

typedef struct FrameData {
    u8 raw[0x8D8];
} FrameData;

typedef struct OrderingTable {
    OT_TYPE ot[0x218];
} OrderingTable;

extern State16 D_80082E60;
extern volatile State12 D_8008148C;
extern volatile State12 D_80081480;
extern State16 D_80083160;
extern FrameData D_801C9E40;
extern OrderingTable D_801DA784;

extern void func_8003FAD4(s32);
extern void func_800410FC(void);
extern OT_TYPE *ClearOTagR(OT_TYPE *, s32);
extern void SetDispMask(s32);
extern void func_8003F7E4(void);
extern void func_80040A88(s32);
extern void func_80041AB0(void);

void func_80041A10(void)
{
    s32 value;

    D_80082E60.field0 |= 1;
    value = D_8008148C.field0;
    ASM_KEEP(value);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    D_80081480.field0 = value;
    func_8003FAD4(value);
    func_800410FC();
    D_80083160.field0 = (s32)&D_801C9E40;
    ClearOTagR((OT_TYPE *)(D_801C9E40.raw + 0x70), 0x218);
    ClearOTagR(D_801DA784.ot, 0x218);
    {
        u8 *p = (u8 *)D_80083160.field0;
        *(void **)(p + 0x8D0) = p + 0x8D4;
    }
    SetDispMask(1);
    func_8003F7E4();
    func_80040A88((s32)func_80041AB0);
}
