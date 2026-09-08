#include "common.h"

typedef struct {
    u8 pad0;
    u8 field1;
    u8 pad2[6];
} Slot;

extern s32 D_80083780[];
extern Slot D_80082660[];
extern void func_800C5C3C(void);

void func_800C5BA8(void *arg0, s32 *arg1) {
    s32 target;
    s32 value;
    s32 value2;
    u16 timer;

    target = D_80083780[0];
    value = arg1[0];
    arg1[0] = value + ((target - value) / 2);
    target = D_80083780[1];
    value2 = arg1[1];
    arg1[1] = value2 + ((target - value2) / 2);

    timer = *(u16 *)((u8 *)arg0 + 0x6C) - 1;
    *(u16 *)((u8 *)arg0 + 0x6C) = timer;
    if ((s16)timer <= 0) {
        *(void (**)(void))((u8 *)arg0 + 0x54) = func_800C5C3C;
        D_80082660[*(s32 *)((u8 *)arg0 + 0x60)].field1 = 0;
    }
}
