#include "common.h"
#include "shared/object_node.h"

typedef struct {
    s32 unk0[4];
    void *field10;
} Func8003FF2CResult;

extern Func8003FF2CResult *initializeRuntimeNodeStorage(s32, s32 *, s16, s32 *);
extern void dungeonDispatchActionCallbackByOpcode(u8 *w);
extern s32 D_800E58B8[];

/* Create a record and assign dungeonDispatchActionCallbackByOpcode to its field10 pointer. */
void dungeonCreateRecordWithEffectCallback(void) {
    initializeRuntimeNodeStorage(0, D_800E58B8, 0x10, ((s32 *)(&D_80083498)))->field10 = dungeonDispatchActionCallbackByOpcode;
}
