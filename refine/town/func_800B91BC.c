#include "common.h"

extern void func_800B67A4(void *arg0, void *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5);
extern void func_800B683C(void *arg0);
extern void func_800B68C8(void *arg0, s32 arg1, s32 arg2);

/* Initialize an object's position, internal links, and resource state. */
void func_800B691C(void *object, s32 entityId, s32 resourceIndex, s32 positionX, s32 positionY, s32 positionZ) {
    func_800B67A4((u8 *)object + 0x88, (u8 *)object + 0x60, (u8 *)object + 0x70, positionX, positionY, positionZ);
    func_800B683C(object);
    func_800B68C8(object, entityId, resourceIndex);
}
