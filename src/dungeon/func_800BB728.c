#include "common.h"

typedef struct S_800C0E88_0 {
    u8 pad_00[0x110];
    u8 * unk_110;
} S_800C0E88_0;   /* equal_object in func_800C0E88 */

typedef struct S_800C0E88_1 {
    u8 pad_00[0x2];
    union { s8 s; u8 u; } unk_02;   /* accessed as both */
} S_800C0E88_1;   /* data in func_800C0E88 */

typedef struct S_800C0E88_2_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_800C0E88_2_pre;   /* the 0x14 bytes before object in func_800C0E88, addressed as object[-1] */

typedef struct S_800C0E88_2 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 unk_09;
    u8 pad_0A[0xA];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
} S_800C0E88_2;   /* object in func_800C0E88 */

typedef struct S_800C0E88_3 {
    u8 pad_00[0x9];
    u8 unk_09;
    u8 unk_0A;
} S_800C0E88_3;   /* scan in func_800C0E88 */

typedef struct S_800C0E88_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C0E88_4;   /* tail_status in func_800C0E88 */

typedef struct S_800C0E88_5 {
    u8 pad_00[0x98];
    u16 unk_98;
} S_800C0E88_5;   /* current in func_800C0E88 */

typedef struct S_800C0E88_6 {
    u8 pad_00[0xA];
    u16 unk_0A;
    void * unk_0C;
} S_800C0E88_6;   /* status in func_800C0E88 */

typedef struct S_800C0E88_7 {
    u8 pad_00[0x98];
    u16 unk_98;
} S_800C0E88_7;   /* D_800814A8[0] in func_800C0E88 */



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
    register u8 *data ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
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
    s32 quotient;
    s32 value;
    s32 x;
    s32 y;
    s16 timer;
    u32 flags;

    object = arg0;
    data = arg1;
    ASM_KEEP_NV(data);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    arg1 = arg3;
    ASM_KEEP_NV(arg1);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    if (arg2 == 13) {
        return func_80098864(data, arg1);
    }

    current = D_800E3D7C[0];
    if (object == current) {
        callback = D_80083780;
        data[3] |= 0x20;
        equal_object = D_800E3D7C[0];
        ((S_800C0E88_0 *)equal_object)->unk_110 = data;
        func_8008D344(equal_object, callback, D_80082E80, equal_object);
return_zero:
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        return 0;
    }

    if ((u32)object <= 0x9FFFFFFF) {
        func_800A6480(object, data);

        if (((S_800C0E88_1 *)data)->unk_02.s >= 10 && data[0] < 16) {
            slot = ((data[0] - 1) * 3) + 1;
            if ((s16)func_800A57B4(object, slot) >= 0) {
                goto normal_finish;
            }
            message_table = D_8006DE24;
            scan = object;
scan_next:
            if (scan[8] == 0) {
                flags = ((S_800C0E88_2 *)object)->unk_14;
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

                quotient = ((S_800C0E88_1 *)data)->unk_02.s;
                quotient /= 10;
                ((S_800C0E88_3 *)scan)->unk_0A = quotient;
                ((S_800C0E88_3 *)scan)->unk_09 = quotient;

                if (((S_800C0E88_2 *)object)->unk_14 & 0x4000) {
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
        ASM_KEEP_NV(tail_status);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        tail_status += 0x3460;
        goto decrement_status;
    }

    if (((S_800C0E88_1 *)data)->unk_02.s == 0) {
        func_800997FC(D_800E1456);
        tail_status = D_80083460;
        data[3] &= 0xDF;
decrement_status:
        ((S_800C0E88_4 *)tail_status)->unk_0A--;
        goto return_one;
    }

    ((S_800C0E88_5 *)current)->unk_98 &= 0xFF7F;
    ((S_800C0E88_2 *)object)->unk_09 = 0xFF;

    slot = (data[0] - 1) * 3;
    ((S_800C0E88_2 *)object)->unk_08 = slot + 1;
    flags = *(u16 *)(D_80073470[0] + (data[0] * 20));
    if (flags & 2) {
        ((S_800C0E88_2 *)object)->unk_08 = slot + 2;
    } else if (flags & 4) {
        ((S_800C0E88_2 *)object)->unk_08 = slot + 3;
    }

    record = ((S_800C0E88_2_pre *)object)[-1].unk_00;
    object = (u8 *)((u32)object & 0xDFFFFFFF);
    ((S_800C0E88_2 *)object)->unk_60 = func_800A05A4(
        object, record[0x24], record[0x25], ((S_800C0E88_2 *)object)->unk_2A, 16);
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */

    x = ((S_800C0E88_2 *)object)->unk_72;
    y = ((S_800C0E88_2 *)object)->unk_73;
    if (x < 0) {
        x = -x;
    }
    if (y < 0) {
        y = -y;
    }
    ((S_800C0E88_2 *)object)->unk_72 = x;
    ((S_800C0E88_2 *)object)->unk_73 = y;

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
    ((S_800C0E88_6 *)status)->unk_0C = object;
    ((S_800C0E88_7 *)(D_800814A8[0]))->unk_98 |= 0x80;
    ((S_800C0E88_1 *)data)->unk_02.u--;

    message = func_800990FC();
    value = func_800992E8(data, message);
    value = func_80099194(D_800E146F, value);
    func_80099290(value);
    func_800A5720(message);
    ((S_800C0E88_6 *)status)->unk_0A--;
return_one:
    return 1;
}
