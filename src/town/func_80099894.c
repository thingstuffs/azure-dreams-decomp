#include "common.h"

typedef struct {
    u8 unk0[0xC];
    s32 unkC;
    s32 unk10;
} TownObject;

extern void townUpdateStateLimits(TownObject *);
extern s32 townClampCoordinatesToBounds(TownObject *, void *);
extern s32 townPushPointToContainingEdges(TownObject *, void *);

/* Update the object and clear fields selected by the combined status flags. */
s32 townUpdateObjectAndClearStatusFields(TownObject *object) {
    void *object_data;
    s32 status_flags;

    townUpdateStateLimits(object);
    object_data = (u8 *)object + 4;
    status_flags = townClampCoordinatesToBounds(object, object_data);
    status_flags |= townPushPointToContainingEdges(object, object_data);
    if (status_flags & 0x11) {
        object->unkC = 0;
    }
    if (status_flags & 0x1100) {
        object->unk10 = 0;
    }
    return status_flags;
}
