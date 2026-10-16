/* Relinked copy of town/func_80877FEC (func_80877FEC.c); its print interface slot is +0x64 (twin +0x68), otherwise retail differs only at relocation sites. */
#include "common.h"

typedef void (*PrintValue)(char *format, char *name, s32 value);

typedef struct PrintInterface {
    u8 pad_00[0x64];
    PrintValue print_value;
} PrintInterface;

extern PrintInterface *D_00000E68;
extern char D_00000710[];
extern char D_0000071C[];
extern char D_00000724[];
extern char D_0000072C[];
extern s32 D_00000D9C;
extern s32 D_00000DA0;

/* Print kind, mode, and scene/sequence number (sno) with their labels. */
void func_80000760(s32 kind)
{
    D_00000E68->print_value(D_00000710, D_0000071C, kind);
    D_00000E68->print_value(D_00000710, D_00000724, D_00000DA0);
    D_00000E68->print_value(D_00000710, D_0000072C, D_00000D9C);
}
