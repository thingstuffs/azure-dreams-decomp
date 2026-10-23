#ifndef SHARED_TOWN_ROOT_H
#define SHARED_TOWN_ROOT_H

#include "shared/town_services.h"
#include "shared/town_state.h"
#include "shared/town_pointees.h"

/* struct Rec_D_80016000: the record TOWN rows reach through the pointer word D_80016000 (include/shared/record_ptrs.h
 * declares the pointer).  Observed uses of the address: TOWN rows load a pointer word from it; SLUS rows pass
 * &D_80016000 as a buffer to uploadImageTiles / func_800479D4; one DUNGEON row indexes a jump table at &D_80016000.
 * Hand-recovered (r79 phase 11) from the accesses made THROUGH D_80016000 in the town rows; it supersedes the generated
 * include/records/Rec_D_80016000.h for them.  The generated header's census class also merged other objects passed
 * as parameters (position records, handles, D_800DECF8...), which is where its x/y/z-like halves at +0x02/+0x06/+0x0A
 * came from; those rows keep the generated header.  "Accessed as both" unions resolved to one field type each (the
 * minority reads keep a cast at the use).  Names stay unk_ (no use pins a meaning yet); the pointees of unk_20 (a
 * record read up to +0x344) and unk_38 (a record whose +0x2D5C.. words are compared with thresholds) are described in
 * shared/town_services.h and shared/town_state.h (phase 12). */
/* Root of the currently loaded town scene image, reached through D_80016000.
 * Scene loading supplies this graph of service, position, progress and persistent-state pointers. */
typedef struct Rec_D_80016000 {
    /* 0x00 */ void *unk_00;                  /* pointer 21 / volatile int 2 / byte +3 2 */
    /* 0x04 */ unsigned int unk_04;           /* u32 3 / s32 2 */
    /* 0x08 */ int entry_index; /* selected scene-entry index, scaled by the table-specific stride by readers */
    /* 0x0C */ unsigned char pad_0C[8];
    /* 0x14 */ int unk_14;
    /* 0x18 */ unsigned char pad_18[4];
    /* 0x1C */ void *position; /* town position/auxiliary context, viewed as TownPositionState by scene callbacks */
    /* 0x20 */ TownServiceTable *services; /* town service callback table */
    /* 0x24 */ void *unk_24;
    /* 0x28 */ void *unk_28;
    /* 0x2C */ void *unk_2C;
    /* 0x30 */ void *unk_30;                  /* int 3 (an address: cast back to s32 **) / int * 3 */
    /* 0x34 */ void *unk_34;
    /* 0x38 */ TownStateRecord *town_state; /* town saved/list/history state, viewed as TownStateRecord */
    /* 0x3C */ unsigned char pad_3C[4];
    /* 0x40 */ void *event_data; /* town event/progress context; event entries are addressed with eight-byte stride */
} Rec_D_80016000;

#endif
