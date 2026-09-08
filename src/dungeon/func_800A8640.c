#include "common.h"

typedef struct DungeonGateState {
    u16 unk0;
    u16 flags;
    u8 pad4[4];
    s16 active;
} DungeonGateState;

typedef struct DungeonOwner {
    u8 pad0[0x58];
    void *field58;
} DungeonOwner;

extern DungeonGateState D_80083460;
extern DungeonOwner *D_800814A8;

extern s32 func_8009A180(void *, void *);
extern s16 func_800ADE74(void *, void *, void *, s16, s16, s32);

s16 func_800ADDA0(void *arg0, void *arg1, void *arg2, s16 arg3, s16 arg4,
                   s32 arg5) {
    register u16 entityFlags ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s16 result = func_800ADE74(arg0, arg1, arg2, arg3, arg4, arg5);

    if (result && (result != 2) && (result != 3) &&
        ((D_80083460.active != 0) ||
         ((D_80083460.flags & 0x2808) != 0)) &&
        ((s16)func_8009A180(arg2,
                            (u8 *)D_800814A8->field58 + 0x20) != 0)) {
        register s16 returnValue ASM_REG("$2") = -1;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

        ASM_USE(returnValue);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        entityFlags = *(u16 *)((u8 *)arg2 + 0x46);
        entityFlags &= 0x7FFF;
        *(u16 *)((u8 *)arg2 + 0x46) = entityFlags;
        return;
        return returnValue;
    }
       /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    return result;
}

/* MECHANISM: The seed preserves the 0x28 frame, s0/s1 lifetimes, and noreturn tail call.
   An input-only pinned v0 materializes li -1; the shared-return scheduling fence prevents
   target-sll delay duplication, placing li at word 39 and retaining the tail store slot. */
