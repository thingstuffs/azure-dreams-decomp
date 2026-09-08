#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E11FD[];
extern s32 D_800E296C;
extern u8 *D_800E3D7C;

extern void func_8008D344(void *, void *, void *, void *);
extern s32 func_80098864(s32, s32);
extern void func_80098B38(s32);
extern void func_800997FC(void *, s32, s16);
extern void func_8009D8A4(void);
extern void func_800A56E0(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);



s32 func_800BF210(Rec_D_800E3D7C *arg0, s32 arg1, s16 arg2, s32 arg3)
{
    if (arg2 == 13) {
        return func_80098864(arg1, arg3);
    }

    if (arg0 == D_800E3D7C) {
        arg0->unk_110 = arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, arg0);
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A6480(arg0, arg1, arg2);
        if (func_800AD6FC(arg0,
                          D_800DDE84[arg0->unk_10.at03_u8.v] & 3,
                          arg1) == 0) {
            func_800A5F38(arg0, arg1);
            return 1;
        }
    } else {
        func_800997FC(D_800E11FD, arg3, arg2);
        func_8009D8A4();
        D_800E296C |= 0x800000;
        func_800A56E0(0x80F);
    }

    D_80083460.field_A--;
    func_80098B38(arg1);
    return 1;
}
