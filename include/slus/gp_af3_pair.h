#ifndef SLUS_GP_AF3_PAIR_H
#define SLUS_GP_AF3_PAIR_H

/* Present C interface; historical filename and TU boundary remain inferred. */
#include "common.h"

/* S_8006E704: array of pointers to a small struct whose only field this
 * function touches is a packed 32-bit "color/mode" word at offset 0 (top 9
 * bits = category, low 23 bits = an id taken from the ADDRESS of one of two
 * marker tables D_801C4640 / D_801BEE40, mirroring the func_8003F6D4 pack
 * idiom: (cat<<23) | (id & 0x7FFFFF)). */
typedef struct S_8006E704 {
    s32 field_0;
} S_8006E704;

extern S_8006E704 *D_8006E704[];
/* S_80080AF3 : a single scalar byte, gp-relative (<=8B). Kept a plain scalar
 * (not wrapped in a struct) because this function's only access is a bare
 * lb of the symbol itself, with no offset. */
extern s8 D_80080AF3;
/* D_80080AF4: 2-entry array of pointers into D_8006E704's entries, indexed by
 * the "current"/"toggled" slot selector D_80080AFC (0 or 1). Its TRUE finite
 * size (2, not an oversized/incomplete decl) is load-bearing for codegen --
 * see globals/learnings. */
extern S_8006E704 *D_80080AF4[2];
/* Declared oversized (>8B) so their ADDRESS is taken via %hi/%lo, matching
 * the target's lui/addiu pair (their contents are never dereferenced --
 * only the low 23 bits of the address itself are used as a packed id). */
extern s32 D_801C4640[4];
extern s32 D_801BEE40[4];

extern void func_800542BC(void);
extern void wait_until_sound_idle(void);
extern void func_80044698(void);
extern s32 load_sound_set(s16 mode);
extern s32 func_8004450C(s16 mode);
extern s32 Control_CD(s32 a0, void *a1, s32 a2);
extern void drain_cd_command_queue(void);
extern short SD_Call(int a0);

/* Selects a buffered entry, registering it with the slot marker and applying the requested mode. */

#include "common.h"

/* gp-relative scalar: current registered state index */
extern s8 D_80080AF3;

/* S_8006E6F4: array of 8-byte entries, indexed by state; forces %hi/%lo
 * addressing (accessed with a computed base + reused offsets). */
typedef struct {
    s32 field0; /* offset 0x0 */
    s32 field4; /* offset 0x4 */
} S_8006E6F4;
extern S_8006E6F4 D_8006E6F4[];

/* External words: current buffer write position and buffer base. */
extern s32 D_80081480;
extern s32 D_8008148C;

extern int Control_CD(int a0, void *a1, int a2);
extern void DrawSync(s32 a0);
extern void drain_cd_command_queue(void);
extern void func_8003F5E0(int a0);
extern short SD_Call(int a0);
extern void func_800542BC(void);
extern s16 test_sound_channel_availability(s16 n);

/* Register callbacks and complete a state transition, returning 1 if already current. */

s32 select_sound_stream(s16 entry_index, s16 mode);
s32 func_8004437C(s16 entry_index, s16 mode);
s32 load_sound_set(s16 state_index);
s32 func_8004450C(s16 state_index);

#endif
