#include "common.h"
#include "records/Rec_D_800E3D7C.h"


typedef struct S_801720D8_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_801720D8_1;   /* arg0 in func_801720D8 */


typedef struct {
    u8 pad[0xA];
    u16 counter;
} State;


extern void func_80047784(void *, u8, s32);
extern s32 func_800A2BDC(void *);
extern s32 func_800A6D30(void);
extern s16 D_80083228;
extern State D_80083460;
extern u16 D_80083462;
extern u8 D_80174AE4[];

void func_801720D8(void *arg0, void *arg1, void *arg2, void *arg3) {
    register s32 value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    ((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 = (u8)(((Rec_D_800E3D7C *)arg3)->unk_71.as_u8 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2BDC(arg3) << 16) == 0)) {
        ((S_801720D8_1 *)arg0)->unk_8C = 0;
        ((S_801720D8_1 *)arg0)->unk_9A = 0x17;
        ((S_801720D8_1 *)arg0)->unk_9B = 0;
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 & 0x400) {
            value = ((Rec_D_800E3D7C *)arg3)->unk_14.as_s32;
            if (value >= 0) {
                ((Rec_D_800E3D7C *)arg3)->unk_14.as_s32 = (s32)(value | 0x80000000);
                ((Rec_D_800E3D7C *)arg3)->unk_2A.as_u16 = (u16)(((Rec_D_800E3D7C *)arg3)->unk_2A.as_u16 + ((func_800A6D30() & 7) << 9));
            }
        }
        ((S_801720D8_1 *)arg0)->unk_96 = 0;
        D_80083460.counter = (u16)(D_80083460.counter + 1);
        ((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 = (u8)(((Rec_D_800E3D7C *)arg3)->unk_6D.as_u8 - 1);
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174AE4;
        func_80047784(arg2, D_80174AE4[((D_80083228 + (s16)((Rec_D_800E3D7C *)arg3)->unk_2A.as_u16 + 0x100) >> 9) & 7], 0);
    }
}
