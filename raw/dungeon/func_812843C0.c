#include "common.h"

/* This monster bank is the current-link bank at file 0x1277060 relinked
 * against an EARLIER resident layout: the two banks differ only in
 * relocated fields (engine calls +0x1200..+0x134C, resident data moved).
 * The same wrapper in the current-link bank is func_800F67A4
 * (src/dungeon/func_809217A4.c, file 0x9417A4 and its instances), which
 * calls func_800A56E0 and stores D_800DCF4D.  Evidence:
 * docs/evidence/r121_rem_opus.md. */

/* Encoded import 0x800A4398 = func_800A56E0 (src/dungeon/func_8009FF80.c)
 * in the shipped engine (+0x1348): one s32 argument in a0. */
extern void func_800A4398(s32 query_value);

/* Encoded resident byte 0x800DBB9D = D_800DCF4D in the shipped layout. */
extern s8 D_800DBB9D;

/* Calls func_800A4398 with 180 and sets D_800DBB9D to -1. */
void func_8016CBC0(void)
{
    func_800A4398(0xB4);
    D_800DBB9D = -1;
}
