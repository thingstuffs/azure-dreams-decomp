#ifndef SLUS_JTBL_80042BDC_H
#define SLUS_JTBL_80042BDC_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"
#include "shared/record_ptrs.h"
extern int D_800814A0;
#include "shared/dungeon_status.h"

typedef struct S_80042BDC {
    /* 0x00 */ u8   pad00[0x13];
    /* 0x13 */ u8   x13;
    /* 0x14 */ u32  x14;
    /* 0x18 */ u8   pad18[0x1C - 0x18];
    /* 0x1C */ u32  x1C;
    /* 0x20 */ u8   pad20[0x25 - 0x20];
    /* 0x25 */ u8   x25;
    /* 0x26 */ u8   pad26[0x60 - 0x26];
    /* 0x60 */ void *x60;
    /* 0x64 */ u8   pad64[0x71 - 0x64];
    /* 0x71 */ u8   x71;
    /* 0x72 */ u8   pad72[0x88 - 0x72];
    /* 0x88 */ s16  x88;
    /* 0x8A */ u16  x8A;
    /* 0x8C */ u8   pad8C[0x98 - 0x8C];
    /* 0x98 */ u16  x98;
    /* 0x9A */ u8   pad9A[0xA6 - 0x9A];
    /* 0xA6 */ u16  xA6;
    /* 0xA8 */ u8   xA8;
} S_80042BDC;

/* child object at *(ent - 0x14) */
typedef struct S_80042BDC_child {
    /* 0x00 */ u8  pad00[0x12];
    /* 0x12 */ s16 x12;
    /* 0x14 */ u8  pad14[0x24 - 0x14];
    /* 0x24 */ u8  x24;
    /* 0x25 */ u8  x25;
} S_80042BDC_child;


extern void *D_800E3DF0[32];

extern char D_800E1D55[];
extern char D_800E1D61[];
extern char D_800E1D80[];
extern char D_800E1D9F[];
extern char D_800E1DCF[];
extern char D_800E1DEE[];
extern char D_800E1E0D[];
extern char D_800E1E32[];
extern char D_800E1E4B[];
extern char D_800E1E6A[];
extern char D_800E1E8C[];
extern char D_800E1EC1[];
extern char D_800E1EF7[];
extern char D_800E1F1C[];
extern char D_800E1F41[];

typedef S_80042BDC *(*Ctor_80042BDC)(int a0, int a1, int a2, int a3);

extern void          *func_800990FC(void);
extern int            func_80099734(S_80042BDC *ent, void *ctx);
extern int            func_80099194(char *str, int arg);
extern int            func_80099290(int arg);
extern void           func_800A5720(void *ctx);
extern void           func_800AA53C(S_80042BDC *ent);
extern void           func_800D5460(void *p, int a1, int a2);
extern void          *func_800A1618(int a0, s16 a1);
extern void           func_8009A3D0(int a0, int a1, int a2);
extern Ctor_80042BDC  func_800A0B94(int a0, void *a1, int a2);
extern void           func_8003F320(void);
extern void           func_8004397C(S_80042BDC *ent);
extern void           func_80042710(S_80042BDC *obj, S_80042BDC *ent);
extern void           func_80042984(S_80042BDC *obj);
extern void           func_800A9A0C(S_80042BDC *obj);
extern int            func_800A1BD0(S_80042BDC *ent);
extern void           func_800AA888(S_80042BDC *obj, int a1, int a2, S_80042BDC *a3);
extern void           func_800AC82C(S_80042BDC *obj, int a1, int a2, S_80042BDC *a3);
extern void           func_800A32A4(S_80042BDC *ent);
extern void           func_8009A028(S_80042BDC *ent);
extern void           func_8009A21C(int a0, int a1, int a2);
extern void           func_800AA36C(S_80042BDC *ent, int a1, S_80042BDC_child *a2, S_80042BDC *a3);
extern void           func_80041E70(S_80042BDC *ent);

/* Dispatch entity actions, update flags, and create a replacement entity when requested. */

void func_80042BDC(S_80042BDC *ent, s16 action);

#endif
