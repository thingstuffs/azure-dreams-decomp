#ifndef DUNGEON_OVL_16B08_F6A8_H
#define DUNGEON_OVL_16B08_F6A8_H
#include "common.h"
#include "m2c_compat.h"
typedef struct ovl_16b08_f6a8_7FFEF6A8_S_7FFEF6A8_0 {
    u8 pad_00[0x6C];
    union { struct { s32 v; } ovl_16b08_f6a8_7FFEF6A8_at00; struct { u8 pad[0x2]; s16 v; } ovl_16b08_f6a8_7FFEF6A8_at02; } ovl_16b08_f6a8_7FFEF6A8_unk_6C;   
    union { struct { s32 v; } ovl_16b08_f6a8_7FFEF6A8_at00; struct { u8 pad[0x2]; s16 v; } ovl_16b08_f6a8_7FFEF6A8_at02; } ovl_16b08_f6a8_7FFEF6A8_unk_70;   
    union { struct { s32 v; } ovl_16b08_f6a8_7FFEF6A8_at00; struct { u8 pad[0x2]; s16 v; } ovl_16b08_f6a8_7FFEF6A8_at02; } ovl_16b08_f6a8_7FFEF6A8_unk_74;   
    union { struct { s32 v; } ovl_16b08_f6a8_7FFEF6A8_at00; struct { u8 pad[0x2]; s16 v; } ovl_16b08_f6a8_7FFEF6A8_at02; } ovl_16b08_f6a8_7FFEF6A8_unk_78;   
    s32 unk_7C;
    s32 unk_80;
    s32 unk_84;
    s32 unk_88;
    u8 pad_8C[0x4];
    s32 unk_90;
    s32 unk_94;
    s32 unk_98;
} ovl_16b08_f6a8_7FFEF6A8_S_7FFEF6A8_0;
s32 func_80065F90();
s32 check_scratch_quad_half_turn_gaps(ovl_16b08_f6a8_7FFEF6A8_S_7FFEF6A8_0 *poly);
#endif
