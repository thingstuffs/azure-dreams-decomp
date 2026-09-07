#include "common.h"

typedef struct S_800BF074_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0xFC];
    s32 unk_110;
} S_800BF074_0;   /* arg0 in func_800BF074 */

typedef struct S_800BF074_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800BF074_1;   /* base in func_800BF074 */

typedef struct S_800BF074_2 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800BF074_2;   /* ((S_800BF074_1 *)base)->unk_04 in func_800BF074 */



typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_80082E80[];
extern s32 D_80082EB0[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u8 D_80089374[];
extern u16 D_800DDE84[];
extern u8 D_800E11F5[];
extern void *D_800E3D7C[];

extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern s32 func_80099368(void *, s32);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32);
extern void func_800A90E8(void *);
extern s32 func_800AD6FC(void *, s32, s32);

s32 func_800BF074(S_800BF074_0 *arg0, s32 arg1, s16 arg2, s32 arg3) {
    s32 *base;
    s32 temp_v0;
    s32 var_s1;

    if (arg2 == 0xD) {
        return func_80098864(arg1, arg3);
    }

    if (arg0 == D_800E3D7C[0]) {
        arg0->unk_110 = arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A6480(arg0, arg1);
        if (func_800AD6FC(arg0, D_800DDE84[arg0->unk_13] & 3, arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    } else {
        do {
            temp_v0 = func_800990FC();
        } while (0);
        base = D_80082EB0;
        var_s1 = temp_v0;
        temp_v0 = func_80099194(D_800E11F5, func_80099368(((S_800BF074_1 *)base)->unk_04, temp_v0));
        ((S_800BF074_2 *)(((S_800BF074_1 *)base)->unk_04))->unk_03 &= 0x7F;
        func_800A90E8(((S_800BF074_1 *)base)->unk_04);
        func_80099290(func_80099194(D_80089374, func_80099368(((S_800BF074_1 *)base)->unk_04, temp_v0)));
        func_800A5720(var_s1);
    }

    D_80083460.field_A--;
    func_80098B38(arg1);
    return 1;
}
