#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"



typedef struct S_8009B014_1 {
    u8 pad_00[0x4];
    s32 * unk_04;
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x20];
    s16 unk_32;
} S_8009B014_1;   /* arg0 in advance_player_toward_target */



extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern void clear_entity_record_fields(void *record);
extern void *D_8009AFF4[3];
extern u8 town_scene_record_handlers[3];
extern s32 town_player_target_adjustment;
extern s32 D_800D0640[3];

/* Updates motion toward the target and advances the state when the countdown expires. */
void advance_player_toward_target(void *state, ObjectPosition *motion, s32 context) {
    u16 ticks_left;
    s32 target_index;
    s32 *target_bases;
    s32 *target_base;

    target_index = town_player_target_adjustment;
    target_bases = D_800D0640;
    target_base = target_bases + target_index;
    motion->velocity_y = (s32) ((u32) (((S_8009B014_1 *)state)->unk_32 * 0x10000) + (u32) *target_base
        - (u32) motion->y.v) / ((S_8009B014_1 *)state)->unk_0A.s;
    ticks_left = (u16) ((S_8009B014_1 *)state)->unk_0A.s - 1;
    ((S_8009B014_1 *)state)->unk_0A.u = ticks_left;
    if (((s16) ticks_left * 0x10000) <= 0) {
        motion->y.v = (s32) ((u32) (((S_8009B014_1 *)state)->unk_32 * 0x10000) + (u32) *target_base);
        clear_entity_record_fields(motion);
        ((S_8009B014_1 *)state)->unk_10 = 0x400;
        ((S_8009B014_1 *)state)->unk_0A.u = 0xA;
        call_the_handler_selects_nonzero_entry(town_scene_record_handlers, state, context);
        ((S_8009B014_1 *)state)->unk_04 = D_8009AFF4;
    }
}
