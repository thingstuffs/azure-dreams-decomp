#include "common.h"

typedef s32 (*TownCallback)(s32);

extern void *D_80016000[];
extern u8 D_80016300[];
extern u8 D_800164EB[];

u8 *func_800168D4(void)
{
    u8 *message;

    message = (*(u8 *(**)(s32))((u8 *)*(void **)
        ((u8 *)D_80016000[0] + 0x20) + 0x2FC))(0);
    if (message != 0 && message[0] == 2 && message[1] == 0x13) {
        if ((*(TownCallback *)((u8 *)*(void **)
            ((u8 *)D_80016000[0] + 0x20) + 0x300))(0) == -1) {
            if (*(s32 *)((u8 *)D_80016000[0] + 8) != 0x29) {
                return D_80016300;
            }
        }
        if (*(s32 *)((u8 *)D_80016000[0] + 8) == 0x25) {
            return D_80016300;
        }
    }
    return D_800164EB;
}
