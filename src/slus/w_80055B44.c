#include "common.h"

/* Canonical status-block struct at D_800847D0 (see src/w_800552C8.c, src/w_800553D4.c, etc). */
typedef struct S_800847D0 {
    u32 flags1;   /* 0x00 */
    u32 flags2;   /* 0x04 */
    u32 field8;   /* 0x08 */
    u32 fieldC;   /* 0x0C */
    u32 field10;  /* 0x10 */
    u32 field14;  /* 0x14 */
    u32 field18;  /* 0x18 */
    u8 pad1C[2];  /* 0x1C */
    s16 field1E;  /* 0x1E */
    s16 field20;  /* 0x20 */
    s16 field22;  /* 0x22 */
    u8 pad24[2];  /* 0x24 */
    s16 field26;  /* 0x26 */
    u8 field28;   /* 0x28 */
    u8 pad29[7];  /* 0x29 */
    s8 field30;   /* 0x30 */
    s8 field31;   /* 0x31 */
    s8 field32;   /* 0x32 */
    s8 field33;   /* 0x33 */
} S_800847D0;

extern S_800847D0 D_800847D0;

/* CD attenuator-volume struct, matches libcd.h CdlATV. */
typedef struct CdlATV {
    u8 val0;
    u8 val1;
    u8 val2;
    u8 val3;
} CdlATV;

extern void func_8005A3D4(void);
extern int func_8005A3E0(void);
extern int CdMix(CdlATV *vol);

/* Sets the CD-audio mix level: full volume (0x4F) + status bit 0x20 when a0==1,
   otherwise low volume (0x7F on L/R, 0 on the cross channels) + status bit 0x10,
   then applies it via CdMix. */
void func_80055B44(unsigned char a0) {
    CdlATV vol;

    if (a0 == 1) {
        func_8005A3E0();
        vol.val0 = vol.val2 = 0x4F;
        vol.val1 = vol.val3 = 0x4F;
        D_800847D0.flags1 = (D_800847D0.flags1 & ~0x10) | 0x20;
    } else {
        func_8005A3D4();
        vol.val0 = vol.val2 = 0x7F;
        vol.val1 = vol.val3 = 0;
        D_800847D0.flags1 = (D_800847D0.flags1 & ~0x20) | 0x10;
    }

    CdMix(&vol);
}
