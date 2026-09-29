#ifndef SHARED_TOWN_ROOT_H
#define SHARED_TOWN_ROOT_H

/* struct Rec_D_80016000: the record TOWN rows reach through the pointer word D_80016000 (include/shared/record_ptrs.h
 * declares the pointer).  Observed uses of the address: TOWN rows load a pointer word from it; SLUS rows pass
 * &D_80016000 as a buffer to uploadImageTiles / func_800479D4; one DUNGEON row indexes a jump table at &D_80016000.
 * Hand-recovered (r79 phase 11) from the accesses made THROUGH D_80016000 in the town rows; it supersedes the generated
 * include/records/Rec_D_80016000.h for them.  The generated header's census class also merged other objects passed
 * as parameters (position records, handles, D_800DECF8...), which is where its x/y/z-like halves at +0x02/+0x06/+0x0A
 * came from; those rows keep the generated header.  "Accessed as both" unions resolved to one field type each (the
 * minority reads keep a cast at the use).  Names stay unk_ (no use pins a meaning yet); the pointees of unk_20 (a
 * record read up to +0x344) and unk_38 (a record whose +0x2D5C.. words are compared with thresholds) are the next
 * types to recover. */
typedef struct Rec_D_80016000 {
    /* 0x00 */ void *unk_00;                  /* pointer 21 / volatile int 2 / byte +3 2 */
    /* 0x04 */ unsigned int unk_04;           /* u32 3 / s32 2 */
    /* 0x08 */ int unk_08;                    /* s32 24: an index (scaled by 8 into the unk_40 table) */
    /* 0x0C */ unsigned char pad_0C[8];
    /* 0x14 */ int unk_14;
    /* 0x18 */ unsigned char pad_18[4];
    /* 0x1C */ void *unk_1C;                  /* pointer 42 / void ** 4 */
    /* 0x20 */ void *unk_20;                  /* pointer 75: a record read up to +0x344 */
    /* 0x24 */ void *unk_24;
    /* 0x28 */ void *unk_28;
    /* 0x2C */ void *unk_2C;
    /* 0x30 */ void *unk_30;                  /* int 3 (an address: cast back to s32 **) / int * 3 */
    /* 0x34 */ void *unk_34;
    /* 0x38 */ void *unk_38;                  /* pointer 37 / int 2 / s8 * 1 */
    /* 0x3C */ unsigned char pad_3C[4];
    /* 0x40 */ void *unk_40;                  /* int 19 (an address: `+ 0x68`, `+ index * 8`) / pointer 10 / u8 * 4 */
} Rec_D_80016000;

#endif
