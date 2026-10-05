#include "common.h"
#include "shared/object_node.h"

extern void *func_8003FD64();
extern s32 D_800C4E00[4];

/* Creates an object with the D_800C4E00 table and initializes its payload fields. */
void *func_800C4EB4(s32 unused0, s32 unused1, s32 unused2, s16 payloadValueA, s16 payloadValueC) {
    void *object;
    void *payload;

    object = func_8003FD64(0, ((s32 *)&D_80083498.next));
    if (object != 0) {
        *(s32 **)((s8 *)object + 0x10) = &D_800C4E00[0];
        payload = (s8 *)object + 0x20;
        *(s16 *)((s8 *)payload + 8) = 0x40;
        *(s16 *)((s8 *)payload + 0xA) = payloadValueA;
        *(s16 *)((s8 *)payload + 0xC) = payloadValueC;
    }
    return object;
}
