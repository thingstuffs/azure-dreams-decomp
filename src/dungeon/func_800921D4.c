#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_8003DB94(void *arg0, void *arg1, s32 arg2);
extern void func_80042B68(void *arg0, s32 arg1);
extern void func_8008CBD4(void *arg0, void *arg1, void *arg2, void *arg3);
extern void func_80096384(void);
extern void func_80097A48(void) __attribute__((noreturn));
extern void func_800AD4D0(void *arg0);

extern s16 D_80083228[5];
extern s32 D_80083460[5];
extern void *D_800DD274[8];






void func_80097934(Rec_func_8008ACDC_arg0 *arg0, Rec_D_800E3D7C *arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    s32 value;
    s32 *global;

    if (arg0->unk_9B.as_u8 == 0) {
        func_800AD4D0(arg3);
        arg0->unk_9B.as_u8++;
    }

    if (arg2->unk_14.at00_u16.v & 0xE000) {
        arg2->unk_2C.as_pv = D_800DD274;
        func_8003DB94(
            arg2,
            D_800DD274[
                ((D_80083228[0] + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);

        global = D_80083460;
        value = global[4];
        if (value == (u32)((u8 *)arg3 - 0x20)) {
            global[4] = value & 0x7FFFFFFF;
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_28 == 0) {
            ((Rec_D_800E3D7C *)arg3)->unk_28 = 0;
            arg1->unk_14.as_s32 = 0;
            arg1->unk_10.at00_s32.v = 0;
            arg1->unk_0C.as_s32 = 0;
            func_80042B68(arg3, 10);
            func_8008CBD4(arg0, arg1, arg2, arg3);
            func_80097A48();
        }

        arg0->unk_96.as_s16 = 8;
        arg0->unk_8C.as_pv = func_80096384;
    }
}
