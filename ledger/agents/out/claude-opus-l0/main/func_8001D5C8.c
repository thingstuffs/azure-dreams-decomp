#include "common.h"

/* Address-taken via %hi/%lo — declare >8B so codegen uses lui+addiu, not gp. */
extern s32 D_80083840[];

void func_804045C8(void *arg0, s32 arg1) {
    void *temp_a0;

    if (arg0 != 0) {
        *(s32 *)((s8 *)arg0 + 0x1C0) = 0x808080;
        temp_a0 = *(void **)((s8 *)arg0 + 0x21C);
        if (arg1 != 0) {
            *(void **)temp_a0 = (void *)&D_80083840;
        } else {
            *(s32 *)temp_a0 = 0;
        }
        *(s16 *)((s8 *)(*(void **)((s8 *)temp_a0 + 4)) + 8) = 0x60;
        *(s16 *)((s8 *)(*(void **)((s8 *)temp_a0 + 4)) + 0xA) = 0x18;
    }
}
