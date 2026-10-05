#include "common.h"

/* Address-taken via %hi/%lo — declare >8B so codegen uses lui+addiu, not gp. */
extern s32 D_80083840[];

void func_804045C8(void *basePtr, s32 flag) {
    void *targetPtr;

    if (basePtr != 0) {
        *(s32 *)((s8 *)basePtr + 0x1C0) = 0x808080;
        targetPtr = *(void **)((s8 *)basePtr + 0x21C);
        if (flag != 0) {
            *(void **)targetPtr = (void *)&D_80083840;
        } else {
            *(s32 *)targetPtr = 0;
        }
        *(s16 *)((s8 *)(*(void **)((s8 *)targetPtr + 4)) + 8) = 0x60;
        *(s16 *)((s8 *)(*(void **)((s8 *)targetPtr + 4)) + 0xA) = 0x18;
    }
}
