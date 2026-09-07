#include "common.h"

typedef struct {
    u8 pad0;
    u8 field1;
    u8 pad2[6];
} Slot;

extern s32 D_80083780[];
extern Slot D_80082660[];
extern void func_800C5C3C(void);

/* Move coordinates halfway toward the target and advance state when the timer expires. */
void func_800C5BA8(void *state, s32 *coords) {
    s32 target;
    register s32 value ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    u16 timer;

    target = D_80083780[0];
    value = coords[0];
    coords[0] = value + ((target - value) / 2);
    target = D_80083780[1];
    value = coords[1];
    coords[1] = value + ((target - value) / 2);

    timer = *(u16 *)((u8 *)state + 0x6C) - 1;
    *(u16 *)((u8 *)state + 0x6C) = timer;
    if ((s16)timer <= 0) {
        *(void (**)(void))((u8 *)state + 0x54) = func_800C5C3C;
        D_80082660[*(s32 *)((u8 *)state + 0x60)].field1 = 0;
    }
}
