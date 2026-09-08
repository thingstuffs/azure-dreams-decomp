#include "common.h"

typedef struct S_80079968 {
    volatile s32 unk0;
} S_80079968;

typedef struct D_80079968_wrap {
    S_80079968 *ptr;
    s32 pad[2];
} D_80079968_wrap;

extern D_80079968_wrap D_80079968;

/* Replaces status bits 0x70000 with 0x30000 when use_status_3 is nonzero, otherwise 0x50000. */
void func_8005D678(s32 use_status_3) {
    D_80079968.ptr->unk0 &= ~0x70000;
    if (use_status_3) {
        D_80079968.ptr->unk0 |= 0x30000;
    } else {
        D_80079968.ptr->unk0 |= 0x50000;
    }
}
