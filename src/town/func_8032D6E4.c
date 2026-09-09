#include "common.h"

extern void func_80019BC0(void);
extern void func_8001ACE8(s32 arg0);
extern u8 D_8001DCD4[];
extern u8 D_8001DD86[];
extern u8 D_8001DDA1[];

#ifndef NON_MATCHING
register s32 dispatch_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

/* Dispatch the selected action and return its associated data pointer. */
void *func_80017EE4(s32 unused_1, s32 unused_2, s32 action) {
#ifndef NON_MATCHING
    dispatch_result = 1;
    if (action == dispatch_result) {
#else
    if (action == 1) {
#endif
        func_8001ACE8(0xD7A);
#ifndef NON_MATCHING
        dispatch_result = 0x80020000;
        dispatch_result -= 0x232C;
#else
        return D_8001DCD4;
#endif
    } else {
#ifndef NON_MATCHING
        dispatch_result = 3;
        if (action != dispatch_result) {
            dispatch_result = 0x80020000;
            dispatch_result -= 0x227A;
#else
        if (action != 3) {
            return D_8001DD86;
#endif
        } else {
#ifndef NON_MATCHING
            dispatch_result = 0x80020000;
            ASM_KEEP(dispatch_result);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#endif
            func_80019BC0();
#ifndef NON_MATCHING
            dispatch_result = 0x80020000;
            dispatch_result -= 0x225F;
               /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#else
            return D_8001DDA1;
#endif
        }
    }
#ifndef NON_MATCHING
    return (void *)dispatch_result;
#endif
}
