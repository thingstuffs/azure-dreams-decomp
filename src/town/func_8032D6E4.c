#include "common.h"

extern void func_80019BC0(void);
extern void func_8001ACE8(s32 arg0);
extern u8 D_8001DCD4[];
extern u8 D_8001DD86[];
extern u8 D_8001DDA1[];

#ifndef NON_MATCHING
register s32 dispatch_result ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
#endif

void *func_80017EE4(s32 arg0, s32 arg1, s32 arg2) {
#ifndef NON_MATCHING
    dispatch_result = 1;
    if (arg2 == dispatch_result) {
#else
    if (arg2 == 1) {
#endif
        func_8001ACE8(0xD7A);
#ifndef NON_MATCHING
        dispatch_result = 0x80020000;
        dispatch_result -= 0x232C;
#else
        (void)D_8001DCD4;
#endif
        return;
    }
#ifndef NON_MATCHING
    dispatch_result = 3;
    if (arg2 != dispatch_result) {
        dispatch_result = 0x80020000;
        dispatch_result -= 0x227A;
#else
    if (arg2 != 3) {
        (void)D_8001DD86;
#endif
        return;
    }
#ifndef NON_MATCHING
    dispatch_result = 0x80020000;
    ASM_KEEP(dispatch_result);   /* MATCH pin: keeps a constant in a register as retail does */
#endif
    func_80019BC0();
#ifndef NON_MATCHING
    dispatch_result = 0x80020000;
    dispatch_result -= 0x225F;
    return (void *)dispatch_result;
#else
    return D_8001DDA1;
#endif
}
