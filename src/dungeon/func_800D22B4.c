#include "common.h"

typedef struct {
    u8 pad0[0xA];
    u16 field0xA;
    u8 pad0xC[0x14];
} D_80083460_t;

extern void *func_8003FD64(s32 arg0, void *arg1);
extern D_80083460_t D_80083460;
extern s32 D_80083498[4];
extern u8 D_800D7A78[];

// Creates an object, assigns its data and payload, and increments the object count.
void func_800D7A14(s32 objectPayload) {
    void *newObject;

    newObject = func_8003FD64(2, D_80083498);
    if (newObject != 0) {
        D_80083460.field0xA += 1;
        *(void **)((u8 *)newObject + 0x10) = D_800D7A78;
        *(s32 *)((u8 *)newObject + 0x2C) = objectPayload;
    }
}
