#include "common.h"

typedef struct {
    u8 pad0[2];
    u16 field2;
    u8 pad4[6];
    s16 fieldA;
} D_80083460_t;

extern void func_80048A44(void *a0, u8 a1, s32 a2, s32 a3);
extern void func_8008E798(void);
extern void func_8008E85C(void *a0, u8 a1, s32 a2);
extern void func_8008E864(void);
extern void func_8008EA24(void);
extern void func_80099F04(s32 a0);
extern void func_80099F70(s32 a0);
extern s16 func_8009AF18(s16 a0, void *a1, void *a2, s32 a3);
extern void func_8009F644(void *a0, s32 a1, s16 a2, s32 a3);
extern void func_800A56E0(s32 a0);

extern u16 D_80013714[5];
extern s32 D_80081484[3];
extern s16 D_80083228[5];
extern D_80083460_t D_80083460;
extern s32 D_8008ACDC;
extern u8 D_8008EAC8[];
extern u8 D_800DCFD0[8];
extern u8 D_800DD048[8];
extern u8 D_800DD060[8];
extern u8 D_800DD0C8[8];
extern s32 D_800E3540[3];

void func_8008E700(u8 *arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    s16 result;
    s32 flags;
    s32 saved;
    s32 index;
    u16 count;
    u8 mode;
    u8 *child;

    mode = arg0[0x9B];
    if (mode == 1) {
        goto case_1;
    }
    if (mode < 2) {
        if (mode == 0) {
            goto case_0;
        }
        func_8008EA24();
        return;
    }
    if (mode == 2) {
        goto case_2;
    }
    func_8008EA24();
    return;

case_0:
    if (*(u16 *)(arg2 + 0x14) & 0x6000) {
        *(s32 *)(arg1 + 0x14) = 0xFFEA0000;
        if (*(s32 *)(arg3 + 0x1C) & 0x100000) {
            func_8008E798();
            return;
        }
        *(u8 **)(arg2 + 0x2C) = D_800DD048;
        index = ((D_80083228[0] + *(s16 *)(arg3 + 0x2A) + 0x100) >> 9) & 7;
        func_8008E85C(arg2, (*(u8 **)(arg2 + 0x2C))[index], 0);
    }
    return;

case_1:
    count = *(u16 *)(arg0 + 0x96) + 1;
    *(u16 *)(arg0 + 0x96) = count;
    if ((*(u16 *)(arg0 + 0xA2) & 0x10) && ((s16)count >= 4)) {
        *(s32 *)(arg1 + 0x14) = 0;
        if (*(s32 *)(arg3 + 0x1C) & 0x100000) {
            *(u8 **)(arg0 + 0x8C) = D_8008EAC8;
            func_8008E864();
            return;
        }
        *(u8 **)(arg2 + 0x2C) = D_800DD060;
        index = ((D_80083228[0] + *(s16 *)(arg3 + 0x2A) + 0x100) >> 9) & 7;
        func_80048A44(arg2, D_800DD060[index], 0, 1);
        arg0[0x9B]++;
        func_8008EA24();
        return;
    }

    if (((*(s32 *)(arg3 + 0x1C) & 0x300000) == 0x100000) &&
        !(D_80013714[0] & 1)) {
        result = func_8009AF18(*(s16 *)(arg3 + 0x2A), arg1, arg2, 8);
        if ((result << 16) != 0) {
            child = *(u8 **)(arg0 + 0x124);
            *(s32 *)(child + 0x1C) |= 0x200000;
            *(s32 *)(arg3 + 0x1C) |= 0x200000;
            *(s16 *)(*(u8 **)(arg0 + 0x124) + 0x8A) = result;
            *(u8 *)(*(u8 **)(arg0 + 0x124) + 0x84) = 0x78;
            *(u8 *)(*(u8 **)(arg0 + 0x124) + 0x85) = 2;
            func_8009F644(arg3, 0x30, *(s16 *)(arg0 + 0x96), 0);

            saved = D_80081484[0];
            D_80081484[0] = 0;
            *(s32 *)(arg3 + 0x1C) &= 0xFFEFFFFF;
            D_80083460.fieldA++;
            *(u8 **)(arg2 + 0x2C) = D_800DCFD0;
            D_800E3540[0] = saved;
            index = ((D_80083228[0] + *(s16 *)(arg3 + 0x2A) + 0x100) >> 9) & 7;
            func_80048A44(arg2, D_800DCFD0[index], 5, 1);
            func_800A56E0(0x512);
            func_8008EA24();
            return;
        }
    }
    return;

case_2:
    if ((*(u16 *)(arg2 + 0x14) & 0x6000) &&
        (D_80083460.fieldA == 0)) {
        flags = *(s32 *)(arg3 + 0x1C);
        if (flags & 0x200000) {
            *(s32 *)(arg3 + 0x1C) = flags & 0xFFDFFFFF;
            D_80083460.field2 |= 0x412;
            func_80099F70(*(s32 *)(arg3 + 0x5C));
            func_80099F04(*(s32 *)(arg3 + 0x5C));
        }
        *(s32 **)(arg0 + 0x8C) = &D_8008ACDC;
    }
}

