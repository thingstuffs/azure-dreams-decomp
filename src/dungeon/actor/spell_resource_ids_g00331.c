/* Spell resource ids (G00331). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800A3C30, PD:dungeon/engine:800DD8E7. */
#include "dungeon/actor/spell_resource_ids_g00331.h"

s32 resolve_spell_effect_resource_id(s16 index) {
    s32 compare;

    index = D_800DD8E7[index];
    if (((Inner *)D_800E3D7C->unk_4C)->flag != 0) {
        compare = index;
        if (compare == 0x32) {
            return 0x33;
        }
        if (compare == 0x39) {
            return 0x3A;
        }
        if (compare == 0x40) {
            return 0x42;
        }
    }
    return index;
}

/* Maps special tile codes to mode-dependent values, otherwise returning the tile index. */

s32 resolve_alternate_spell_id(s32 tile_index)
{
    s16 index;
    u8 *tile;
    s32 tile_code;

    index = tile_index;
    tile = D_800DD8E7 + (s16)tile_index;
    tile_code = *tile;

    if (*(*(u8 **)(((u8 *)D_800E3D7C) + 0x4C) + 1) != 0) {
        if (tile_code == 0x32) {
            return 7;
        }
        if (tile_code == 0x39) {
            return 8;
        }
        if (tile_code == 0x40) {
            return 9;
        }
    } else {
        if (tile_code == 0x32) {
            return 1;
        }
        if (tile_code == 0x39) {
            return 2;
        }
        if (tile_code == 0x40) {
            return 3;
        }
    }

    return index;
}
