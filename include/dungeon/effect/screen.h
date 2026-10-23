#ifndef DUNGEON_EFFECT_SCREEN_H
#define DUNGEON_EFFECT_SCREEN_H

/* Function contracts owned by src/dungeon/effect/screen/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "shared/entity.h"
void add_random_quarter_value(void *source, void *target);
void create_wrapped_texture_scroll(s16 value);
void draw_content_or_rect(s32 *line_start, s32 *line_end, u8 *rect, s16 fill, s32 content_id);
s32 get_masked_record_flags(EntityRec *record, s32 mask, s32 mode);
void pack_and_submit_cell_height_levels(void);
void update_packed_map_levels(void);
s32 try_trigger_target_record_effect(void *entity, s32 flags, void *record);


#endif
