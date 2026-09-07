#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 func_80047FD8(void *arg0);
extern void *func_8003C714(s32 arg0, void *arg1, s32 arg2);
extern void func_80040560(void *arg0, void *arg1);
extern void func_8007BEF0(s32 arg0);
extern void func_8007BFE0(void *arg0, s32 arg1);
extern void func_8007C040(void *arg0, void *arg1, s32 arg2);
extern s32 func_8040422C(void *arg0);
extern void func_80404224(void);
extern void func_80404254(void *arg0, s32 arg1);
extern void func_80404314(void *arg0, s32 arg1, s32 arg2);
extern void func_80404570(void *arg0);

extern u8 D_804005F8[];
extern u8 D_80400620[];
extern u8 D_8040861C[];
extern u8 D_8040A0F0[];

void func_80404364(s32 arg0, s32 arg1)
{
    u8 *record;
    u8 *body;
    s32 offset;

    offset = arg1 * 0x360;
    record = D_8040A0F0 + offset;
    body = record + 0x20;

    if (arg1 >= 5) {
        func_8007C040(D_804005F8, D_80400620, 0x12B);
        func_8007BEF0(1);
    }
    if (arg1 < 0) {
        func_8007C040(D_804005F8, D_80400620, 0x12C);
        func_8007BEF0(1);
    }

    if (func_80047FD8(record) == 0) {
        record = func_8003C714(0, record, 0xD8);
        if (record == 0) {
            func_8007C040(D_804005F8, D_80400620, 0x12F);
            func_8007BEF0(1);
        }
        func_80040560(record, D_8040861C);
        goto initialize_body;
    }

    func_80404570(record);
    FIELD(record, u16, 0x1E) &= 0x7FFF;
    func_8007BFE0(body, 0x340);

initialize_body:
    func_80404254(body, 10);
    FIELD(record, void *, 0xC) = body + 0x1C8;
    FIELD(body, s32, 0x1D4) = func_8040422C(body + 0x1D8);
    func_80404314(body, arg0, arg1);
    {
        typedef void (*Callback)(void);
        u8 *owner;
        Callback callback;
        Callback fallback;

        fallback = func_80404224;

        if (arg0 != 0) {
            owner = record + (arg0 - arg0);
        } else {
            owner = record + arg0;
        }
        if (arg0 != 0) {
            callback = func_80404224;
        } else {
            callback = fallback;
        }
        FIELD(owner, Callback, 0x10) = callback;
    }
}
