#include "common.h"

typedef struct {
    u8 pad_0[0x10];
    s32 field_10;
} State;

typedef struct {
    u8 pad_0[0x1C];
    s32 flags_1C;
} Entity;

typedef struct {
    u8 pad_0[0x24];
    u8 field_24;
    u8 field_25;
} Source;

extern State D_80083460[];
extern s32 D_800814A0[];
extern void func_800A32A4(Entity *);
extern void func_8009A3D0(u8, u8, s32);
extern void func_8009A028(Entity *);

void func_800B30E4(void *arg0, void *arg1, Source *arg2, Entity *arg3) {
    State *state = D_80083460;
    s32 value;
    u8 first;
    u8 second;

    if (state->field_10 == (s32)((u8 *)arg3 - 0x20)) {
        state->field_10 &= 0x7FFFFFFF;
    }
    func_800A32A4(arg3);
    first = arg2->field_24;
    second = arg2->field_25;
    value = 0x3000;
    if (arg3->flags_1C & 0x2000) {
        value = 0x300;
    }
    func_8009A3D0(first, second, value);
    func_8009A028(arg3);
    *(u16 *)((u8 *)arg3 - 2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}

/* MECHANISM: The four-slot ABI assigns source/entity to a2/a3, yielding the
   retail s1/s0 saved pair and 0x20 frame. Named byte locals make both call
   arguments live across the flag branch, exposing its load-delay schedule. */
