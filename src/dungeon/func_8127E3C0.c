#include "common.h"

/* This monster bank is the current-link bank at file 0x1271060 relinked
 * against an EARLIER resident layout: the two banks differ only in
 * relocated fields (engine calls +0x1200..+0x134C, resident data moved).
 * The same wrapper in the current-link bank is play_transition_sound_and_reset_status
 * (src/dungeon/func_809217A4.c, file 0x9417A4 and its instances), which
 * calls play_sound_if_enabled and stores D_800DCF4D.  Evidence:
 * docs/evidence/r121_rem_opus.md. */

/* Encoded import 0x800A4398 = play_sound_if_enabled (src/dungeon/func_8009FF80.c)
 * in the shipped engine (+0x1348): one s32 argument in a0. */
extern void func_800A4398(s32 query_value);

/* Encoded resident byte 0x800DBB9D = D_800DCF4D in the shipped layout. */
extern s8 D_800DBB9D;

/* Calls func_800A4398 with 180 and sets D_800DBB9D to -1. */
void call_engine_routine_and_reset_state(void)
{
    func_800A4398(0xB4);
    D_800DBB9D = -1;
}
