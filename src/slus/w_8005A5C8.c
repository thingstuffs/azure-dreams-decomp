#include "common.h"

/* Builds a sound/SPU channel-parameter block on the stack (flags=0xF; two
   fields set to arg0<<7 / arg1<<7; two fields zeroed) and dispatches it to
   func_8005EDA0. */
typedef struct {
    s32 unk00;
    s16 unk04;
    s16 unk06;
    s16 unk08;
    s16 unk0A;
    s8  pad0C[0x1C];
} S_8005A5C8_Snd;

extern void func_8005EDA0(S_8005A5C8_Snd *arg0);

void func_8005A5C8(s32 arg0, s32 arg1)
{
    S_8005A5C8_Snd buf;

    buf.unk00 = 0xF;
    buf.unk04 = arg0 << 7;
    buf.unk06 = arg1 << 7;
    buf.unk08 = 0;
    buf.unk0A = 0;
    func_8005EDA0(&buf);
}
