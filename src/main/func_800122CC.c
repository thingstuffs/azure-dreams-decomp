#include "common.h"

typedef struct TableEntry_800252CC {
    s32 value;
    u8 pad04[0x7C];
} TableEntry_800252CC;

extern void cardBootShowLoadingProgress(void *, void *);
extern void cardBootShowNoSavedGameNotice(void *);
extern u8 D_80024FAC[];
extern u8 D_800252A4[];
extern u8 D_8002593C[];
extern TableEntry_800252CC D_80083E98[];

#define FIELD32(base, offset) (*(s32 *)((u8 *)(base) + (offset)))
#define FIELDP(base, offset) (*(void **)((u8 *)(base) + (offset)))

/* Selects the parent handler and initializes state based on the indexed table value. */
void cardBootBeginSelectedSlotLoad(void *state)
{
    s32 enabled;
    void *parent;

    parent = (u8 *)state - 0x20;
    if (D_80083E98[FIELD32(state, 0x28)].value != 0) {
        enabled = 1;
        FIELD32(state, 0x3C) = enabled;
        cardBootShowLoadingProgress(parent, (u8 *)state + 0x40);
        FIELD32(state, 0x40) = enabled;
        FIELDP(state, -0x10) = D_800252A4;
    } else {
        FIELDP(state, 0x34) = D_8002593C;
        cardBootShowNoSavedGameNotice(parent);
        FIELDP(state, -0x10) = D_80024FAC;
    }
}
