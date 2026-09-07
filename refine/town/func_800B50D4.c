#include "common.h"

typedef struct {
    u8 bytes[4];
} FourBytes;

extern u8 D_800133BA;
extern FourBytes D_8008925C;

/* Returns the index of the target byte or the first zero in the copied four-byte table. */
s32 func_800B2834(void) {
    FourBytes searchBytes;
    register u8 *searchBytesSource ASM_REG("$6");   /* MATCH pin: retail register colouring depends on it */
    s32 searchBytesPage;
    s32 byteIndex;
    s32 targetByte;

    searchBytesPage = (s32)0x80090000;
    ASM_KEEP(searchBytesPage);   /* MATCH pin: keeps a statement from moving across a call/branch */
    searchBytesSource = (u8 *)(searchBytesPage - 0x6DA4);
    ASM_KEEP(searchBytesSource);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    __builtin_memcpy(&searchBytes, searchBytesSource, 4);
    ASM_KEEP(searchBytesPage);   /* MATCH pin: keeps a statement from moving across a call/branch */
    targetByte = D_800133BA;
    byteIndex = 0;
    while (searchBytes.bytes[byteIndex] != 0) {
        if (searchBytes.bytes[byteIndex] == targetByte) {
            break;
        }
        byteIndex++;
    }
    return byteIndex;
}
