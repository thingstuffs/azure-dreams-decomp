#include "common.h"

#include "common.h"

typedef struct {
    u8 pad00[0x4C];
    u8 f4C;
    u8 f4D;
    u8 f4E;
} S_80057A94;

typedef struct {
    u8 pad00[1];
    u8 x1;
    u8 pad2[4];
    u8 x6;
    u8 x7;
    u8 pad8[8];
    u16 h10;
    u16 h12;
} S_80057A94_cell;

typedef struct {
    s32 type;
    s32 f4;
    s16 x;
    s16 y;
    s32 fc;
    s32 f10;
    s32 f14;
} S_80057A94_msg;

extern s32 func_80057A50(void *arg0, s32 arg1);
extern s32 func_8005DA68(void);
extern void func_8005D88C(s32 arg0);
extern s32 func_8005DA88(void *arg0);

extern u8 D_8007382B[0x10];
extern void *jtbl_80032EA4[23];

void func_80057A94(S_80057A94 *arg0) {
    S_80057A94_cell *dst;
    S_80057A94_msg msg;
    u32 selector;
    static void *const keepalive[] = {
        &&L1, &&L2, &&L3, &&L4, &&L5, &&L6, &&L7, &&L8,
        &&L9, &&L10, &&L11, &&L12, &&L15, &&L16, &&L17, &&L18
    };

    dst = (S_80057A94_cell *)func_80057A50(arg0, arg0->f4D & 0xF);
    selector = arg0->f4C;
    if (selector >= 23) {
        goto L_default;
    }
    goto *jtbl_80032EA4[selector];

L1:
    dst->x1 = arg0->f4E;
    goto L_default;
L2:
    dst->x6 = arg0->f4E;
    goto L_default;
L3:
    dst->x7 = arg0->f4E;
    goto L_default;
L4:
    dst->h10 = (dst->h10 & 0xFF) | ((0x7F - arg0->f4E) << 8);
    goto L_default;
L5:
    dst->h10 = (dst->h10 & 0xFF) | ((0x7F - arg0->f4E) << 8) | 0x8000;
    goto L_default;
L6:
    dst->h10 = (dst->h10 & 0xFF0F) | ((arg0->f4E << 1) & 0xF0);
    goto L_default;
L7:
    dst->h10 = (dst->h10 & 0xFFF0) | (arg0->f4E >> 3);
    goto L_default;
L8:
    dst->h12 = (dst->h12 & 0x603F) | ((0x7F - arg0->f4E) << 6);
    goto L_default;
L9:
    dst->h12 = (dst->h12 & 0x603F) | ((0x7F - arg0->f4E) << 6) | 0x8000;
    goto L_default;
L10:
    dst->h12 = (dst->h12 & 0xFFC0) | ((0x7F - arg0->f4E) >> 3);
    goto L_default;
L11:
    dst->h12 = ((dst->h12 & 0xFFC0) | ((0x7F - arg0->f4E) >> 3)) | 0x20;
    goto L_default;
L12:
    if (arg0->f4E < 0x41) {
        dst->h12 |= 0x4000;
    } else {
        dst->h12 &= 0xBFFF;
    }
    goto L_default;
L15:
    if (func_8005DA68() == 1) {
        func_8005D88C(0);
    }
    if (arg0->f4E != 0) {
        msg.type = 1;
        msg.f4 = arg0->f4E;
        D_8007382B[0] = arg0->f4E;
        func_8005DA88(&msg);
        func_8005D88C(1);
    }
    goto L_default;
L16:
    msg.type = 6;
    msg.x = arg0->f4E << 8;
    msg.y = arg0->f4E << 8;
    func_8005DA88(&msg);
    func_8005D88C(1);
    goto L_default;
L17:
    msg.type = 0x10;
    msg.f10 = arg0->f4E;
    func_8005DA88(&msg);
    goto L_default;
L18:
    msg.type = 8;
    msg.fc = arg0->f4E;
    func_8005DA88(&msg);
L_default:
    return;
}
