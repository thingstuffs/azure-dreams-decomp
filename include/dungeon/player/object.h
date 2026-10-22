#ifndef DUNGEON_PLAYER_OBJECT_H
#define DUNGEON_PLAYER_OBJECT_H

/* Function contracts owned by src/dungeon/player/object/ (decision 74; maintained by tools/headers). */
#include "common.h"
#include "records/Rec_func_8008ACDC_arg0.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
void accumulate_experience_award(u8 *record, u16 amount);
void begin_throw_carried_object(Rec_func_8008ACDC_arg0 *object, s32 unusedArg1, s32 unusedArg2, s32 handlerContext);
s32 find_first_unused_entity_entry(void);
s32 is_dungeon_action_enabled(void);
s32 lower_entity_level(void *entity_data, s32 show_message);
void *register_item_object_in_free_slot(void *target, void *ptr1, void *ptr2, s16 flag);
void try_begin_put_down_carried_object(void *state, EntityRec *target, SpriteFrameState *sprite, u32 actor_or_can);


#endif
