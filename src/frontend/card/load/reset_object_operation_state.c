#include "common.h"
#include "frontend/card/load.h"
#include "main/data.h"

extern s32 func_80406B9C(void *ptr);

void reset_object_operation_state(void *ptr) {
    if (*(s32 *)((u8 *)ptr + 0x38) != 0) {
        *(s32 *)((u8 *)ptr - 16) = (s32)&D_80406DA0;
        return;
    } else {
        func_80406B9C(ptr);
    }
}
