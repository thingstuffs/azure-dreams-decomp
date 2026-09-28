#ifndef SHARED_SYS_FLAGS_H
#define SHARED_SYS_FLAGS_H

/* D_80013714: a system-wide u16 flag word in SLUS data, read by every binary but ovmovie (lhu 80 / sh 18 sites in
 * 62 rows, always offset 0).  Bits seen: 0x2 (set around callback replays in slus/w_80042560; the node allocators
 * func_8003FC64 / func_8003FD64 test it with their 0x200 flag), 0x8 and 0x10 (dungeon tests), 0x1 (dungeon
 * menus); cleared as & 0xFFF6 / & 0xFFF8.  The meaning of each bit is not proven, so the name stays D_. */
extern unsigned short D_80013714;

#endif
