#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_80082E80.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_80083460[3];
extern s16 D_80083228[5];
s32 func_800A2BDC();                          /* extern */
M2C_UNK func_800A48F0();    /* extern */
s32 func_800A4ACC();                      /* extern */
extern u8 D_801741D4[8];


typedef struct S_80F60808_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80F60808_1;   /* arg0 in func_80F60808 */


void func_80F60808(S_80F60808_1 *arg0, void *arg1, Rec_D_80082E80 *arg2, Rec_D_800E3D7C *arg3) {
    u16 *state = (u16 *)D_80083460;
    arg3->unk_71.as_u8 = (u8) (arg3->unk_71.as_u8 & 0x7F);
    if (!(state[1] & 0x2000) && ((func_800A2BDC(arg3) << 0x10) == 0)) {
        arg0->unk_9A = 0xD;
        arg0->unk_8C = 0;
        arg0->unk_9B = 0;
        arg2->unk_2C.as_pm = &D_801741D4;
        func_80047784(arg2, D_801741D4[(((s32) (*D_80083228 + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7)], 0);
        arg3->unk_1C.as_s32 = (s32) (arg3->unk_1C.as_s32 | 0x200);
        func_800A48F0(arg3, 1, 4);
        arg3->unk_44.at02_u16.v = (u16) (arg3->unk_44.at02_u16.v & 0x7FFF);
        func_800A4ACC(arg3);
        arg3->unk_6D.as_u8 = (u8) (arg3->unk_6D.as_u8 - 1);
        state[5] = (u16) (state[5] + 1);
    }
}
