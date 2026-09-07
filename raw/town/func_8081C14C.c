#include "common.h"

#define S8(p, o)  (*(s8 *)((u8 *)(p) + (o)))
#define U8(p, o)  (*(u8 *)((u8 *)(p) + (o)))
#define S16(p, o) (*(s16 *)((u8 *)(p) + (o)))
#define U16(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(u8 **)((u8 *)(p) + (o)))

extern void func_800252B8();
extern void func_800267DC();
extern void func_80026978();
extern void *func_8003FC64();
extern void func_8004491C();
extern void func_80053DA8();
extern s32 rand();

extern u8 D_80026748[];
extern u8 D_80045340[];
extern s32 D_800814A0;
extern u8 D_80082E80[16];
extern s32 D_80083784;
extern u8 D_800F7950[];
extern u8 D_800F795C[];

void func_8002614C(void *in0, void *in1, void *in2)
{
    register u8 *arg0 ASM_REG("$19") = in0;
    register s32 *arg1 ASM_REG("$20") = in1;
    register u8 *arg2 ASM_REG("$16") = in2;
    register u8 *obj ASM_REG("$18");
    register u8 *owner ASM_REG("$21");
    s32 i;
    s32 x1;
    s32 x2;
    s32 x3;
    s32 x4;
    s32 r1;
    s32 r2;
    s32 r4;
    u16 type;
    u8 *p;
    u8 *node;
    u8 *vec;
    u8 *part;
    u8 *global;

    ASM_KEEP_NV(arg0);
    ASM_KEEP_NV(arg1);
    obj = PTR(arg0, 0);
    U16(obj, 0x58) |= 1;
    owner = PTR(obj, 0);

    if (S16(obj, 0x54) == 9 && S16(arg0, 0xC) == 1 && *arg1 <= 0x4DFFFFF) {
        switch (S16(obj, 0x56)) {
        case 0:
            U8(arg2, 0xC) = 0xFF;
            i = 3;
            do {
                func_800267DC(arg1);
                i--;
            } while (i >= 0);
            break;
        case 1:
            U16(arg2, 0x14) |= 0xC;
            i = 2;
            do {
                func_80026978(arg1);
                i--;
            } while (i >= 0);
            break;
        case 2:
            U16(arg2, 0x1E) += 0x200;
            U16(arg2, 0x1C) = U16(arg2, 0x1E);
            break;
        }
    }

    switch (S16(arg0, 0xC)) {
    case 0:
        if (S16(arg0, 0xE) == 0x10) {
            U16(obj, 0x58) |= 4;
        } else {
            U16(obj, 0x58) &= 0xFFFB;
        }
        U16(arg0, 0xE)--;
        if (S16(arg0, 0xE) > 0) {
            break;
        }
        func_80053DA8(0x518);
        U16(PTR(obj, 0), 0x12)++;
        S16(arg0, 0xC) = 1;
        U16(arg2, 0x14) &= 0xFF7F;
        break;

    case 1:
        S32(arg0, 4) += S32(arg0, 8);
        x1 = *arg1 + S32(arg0, 4);
        *arg1 = x1;
        if (x1 <= 0x427FFFF) {
            S16(arg0, 0xE) = 6;
            global = D_80082E80;
            if (U8(global, 0xC) >= 9) {
                S32(global, 0xC) -= 0x80808;
            }
            U16(arg2, 0x14) |= 0x80;
            func_80053DA8(0x506);
            S16(arg0, 0xC) = 2;
            break;
        }
        r1 = D_80083784 - arg1[1];
        if (r1 < 0) {
            r1 = -r1;
        }
        ASM_SCHED_BARRIER();
        if (r1 > 0x200000 || x1 > 0x43FFFFF || (U16(arg0, 0x10) & 4)) {
            break;
        }
        type = U16(owner, 0x16) - 3;
        if ((u32)type < 3) {
            func_80053DA8(0x513);
            S32(arg0, 4) = 0x180000;
            S16(arg0, 0xC) = 3;
            U16(arg0, 0x10) |= 4;
            U16(obj, 0x54)++;
            U16(PTR(obj, 0), 0x14) += 2;
            if (S16(obj, 0x54) == 10) {
                U16(PTR(obj, 0), 0x14) += 10;
            }
            break;
        }
        if ((u32)type >= 7) {
            break;
        }

        func_80053DA8(0x510);
        i = 1;
        U16(arg0, 0x10) |= 4;
        U16(PTR(obj, 0), 0x14)++;
        do {
            p = func_8003FC64(0x136);
            if (p != 0) {
                PTR(p, 0x10) = D_80026748;
                func_8004491C(p, D_80045340);
                vec = PTR(p, 8);
                part = PTR(p, 0xC);
                S32(vec, 0) = arg1[0];
                S32(vec, 4) = arg1[1];
                S32(vec, 8) = arg1[2];
                node = p + 0x20;
                S32(node, 4) = S32(arg0, 4);
                ASM_KEEP(node);
                PTR(p, 0x20) = obj;
                S16(part, 0x1E) = 0x1000;
                S16(part, 0x1C) = 0x1000;
                if (i != 0) {
                    PTR(part, 8) = D_800F795C;
                    S32(vec, 0x10) = 0x80000;
                } else {
                    PTR(part, 8) = D_800F7950;
                    S32(vec, 0x10) = 0xFFF80000;
                }
                U8(part, 4) = 0;
                U8(part, 5) = 0;
                S32(part, 0xC) = 0x00808080;
            }
            i--;
        } while (i >= 0);
        S16(arg0, 0xC) = 0xFF;
        break;

    case 2:
        i = 7;
        do {
            r2 = (rand() & 0xFF) - 0x80;
            x2 = *arg1 + (r2 << 14);
            func_800252B8(0, x2, arg1[1] + 0x80000,
                ((rand() % 80) << 16) + 0xFFB00000);
            i--;
        } while (i >= 0);
        goto common_countdown;

    case 3:
        U16(obj, 0x58) |= 2;
        x3 = *arg1 + S32(arg0, 4);
        *arg1 = x3;
        if (x3 > 0x55FFFFF) {
            S16(arg0, 0xE) = 5;
            func_80053DA8(0x50C);
            S16(arg0, 0xC) = 4;
        }
        break;

    case 4:
        i = 7;
        U16(obj, 0x58) |= 2;
        do {
            x4 = (((rand() & 0xFF) - 0x80) << 14) + 0x5600000;
            r4 = ((rand() & 0x3F) << 16) | 0xFFC00000;
            func_800252B8(0, x4, arg1[1] + 0x80000, r4);
            i--;
        } while (i >= 0);
common_countdown:
        U16(arg0, 0xE)--;
        if (S16(arg0, 0xE) <= 0) {
            S16(arg0, 0xC) = 0xFF;
        }
        break;

    case 0xFF:
        U16(obj, 0x58) &= 0xFFFE;
        U16(arg0, -2) |= 0x8000;
        D_800814A0 |= 0x8000;
        break;
    }
}
