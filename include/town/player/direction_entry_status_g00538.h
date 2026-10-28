#ifndef TOWN_PLAYER_DIRECTION_ENTRY_STATUS_G00538_H
#define TOWN_PLAYER_DIRECTION_ENTRY_STATUS_G00538_H
/* G00538: shared declarations for direction entry status. */
/* Original-file evidence (G00538): inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0464, PD:town/engine:800D046C. */

#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_D_800CFCB4.h"

typedef struct S_8009567C_0 {
    u8 pad_00[0x3A];
    u8 unk_3A;
} S_8009567C_0;

typedef struct S_8009567C_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_8009567C_1;

typedef struct S_8009567C_3 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_8009567C_3;

typedef struct S_80095760_0 {
    u8 pad_00[0x3A];
    u8 unk_3A;
} S_80095760_0;

typedef struct S_80095760_1 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80095760_1;

typedef struct S_80095760_2 {
    u8 pad_00[0x14];
    u8 unk_14;
} S_80095760_2;

extern s16 D_800D0464[4];
extern s32 D_800D046C[4];
extern s32 input_angle_with_offset(s32 unused, s32 angle_offset);

/* Functions defined in this translation unit. */
s32 select_an_available_entry_matching_direction_returns_status(void *record);
s32 get_status_active_entry_matching_direction(void *entries);

#endif
