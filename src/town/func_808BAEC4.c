/* Relinked copy of town/func_80877FEC (func_80877FEC.c); its print interface slot is +0x64 (twin +0x68), otherwise retail differs only at relocation sites. */
#include "common.h"

typedef void (*PrintValue)(char *format, char *name, s32 value);

typedef struct PrintInterface {
    u8 pad_00[0x64];
    PrintValue print_value;
} PrintInterface;

extern PrintInterface *D_00001040;
extern char D_00000630[];
extern char D_0000063C[];
extern char D_00000644[];
extern char D_0000064C[];
extern s32 D_00000F08;
extern s32 D_00000F0C;

/* Print kind, mode, and scene/sequence number (sno) with their labels. */
void func_800006C4(s32 kind)
{
    D_00001040->print_value(D_00000630, D_0000063C, kind);
    D_00001040->print_value(D_00000630, D_00000644, D_00000F0C);
    D_00001040->print_value(D_00000630, D_0000064C, D_00000F08);
}
