#include "common.h"

extern s32 func_8009FF8C(s32 arg0, void *arg1);
extern void func_800A00E8(s32 arg0);
extern s32 func_800B28A0(void);
extern s32 D_8009ED7C;
extern u8 D_80100B3B;

/* Resets object state and passes the selected result to func_800A00E8. */
void func_8009EC70(void *object, void *status, void *context) {
    s32 result;
    *((s8 *)status + 0x15) = 0;
    *(s32 *)((u8 *)context + 0xC) = 0;
    *(s32 *)((u8 *)context + 0x10) = 0;
    *(s32 *)((u8 *)context + 0x14) = 0;
    *(s32 **)((u8 *)object + 0x50) = &D_8009ED7C;
    *(s16 *)((u8 *)object + 0x6C) = 0xA;
    if (*((u8 *)object + 0x4D) == 0x13) {
        result = D_80100B3B;
    } else {
        result = func_8009FF8C(func_800B28A0(), context);
    }
    func_800A00E8(result);
}
