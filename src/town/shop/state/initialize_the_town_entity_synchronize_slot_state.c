#include "common.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_80094268_arg0.h"

typedef struct S_8009F4C0_3 {
    u8 pad_00[0xAC3];
    u8 unk_AC3;
} S_8009F4C0_3;

typedef struct S_8009F4C0_4 {
    u8 pad_00[0x983];
    u8 unk_983;
} S_8009F4C0_4;   /* ((arg0->unk_95 * 4) + (u8 *)baseD) in initialize_the_town_entity_synchronize_slot_state */

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

void register_node_if_unregistered(void *, s32);                   /* extern */
void *runtime_get_mode_indexed_value();               /* extern */
void func_8003E188(s32 field_index, s32 flag);        /* extern */
typedef struct S_800422DC_Other S_800422DC_Other;
typedef struct S_800422DC_Self S_800422DC_Self;
void build_entity_slot_snapshot(S_800422DC_Self *snapshot, S_800422DC_Other *source);            /* extern */
typedef struct S_800423C0_Src S_800423C0_Src;
typedef struct S_800423C0_Obj S_800423C0_Obj;
void apply_actor_template_and_direction(S_800423C0_Obj *obj, s16 unused, S_800423C0_Src *source);      /* extern */
void func_80042640(void *obj, s16 monsterId);               /* extern */
void *memset(); /* extern */
void set_object_state_for_mode(void *, void *, s32, s32);    /* extern */
#include "records/Rec_D_800CFCB4.h"
typedef struct S_8009F374_2 S_8009F374_2;
#include "shared/entity.h"
void handle_jitter_position_pulse_scale_until_countdown_expires(Rec_D_800CFCB4 *state, s32 context, EntityRec *position, S_8009F374_2 *scale);
extern s32 town_actor_scratch;
extern struct TownCopy84 town_slot_snapshot;


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

/* Initialize the town entity record and synchronize its slot state. */
void initialize_the_town_entity_synchronize_slot_state(Rec_func_80094268_arg0 *entity, s32 unused_arg1, s32 unused_arg2, void *context) {
    void *stored_entry;
    s32 unused_value;
    s32 record_offset;
    s32 record_value;
    s32 slot_index;
    register s32 record_index;
    void *source_entry;
    S_8009F4C0_2 *slot_flags;
    S_8009F4C0_1 *slot_state;
    void *data_base;

    slot_index = entity->unk_95;
    register_node_if_unregistered(entity, (s32)(project_sprite_chain));
    slot_state = (slot_index * 4) + 0x80010000;
    slot_state->unk_981 = 0x13;
    memset(&town_actor_scratch, 0, 0x54);
    func_80042640(&town_actor_scratch, entity->unk_4C);
    record_index = slot_index;
    apply_actor_template_and_direction(&town_actor_scratch, entity->unk_4C, 0);
    build_entity_slot_snapshot(&town_slot_snapshot, &town_actor_scratch);
    *(struct TownCopy84 *)((u8 *)0x80010A80 + (record_index * 0x54)) = town_slot_snapshot;
    stored_entry = (void *) 0x80010AB4;
    record_offset = record_index * 0x54;
    stored_entry = (u8 *)stored_entry + record_offset;
    source_entry = runtime_get_mode_indexed_value(entity->unk_4C);
    *(struct PackedTownEntry *)stored_entry = *(struct PackedTownEntry *)source_entry;
    data_base = (void *) 0x80010000;
    slot_flags = (slot_index * 4) + (u8 *)data_base;
    slot_flags->unk_983 = (u8) ((slot_flags->unk_983 & 0xC0) | record_index);
    ((S_8009F4C0_3 *)((record_offset + (u8 *)data_base)))->unk_AC3 = slot_index;
    entity->unk_4D = (u8) slot_flags->unk_981;
    entity->unk_4F = (u8) slot_flags->unk_983;
    record_index = (u8) (((S_8009F4C0_4 *)(((entity->unk_95 * 4) + (u8 *)data_base)))->unk_983 & 0x3F);
    record_value = ((S_8009F4C0_5 *)(((record_index * 0x54) + (u8 *)data_base)))->unk_A94;
    func_8003E188(entity->unk_4C, 1);
    set_object_state_for_mode(entity, context, entity->unk_4C, record_value);
    entity->unk_50.as_pm = &handle_jitter_position_pulse_scale_until_countdown_expires;
    entity->unk_6C.as_s16 = 0xA;
}
