#include "common.h"

typedef struct S_8002593C_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    u8 pad_34[0x10];
    s32 unk_44;
    s32 unk_48;
} S_8002593C_0;   /* object in func_8002593C */



extern s32 D_80083160[];

extern void func_80053DA8(s32);
extern void func_80025D34(void *);
extern void func_80027AFC(s32, s32);
extern void func_8002592C(void *);
extern void func_800258C8(void *);
extern s32 func_80049DE8(s32, s32, s32);
extern void func_80025030(void *);
extern s32 func_8002168C(void);
extern void func_80021904(void);

void func_8002593C(u8 *object)
{
    s32 input;
    s32 flags;
    s32 new_input;
    s32 status;
    s32 value;
    s32 changed;
    s32 *controller;

    input = D_80083160[2];
    controller = D_80083160;
    status = 0;
    changed = status;
    if (input != 0) {
        flags = controller[4];
        if (flags & 0x20) {
            func_80053DA8(0x515);
            func_80025D34(object - 0x20);
            func_80027AFC(((S_8002593C_0 *)object)->unk_20, 0);
            goto epilogue;
        }
        if (flags & 0x40) {
            func_80053DA8(0x503);
            if (((S_8002593C_0 *)object)->unk_48 == 0) {
                func_8002592C(object);
                changed = 1;
                goto direction_check;
            }
            func_800258C8(object);
            goto direction_check;
        }
        if (input & 0x5000) {
            if (flags & 0x5000) {
                ((S_8002593C_0 *)object)->unk_30 = 0;
                flags = controller[4];
                if (flags & 0x1000) {
                    status = -1;
                } else if (flags & 0x4000) {
                    status = 1;
                }
            } else {
                value = ((S_8002593C_0 *)object)->unk_30;
                if (value >= 13) {
                    ((S_8002593C_0 *)object)->unk_30 = value - 4;
                    new_input = controller[2];
                    if (new_input & 0x1000) {
                        status = -1;
                    } else if (new_input & 0x4000) {
                        status = 1;
                    }
                } else {
                    ((S_8002593C_0 *)object)->unk_30 = value + 1;
                }
            }
            goto direction_check;
        }

        if (input & 0xA000) {
            if (input & 0x2000) {
                ((S_8002593C_0 *)object)->unk_48 = 1;
                changed = 1;
                goto direction_check;
            }
            ((S_8002593C_0 *)object)->unk_48 = 0;
            changed = 1;
        }

direction_check:
        if (status != 0) {
            func_80053DA8(0x502);
            if (((S_8002593C_0 *)object)->unk_48 == 1) {
                ((S_8002593C_0 *)object)->unk_28 =
                    func_80049DE8(((S_8002593C_0 *)object)->unk_28, status, 5);
            } else {
                ((S_8002593C_0 *)object)->unk_44 =
                    func_80049DE8(((S_8002593C_0 *)object)->unk_44, status, 3);
            }
            func_80025030(object);
        }
    }

    status = func_8002168C();
    func_80021904();
    if (status == 0) {
        goto changed_check;
    }
    if (status == 1) {
        goto changed_check;
    }

forced_tail:
    func_80025D34(object - 0x20);
    func_80027AFC(((S_8002593C_0 *)object)->unk_20, 0);

changed_check:
    if (changed != 0) {
        func_80025030(object);
    }
epilogue:
    return;
}
