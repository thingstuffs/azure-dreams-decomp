/* Relinked copy of town/func_80877FEC (func_80877FEC.c); its print interface slot is +0x64 (twin +0x68), otherwise retail differs only at relocation sites. */
#include "common.h"

typedef void (*PrintValue)(char *format, char *name, s32 value);

typedef struct PrintInterface {
    u8 pad_00[0x64];
    PrintValue print_value;
} PrintInterface;

extern PrintInterface *D_00004610;
extern char D_000034B0[];
extern char D_000034BC[];
extern char D_000034C4[];
extern char D_000034CC[];
extern s32 D_00003F50;
extern s32 D_00003F54;

/* Print kind, mode, and scene/sequence number (sno) with their labels. */
void print_scene_sequence_number_sno(s32 kind)
{
    D_00004610->print_value(D_000034B0, D_000034BC, kind);
    D_00004610->print_value(D_000034B0, D_000034C4, D_00003F54);
    D_00004610->print_value(D_000034B0, D_000034CC, D_00003F50);
}
