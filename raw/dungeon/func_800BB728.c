#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8003F270(void);
extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864();
extern void func_80098B38();
extern s32 func_800990FC(void);
extern s32 func_80099194();
extern void func_80099290();
extern s32 func_800992E8();
extern s32 func_80099734();
extern void func_800997FC();
extern void *func_800A05A4();
extern void func_800A5720();
extern s32 func_800A57B4();
extern void func_800A5F38();
extern void func_800A6480();
extern s32 func_800A94A0();
extern s32 func_800AD6FC();

extern u8 D_8006DE24[];
extern u8 *D_80073470[];
extern void *D_800814A8[];
extern u8 D_80082E80[];
extern u8 D_80083460[];
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u16 D_800DF4B0[];
extern u8 D_800E1440[];
extern u8 D_800E144C[];
extern u8 D_800E1456[];
extern u8 D_800E146F[];
extern u8 *D_800E3D7C[];

s32 func_800C0E88(void *arg0, void *arg1, s16 arg2, void *arg3)
{
    u8 *object;
    register u8 *data ASM_REG("$19");
    u8 *scan;
    u8 *record;
    u8 *status;
    u8 *current;
    u8 *tail_status;
    u8 *equal_object;
    u8 *callback;
    u8 *message_table;
    s32 message;
    s32 slot;
    s32 scan_slot;
    register s32 quotient ASM_REG("$2");
    s32 value;
    s32 x;
    s32 y;
    s16 timer;
    u32 flags;

    object = arg0;
    data = arg1;
    ASM_KEEP_NV(data);
    arg1 = arg3;
    ASM_KEEP_NV(arg1);

    if (arg2 == 13) {
        return func_80098864(data, arg1);
    }

    current = D_800E3D7C[0];
    if (object == current) {
        callback = D_80083780;
        ASM_KEEP_NV(callback);
        data[3] |= 0x20;
        equal_object = D_800E3D7C[0];
        FIELD(equal_object, u8 *, 0x110) = data;
        func_8008D344(equal_object, callback, D_80082E80, equal_object);
return_zero:
        ASM_SCHED_BARRIER();
        return 0;
    }

    if ((u32)object <= 0x9FFFFFFF) {
        func_800A6480(object, data);

        if (FIELD(data, s8, 2) >= 10 && data[0] < 16) {
            slot = ((data[0] - 1) * 3) + 1;
            if ((s16)func_800A57B4(object, slot) >= 0) {
                goto normal_finish;
            }
            message_table = D_8006DE24;
            scan = object;
scan_next:
            if (scan[8] == 0) {
                flags = FIELD(object, u32, 0x14);
                if (flags & 1) {
                    scan_slot = ((data[0] - 1) * 3) + 1;
                    goto set_scan_slot;
                } else if (flags & 2) {
                    scan_slot = ((data[0] - 1) * 3) + 2;
                    goto set_scan_slot;
                } else if (flags & 4) {
                    scan_slot = ((data[0] - 1) * 3) + 3;
set_scan_slot:
                    scan[8] = scan_slot;
                }

                quotient = FIELD(data, s8, 2);
                quotient /= 10;
                ASM_KEEP_NV(quotient);
                FIELD(scan, u8, 0xA) = quotient;
                FIELD(scan, u8, 9) = quotient;

                if (FIELD(object, u32, 0x14) & 0x4000) {
                    message = func_800990FC();
                    value = func_80099734(object, message);
                    value = func_80099194(D_800E1440, value);
                    value = func_80099194(
                        *(void **)(message_table + (scan[8] * 20)), value);
                    value = func_80099194(D_800E144C, value);
                    func_80099290(value);
                    func_800A5720(message);
                    goto normal_finish;
                }
                goto normal_finish;
            }

            scan += 3;
            if ((s32)scan >= (s32)object + 9) {
                goto normal_finish;
            }
            goto scan_next;
        }

        if (func_800AD6FC(object,
                          D_800DDE84[object[0x13]] & 3, 0) == 0) {
            func_800A5F38(object, data);
            return 1;
        }

normal_finish:
        func_80098B38(data);
        tail_status = (u8 *)0x80080000;
        ASM_KEEP_NV(tail_status);
        tail_status += 0x3460;
        goto decrement_status;
    }

    if (FIELD(data, s8, 2) == 0) {
        func_800997FC(D_800E1456);
        tail_status = D_80083460;
        data[3] &= 0xDF;
decrement_status:
        FIELD(tail_status, u16, 0xA)--;
        goto return_one;
    }

    FIELD(current, u16, 0x98) &= 0xFF7F;
    FIELD(object, u8, 9) = 0xFF;

    slot = (data[0] - 1) * 3;
    FIELD(object, u8, 8) = slot + 1;
    ASM_SCHED_BARRIER();
    flags = *(u16 *)(D_80073470[0] + (data[0] * 20));
    if (flags & 2) {
        FIELD(object, u8, 8) = slot + 2;
    } else if (flags & 4) {
        FIELD(object, u8, 8) = slot + 3;
    }

    record = FIELD(object, u8 *, -0x14);
    object = (u8 *)((u32)object & 0xDFFFFFFF);
    FIELD(object, void *, 0x60) = func_800A05A4(
        object, record[0x24], record[0x25], FIELD(object, s16, 0x2A), 16);
    ASM_SCHED_BARRIER();

    x = FIELD(object, s8, 0x72);
    y = FIELD(object, s8, 0x73);
    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }
    FIELD(object, s8, 0x72) = x;
    FIELD(object, s8, 0x73) = y;

    if (data[3] & 0x20) {
        if (func_800A94A0(object, object + 8, 0,
                          D_800E3D7C[0] + 0x98) == 0) {
            goto return_zero;
        }
        D_800DF4B0[0] = 16;
        data[3] &= 0xDF;
    }

    timer = D_800DF4B0[0] - 1;
    D_800DF4B0[0] = timer;
    if (timer >= 0) {
        return 0;
    }

    D_800DF4B0[0] = 0;
    if (func_8003F270() != 0) {
        return 0;
    }

    status = D_80083460;
    FIELD(status, void *, 0xC) = object;
    FIELD(D_800814A8[0], u16, 0x98) |= 0x80;
    FIELD(data, u8, 2)--;

    message = func_800990FC();
    value = func_800992E8(data, message);
    value = func_80099194(D_800E146F, value);
    func_80099290(value);
    func_800A5720(message);
    FIELD(status, u16, 0xA)--;
return_one:
    return 1;
}
