#include "common.h"

/* D_80085458[64]: stride 0x78 table; only fields f06 (dispatch index), f10, f12
   (params forwarded to func_800563B0) are touched by this function. */
typedef struct S_800564A8_85458 {
    /* 0x00 */ u8 pad00[6];
    /* 0x06 */ u16 f06;
    /* 0x08 */ u8 pad08[8];
    /* 0x10 */ u16 f10;
    /* 0x12 */ u16 f12;
    /* 0x14 */ u8 pad14[0x78 - 0x14];
} S_800564A8_85458;

/* D_80084960[16]: stride 0x9C table (canonical layout, reconciled with
   code8.c/w_80056A08.c siblings). This function only takes the address of an
   element (&D_80084960[f06]); no field of it is read/written here. */
typedef struct S_80084960 {
    s32 f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c;
    s8 f30; u8 pad31[9];
    s16 f3a; u8 pad3c[4];
    s16 f40; u8 pad42[2];
    s32 f44, f48; u8 pad4c[4];
    s16 f50; u8 pad52[0xD];
    s8 f5f, f60, f61; u8 pad62[2];
    s32 f64, f68; u8 pad6c[0xE];
    s8 f7a, f7b, f7c; u8 pad7d[3];
    s32 f80, f84; u8 pad88[0xC];
    s32 f94; s8 f98; u8 pad99[3];
} S_80084960;

extern s32 D_80073734[4];
extern S_800564A8_85458 D_80085458[64];
extern S_80084960 D_80084960[16];

extern void func_800561D8(S_800564A8_85458 *arg0, S_80084960 *arg1);
extern s32 func_800563B0(s32 a0, u16 a1, u16 a2);

/* Process each entry with a valid dispatch index using its dispatch record and parameters. */
void func_800564A8(void) {
    s32 entry_index;

    for (entry_index = 0; entry_index < D_80073734[0]; entry_index++) {
        if ((u16)D_80085458[entry_index].f06 < 0x10) {
            func_800561D8(&D_80085458[entry_index], &D_80084960[D_80085458[entry_index].f06]);
            func_800563B0(entry_index, D_80085458[entry_index].f10, D_80085458[entry_index].f12);
        }
    }
}
