#include "common.h"

/* Arg-carrying sibcall member (config/sibcall_syms.txt): LEAD 22 jal->j + LEAD 23
 * ra-only frame elision yield retail's bare `j func_804045F8` with no stack frame. */
extern void func_804045F8(void *arg0);

/* Address-taken via %hi/%lo — declare >8B so codegen uses lui+addiu, not gp. */
extern s32 D_80083840[];

void func_8001D5C8(void *arg0, s32 arg1) {
    void *temp_a0;

    if (arg0 != 0) {
        *(s32 *)((s8 *)arg0 + 0x1C0) = 0x808080;
        temp_a0 = *(void **)((s8 *)arg0 + 0x21C);
        if (arg1 != 0) {
            *(void **)temp_a0 = (void *)&D_80083840;
            func_804045F8(temp_a0);
        } else {
            *(s32 *)temp_a0 = 0;
            /* Empty barrier: (1) blocks gcc from filling the preceding beqz-a1 delay
             * with `li v0,0x60` (retail leaves nop); (2) keeps `sw zero` before the
             * subsequent lw/li/sh schedule. */
            __asm__("");
            *(s16 *)((s8 *)(*(void **)((s8 *)temp_a0 + 4)) + 8) = 0x60;
            *(s16 *)((s8 *)(*(void **)((s8 *)temp_a0 + 4)) + 0xA) = 0x18;
        }
    }
}
