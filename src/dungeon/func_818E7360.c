#include "common.h"

extern void func_80024C50(void) __attribute__((noreturn));
typedef struct {
    s32 value;
    s32 pad[2];
} GlobalFlags;

extern GlobalFlags D_800814A0;

#define S16_AT(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32_AT(p, o) (*(s32 *)((u8 *)(p) + (o)))

void func_80024B60(void *arg0)
{
    s32 state;
    u16 timer;
    u16 counter;
    void *object;

    object = *(void **)arg0;
    S32_AT(object, 0x10) |= 0x8000;

    state = S16_AT(arg0, 0x4C);
    timer = U16_AT(arg0, 0x4E) + 1;
    U16_AT(arg0, 0x4E) = timer;

    if (state == 1) {
        goto update_counter;
    }
    if (state >= 2) {
        goto state_at_least_2;
    }
    if (state == 0) {
        goto initialize;
    }
    func_80024C50();

state_at_least_2:
    if (state == 2) {
        goto state_2;
    }
    func_80024C50();

initialize:
    U16_AT(arg0, 0x4E) = 0;
    U16_AT(arg0, 0x48) = 0;
    S16_AT(arg0, 0x46) = 0x1F;
    S16_AT(arg0, 0x44) = 0x1F;
    U16_AT(arg0, 0x4C)++;

update_counter:
    counter = U16_AT(arg0, 0x48) + 1;
    U16_AT(arg0, 0x48) = counter;
    S16_AT(arg0, 0x4A) = (s16)counter * 0x30;

    if (S16_AT(arg0, 0x48) >= 4) {
        U16_AT(arg0, 0x4C)++;
        func_80024C50();
    }
    goto update_position;

state_2:
    if ((s16)timer >= 0xF) {
        U16_AT(arg0, -2) |= 0x8000;
        D_800814A0.value |= 0x8000;
    }

update_position:
    S16_AT(arg0, 0x40) = ((U16_AT(arg0, 0x4E) & 3) << 5) + 0x80;
    S16_AT(arg0, 0x42) = ((s16)U16_AT(arg0, 0x4E) >> 2) << 5;
}

/* MECHANISM: Zero-arg noreturn dispatcher calls trigger LEAD 18 tail jumps and LEAD 19 removal
   of the ra-only frame; natural arg0 liveness preserves the incoming pointer.
   Holding state as s32 selects retail's direct lh and avoids the two-word s16 promotion. */
