#include "shared/dungeon_item_entries.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

/* This data symbol has no shared-catalog address. */

extern u8 D_80081470[];
extern u8 D_800E3648[];

extern s32 func_800A4474(u8, u8);
extern s16 func_800B500C(u8, u8, s16);
extern s16 func_800A70E4(u8, u8, s16);

typedef struct S_800A4300_2 {
    u8 pad_00[0xF0];
    union { void * p; s32 i; } unk_F0;   /* accessed as both */
} S_800A4300_2;   /* D_800814A8[0] in func_800A4300 */

/* Selects data at the entity's position and updates the owner's map or floor entry. */
void func_800A4300(Rec_D_80082E80 *entity, EntityRec *search_state) {
    s32 lookup_code;
    void *owner;
    u32 map_index_bits, floor_index_bits;
    u8 *map_base, *floor_base;
    s16 floor_index, map_index;
    u8 *floor_entry, *map_entry;

    lookup_code = func_800A4474(entity->unk_24, entity->unk_25);
    if ((lookup_code << 16) != 0) {
#ifndef NON_MATCHING
        *(s16 *)D_80081470 = (s16)(lookup_code | 0x1400);
        D_800814A8->unk_F0 = 0;
        return;
#else
        *(s16 *)D_80081470 = (s16)(lookup_code | 0x1400);
        owner = *(void *volatile *)((void * *)(&D_800814A8));
#endif
    } else {
        map_index_bits = (u32)func_800B500C(entity->unk_24,
                                            entity->unk_25,
                                            search_state->unk_88) << 16;
        map_index = (s16)((s32)map_index_bits >> 16);
        if (map_index >= 0) {
            map_base = D_800E3648;
            map_entry = map_base + map_index * 4;
            if (!(map_entry[3] & 0x40)) {
                *(void **)D_80081470 = *(void **)map_entry;
                D_800814A8->unk_F0 = map_entry;
                return;
            }
            D_800814A8->unk_F0 = 0;
            return;
        }

        floor_index_bits = (u32)func_800A70E4(entity->unk_24,
                                              entity->unk_25,
                                              search_state->unk_88) << 16;
        floor_index = (s16)((s32)floor_index_bits >> 16);
        if (floor_index >= 0) {
            floor_base = ((u8 *)D_800E3548);
            floor_entry = floor_base + floor_index * 4;
            *(void **)D_80081470 = *(void **)floor_entry;
            D_800814A8->unk_F0 = floor_entry;
            return;
        }

        owner = D_800814A8;
        *(void **)D_80081470 = 0;
    }
    ((S_800A4300_2 *)owner)->unk_F0.i = 0;
}
