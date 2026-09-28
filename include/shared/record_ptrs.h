#ifndef SHARED_RECORD_PTRS_H
#define SHARED_RECORD_PTRS_H

/* Global POINTERS to records, declared once with the record type the struct census already built for what they
 * point at (include/records/Rec_*.h - generated; include that header to dereference).  Each global is a single
 * pointer: every access in the pinned listings is a 4-byte lw/sw of the word itself (r78 phase 4 census), and the
 * rows' `void *X[3]` / `u8 *X[]` array spellings only ever used element 0.  Names stay address-based: what the
 * records are (an entity/actor record for D_800E3D7C: familiar owner slot +0x124, facing angle +0x2A) is not yet
 * proven well enough for a name.
 *   D_800814A8: 230 rows (dungeon, slus, town) - SLUS .bss, the word after objectFlagBlock's reserved bytes.
 *   D_800E3D7C: 190 rows (dungeon, slus)        - DUNGEON overlay .bss.
 *   D_80016000: 298 rows (dungeon, slus, town)  - below the SLUS image (0x80016000). */
struct Rec_D_800814A8;
struct Rec_D_800E3D7C;
struct Rec_D_80016000;
extern struct Rec_D_800814A8 *D_800814A8;
extern struct Rec_D_800E3D7C *D_800E3D7C;
extern struct Rec_D_80016000 *D_80016000;

#endif
