#include "common.h"

extern s32 func_800A0668(void *);
extern s32 func_800A0F10(void *arg0, void *arg1);
extern void func_800A0B74(void *arg0, s32 arg1);
extern void func_8009A8EC(s16 arg0, s16 arg1, s16 arg2);
extern void *D_800A08E8;

/* Check interaction conditions, apply the target value, and trigger a positional effect. */
void func_800A0AC8(void *actor, void *target, void *position) {
    if (*(s16 *)((u8 *)actor + 0x68) == 0) {
        if (func_800A0668(actor) != 0) {
            return;
        }
    } else {
        if (func_800A0668(actor) == 0) {
            return;
        }
    }
    if (func_800A0F10(actor, target) == 0) {
        return;
    }
    func_800A0B74(actor, *(s32 *)((u8 *)target + 0x48));
    *(void **)((u8 *)actor + 0x50) = &D_800A08E8;
    func_8009A8EC(*(s16 *)((u8 *)actor + 0x72), *(s16 *)((u8 *)position + 2), *(s16 *)((u8 *)position + 6));
}
