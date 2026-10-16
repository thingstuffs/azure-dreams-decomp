#include "modules/dungeon_ovl_ccb000.h"

void func_8015902C(CL_CCB000_8017102C_S_8017102C_0 *state, void *motion, CL_CCB000_8017102C_S_8017102C_2 *sprite, CL_CCB000_8017102C_S_8017102C_1 *actor) {
 u16 terrain_flags;
 u8 *frames;
 s32 room;
 s32 actor_flags;
 u16 flags;
 if(dungeonStatus.flags & 0x1000) {
  state->unk_9A=14;
  func_80159590(state,motion,sprite,actor);
  return;
 }
 if(actor->unk_25==0) {
  func_800AA79C(state,motion,sprite,actor);
  if(sprite->unk_2C==D_8015D2FC) return;
  sprite->unk_2C=D_8015D2F4;
  func_80047784(sprite,D_8015D2F4[((gameWork.view.viewAngle+actor->unk_2A+0x100)>>9)&7],0);
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
   if(func_800AA924(state,motion,sprite,D_8015D2F4)!=0) return;
  }
  if(!(dungeonStatus.flags & 0x2000)) {
   if(actor->unk_1C & 0x100) {
    func_800AA258(state,motion,sprite,actor);
    return;
   }
   if(state->unk_9A!=14) {
    if(sprite->unk_2C!=D_8015D2B4) {
     sprite->unk_2C=D_8015D2B4;
     func_80047784(sprite,D_8015D2B4[((gameWork.view.viewAngle+actor->unk_2A+0x100)>>9)&7],0);
    }
    state->unk_9A=14;
   }
   state->unk_98 &= 0xFFF3;
   if(actor->unk_64!=0 && func_800AA6B4(state,motion,sprite,D_8015D2BC)!=0) return;
   if(actor->unk_1C & 0x80000) {
    func_800AA888(state,motion,sprite,actor);
    func_8015BA38(state,motion,sprite,actor);
    return;
   }
   if((func_800A1C58(actor)<<16)!=0 && (func_800AAB10(state,motion,sprite,actor)<<16)!=0)
    func_8015CB3C(state,motion,sprite,actor);
  }
  room=func_8009FB34(sprite->tile.bytes.x,sprite->tile.bytes.y);
  sprite->unk_26=room;
  if(actor->unk_6D>0) {
   if(actor->unk_1C & 0x20) {
    func_800A9A0C(actor);
    return;
   }
   if(sprite->tile.packed==D_80082EA4) {
    func_80159810(state,motion,sprite,actor);
    return;
   }
   if(!(actor->unk_46 & 0x8000)) {
    if((!(dungeonStatus.flags & 0x2000) || (func_8009A180(actor,((CL_CCB000_8017102C_S_8017102C_3 *)D_800814A8)->unk_58+0x20)<<16)==0)
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
    actor->unk_2A=func_800A0818(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY,&terrain_flags);
    if(((CL_CCB000_8017102C_S_8017102C_3 *)D_800814A8)->unk_9A==17) {
     func_800AAF00(state,motion,sprite,D_8015D2EC,func_8015902C);
     return;
    }
    /* A failed pursuit falls through to the same completion path as action 12. */
   case 12:
    func_800A9A0C(actor);
    return;
   case 1: case 2: case 3:
    func_800AAF00(state,motion,sprite,D_8015D2EC,func_8015902C);
    return;
   default:
    func_80159810(state,motion,sprite,actor);
    return;
   }
  }
  actor_flags=actor->unk_1C;
  if(!(actor_flags & 0x2000) && ((s8)room<0 || !(((CL_CCB000_8017102C_S_8017102C_5 *)((u8 *)D_800E2970+(s8)room*20))->unk_0C & 2)) && !(actor_flags & 0x430)) {
   if((func_8009FD7C(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY)<<16)!=0)
    actor->unk_2A=func_800A0818(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY,&terrain_flags);
  }
  if((dungeonStatus.flags & 0x2000) || (sprite->unk_14 & 0x40)) return;
  frames=D_8015D2B4;
  if(sprite->unk_2C==frames) return;
 }
 sprite->unk_2C=frames;
 func_80047784(sprite,*((((gameWork.view.viewAngle+actor->unk_2A+0x100)>>9)&7)+frames),0);
}
