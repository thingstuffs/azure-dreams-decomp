#include "common.h"

extern void townClearEntityRecordFields(s32 record);
extern s8 D_80082669;
extern void *D_80097DE8[];

typedef struct {
    s32 unk0;
    void **unk4;
} Struct8009B228;

/* Initialize the target, assign the state table, and clear the global flag. */
void townInitializeTargetAndHandlerTable(Struct8009B228 *state, s32 target) {
    townClearEntityRecordFields(target);
    state->unk4 = D_80097DE8;
    D_80082669 = 0;
}
