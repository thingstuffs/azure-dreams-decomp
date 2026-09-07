#include "common.h"

typedef struct {
    s8 pad00[0xA8];
    s32 field_A8;
} Inner;

typedef struct {
    u8 pad00[0x1E];
    u16 flags;
    Inner inner;
} Object;

extern void func_8004B248(void *arg0);
extern void func_800B0318(s32 arg0);
extern s32 D_800814A0;

void func_800B03B4(Object *arg0)
{
    Inner *inner;

    if (arg0 != 0) {
        inner = &arg0->inner;
        func_8004B248((u8 *)arg0 + 0xCC);
        func_800B0318(inner->field_A8);
        arg0->flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
