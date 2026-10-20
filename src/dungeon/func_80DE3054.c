#include "modules/dungeon_ovl_e0365c.h"
#include "shared/sprite_frame_state.h"

void *spawn_mode_dependent_112_object(s16 flags,s16 attr_x,s16 attr_y,s16 attr_height) {
 E_80170854_SpawnActor *actor=0;
 E_80170854_SpawnObject *object;
 E_80170854_SpawnMotion *motion;
 s16 saved_flags;
 s32 kind;
 s8 tile_x; s16 height; s8 tile_y;
 {
 SpriteFrameState *sprite;
 E_80170854_SpawnState *state;
 tile_x=attr_x; height=attr_height; tile_y=attr_y;
 object=allocate_list_node(0x112,&D_80083498);
 saved_flags=flags;
 if(object) {
  actor=(E_80170854_SpawnActor *)((u8 *)object+0x20);
  actor->kind=0x1C;
  register_node(object,project_sprite_chain);
  motion=object->motion;
  kind=flags&3;
  motion->height=height;
  sprite=object->sprite;
  sprite->unk_24=tile_x;
  sprite->unk_25=tile_y;
  state=(E_80170854_SpawnState *)actor;
  if(kind==1) {
   actor->handler=update_actor_behavior_facing_and_animation_2;
   actor->flags14|=0x6000;
   actor->flags1C|=0x6000;
   sprite->frameTable=D_80174510;
  } else if(kind>=2) {
   actor->handler=update_actor_behavior_facing_and_animation_2;
   actor->flags14|=0x2000;
   actor->flags1C|=0x2000;
   sprite->frameTable=D_80174510;
  } else if((s16)(flags&~3)==0) {
   if(!(actor->flags14&0x200) && (generate_random_value()&1)) {
    set_or_clear_actor_status_slot(actor,1,(generate_random_value()&0x3F)|0x20);
    sprite->frameTable=D_80174538;
   }
   state->handler=update_actor_behavior_facing_and_animation_2;
   sprite->frameTable=D_80174510;
  } else { actor->handler=update_actor_behavior_facing_and_animation_2;
   sprite->frameTable=D_80174510;
  }
  object->update=update_entity_facing_and_ground;
  initialize_actor_sprite_and_animation(object,motion,sprite,saved_flags);
  state->action_id=0xFF;
  state->direction=-1;
  try_move_actor_to_valid_position(state,motion,sprite,actor);
 }
 }
 return actor;
}
