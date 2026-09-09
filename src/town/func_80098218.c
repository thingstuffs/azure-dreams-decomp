#include "common.h"

typedef s32 M2C_UNK;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 unused[3];
} LocalRecord;

extern s16 func_8008C758(LocalRecord *, M2C_UNK *, s32, s32 *, s32, s32);
extern s16 func_8008CF48(LocalRecord *, s32 *);
extern M2C_UNK *D_800D0408;
extern s32 D_800FE5C0[];

/* Selects the smaller position query result, capped at 64, and writes its associated value. */
s32 func_80095978(s32 *position, s32 *out_value) {
    LocalRecord local_pos;
    s32 query_value;
    s32 *height_base;
    s32 *query_value_ptr;
    s32 result;
    s16 min_result;
    s16 candidate_result;

    height_base = D_800FE5C0;
    query_value_ptr = &query_value;
    local_pos.x = position[0];
    local_pos.y = position[1];
    local_pos.z = position[2] - height_base[5];
    min_result = func_8008CF48(&local_pos, query_value_ptr);
    *out_value = query_value;
    local_pos.x = position[0];
    local_pos.y = position[1];
    local_pos.z = position[2] - height_base[5];
    candidate_result = func_8008C758(&local_pos, D_800D0408, 4, query_value_ptr, min_result, *out_value);
    if (candidate_result < min_result) {
        min_result = candidate_result;
        *out_value = query_value;
    }
    if (min_result >= 64) {
        min_result = 64;
    }
    result = min_result;
    do {
        return result;
    } while (0);
}

/* MECHANISM: A 24-byte escaping record at sp+0x18 followed by the sibling
   output local at sp+0x30 creates retail's 0x50 frame.  The global height
   base and output-local address remain live across both external calls.
   A kept named return value prevents the final sign extension sinking. */
