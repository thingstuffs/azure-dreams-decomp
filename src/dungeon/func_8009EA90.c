#include "common.h"

extern s32 func_80042900(void *entity, s32 arg1);
extern s32 func_8009A350(s32 arg0, s32 arg1, s32 arg2, u16 *arg3);

#ifdef NON_MATCHING
#define LEGACY_KEEP(var) ((void)0)
#else
#define LEGACY_KEEP(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

s32 func_800A41F0(void *arg0) {
    u16 sp10;
    void *v1;
    register s32 result ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */

    if ((*(u8 *)((u8 *)arg0 + 0x28) + *(s16 *)((u8 *)arg0 + 0x64)) > 0) {
        if (*(s32 *)((u8 *)arg0 + 0x1C) & 0x2000) {
            v1 = *(void **)((u8 *)arg0 - 0x14);
            func_8009A350(*(u8 *)((u8 *)v1 + 0x24) - 1,
                          *(u8 *)((u8 *)v1 + 0x25), 0, &sp10);
            if (sp10 & 2) {
                return 0;
            }
        }
        if (!(*(s32 *)((u8 *)arg0 + 0x1C) & 0x290000)) {
            result = func_80042900(arg0, 0x1B) << 16;
            LEGACY_KEEP(result);
            return result == 0;
        }
        return 0;
    }
    return 0;
}
