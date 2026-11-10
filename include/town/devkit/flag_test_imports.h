#ifndef TOWN_DEVKIT_FLAG_TEST_IMPORTS_H
#define TOWN_DEVKIT_FLAG_TEST_IMPORTS_H
/*
 * Imports of the devkit flag-test scene program: the scene images at TOWN 0x7F4000-0x804000 linked at 0x80700000
 * and its low copies at TOWN 0x82D800-0x846000 (sub-images linked at 0x80700000, 0xA0700000, 0x80003000 and
 * 0x80000000; docs/evidence/town_prototypes_run7/owner_audit.md, devkit_8070_scenes and devkit_low_copies).
 * Several builds of one program: their calls target the devkit layout they were linked against (other builds'
 * windows at 0x8070xxxx / 0xA070xxxx, the BIOS-RAM 0x8000xxxx copies, a devkit town engine), which are
 * mid-function, data or nothing in the retail images.  Each import is declared once here with its address
 * spelling, so the call keeps its bytes.
 *
 * foreign-program: town 0x7F4000-0x804000; town 0x82D800-0x846000
 */
#include "common.h"

/* Imported declarations, one per address. */
void func_80000858(s32, s32);
void func_80000BC8(s32);
void func_80000C18(s32);
#ifndef AZ_FOREIGN_LOCAL_FUNC_80000C6C
s32 func_80000C6C(u16);
#endif
void func_80000DC8(void);
void func_807001B4(s32);
#ifndef AZ_FOREIGN_LOCAL_FUNC_80700244
void func_80700244(s32);
#endif
s32 func_80700304(s32, s32, s32, s32);
s32 func_8070042C(void);
void func_80700488(void);
#ifndef AZ_FOREIGN_LOCAL_FUNC_80700590
s32 func_80700590(s32, u8 *);
#endif
void func_80700674(void);
s32 func_807006AC(s32);
void func_807006FC(u16);
void func_807007D8(s32);
void func_80700804(s32);
void func_80700868(s32);
void func_80700894(s32);
void func_807008D0(s32, s32);
s32 func_807008FC(s32);
s32 func_80700928(s32);
void func_8070096C(s32, s32);
s32 func_80700A78(void);
void func_80700BC4(s32);
void func_80700BCC(void);
void func_80700C08(s32);
#ifndef AZ_FOREIGN_LOCAL_FUNC_80700C54
void func_80700C54(s32);
#endif
s32 func_80700C9C(s32);
void func_80700D58(s32, s32);
s32 func_80700D74(s32);
#ifndef AZ_FOREIGN_LOCAL_FUNC_80700D84
s32 func_80700D84(s32, s32, s32, s32);
#endif
s32 func_80700DC0(s16);
s32 func_80700E3C(void);
void func_80700E98(void);
void func_80700EB4(void);
void func_80700ED8(s32, s32);
s32 func_80700F98(s32);
#ifndef AZ_FOREIGN_LOCAL_FUNC_80701060
s32 func_80701060(s32 *, s32);
#endif
s32 func_8070114C(void);
void func_80701298(s32, s32);
s32 func_80701404(void);
void func_80702924(s32);
void func_80702A54(void);
/* --- end of imports --- */

#endif
