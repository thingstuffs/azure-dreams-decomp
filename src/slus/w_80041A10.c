#include "shared/runtime_dispatch.h"
#include "common.h"
#include "shared/game_work.h"

typedef u32 OT_TYPE;

typedef struct FrameData {
    u8 raw[0x8D8];
} FrameData;

typedef struct OrderingTable {
    OT_TYPE ot[0x218];
} OrderingTable;


extern s32 D_8008148C;
extern s32 D_80081480;
extern FrameData D_801C9E40;
extern OrderingTable D_801DA784;

extern void func_8003FAD4(s32);
extern void func_800410FC(void);
extern OT_TYPE *ClearOTagR(OT_TYPE *, s32);
extern void SetDispMask(s32);
extern void func_8003F7E4(void);
extern void func_80040A88(s32);
extern void func_80041AB0(void);

/* Initializes frame data and ordering tables, then enables display output. */
void func_80041A10(void)
{
    s32 saved_state;

    D_80082E60.field_0 |= 1;
    saved_state = D_8008148C;
    do {
        D_80081480 = saved_state;
    } while (0);
    func_8003FAD4(saved_state);
    func_800410FC();
    gameWork.unk_000 = (s32)&D_801C9E40;
    ClearOTagR((OT_TYPE *)(D_801C9E40.raw + 0x70), 0x218);
    ClearOTagR(D_801DA784.ot, 0x218);
    {
        u8 *frame_data = (u8 *)((s32)gameWork.unk_000);
        *(void **)(frame_data + 0x8D0) = frame_data + 0x8D4;
    }
    SetDispMask(1);
    func_8003F7E4();
    func_80040A88((s32)func_80041AB0);
}
