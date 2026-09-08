#include "common.h"

typedef struct {
    u8 pad00[0xC];
    u8 active;
    u8 pad0D;
    u8 flags;
} TownObject;

typedef struct {
    s32 pad00[12];
    void **slot30;
    void **slot34;
    s32 pad38[12];
    void **slot68;
    void **slot6C;
} TownState;

extern TownState D_80129728;
extern void **D_80129758[];
extern void **D_8012975C[];
extern u8 D_801285FC[];
extern u8 D_80128608[];

/* Set town slots from an active object's flags, or clear them when inactive. */
void func_80125730(TownObject *object)
{
    if (object->active != 0) {
        if (object->flags & 1) {
            *D_80129758[0] = D_801285FC;
        }
        if (object->flags & 2) {
            *D_8012975C[0] = D_80128608;
            return;
        }
    } else {
        TownState *state = &D_80129728;

        *state->slot30 = 0;
        *state->slot34 = 0;
        *state->slot68 = 0;
        *state->slot6C = 0;
    }
}
