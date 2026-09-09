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

/* Updates global flags and stores the pointer selected by the source flags. */
void *func_8008EA40(void *state, void *unused_1, void *unused_2, void *source) {
    void *next_ptr;

    func_80099F70(*(s32 *)((u8 *)source + 0x5C));
    func_80099F04(*(s32 *)((u8 *)source + 0x5C));
    D_80083460.field2 |= 0x812;
    if (*(s32 *)((u8 *)source + 0x1C) & 0x100000) {
        next_ptr = D_8008EAC8;
    } else {
        next_ptr = &D_8008ACDC;
    }
    *(void **)((u8 *)state + 0x8C) = next_ptr;
    return next_ptr;
}
