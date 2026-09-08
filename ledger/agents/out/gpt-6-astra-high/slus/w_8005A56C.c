#include "common.h"

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

/* Dispatches a mode-selected command containing two values scaled by 256. */
void func_8005A56C(s32 mode, s32 value_1, s32 value_2)
{
    S_8005A56C_Cmd command;
    s32 scaled_1 = (value_1 << 16) >> 8;
    s32 scaled_2 = (value_2 << 16) >> 8;

    if ((mode << 16) == 0) {
        command.unk00 = 0xC0;
        command.unk10 = scaled_1;
        command.unk12 = scaled_2;
    } else {
        command.unk00 = 0xC00;
        command.unk1C = scaled_1;
        command.unk1E = scaled_2;
    }
    func_8005EDA0(&command);
}
