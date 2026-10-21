#include "common.h"
extern int abs(int);
#include "shared/object_index_slots.h"

extern int sound_payload_buffer;
extern int message_handler_mode;
extern int message_command_start_index;
extern int message_command_write_index;
extern unsigned char D_80071298[];
extern int D_800712B4[];
extern int card_server_initialized[3];
s32 runtime_estimate_vector_length(s32, s32);
#include "town/player/initialize_record_with_handler_table_api.h"
u16 query_lowered_transform_position();
void advance_player_position_and_angle(void *work_data, void *position_data, s32 context);
/* Set travel timing from distance and speed, or snap motion to the destination. */
void set_player_travel_timing(void *actor, void *motion, s32 context)
{
    s32 base_ticks;
    s32 scaled_ticks;
    s32 distance;
    s32 speed_modifier;
    s32 modifier_magnitude;
    s8 *movement_state;
    *(((*((s32 *) (((s8 *) actor) + 0x40))) * 8) + ((u8 *)object_index_slots)) = 0;
    *((s32 **) (((s8 *) actor) + 4)) = &advance_player_position_and_angle;
    distance = runtime_estimate_vector_length(((*((s16 *) (((s8 *) actor) + 0x36))) << 0x10) - (*((s32 *) (((s8 *) motion) + 0))),
        ((*((s16 *) (((s8 *) actor) + 0x38))) << 0x10) - (*((s32 *) (((s8 *) motion) + 4))));
    if (distance < 0) {
        distance += 0x1FFFF;
    }
    movement_state = (s8 *) (((*((s32 *) (((s8 *) actor) + 0x40))) * 8) + ((u8 *)object_index_slots));
    base_ticks = distance >> 0x11;
    *((s16 *) (((s8 *) actor) + 0xA)) = (s16) base_ticks;
    speed_modifier = *((s8 *) (movement_state + 2));
    if (speed_modifier == (-0x80)) {
        *((s32 *) (((s8 *) motion) + 0)) = (s32) ((*((s16 *) (((s8 *) actor) + 0x36))) << 0x10);
        *((s32 *) (((s8 *) motion) + 4)) = (s32) ((*((s16 *) (((s8 *) actor) + 0x38))) << 0x10);
        *((u16 *) (((s8 *) motion) + 0xA)) = (u16) ((*((u16 *) (((s8 *) motion) + 0xA))) - 0x80);
        *((u16 *) (((s8 *) motion) + 0xA)) = query_lowered_transform_position(motion);
        initialize_record_with_handler_table(actor, (s32)(motion), context);
        return;
    }
    if (speed_modifier > 0) {
        *((s16 *) (((s8 *) actor) + 0xA)) = (s16) ((base_ticks << 4) / (speed_modifier + 0x10));
        return;
    }
    if (speed_modifier < 0) {
        modifier_magnitude = abs(speed_modifier);
        scaled_ticks = base_ticks * (modifier_magnitude + 0x10);
        *((s16 *) (((s8 *) actor) + 0xA)) = (s16) (scaled_ticks / 16);
    }
}
