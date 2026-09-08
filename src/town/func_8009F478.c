#include "common.h"

extern void func_8009CB64(void *arg0, void *arg1, void *arg2, void *arg3);
extern s32 D_800F8B6C[];

/* Initialize the record, clear its counter, and set its flags. */
void func_8009CBD8(void *context, void *source, void *record) {
    func_8009CB64(context, source, record, &D_800F8B6C[0]);
    *(s16 *)((u8 *)record + 0x10) = 0;
    *(u16 *)((u8 *)record + 0x14) = *(u16 *)((u8 *)record + 0x14) | 0x1C;
}
