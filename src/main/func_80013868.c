#include "shared/object_node.h"
#include "common.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 cardBootInitializeSaveMenuRequest(void *a0, s32 a1);
extern void cardBootEraseTemporaryFile(void);
extern void cardBootRefreshDirectorySummary(void);
extern s32 createOrResetSevenEntryMenuBackdrop(void *a0, s32 a1);
extern s32 func_80024D58(void *a0, s32 a1, s32 a2);
extern s32 mainCreateSaveHeading(void *a0);
extern s32 D_800267C0[];

/* Allocate an object and initialize its state and dispatch table. */
void *cardBootCreateSaveSlotMenu(s32 init_value, s32 state_value)
{
    void *object;
    void *state;

    object = func_8003FC64(0);
    if (object != NULL) {
        state = (u8 *)object + 0x20;
        *(s32 *)((u8 *)state + 0x24) = state_value;
        cardBootInitializeSaveMenuRequest(state, init_value);
        cardBootEraseTemporaryFile();
        cardBootRefreshDirectorySummary();
        *(s32 *)((u8 *)object + 0x20) = createOrResetSevenEntryMenuBackdrop(object, 0);
        *(s32 *)((u8 *)state + 4) = func_80024D58(object, *(s32 *)((u8 *)state + 0x2C), 3);
        *(s32 *)((u8 *)state + 8) = mainCreateSaveHeading(object);
        *(s32 *)((u8 *)state + 0x28) = 0;
        *(void **)((u8 *)object + 0x10) = D_800267C0;
    }
    return object;
}
