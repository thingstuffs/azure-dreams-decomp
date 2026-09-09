#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[8];
} D_80083460_t;

extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern D_80083460_t D_80083460;
extern s32 D_8008ACDC;
extern u8 D_8008EAC8[];

void *func_8008EA40(void *arg0, void *arg1, void *arg2, void *arg3) {
#ifndef NON_MATCHING
    register u8 *dead_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
#endif
    void *result;

    func_80099F70(*(s32 *)((u8 *)arg3 + 0x5C));
    func_80099F04(*(s32 *)((u8 *)arg3 + 0x5C));
    D_80083460.field2 |= 0x812;
    if (*(s32 *)((u8 *)arg3 + 0x1C) & 0x100000) {
#ifndef NON_MATCHING
        dead_v0 = (u8 *)0x80090000;
        ASM_KEEP(dead_v0);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        result = dead_v0 - 0x1538;
#else
        result = D_8008EAC8;
#endif
    } else {
        result = &D_8008ACDC;
    }
    *(void **)((u8 *)arg0 + 0x8C) = result;
    return result;
}
