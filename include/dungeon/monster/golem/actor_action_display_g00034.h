#ifndef DUNGEON_MONSTER_GOLEM_ACTOR_ACTION_DISPLAY_G00034_H
#define DUNGEON_MONSTER_GOLEM_ACTOR_ACTION_DISPLAY_G00034_H
/* Actor action display shared declarations (G00034). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00034 - CL:dungeon/func_81084A18@dungeon/bank_10a3000, CL:dungeon/func_81084A18@dungeon/bank_10a9000, CL:dungeon/func_81084A18@dungeon/bank_10af000, CL:dungeon/func_81084A18@dungeon/bank_10b5000, CL:dungeon/func_81084A18@dungeon/bank_10bb000, CL:dungeon/func_81084A18@dungeon/bank_10c1000. */

#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_func_800A9E70_arg0.h"

typedef struct S_80172050_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x29];
    u8 unk_71;
    u8 pad_72[0x12];
    s8 unk_84;
    s8 unk_85;
} S_80172050_0;

/* actor in attempt_actor_action_and_display */
typedef struct S_80172050_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80172050_1;

/* actor_info in attempt_actor_action_and_display */
typedef struct S_80172050_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_80172050_2;

/* out in attempt_actor_action_and_display */
typedef struct S_80172050_3 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x41];
    u8 unk_6D;
} S_80172050_3;

typedef struct Ent Ent;

extern s32 get_actor_height_difference(s32, void *);
extern s32 probe_directional_neighbor(void *, s32, s32, s32);
extern s32 check_entity_interaction_compatibility(void *, s32);
extern u8 D_80175F48;

typedef struct S_80047784 S_80047784;
typedef struct { u8 pad0[0x24]; u8 unk24; u8 unk25; } Pos;
extern void select_sprite_entry(S_80047784 *, s16, s16);
extern Ent *prepare_directional_attack(Ent *, Pos *, u32, s32, Ent *);
extern s16 try_claim_dungeon_action_slot(s32);
extern s32 apply_camera_offset_and_select_target(s32, void *, s32, s32);

/* Functions defined in this translation unit. */
s32 attempt_actor_action_and_display(void *action_out, s32 action_param, void *actor_info, void *acting_actor);
void update_eligible_actor_action(void *action_state, s32 action_context, void *sprite, EntityRec *actor);

#endif
