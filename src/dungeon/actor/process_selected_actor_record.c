#include "shared/actor_status_flags.h"
#include "shared/actor_property_flags.h"

struct ObjectPosition;
#include "common.h"
#include "shared/sys_flags.h"
#include "shared/dungeon_floor.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80083460.h"

s32 get_entity_effect_value(void *, s32);
s32 can_entity_gain_level(void *);
void raise_entity_level(void *, s32);
void play_sound_if_enabled(s32);
void select_nearby_target_and_initialize_slot(s32 slot_id,struct ObjectPosition *target, s32 target_id, s16 slot_value);
extern s32 monster_species_table;
extern s8 scene_music_hold;
extern s8 D_80080AA0;

typedef struct S_800AAB10_2_pre {
    u16 unk_00;
    u8 pad_02[0x12];
} S_800AAB10_2_pre;   /* 0x14-byte header immediately before the payload. */

/* Processes the selected record, checks eligibility, and clears completed state. */
s32 process_selected_actor_record(s32 buffer_addr, s32 source, s32 unused, ActorRecord *record) {
    s32 eligible;
    u8 type_id;

    eligible = 0;
    if (dungeon_floor_flags & 0x100000) {
        if ((g_dungeon_status.active_actor) != 0) {
            if (((s32)g_dungeon_status.active_actor) == record) {
                if (g_dungeon_status.activity_counts.parts.pending_action_count == 0) {
                    if (!(g_dungeon_status.flags & 8)) {
                        select_nearby_target_and_initialize_slot((void *)(buffer_addr - 0x20), source, 8, 0x300);
                        raise_entity_level(record, 1);
                        play_sound_if_enabled(0x201);
                        if (!(system_update_flags & 2)) {
                            D_80080AA0 = 1;
                            scene_music_hold = 0;
                        }
                        if (!(record->status_flags & 0x800000) && (record->flags14 & ACTOR_PARTY_MEMBER)) {
                            type_id = (*(u8 *)((u8 *)&record->unk_10 + 3));
                            if ((((S_800AAB10_2_pre *)(((type_id * 0x14) + monster_species_table)))[-1].unk_00 & 0x80)
                                && (type_id >= 2U) && ((u8) (*(u8 *)((u8 *)&record->unk_10 + 1)) >= 0x14U)
                                && !(record->flags1C & (ACTOR_MP_EMPTY | ACTOR_PARALYZED | ACTOR_ASLEEP)) && ((get_entity_effect_value(record, 0x18) << 0x10) == 0)) {
                                eligible = 1;
                            }
                        }
                        if ((can_entity_gain_level(record) << 0x10) != 0) {
                            return 0;
                        }
                        g_dungeon_status.active_actor = 0;
                    } else {
                        return 0;
                    }
                } else {
                    return 0;
                }
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }
    return eligible;
}
