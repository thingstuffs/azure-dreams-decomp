#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"

typedef struct S_800A3D18_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800A3D18_0;   /* owner in choose_best_eligible_entry */

typedef struct S_800A3D18_1_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_800A3D18_1_pre;   /* the 0x14 bytes before cur in choose_best_eligible_entry, addressed as cur[-1] */

typedef struct S_800A3D18_1 {
    u8 pad_00[0x43];
    u8 unk_43;
    u8 pad_44[0x18];
    void * unk_5C;
    u8 pad_60[0x28];
    s16 unk_88;
} S_800A3D18_1;   /* cur in choose_best_eligible_entry */

typedef struct S_800A3D18_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800A3D18_2;   /* other in choose_best_eligible_entry */

typedef struct S_800A3D18_3 {
    u8 pad_00[0x3D7C];
    u8 * unk_3D7C;
} S_800A3D18_3;   /* global_page in choose_best_eligible_entry */

typedef struct S_800A3D18_4 {
    u8 pad_00[0x88];
    s16 unk_88;
} S_800A3D18_4;   /* base in choose_best_eligible_entry */

typedef struct S_800A3D18_5 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800A3D18_5;   /* best in choose_best_eligible_entry */


extern s32 get_tile_chebyshev_distance(void *, void *);
extern s32 check_monster_neighbor_relations(u8, u8, s16, u8, u8, s16);
extern s32 check_entity_interaction_compatibility(void *, void *);
extern s32 check_entity_eligibility(void *);

/* Selects the best eligible list candidate, resolving ties with the global candidate. */
void *choose_best_eligible_entry(void *owner_arg, void *start, s32 score_limit)
{
    void *candidate;
    S_800A3D18_4 *base;
    void *best;
    void *special;
    s16 special_score;
    s16 best_score;
    u8 *global_page;
    S_800A3D18_2 *candidate_owner;
    void *next_link;
    s32 score;
    s32 special_cmp;
    s32 best_cmp;

    candidate = start;
    best = 0;
    special = best;
    special_score = 0x100;
    base = candidate;

    if ((s16)score_limit < 0) {
        best_score = -score_limit;
    } else {
        best_score = 0x100;
        if (((S_800A3D18_0 *)owner_arg)->unk_26 < 0) {
            best_score = score_limit;
        }
    }

    next_link = ((S_800A3D18_1 *)candidate)->unk_5C;
    candidate = (u8 *)next_link + 0x20;
    if (candidate != base) {
        global_page = (u8 *)0x800e0000;
        while (candidate != base) {
            void *next_link;
            if ((s16)check_entity_interaction_compatibility(base, candidate) != 0 && (s16)check_entity_eligibility(candidate) != 0) {
                candidate_owner = ((S_800A3D18_1_pre *)candidate)[-1].unk_00;
                if (((S_800A3D18_0 *)owner_arg)->unk_26 == candidate_owner->unk_26) {
                    score = get_tile_chebyshev_distance(candidate_owner, owner_arg);
                    if ((s16)score < best_score) {
                        if (candidate == ((S_800A3D18_3 *)global_page)->unk_3D7C) {
                            special = candidate;
                            special_score = score;
                        } else {
                            best = candidate;
                            best_score = score;
                        }
                    }
                } else if ((s16)check_monster_neighbor_relations(((S_800A3D18_0 *)owner_arg)->unk_24,
                                              ((S_800A3D18_0 *)owner_arg)->unk_25,
                                              base->unk_88,
                                              candidate_owner->unk_24,
                                              candidate_owner->unk_25,
                                              ((S_800A3D18_1 *)candidate)->unk_88) != 0) {
                    if (candidate == ((S_800A3D18_3 *)global_page)->unk_3D7C) {
                        special = candidate;
                        special_score = 1;
                    } else {
                        best = candidate;
                        best_score = 1;
                    }
                    break;
                }
            }
            next_link = ((S_800A3D18_1 *)candidate)->unk_5C;
            candidate = (u8 *)next_link + 0x20;
        }
    }

    if (special == 0) {
        return best;
    }
    if (best == 0) {
        best = special;
    } else {
        special_cmp = (s16)special_score;
        best_cmp = (s16)best_score;
        if (special_cmp == best_cmp) {
            if (((S_800A3D18_5 *)best)->unk_1C & 8) {
                best = special;
            } else if (!((((EntityRec *)((u8 *)D_800E3D7C))->unk_128 + ((S_800A3D18_1 *)candidate)->unk_43) & 3)) {
                best = special;
            }
        } else if (special_cmp < best_cmp) {
            best = special;
        }
    }
    return best;
}
