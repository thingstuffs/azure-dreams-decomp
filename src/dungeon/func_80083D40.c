#include "common.h"

typedef struct {
    u8 before_flags[0x1C];
    u32 flags;
} DungeonControl;
extern s32 D_800814A0;
extern u8 D_80080A86;
extern u16 D_80013714;
extern u8 D_80083160[];
extern DungeonControl *D_800814A8;
extern void runActiveNodeCallbacks(void);
extern void removeMarkedActiveNodes(void);
extern void integrateActiveNodeVectors(void);
extern void func_8004D70C(void);
extern void dungeonProcessCurrentFacingDirections(void);
extern void dungeonRenderMapCellMesh(void);
extern void dungeonDispatchObjectRenderers(void);
extern void appendDrawModePrimitive(void);
extern void dungeonQueueFramebufferStripQuads(void);

void func_800894A0(void) {
    u8 *work = D_80083160;
    runActiveNodeCallbacks();
    if (D_800814A0 & 0x8000) {
        removeMarkedActiveNodes();
    }
    D_800814A0 = 0;
    if (D_80080A86 == 0) {
        integrateActiveNodeVectors();
        if (D_80013714 & 2) {
            return;
        }
        if (*(s32 *)(work + 0x1DC) != 0) {
            func_8004D70C();
            dungeonProcessCurrentFacingDirections();
            if (!(D_800814A8->flags & 0x10)) {
                dungeonRenderMapCellMesh();
            }
        }
    }
    dungeonDispatchObjectRenderers();
    appendDrawModePrimitive();
    dungeonQueueFramebufferStripQuads();
}
