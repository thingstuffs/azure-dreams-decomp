#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80020984(void);
extern s32 func_8002219C(s32 arg0);
extern void func_8002316C(void *arg0);
extern void func_80024298(s32 arg0);
extern u8 D_80024F7C[];
extern u8 D_8002593C[];

void func_80025788(void *arg0) {
    u8 *cursor;
    s32 count;

    if (FIELD(arg0, s32, 0x38) != 0) {
        FIELD(arg0, void *, -0x10) = D_8002593C;
        return;
    }

    if (func_8002219C(FIELD(arg0, s32, 0x28)) != 0) {
        FIELD(arg0, void *, -0x10) = D_8002593C;
        count = 0;
        cursor = arg0;
        do {
            func_80024298(FIELD(cursor, s32, 4));
            cursor += 4;
            count++;
        } while (count < 5);
    } else {
        FIELD(arg0, void *, 0x34) = D_8002593C;
        func_8002316C((u8 *)arg0 - 0x20);
        FIELD(arg0, void *, -0x10) = D_80024F7C;
    }

    func_80020984();
    FIELD(arg0, s32, 0x40) = 0;
}
