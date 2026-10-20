#ifndef SLUS_CD_COHORT_TYPES_H
#define SLUS_CD_COHORT_TYPES_H
#include "engine/scene/cd_state.h"

/* Observed driver prefix only; no enclosing allocation extent is asserted. */
typedef struct {
    u32 unk0;
    u8 unk4;
    u8 unk5;
    u16 counter1;
    u16 counter2;
    u16 flags;
} SlusCdDriverPrefix;
extern SlusCdDriverPrefix cd_driver_prefix[];

typedef struct {
    u8 unk00;
    u32 unk04;
    u8 unk08[15];
    u8 unk17;
} SlusCdQueueEntry;
extern SlusCdQueueEntry cd_command_records[32];
#endif
