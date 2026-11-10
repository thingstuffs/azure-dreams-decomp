#ifndef TOWN_DEVKIT_OLD_MINIGAME_IMPORTS_H
#define TOWN_DEVKIT_OLD_MINIGAME_IMPORTS_H
/*
 * Imports of the stale casino / betting / collection-round minigame image: TOWN 0x78B800-0x796000, built with
 * gcc 2.6.3 and linked at the devkit address 0x80526400 (docs/evidence/town_prototypes_run7/owner_audit.md).
 * Nothing loads it on retail; the same sectors sit unreferenced in the JP TOWN file.  Its absolute calls target
 * the devkit memory map it was linked against (a devkit executable at 0x8003xxxx-0x8007xxxx and an older town
 * engine linked high at 0x8023xxxx-0x8025xxxx): those addresses are mid-function, data or nothing in the retail
 * images, so no C body can own these names.  Each import is declared once here with its address spelling, so the
 * call keeps its bytes; a comment names the current function where the JP twin chain proves the identity.
 *
 * foreign-program: town 0x78B800-0x796000
 */
#include "common.h"

/* Imported declarations, one per address. */
#ifndef AZ_FOREIGN_LOCAL_FUNC_80034A1C
void func_80034A1C(void *, void *, s32);
#endif
void func_800351A8(s32, s32);
#ifndef AZ_FOREIGN_LOCAL_FUNC_800373DC
void *func_800373DC(s32);
#endif
void *func_800374FC(s32, void *);   /* current allocate_list_node (0x8003FD64; JP twin chain, town_prototypes_run7 owner audit) */
void func_8003B0B8(void *, void *);
void func_8003BC18(void *, void *);
void func_8003EA54(void *);
void func_8003F75C(s32);
void func_8003F8A8(s32);
void func_80050BD8(s32);
#ifndef AZ_FOREIGN_LOCAL_FUNC_80050BFC
void func_80050BFC(s32);
#endif
void func_80050D68(void *);
s32 func_80052374(s32);
void func_80058588(s32, s32, char *);
void func_8005888C(void);
#ifndef AZ_FOREIGN_LOCAL_FUNC_80058F88
void func_80058F88(s32);   /* current SD_Call (0x80053DA8; JP twin chain, town_prototypes_run7 owner audit) */
#endif
s32 func_8006AB90(s32);
s32 func_8006BC50(void *, void *, s32 *, s32 *);
void func_8006BFA0(void *, void *, void *, void *, void *, s32);
u32 func_8006D9DC(s32, s32, s32, s32);
void func_8006DBBC(void *, s32);
void func_8006DD38(void *);
void func_8006DD4C(void *);
void func_8006E590(s32);
void func_8006E854(s16 *, u8 *);
void func_8006E8B8(void *, void *);
void func_8006E91C(void *, s32, s32);
void func_8006F49C(void *, s32, s32, s32, s32);
s32 func_80071424(char *);   /* current strlen (0x80069E98; JP twin chain, town_prototypes_run7 owner audit) */
#ifndef AZ_FOREIGN_LOCAL_FUNC_80071494
s32 func_80071494(void);   /* current rand (0x80069EF8; JP twin chain, town_prototypes_run7 owner audit) */
#endif
s32 func_80232868(s32, s32, s32);
void func_80232A08(s32);
#ifndef AZ_FOREIGN_LOCAL_FUNC_8023FA58
void func_8023FA58(void *, void *, void *);
#endif
void func_8023FAE8(void *, void *, void *);
void func_8023FB18(void *);
s32 func_80240810(void *, void *, void *, void *);
s32 func_80243A38();
#ifndef AZ_FOREIGN_LOCAL_FUNC_802441A4
void func_802441A4(void *);
#endif
void func_80244588(void);
void func_802445FC(s32);
void func_80244660();
void func_80245C10(void *);
s32 func_802483B8();
void func_8024A884(void);
void func_8024A900(void);
s32 func_80252550(void *, void *);
void func_8028E170(void);
s32 func_80290318();
void func_80529438(void *, ...);
s32 func_8006A3A4(s32);
s32 func_8006A470(s32);
/* --- end of imports --- */

#endif
