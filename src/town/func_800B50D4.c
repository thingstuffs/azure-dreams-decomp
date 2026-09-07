#include "common.h"

typedef struct {
    u8 bytes[4];
} FourBytes;

extern u8 D_800133BA;
extern FourBytes D_8008925C;

s32 func_800B2834(void) {
    FourBytes local;
    register u8 *source ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    s32 page;
    s32 i;
    s32 target;

    page = (s32)0x80090000;
    ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    source = (u8 *)(page - 0x6DA4);
    ASM_KEEP(source);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    __builtin_memcpy(&local, source, 4);
    ASM_KEEP(page);   /* MATCH pin: keeps a statement from moving across a call/branch */
    target = D_800133BA;
    i = 0;
    while (local.bytes[i] != 0) {
        if (local.bytes[i] == target) {
            break;
        }
        i++;
    }
    return i;
}

/* MECHANISM: A four-byte stack object supplies the 8-byte frame and unaligned block copy.
   Holding the 0x80090000 page in v0 through that copy and its derived base in a2
   forces the copy word into v1; an s32 cached target avoids the spurious andi. */
