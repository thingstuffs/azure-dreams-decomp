#include "common.h"

extern void func_800A21DC(void);
extern s32 D_800814A0;

typedef struct Func800A4A20Object {
    void (*callback)(void);
    u8 pad04[0x3c];
    u8 *state;
} Func800A4A20Object;

void func_800A2180(Func800A4A20Object *arg0)
{
    u8 *state;

    state = arg0->state;
    if (state != 0 && *state == 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
        return func_800A21DC();
    }
    arg0->callback();
}
