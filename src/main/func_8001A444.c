#include "common.h"

extern s32 func_8007C9C8(s32 arg0);
extern s32 func_804014CC(void);

extern s32 D_80409270[];
extern s32 D_80409274[];
extern s32 D_80409278[];
extern s32 D_8040927C[];

#if !defined(NON_MATCHING) && __GNUC__ < 3
#define ASM_KEEP(value) \
    __asm__ __volatile__("" : "=r"(value) : "0"(value))
#else
#define LEGACY_ASM_KEEP(value) ASM_KEEP(value)
#endif

s32 func_8001A444(void) {
    s32 var_v0;
    s32 result;

    var_v0 = 0;
    if (func_8007C9C8(D_80409270[0]) != 0) {
        var_v0 = 1;
        result = func_804014CC();
        ASM_KEEP(var_v0);
        return result;
    }
    if (func_8007C9C8(D_80409274[0]) != 0) {
        var_v0 = 2;
        result = func_804014CC();
        ASM_KEEP(var_v0);
        return result;
    }
    if (func_8007C9C8(D_80409278[0]) != 0) {
        var_v0 = 3;
        result = func_804014CC();
        ASM_KEEP(var_v0);
        return result;
    }
    if (func_8007C9C8(D_8040927C[0]) != 0) {
        var_v0 = 4;
    }
    return var_v0;
}
