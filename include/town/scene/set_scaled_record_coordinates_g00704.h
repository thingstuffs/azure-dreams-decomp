#ifndef TOWN_SCENE_SET_SCALED_RECORD_COORDINATES_G00704_H
#define TOWN_SCENE_SET_SCALED_RECORD_COORDINATES_G00704_H
/* Set scaled record coordinates. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00704 - XB:town/func_8032FE28. */

#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "shared/dungeon_delay_views.h"

typedef struct S_8001A678_1 {
    void * unk_00;
} S_8001A678_1;

/* entry_ptr in set_position_from_tile_and_entry_offsets */
typedef struct S_8001A678_2 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
} S_8001A678_2;

typedef struct S_8001A704_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
} S_8001A704_0;

/* (void *)index in set_selected_entry_position */
typedef struct S_8001A704_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A704_1;

typedef struct S_8001A760_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    void * unk_1C;
    u8 pad_20[0x10];
    void ** unk_30;
} S_8001A760_0;

/* ctx in set_tile_center_destination */
typedef struct S_8001A760_1 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
} S_8001A760_1;

/* tile in set_tile_center_destination */
typedef struct S_8001A760_2 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A760_2;

typedef struct S_8001A7F4_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    void * unk_1C;
} S_8001A7F4_0;

/* base in set_scaled_destination_coordinates */
typedef struct S_8001A7F4_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001A7F4_1;

/* Functions defined in this translation unit. */
void set_scaled_record_coordinates(s32 unused, s32 x, s32 y);
void set_scaled_pointer_value(s32 value);
void set_position_from_tile_and_entry_offsets(s32 unused, u32 x, u32 y);
void set_record_scaled_auxiliary_values(s32 unused, s32 value_04, s32 value_08);
void set_selected_entry_position(s32 unused, s32 x, s32 y);
void set_tile_center_destination(s32 unused, s32 x_offset, s32 y_offset);
void set_scaled_destination_coordinates(s32 unused, s32 x, s32 y);

#endif
