#include "common.h"

extern void func_80099F04(s32);
extern void func_80099F70(s32);
typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[8];
} D_80083460_t;
extern D_80083460_t D_80083460;
extern u8 D_80096384[];

void func_80096A54(void *arg0, void *arg1, void *arg2, void *arg3) {
    func_80099F70(*(s32 *)((u8 *)arg3 + 0x5C));
    func_80099F04(*(s32 *)((u8 *)arg3 + 0x5C));
    D_80083460.field2 |= 0x812;
    *(void **)((u8 *)arg0 + 0x8C) = D_80096384;
}
