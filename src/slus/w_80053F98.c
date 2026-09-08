#include "common.h"

extern void func_8005A2FC(void);
extern void func_8005A39C(s32 arg0);
extern s32 func_8005A3F0(s32 a0);
extern void func_8005A420(void *a0, s32 a1, s32 a2);
extern void func_8005ACD0(s16 arg0);
extern s32 func_8005B378(s16 a0);
extern s32 func_8005E7E0(s32 a0);
extern void func_8005B320(void);
extern s32 func_8005B3D8(s16 a0, s16 a1);
extern void func_8005A5C8(s32 arg0, s32 arg1);
extern void func_8005A4E8(u8 a0, u8 a1, u8 a2);
extern void func_8005A56C(s32 arg0, s32 arg1, s32 arg2);
extern void func_80055B44(u8 a0);
extern void func_800559B4(void);
extern void func_80055864(void);
extern void func_800557BC(void);
extern void func_8005A37C(void);

extern u8 D_80084548[];

/* Initializes audio subsystems, buffers, and playback defaults. */
void func_80053F98(void) {
    func_8005A2FC();
    func_8005A39C(1);
    func_8005A3F0(0x18);
    func_8005A420(D_80084548, 1, 1);
    func_8005ACD0(0);
    func_8005B378(4);
    func_8005E7E0(4);
    func_8005B320();
    func_8005B3D8(0x3C, 0x3C);
    func_8005A5C8(0x7F, 0x7F);
    func_8005A4E8(0, 0, 0);
    func_8005A56C(0, 0, 0);
    func_80055B44(2);
    func_800559B4();
    func_80055864();
    func_800557BC();
    func_8005A37C();
}
