#include "common.h"

/* Builds a mode-tagged command block on the stack (mode 0xC0 or 0xC00 chosen by whether arg0's low 16 bits are nonzero) with two scaled s16 fields (arg1,arg2 sign-extended-then-<<8) placed at different offsets per mode, and dispatches it to func_8005EDA0. */
typedef struct {
    s32 unk00;
    s8  pad04[0x0C];
    s16 unk10;
    s16 unk12;
    s8  pad14[0x08];
    s16 unk1C;
    s16 unk1E;
    s8  pad20[0x08];
} S_8005A56C_Cmd;

extern void func_8005EDA0(S_8005A56C_Cmd *arg0);

void func_8005A56C(s32 arg0, s32 arg1, s32 arg2)
{
    S_8005A56C_Cmd buf;
    s32 t1 = (arg1 << 16) >> 8;
    s32 t2 = (arg2 << 16) >> 8;

    if ((arg0 << 16) == 0) {
        buf.unk00 = 0xC0;
        buf.unk10 = t1;
        buf.unk12 = t2;
    } else {
        buf.unk00 = 0xC00;
        buf.unk1C = t1;
        buf.unk1E = t2;
    }
    func_8005EDA0(&buf);
}
