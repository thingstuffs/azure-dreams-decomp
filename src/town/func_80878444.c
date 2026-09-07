/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK()
#define M2C_SYNC()

extern s32 D_80700000[];
extern s32 D_807014C8[];
extern s32 D_80701DC4[];
extern s32 D_80701DC8[];

extern void func_80702180(s32 index, s32 arg1);
extern void func_80702488(void) __attribute__((noreturn));

s32 func_80702444(void) {
    if (D_80701DC8[0] == 0) {
        register s32 value ASM_REG("$16");   /* MATCH pin: retail register colouring depends on it */

        value = *(s32 *)((u8 *)D_80700000 + (D_80701DC4[0] << 5) + 0x1E30);
        ASM_KEEP(value);   /* MATCH pin: retail basic-block layout depends on it */
        func_80702488();
    }

    {
        s32 value = (s32)D_807014C8;

        ASM_KEEP(value);   /* MATCH pin: retail basic-block layout depends on it */
        func_80702180(D_80701DC4[0], 1);
        return value;
    }
}
