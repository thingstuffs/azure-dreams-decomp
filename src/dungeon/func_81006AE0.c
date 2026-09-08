#include "common.h"
#include "records/Rec_D_800E3D7C.h"

typedef s32 M2C_UNK;


typedef struct S_801722E0_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_801722E0_1;   /* state in func_801722E0 */

typedef struct S_801722E0_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xC];
    void * unk_A8;
} S_801722E0_2;   /* arg0 in func_801722E0 */



extern M2C_UNK func_80047784();
extern s32 func_800990FC();
extern s32 func_80099194();
extern M2C_UNK func_80099290();
extern s32 func_80099734();
extern s32 func_800A2BDC();
extern M2C_UNK func_800A5720();

extern s16 D_80083228;
extern u8 D_80083460[12];
extern u8 D_80170838[16];
extern u8 D_80170848[16];
extern u8 D_80174880[9];

#line 1 "a"
void func_801722E0(void *arg0, void *arg1, void *arg2, void *arg3) {
    register void *call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 pass_value ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 saved_value ASM_REG("$16");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 result;
    u8 *state = D_80083460;

    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = (u8)(((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 & 0x7F);
    if (!(((S_801722E0_1 *)state)->unk_02 & 0x2000) &&
        ((func_800A2BDC(arg3) << 0x10) == 0)) {
        u8 *table = D_80174880;

        ((S_801722E0_2 *)arg0)->unk_9A = 0x17;
        ((S_801722E0_2 *)arg0)->unk_8C = 0;
        ((S_801722E0_2 *)arg0)->unk_9B = 0;
        (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(
            arg2,
            table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8)(((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
        ((S_801722E0_1 *)state)->unk_0A = (u16)(((S_801722E0_1 *)state)->unk_0A + 1);
        result = func_800990FC();
        call_arg = arg3;
        pass_value = result;
        saved_value = pass_value;
        func_80099290(func_80099194(
            D_80170848,
            func_80099734(((S_801722E0_2 *)arg0)->unk_A8,
                func_80099194(D_80170838,
                    func_80099734(call_arg, pass_value)))));
        func_800A5720(saved_value);
    }
}
