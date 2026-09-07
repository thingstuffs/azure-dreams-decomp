#include "common.h"

typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_8008000A[];
extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E0F2D[];
extern u8 D_800E0F44[];
extern u8 D_800E0F65[];
extern u8 D_800E0F85[];
extern u8 *D_800E3D7C[3];

extern void func_80041E70(void *);
extern void func_8008D330(void *, void *, void *, void *);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern s32 func_80099290(s32);
extern s32 func_80099734(void *, s32);
extern void func_800997FC(void *);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A63B8(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern s32 func_800BDE34(void *);
extern s32 func_800BDE84(void *);
extern void func_800BDE98(void);
extern void func_800D5460(void *, u32, s32);

s32 func_800BDC98(void *arg0, s32 arg1, s16 arg2) {
    s16 state;
    s32 value;
    u16 table_value;
    u8 count;

    state = 0;
    if (arg0 == D_800E3D7C[0]) {
        *(s32 *)((u8 *)arg0 + 0x110) = arg1;
        func_8008D330(arg0, D_80083780, D_80082E80, arg0);
        func_800BDE98();
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFFU) {
        func_800A63B8(arg0, arg1, arg2);

        if (((u8 *)arg0)[0x25] == ((u8 *)arg0)[0x66]) {
            state = 1;
        }

        table_value = D_800DDE84[((u8 *)arg0)[0x13]];
        if ((func_800AD6FC(arg0, ((u32)table_value >> 8) & 3, arg1) << 16) == 0) {
            func_800A5F38(arg0, arg1);
            func_800BDE98();
            return 1;
        }

        if (state != 0) {
            count = ((u8 *)arg0)[4];
            if (count < 0xFF) {
                ((u8 *)arg0)[4] = count + 1;
                func_80041E70(arg0);
            }
        }

        if ((*(u32 *)((u8 *)arg0 + 0x14) & 0x4000) != 0) {
            if (state == 0) {
                if (((u8 *)arg0)[0x25] != ((u8 *)arg0)[0x66]) {
                    state = -1;
                }
            }

            value = func_800990FC();
            if (state < 0) {
                func_80099734(arg0, value);
                return func_800BDE34(D_800E0F2D);
            }
            if (state != 0) { /* state>=0 here, so !=0 <=> >0; matches retail beqz */
                ASM_CLOBBER("$4");   /* MATCH pin: retail basic-block layout depends on it */
                func_80099734(arg0, value);
                return func_800BDE34(D_800E0F44);
            }

            ASM_CLOBBER("$4");   /* MATCH pin: retail basic-block layout depends on it */
            func_80099290(func_80099194(D_800E0F65,
                                        func_80099734(arg0, value)));
            func_800A5720(value);
        }

        func_800D5460((u8 *)arg0 - 0x20, 0x20A0A0, 0x702);
        func_80098B38(arg1);
        return func_800BDE84((void *)0x80080000);
    }

    func_800997FC(D_800E0F85);
    func_800A56E0(0x506);
    D_80083460.field_A--;
    return 1;
}

/* MECHANISM: The natural C preserves retail's 40-byte frame and s0/s3/s2/s1 roles.
   Seam-local $a0 clobbers split the positive/zero call live ranges, retaining each
   move a0,s0 and collapsing the one-word branch-displacement cascade to exact. */
