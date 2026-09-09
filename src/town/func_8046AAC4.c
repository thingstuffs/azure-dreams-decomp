#include "common.h"

#ifdef NON_MATCHING
#include <stdint.h>
typedef uintptr_t uptr;
#else
typedef unsigned long uptr;
#endif

typedef struct {
    u8 pad[0x10];
    void *records;
} TownObject;

extern u8 *D_8001E950;
extern s32 func_8001A79C(TownObject *arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_8001BAC4(TownObject *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (D_8001E950[5] == 1) {
        /* MATCH: Save store operands separately so call arguments retain their incoming registers. */
        register TownObject *saved_arg0 ASM_REG("$16") = arg0;
        register s32 saved_arg1 ASM_REG("$17") = arg1;
        *(s32 *)((saved_arg1 * 0x10) + (uptr)saved_arg0->records + 8) =
            func_8001A79C(arg0, arg1, arg2, arg3);
        return 0;
    }
    return 1;
}
