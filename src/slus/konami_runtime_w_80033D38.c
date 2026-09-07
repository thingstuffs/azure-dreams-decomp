#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_80033D38_0 {
    s32 unk_00;
} S_80033D38_0;   /* arg0 in func_80033D38; pointer addresses record offset 0xC */


s32 func_80033D38(void *arg0) {
    return ((S_80033D38_0 *)((u8 *)arg0 - 0xC))->unk_00 != 0;
}
