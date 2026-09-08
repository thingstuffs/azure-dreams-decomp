#include "common.h"

typedef struct {
    u8 pad[0x70];
    void *field_70;
    void *field_74;
} CleanupData;

typedef struct {
    u8 pad_00[0x1E];
    u16 flags;
    CleanupData cleanup;
} CleanupObject;

extern int D_800814A0;
extern void func_80026B44(void *arg0);
extern void func_8004B1A4(void *arg0);

/* Cleans up an object's resources and sets its object and global cleanup flags. */
void func_80026B94(CleanupObject *object)
{
    CleanupData *cleanup;

    if (object != 0) {
        cleanup = &object->cleanup;
        func_80026B44(cleanup->field_70);
        func_8004B1A4(cleanup->field_74);
        object->flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
