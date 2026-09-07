#include "common.h"

typedef struct S_80079968 {
    volatile s32 unk0;
} S_80079968;

typedef struct D_80079968_wrap {
    S_80079968 *ptr;
    s32 pad[2];
} D_80079968_wrap;

extern D_80079968_wrap D_80079968;

/* Clears status-flag bits 0x70000 on *D_80079968.ptr, then ORs in 0x30000
   (a0 != 0) or 0x50000 (a0 == 0). */
void func_8005D678(s32 a0) {
    D_80079968.ptr->unk0 &= ~0x70000;
    if (a0) {
        D_80079968.ptr->unk0 |= 0x30000;
    } else {
        D_80079968.ptr->unk0 |= 0x50000;
    }
}
