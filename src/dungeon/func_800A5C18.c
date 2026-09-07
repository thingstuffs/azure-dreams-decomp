#include "common.h"

typedef struct {
    u8 pad00[0xA];
    u16 fieldA;
} D_80083460_t;

extern D_80083460_t D_80083460;
extern s32 func_800A2B04();

s32 func_800AB378(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 temp_v0;
    void *temp_v1;

    if (*(u16 *)((u8 *)arg2 + 0x14) & 0x8000) {
        *(s16 *)((u8 *)arg0 + 0x96) = 0;
    }
    if (*(s16 *)((u8 *)arg0 + 0x96) != 0) {
        temp_v1 = *(void **)((u8 *)*(void **)((u8 *)arg3 + 0x60) - 0x18);
        *(s32 *)((u8 *)arg1 + 0xC) = *(s32 *)((u8 *)temp_v1 + 0xC);
        *(s32 *)((u8 *)arg1 + 0x10) = *(s32 *)((u8 *)temp_v1 + 0x10);
    }
    temp_v0 = *(u16 *)((u8 *)arg0 + 0x96) - 1;
    *(s16 *)((u8 *)arg0 + 0x96) = temp_v0;
    if ((temp_v0 << 0x10) > 0) {
        return 0;
    }
    *(s32 *)((u8 *)arg1 + 0x14) = 0;
    *(s32 *)((u8 *)arg1 + 0x10) = 0;
    *(s32 *)((u8 *)arg1 + 0xC) = 0;
    func_800A2B04(arg1, *((u8 *)arg2 + 0x24), *((u8 *)arg2 + 0x25));
    *(u16 *)((u8 *)arg0 + 0x98) &= 0xFFF7;
    *(s32 *)((u8 *)arg3 + 0x1C) |= 0x40000000;
    D_80083460.fieldA -= 1;
    return 1;
}
