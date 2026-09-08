#include "common.h"

extern void func_80099F04(s32);
extern void func_80099F70(s32);
typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[8];
} D_80083460_t;
extern D_80083460_t D_80083460;
extern u8 D_80096384[];

// Processes the source object's value, sets global flags, and assigns the destination object's data.
void func_80096A54(void *destinationObject, void *unused1, void *unused2, void *sourceObject) {
    func_80099F70(*(s32 *)((u8 *)sourceObject + 0x5C));
    func_80099F04(*(s32 *)((u8 *)sourceObject + 0x5C));
    D_80083460.field2 |= 0x812;
    *(void **)((u8 *)destinationObject + 0x8C) = D_80096384;
}
