#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80123200(s32);
extern void func_801232DC(void);
extern void func_801234F0(void);
extern void func_80123604(void);
extern void func_801237A4(void *);
extern void func_80124188(void *);
extern void func_8012656C(void *, void *, void *);

void func_80126620(void *arg0) {
    s32 one = 1;

    FIELD(arg0, s16, 0x04) = 0;
    FIELD(arg0, s16, 0x06) = 0;
    FIELD(arg0, s16, 0x08) = 0;
    FIELD(arg0, u8, 0x0A) = 0;
    FIELD(arg0, u8, 0x0B) = 0;
    FIELD(arg0, u8, 0x0C) = one;
    FIELD(arg0, u8, 0x0D) = 0;
    FIELD(arg0, u8, 0x0E) = 0;
    FIELD(arg0, u8, 0x0F) = 0;
    FIELD(arg0, u8, 0x10) = 0;
    FIELD(arg0, u8, 0x11) = 0;
    FIELD(arg0, u8, 0x12) = 0;
    FIELD(arg0, u8, 0x13) = 0;
    FIELD(arg0, u8, 0x14) = 0;
    FIELD(arg0, u8, 0x16) = 0;
    FIELD(arg0, u8, 0x17) = 0xFF;
    FIELD(arg0, u8, 0x18) = 0xFF;

    if ((func_80123200(0x31) & 0xFF) ||
        (func_80123200(0x30) & 0xFF)) {
        FIELD(arg0, u8, 0x15) = 0;
    } else {
        FIELD(arg0, u8, 0x15) = one;
    }

    func_8012656C((u8 *)arg0 + 0x48, (u8 *)arg0 + 0x20,
                  (u8 *)arg0 + 0x30);
    func_801237A4(arg0);
    func_80123604();
    func_801234F0();
    func_801232DC();
    func_80124188(arg0);
}
