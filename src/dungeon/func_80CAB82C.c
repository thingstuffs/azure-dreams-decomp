#include "modules/dungeon_ovl_ccb000.h"

void func_8015902C(CL_CCB000_8017102C_S_8017102C_0 *state, void *motion, CL_CCB000_8017102C_S_8017102C_2 *sprite, CL_CCB000_8017102C_S_8017102C_1 *actor) {
 u16 terrain_flags;
 u8 *frames;
 s32 room;
 s32 actor_flags;
 u16 flags;
 if(g_dungeon_status.flags & 0x1000) {
  state->unk_9A=14;
  func_80159590(state,motion,sprite,actor);
  return;
 }
 if(actor->unk_25==0) {
  advance_actor_pending_action(state,motion,sprite,actor);
  if(sprite->unk_2C==D_8015D2FC) return;
  sprite->unk_2C=D_8015D2F4;
  select_sprite_entry(sprite,D_8015D2F4[((g_game_work.view.camera_rotation.parts.viewAngle+actor->unk_2A+0x100)>>9)&7],0);
  return;
 }
 {
  if(actor->unk_1C & 0x200) {
   if(sprite->unk_2C==D_8015D2FC) {
    state->unk_9A=13;
    state->unk_9B=1;
    state->unk_8C=0;
    actor->unk_1C &= 0xFFFBFFFF;
    return;
   }
   if(reset_actor_action_state(state,motion,sprite,D_8015D2F4)!=0) return;
  }
  if(!(g_dungeon_status.flags & 0x2000)) {
   if(actor->unk_1C & 0x100) {
    begin_pushed_actor_move(state,motion,sprite,actor);
    return;
   }
   if(state->unk_9A!=14) {
    if(sprite->unk_2C!=D_8015D2B4) {
     sprite->unk_2C=D_8015D2B4;
     select_sprite_entry(sprite,D_8015D2B4[((g_game_work.view.camera_rotation.parts.viewAngle+actor->unk_2A+0x100)>>9)&7],0);
    }
    state->unk_9A=14;
   }
   state->unk_98 &= 0xFFF3;
   if(actor->unk_64!=0 && begin_ready_actor_directional_action(state,motion,sprite,D_8015D2BC)!=0) return;
   if(actor->unk_1C & 0x80000) {
    begin_actor_move_to_target_facing(state,motion,sprite,actor);
    func_8015BA38(state,motion,sprite,actor);
    return;
   }
   if((can_entity_gain_level(actor)<<16)!=0 && (process_selected_actor_record(state,motion,sprite,actor)<<16)!=0)
    func_8015CB3C(state,motion,sprite,actor);
  }
  room=find_active_rect_containing_point(sprite->tile.bytes.x,sprite->tile.bytes.y);
  sprite->unk_26=room;
  if(actor->unk_6D>0) {
   if(actor->unk_1C & 0x20) {
    update_actor_status_and_food(actor);
    return;
   }
   if(sprite->tile.packed==D_80082EA4) {
    func_80159810(state,motion,sprite,actor);
    return;
   }
   if(!(actor->unk_46 & 0x8000)) {
    if((!(g_dungeon_status.flags & 0x2000) || (check_entity_relation(actor,((CL_CCB000_8017102C_S_8017102C_3 *)D_800814A8)->unk_58+0x20)<<16)==0)
       && (func_8015A298(state,motion,sprite,0)<<16)!=0) {
     flags=actor->unk_46 | 0x4000;
     actor->unk_46=flags;
     if(!(flags & 0x8000)) {
      func_80159810(state,motion,sprite,actor);
      return;
     }
    } else return;
   }
   switch(actor->unk_46 & 0x3FFF) {
   case 8: case 9:
    if((func_80159FBC(state,motion,sprite,actor)<<16)==0)
     func_8015A180(state,motion,sprite,actor);
    return;
   case 5: case 6: case 7:
    actor->unk_2A=get_rounded_facing_and_rounding_flag(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tile_position.parts.tile_x,D_80082E80.tile_position.parts.tile_y,&terrain_flags);
    if(((CL_CCB000_8017102C_S_8017102C_3 *)D_800814A8)->unk_9A==17) {
     begin_actor_spell_action(state,motion,sprite,D_8015D2EC,func_8015902C);
     return;
    }
    /* A failed pursuit falls through to the same completion path as action 12. */
   case 12:
    update_actor_status_and_food(actor);
    return;
   case 1: case 2: case 3:
    begin_actor_spell_action(state,motion,sprite,D_8015D2EC,func_8015902C);
    return;
   default:
    func_80159810(state,motion,sprite,actor);
    return;
   }
  }
  actor_flags=actor->unk_1C;
  if(!(actor_flags & 0x2000) && ((s8)room<0 || !(((CL_CCB000_8017102C_S_8017102C_5 *)((u8 *)D_800E2970+(s8)room*20))->unk_0C & 2)) && !(actor_flags & 0x430)) {
   if((compare_monster_neighbor_values(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tile_position.parts.tile_x,D_80082E80.tile_position.parts.tile_y)<<16)!=0)
    actor->unk_2A=get_rounded_facing_and_rounding_flag(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tile_position.parts.tile_x,D_80082E80.tile_position.parts.tile_y,&terrain_flags);
  }
  if((g_dungeon_status.flags & 0x2000) || (sprite->unk_14 & 0x40)) return;
  frames=D_8015D2B4;
  if(sprite->unk_2C==frames) return;
 }
 sprite->unk_2C=frames;
 select_sprite_entry(sprite,*((((g_game_work.view.camera_rotation.parts.viewAngle+actor->unk_2A+0x100)>>9)&7)+frames),0);
}
