#ifndef TOWN_SHOP_POSITION_UPDATE_POSITION_DISPLACEMENT_DISPATCH_ACTIVE_ENTITY_HANDLER_G01131_H
#define TOWN_SHOP_POSITION_UPDATE_POSITION_DISPLACEMENT_DISPATCH_ACTIVE_ENTITY_HANDLER_G01131_H
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "engine/window.h"

struct SpriteFrameState;
/* Update position displacement dispatch active entity handler. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - CL:town/func_800A1A60, CL:town/func_800A1D2C, CL:town/func_800A1D60. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_8009EE9C_arg0.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "records/Rec_D_800CFCB4.h"
#include "shared/town_object.h"
#include "shared/dungeon_delay_views.h"
#include "shared/slus_callbacks.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8009EE9C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} S_8009EE9C_0;

typedef struct S_8009F1C0_0 {
    u8 pad_00[0x14];
    s8 unk_14;
    s8 unk_15;
} S_8009F1C0_0;

typedef struct {
    s32 words[0x15];
} Record84;

/* extern */
struct TownObjectRecord;

/* extern */
typedef struct AllocatedObject AllocatedObject;

/* extern */
typedef struct S_8009F374_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_8009F374_2;

typedef struct S_8009F4C0_3 {
    u8 pad_00[0xAC3];
    u8 unk_AC3;
} S_8009F4C0_3;

typedef struct S_8009F4C0_4 {
    u8 pad_00[0x983];
    u8 unk_983;
} S_8009F4C0_4;

/* ((arg0->unk_95 * 4) + (u8 *)baseD) in snapshot_entity_slot_and_start_jitter */
typedef struct S_8009F4C0_5 {
    u8 pad_00[0xA94];
    s32 unk_A94;
} S_8009F4C0_5;

struct PackedTownEntry {
    s32 word0;
    s32 word4;
    s8 byte8;
    s8 byte9;
} __attribute__((packed));

struct TownCopy84 {
    s32 words[21];
};

/* extern */
typedef struct S_800422DC_Other S_800422DC_Other;

typedef struct S_800422DC_Self S_800422DC_Self;

/* extern */
typedef struct S_800423C0_Src S_800423C0_Src;

typedef struct S_800423C0_Obj S_800423C0_Obj;

struct S_8009F374_2;

typedef struct S_8009F4C0_1 {
    u8 pad_00[0x981];
    s8 unk_981;
} S_8009F4C0_1;

typedef struct S_8009F4C0_2 {
    u8 pad_00[0x981];
    u8 unk_981;
    u8 pad_982[0x1];
    u8 unk_983;
} S_8009F4C0_2;

extern s32 town_timed_state_address;
extern M2C_UNK D_80093524[3];
extern s32 remove_object_if_item_found();
extern s32 D_800D09C8[];
extern u8 D_8009EE9C[];
/* arg1 in start_slot_entity_move_toward_view */
extern u32 D_8009EF88;
/* arg2 in bob_entity_and_wait_for_event */
short SD_Call(int flags);
AllocatedObject *allocate_object_with_callbacks();
/* extern */
void check_adjusted_input_indices();
extern void D_800935BC();
void unlink_node_if_registered(void *block_data);
extern void D_8009F2A8();
/* extern */
void *runtime_get_mode_indexed_value(); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
/* extern */
void func_8003E188(s32 field_index, s32 flag);
void build_entity_slot_snapshot(S_800422DC_Self *snapshot, S_800422DC_Other *source);
void apply_actor_template_and_direction(S_800423C0_Obj *obj, s16 unused, S_800423C0_Src *source);
/* extern */
void func_80042640(void *obj, s16 monsterId);
/* extern */
/* extern */
void set_object_state_for_mode(void *,struct SpriteFrameState *, s32, s32);
extern s32 town_actor_scratch;

/* Shared import declarations; data casts preserve each measured view. */
extern s32 scene_object_payload_alias[3];
extern s32 town_target_record[3];
extern u8 town_slot_snapshot[];

/* Functions defined in this translation unit. */
void bob_entity_and_dispatch_handler(Rec_func_8009EE9C_arg0 *entity, s32 entity_id, S_8009EE9C_0 *motion, struct SpriteFrameState *context);
void move_entity_toward_view_reference(void *entity, s32 context, ObjectPosition *motion, s32 mode);
void start_slot_entity_move_toward_view(Rec_func_8009EE9C_arg0 *entity, S_8009F1C0_0 *action, void *unused_motion, struct SpriteFrameState *unused_context);
s32 get_target_itemp(void);
void bob_entity_and_wait_for_event(void *state, s32 event_id, DelayMotionZ *target, struct SpriteFrameState *context);
void jitter_and_pulse_entity_scale(Rec_D_800CFCB4 *state, s32 context, EntityRec *position, S_8009F374_2 *scale);
void unlink_entity_and_set_bob_handler(Rec_func_8009EE9C_arg0 *record, s32 value, void *unused_motion, struct SpriteFrameState *unused_context);
void snapshot_entity_slot_and_start_jitter(TownObjectRecord *entity, s32 unused_arg1, s32 unused_arg2, void *context);

#endif
