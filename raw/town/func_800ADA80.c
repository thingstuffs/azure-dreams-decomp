#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef void (*Callback)(void *, s32, void *);

extern void func_80033D08(void);
extern s32 func_800352FC(void);
extern void func_800AAF5C(void);
extern void func_800AAFE0(void *, s32);
extern void func_800AB2F4(void);
extern void func_800AB3D0(void);
extern void func_800AB3E8(void);
extern void func_800C2C80(void *, void *, s32, s32);
extern void func_800C2CB0(void *, void *, void *, s8);
extern s32 func_800C2E1C(s16, s16);
extern s32 func_800C2F14(s16, s16);

extern s32 D_800814A0;
extern u8 D_80083160[];
extern s32 D_800834A8;
extern u8 D_80083780[];

void func_800AB1E0(void *arg0, s32 arg1, void *arg2) {
    u8 *base = D_80083160;
    s16 buf[12];
    u8 *ref;
    s32 idx;

    if (D_800834A8 == 0) {
        func_80033D08();
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        func_800AB3E8();
        return;
    }

    func_800AAFE0(buf, 0);
    ref = D_80083780;
    if (buf[1] != FIELD(ref, s16, 2) || buf[3] != FIELD(ref, s16, 6) ||
        buf[5] != FIELD(ref, s16, 10) || func_800352FC() != 0 ||
        (FIELD(base, s32, 8) & 0xF000) != 0) {
        func_800AAF5C();
        FIELD(arg0, s16, 0x90) = 0;
        func_800AB2F4();
        return;
    }

    FIELD(arg0, s16, 0x90) = FIELD(arg0, s16, 0x90) + 1;
    if (FIELD(arg0, s16, 0x90) > 100) {
        FIELD(arg0, s16, 0x90) = 100;
        ASM_SCHED_BARRIER();
    }
    FIELD(arg0, Callback, 0x50)(arg0, arg1, arg2);
    if ((FIELD(arg0, u16, -2) & 0x8000) != 0) {
        return;
    }

    idx = func_800C2E1C(FIELD(arg0, s16, 0x72), FIELD(arg0, s16, 0x64));
    if (FIELD(arg0, s16, 0x74) != idx) {
        func_800C2CB0(arg0, arg2, ((void **)FIELD(arg0, void *, 0x78))[idx],
                      FIELD(arg2, s8, 4));
        FIELD(arg0, s16, 0x74) = idx;
    }

    if ((FIELD(arg0, u8, 0x71) & 1) == 0) {
        if ((s16)func_800C2F14(FIELD(arg0, s16, 0x72),
                               FIELD(arg0, s16, 0x64)) == 0) {
            u16 cleared;
            cleared = FIELD(arg2, u16, 0x14) & 0xFFFE;
            ASM_TAILSLOT_PIN(cleared);
            func_800AB3D0();
            return;
        }
    } else {
        if ((s16)func_800C2F14(FIELD(arg0, s16, 0x72),
                               FIELD(arg0, s16, 0x64)) != 0) {
            u16 cleared;
            cleared = FIELD(arg2, u16, 0x14) & 0xFFFE;
            ASM_TAILSLOT_PIN(cleared);
            func_800AB3D0();
            return;
        }
    }

    FIELD(arg2, u16, 0x14) |= 1;
    ASM_SCHED_BARRIER();
    func_800C2C80(arg0, arg2, 0, 0);
}
