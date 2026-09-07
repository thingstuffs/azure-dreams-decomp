#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef struct {
    s32 words[3];
} __attribute__((packed)) Packed12;

#define FIELD(expr, type, offset) (*(type *)((u8 *)(expr) + (offset)))

extern void *func_7003CF18();
extern void func_7010D230();
extern s32 D_80086AD8;
extern u16 D_80094422;
extern u8 D_800E0F20[16];
extern M2C_UNK D_8010CEE0;
extern Packed12 D_8010D40C;

void func_7FFEB1CC(void *arg0, s32 arg1, s32 arg2) {
    s16 timer;
    u16 life;
    void *obj;
    void *part;
    void *primitive;

    timer = FIELD(arg0, u16, 0x16) + 1;
    FIELD(arg0, u16, 0x16) = timer;
    if ((timer < 0x17) && (timer & 1)) {
        obj = func_7003CF18(0x212);
        if (obj != NULL) {
            func_7010D230(obj, arg0, arg1, arg2);
            FIELD(obj, s16, 0x3E) = 0x1E;
            FIELD(obj, s16, 0x40) = 0x1E;
            FIELD(obj, M2C_UNK *, 0x10) = &D_8010CEE0;

            primitive = FIELD(obj, void *, 8);
            FIELD(primitive, u16, 0xA) =
                FIELD(primitive, u16, 0xA) -
                (D_800E0F20[(u8)FIELD(FIELD(arg0, void *, 0), u8, 0x13)] >> 1);

            part = FIELD(obj, void *, 0xC);
            FIELD(obj, Packed12, 0x62) = D_8010D40C;
            FIELD(part, void *, 8) = (u8 *)obj + 0x62;
            FIELD(part, s16, 0x10) = 0x40;
            FIELD(part, s16, 0x1E) = 0x32C8;
            FIELD(part, s16, 0x1C) = 0x32C8;
            FIELD(part, s16, 6) = 0x64;
            FIELD(part, s32, 0xC) = 0;
        }
    }

    life = FIELD(arg0, u16, 0x1E) - 1;
    FIELD(arg0, u16, 0x1E) = life;
    if ((life << 0x10) <= 0) {
        u16 *counter = &D_80094422;
        u16 next_counter;

        FIELD(arg0, u16, -2) |= 0x8000;
        next_counter = *counter - 1;
        D_80086AD8 |= 0x8000;
        *counter = next_counter;
    }
}
