#ifndef GLOBALS_H
#define GLOBALS_H

/* Game globals accessed via $gp (small data). Each must be <= 8 bytes so the
 * compiler keeps it in small data and emits %gp_rel($gp) access, matching the
 * original -G8 build. Addresses are resolved by the linker from
 * config/generated/*.undefined_syms.txt. Names/types provisional. */

extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;

extern unsigned char D_80071298[];

extern volatile int D_80071250[];
extern int D_800712B4[];

extern int D_80084130[3];

extern short D_80084808[8];

extern struct S_80083178 D_80083178;
extern struct S_80083178State D_80083CE8;

#endif /* GLOBALS_H */
