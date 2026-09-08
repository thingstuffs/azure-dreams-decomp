#include "common.h"

extern s32 func_800198D0();

typedef struct {
    s32 value;
    s32 pad[2];
} D_80019BB0_t;

extern D_80019BB0_t D_80019BB0;

/* Set state 4 and return whether check 0x3FE fails or check 0x3FF succeeds. */
s32 func_80017AC4(void) {
    register s32 result ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 ret;

    D_80019BB0.value = 4;
    if (func_800198D0(0x3FE) == 0) {
        goto return_one;
    }
    result = func_800198D0(0x3FF);
    ASM_KEEP(result);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    ret = 0;
    if (result == 0) {
        goto done;
    }

return_one:
    ret = 1;

done:
    return ret;
}

/* MECHANISM: A guarded $v1 pin makes the second call result a distinct branch value.
   A shared return-one barrier preserves retail's branch CFG without emitting a word.
   The post-call ret local supplies $zero in the branch delay slot and avoids an s-reg. */
