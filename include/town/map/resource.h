#ifndef TOWN_MAP_RESOURCE_H
#define TOWN_MAP_RESOURCE_H
/* Prototypes of the functions defined in src/town/map/resource/ (one true prototype each; maintained by tools/headers). */

#include "common.h"

/* create_building_resource_object.c */
void create_building_resource_object(void);

/* load_resource_data.c */
void load_resource_data(void);

/* send_resource_command.c */
void send_resource_command_23(s32 entry_index);

/* town_sd_se_load_init.c */
void town_sd_se_load_init(void);

/* town_sdall_reserve.c */
void town_sdall_reserve(s16 effect_id, s16 sound_id, s16 sequence_effect, s16 sequence_id);

/* town_se_reserve.c */
void town_se_reserve(s16 effect_id, s16 sound_id);

/* town_seq_reserve.c */
void town_seq_reserve(s16 sequence_effect, s16 sequence_id);

/* write_resource_command.c */
void write_resource_command(s32 value, s8 code);

#endif
