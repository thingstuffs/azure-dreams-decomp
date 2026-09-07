#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct SubObj {
    u8 pad[0x28];
    s16 f28;
} SubObj;

typedef struct Obj {
    /* 0x00 */ u8 pad00[4];
    /* 0x04 */ SubObj *slotsA[3];
    /* 0x10 */ SubObj *slotsB[2];
    /* 0x18 */ u8 f18[2];
    /* 0x1a */ s16 f1a;
    /* 0x1c */ s16 f1c;
    /* 0x1e */ s16 f1e;
    /* 0x20 */ s16 state;
    /* 0x22 */ u16 counter;
    /* 0x24 */ s16 f24;
    /* 0x26 */ u16 f26;
} Obj;

typedef struct {
    s32 pad0[2]; /* 0x00 */
    s32 a;       /* 0x08 */
    s32 pad1;    /* 0x0c */
    s32 b;       /* 0x10 */
} S_80083160;

extern S_80083160 D_80083160;
extern u8 D_80080A84[];
extern u8 D_80080A78[];
extern u8 D_80088930[];
extern u8 D_80012094[];
extern s32 D_800814A0[];

extern s32 func_80053428();
extern s32 func_80053604();
extern void func_80053da8();
extern void *func_8003fc64();
extern void func_8003d468();
extern void func_80040aa0();
extern void func_80089c24();

void func_800890EC(Obj *obj, s32 *arg1) {
    int dec;
    int i;
    u16 st;
    void *r;
    S_80083160 *p160 = &D_80083160;

    dec = obj->counter - 1;
    obj->counter = dec;

    switch (obj->state) {
    case 0:
        if (p160->b != 0) {
            obj->state = 16;
            return;
        }
        if ((s16) func_80053428((u8 *) obj + 24)) {
            obj->f26 &= ~1;
            obj->state = 1;
        }
        return;

    case 1:
        if (p160->a != 0) {
            obj->state = 16;
            return;
        }
        arg1[1] += 0xFFFEC000;
        if (*(s16 *) ((u8 *) arg1 + 6) >= 0) {
            return;
        }
        arg1[1] = 0;
        obj->counter = 105;
        obj->state = 2;
        return;

    case 2:
        if (p160->a != 0) {
            obj->state = 19;
            return;
        }
        if ((s16) dec > 0) {
            return;
        }
        for (i = 2; i >= 0; i--) {
            obj->slotsA[i]->f28 = 1;
        }
        for (i = 1; i >= 0; i--) {
            obj->slotsB[i]->f28 = 1;
        }
        obj->counter = 95;
        obj->state = 3;
        return;

    case 3:
        if (p160->a != 0) {
            obj->state = 19;
        }
        if ((s16) obj->counter > 0) {
            return;
        }
        obj->counter = 1800;
        obj->state = 4;
        return;

    case 4:
        if (p160->a != 0) {
            obj->counter = 1800;
        }
        if (p160->b & 0x1000) {
            obj->f24 = (s16) ((obj->f24 + 2) % 3);
        } else if (p160->b & 0x4000) {
            obj->f24 = (s16) ((obj->f24 + 1) % 3);
        }
        if (p160->b & 0x840) {
            func_80053da8(obj->f24 == 2 ? 1314 : 1306);
            obj->counter = 96;
            obj->state = 32;
            return;
        }
        if ((s16) obj->counter > 0) {
            return;
        }
        obj->state = 254;
        return;

    case 16:
        obj->f1a = 0;
        obj->f1c = 8;
        obj->state = 17;
        /* fallthrough */
    case 17:
        if ((s16) func_80053604((u8 *) obj + 24)) {
            arg1[1] = 0;
            obj->f1a = 0;
            obj->state = 18;
        }
        return;

    case 18:
        if ((s16) func_80053428((u8 *) obj + 24)) {
            obj->f1a = 0;
            obj->state = 19;
        }
        return;

    case 19:
        for (i = 2; i >= 0; i--) {
            obj->slotsA[i]->f28 = 16;
        }
        for (i = 1; i >= 0; i--) {
            obj->slotsB[i]->f28 = 2;
        }
        obj->counter = 1800;
        obj->state = 4;
        return;

    case 32:
        if ((s16) dec > 0) {
            return;
        }
        {
            u16 flags = obj->f26;
            D_80080A84[0] = 2;
            obj->f26 = flags | 1;
        }
        switch (obj->f24) {
        case 0:
            r = func_8003fc64(256);
            if (r == NULL) {
                st = 255;
                obj->state = st;
                break;
            }
            *(void **) ((u8 *) r + 16) = (void *) D_80088930;
            obj->state = 253;
            break;
        case 1: {
            u8 *page01;
            u16 a;
            u16 b;
            page01 = (u8 *) 0x80010000;
            a = 5;
            b = 2;
            func_8003d468();
            *(s16 *) (page01 + 0x2094) = a;
            *(u8 *) (page01 + 0x2D6E) = 0;
            *(s16 *) (page01 + 0x2098) = b;
            func_80040aa0(6);
            st = 255;
            obj->state = st;
            break;
        }
        case 2:
            obj->state = 253;
            func_80089c24();
            break;
        default:
            st = 255;
            obj->state = st;
            break;
        }
        return;

    case 253:
        D_80080A84[0] = 2;
        ((u16 *) obj)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;

    case 254: {
        u8 sel;
        D_80080A84[0] = 2;
        sel = D_80080A78[0];
        do {
        switch (sel & 7) {
        case 0:
        case 4:
            func_80040aa0(30);
            break;
        case 2:
        case 6:
            func_80040aa0(32);
            break;
        case 1:
            func_80040aa0(18);
            break;
        case 3:
            func_80040aa0(19);
            break;
        case 5:
            func_80040aa0(20);
            break;
        case 7:
            func_80040aa0(21);
            break;
        }
        } while (0);
        {
            u8 next = D_80080A78[0];
            u16 flags = obj->f26;
            obj->state = 255;
            next = (next + 1) & 7;
            flags |= 1;
            D_80080A78[0] = next;
            obj->f26 = flags;
        }
        return;
    }

    case 255:
        break;

    default:
        return;
    }
}
