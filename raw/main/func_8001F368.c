#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 D_801379A8;
extern s32 D_801379B0;

extern void func_80063FF8(s32 arg0);
extern s32  func_80058FF0(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_804016D0(void);
extern void func_804018FC(void);
extern void func_80405AE8(void *arg0);
extern void func_804062F4(void *arg0);
extern void func_80406358(void *arg0);
extern void func_80406720(void *arg0);
extern void func_804083FC(s32 arg0, s32 arg1);

void func_80406368(void *arg0)
{
    s32 input;
    s32 flags;
    s32 dir;
    s32 status;
    s32 count;

    input = D_801379A8;
    dir = 0;
    status = 0;
    if (input != 0) {
        flags = D_801379B0;
        if (flags & 0x40) {
            func_80063FF8(0x515);
            func_80406720((u8 *) arg0 - 0x20);
            func_804083FC(FIELD(arg0, s32, 0x20), 0);
            return;
        } else if (flags & 0x20) {
            func_80063FF8(0x514);
            if (FIELD(arg0, s32, 0x48) == 0) {
                func_80406358(arg0);
                status = 1;
            } else {
                func_804062F4(arg0);
            }
        } else if (input & 0x5000) {
            if (flags & 0x5000) {
                FIELD(arg0, s32, 0x30) = 0;
                if (D_801379B0 & 0x1000) {
                    dir = -1;
                } else if (D_801379B0 & 0x4000) {
                    dir = 1;
                }
            } else {
                count = FIELD(arg0, s32, 0x30);
                if (count >= 13) {
                    FIELD(arg0, s32, 0x30) = count - 4;
                    if (D_801379A8 & 0x1000) {
                        dir = -1;
                    } else if (D_801379A8 & 0x4000) {
                        dir = 1;
                    }
                } else {
                    FIELD(arg0, s32, 0x30) = count + 1;
                }
            }
        } else if (input & 0xA000) {
            if (input & 0x2000) {
                FIELD(arg0, s32, 0x48) = 1;
            } else {
                FIELD(arg0, s32, 0x48) = 0;
            }
            status = 1;
        }

        if (dir != 0) {
            func_80063FF8(0x502);
            if (FIELD(arg0, s32, 0x48) == 1) {
                FIELD(arg0, s32, 0x28) = func_80058FF0(FIELD(arg0, s32, 0x28), dir, 5);
            } else {
                FIELD(arg0, s32, 0x44) = func_80058FF0(FIELD(arg0, s32, 0x44), dir, 4);
            }
            func_80405AE8(arg0);
        }
    }

    dir = func_804016D0();
    func_804018FC();
    if (dir != 0) {
        if (dir != 1) {
            func_80406720((u8 *) arg0 - 0x20);
            func_804083FC(FIELD(arg0, s32, 0x20), 0);
        }
    }
    if (status != 0) {
        func_80405AE8(arg0);
    }
}
