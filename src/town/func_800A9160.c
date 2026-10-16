#include "common.h"
#include "shared/entity_objects.h"

typedef struct {
    s8 pad00[0x50];
    void (*callback)(void *, void *, void *, s32);
} Obj;
typedef struct { u8 pad00[0x15]; u8 flag15; } State;
typedef struct { s32 x, y, z, dx, dy, dz; } VecState;

extern void townInitializeObjectEntries(void *, s32, void *);
extern void townUpdateTargetFromPreviousState(void);
extern void townApplyPendingIndexedValue(s32, const char *);
extern void townSetFlaggedEntryValues(void *, const char *);
extern void townUpdateActorPositionAndHeading(void *, void *, void *, s32);
extern void *D_80100E28[];
extern u8 D_800D0D54[];
extern char D_800A630C[];
extern char D_800A62E8[];

/* Initialize object state and position, then invoke its new callback. */
void func_800A68C0(Obj *obj, State *state, VecState *motion, s32 callback_arg)
{
    s32 resource_arg;
    void *resource;

    resource_arg = callback_arg;
    state->flag15 = 0;
    resource = D_80100E28[0];
    motion->dx = 0;
    motion->dy = 0;
    motion->dz = 0;
    obj->callback = townUpdateActorPositionAndHeading;
    townInitializeObjectEntries(obj, resource_arg, resource);
    townUpdateTargetFromPreviousState();
    motion->x = D_80083780.x.v;
    motion->y = D_80083780.y.v;
    motion->z = D_80083780.z.v;
    townApplyPendingIndexedValue(0xE5, D_800A630C);
    townSetFlaggedEntryValues(D_800D0D54, D_800A62E8);
    townUpdateActorPositionAndHeading(obj, state, motion, callback_arg);
}
