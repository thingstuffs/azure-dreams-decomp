#include "common.h"

#define FIELD(base, type, offset) \
    (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(void);

extern void *func_8003FD64(s32 kind, void *owner);
extern void func_800A1D1C(void);
extern void func_800A1F00(void);
extern u8 D_80083498[];

/* Creates a display object with callbacks and the supplied payload values. */
void *func_800A1C94(s32 payload_word, s32 payload_halfword)
{
    void *object;
    void *display;
    void *payload;

    object = func_8003FD64(0x136, D_80083498);
    if (object == 0) {
        return 0;
    }

    FIELD(object, Callback, 0x10) = func_800A1D1C;
    display = FIELD(object, void *, 0xC);
    FIELD(object, Callback, 0x20) = func_800A1F00;

    payload = (u8 *)object + 0x20;
    FIELD(payload, s32, 0x10) = payload_word;
    FIELD(payload, s16, 0x20) = payload_halfword;

    FIELD(display, s16, 0x1E) = 0xAAA;
    FIELD(display, s16, 0x1C) = 0xAAA;
    FIELD(display, s16, 6) = 9;
    return object;
}
