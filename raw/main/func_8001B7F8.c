#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 D_801379A8;
extern s32 D_801379B0;
extern u8 D_80408ADE[];

extern s32 func_80056450(s32 arg0, s32 arg1, u8 arg2);
extern void func_80063FF8(s32 arg0);
extern void func_8040274C(void *arg0);
extern s32 func_8040343C(s32 arg0);

void func_804027F8(void *arg0)
{
    s32 input;
    s32 flags;
    s32 status;
    s32 value;

    input = D_801379A8;
    status = 0;
    if (input != 0) {
        arg0 = (u8 *)arg0 + 1;
        arg0 = (u8 *)arg0 - 1;
        flags = D_801379B0;
        if (!(flags & 0x40)) {
            if (flags & 0x20) {
                s32 result;
                s32 *destination;

                func_80063FF8(0x514);
                if (FIELD(arg0, s32 *, 0x20) != 0) {
                    result = func_8040343C(1);
                    destination = FIELD(arg0, s32 *, 0x20);
                    *destination = result;
                } else {
                    func_8040343C(1);
                }
            } else if (input & 0xA000) {
                if (flags & 0xA000) {
                    FIELD(arg0, s32, 0x10) = 0;
                    flags = D_801379B0;
                    if (flags & 0x8000) {
                        status = -1;
                    } else if (flags & 0x2000) {
                        status = 1;
                    }
                } else {
                    value = FIELD(arg0, s32, 0x10);
                    if (value >= 3) {
                        if (input & 0x8000) {
                            status = -1;
                        } else if (input & 0x2000) {
                            status = 1;
                        }
                    } else {
                        FIELD(arg0, s32, 0x10) = value + 1;
                    }
                }
            }
        }

        if (status != 0) {
            s32 result;
            s32 index;

            func_80063FF8(0x502);
            index = FIELD(arg0, s32, 8);
            result = func_80056450(
                FIELD(arg0, s32, 0), status, D_80408ADE[index * 4]);
            FIELD(arg0, s32, 0) = result;
            func_8040274C(arg0);
        }
    }
}
