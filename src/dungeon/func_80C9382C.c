#include "modules/dungeon_ovl_cb3000.h"

void func_8017102C(CB_8017102C_S_8017102C_0 *state, void *motion, CB_8017102C_S_8017102C_2 *sprite, CB_8017102C_S_8017102C_1 *actor) {
 u16 terrain_flags;
 u8 *frames;
 s32 room;
 s32 actor_flags;
 u16 flags;
 if(dungeonStatus.flags & 0x1000) {
  state->unk_9A=14;
  dungeonAdvanceActorStoredPath(state,motion,sprite,actor);
  return;
 }
 if(actor->unk_25==0) {
  dungeonAdvanceActorPendingAction(state,motion,sprite,actor);
  if(sprite->unk_2C==D_801752FC) return;
  sprite->unk_2C=D_801752F4;
  func_80047784(sprite,D_801752F4[((gameWork.view.viewAngle+actor->unk_2A+0x100)>>9)&7],0);
  return;
 }
 {
  if(actor->unk_1C & 0x200) {
   if(sprite->unk_2C==D_801752FC) {
    state->unk_9A=13;
    state->unk_9B=1;
    state->unk_8C=0;
    actor->unk_1C &= 0xFFFBFFFF;
    return;
   }
   if(dungeonResetActorActionState(state,motion,sprite,D_801752F4)!=0) return;
  }
  if(!(dungeonStatus.flags & 0x2000)) {
   if(actor->unk_1C & 0x100) {
    dungeonBeginPushedActorMove(state,motion,sprite,actor);
    return;
   }
   if(state->unk_9A!=14) {
    if(sprite->unk_2C!=D_801752B4) {
     sprite->unk_2C=D_801752B4;
     func_80047784(sprite,D_801752B4[((gameWork.view.viewAngle+actor->unk_2A+0x100)>>9)&7],0);
    }
    state->unk_9A=14;
   }
   state->unk_98 &= 0xFFF3;
   if(actor->unk_64!=0 && dungeonBeginReadyActorDirectionalAction(state,motion,sprite,D_801752BC)!=0) return;
   if(actor->unk_1C & 0x80000) {
    func_800AA888(state,motion,sprite,actor);
    func_80173A38(state,motion,sprite,actor);
    return;
   }
   if((func_800A1C58(actor)<<16)!=0 && (dungeonProcessSelectedActorRecord(state,motion,sprite,actor)<<16)!=0)
    func_80174B3C(state,motion,sprite,actor);
  }
  room=func_8009FB34(sprite->tile.bytes.x,sprite->tile.bytes.y);
  sprite->unk_26=room;
  if(actor->unk_6D>0) {
   if(actor->unk_1C & 0x20) {
    func_800A9A0C(actor);
    return;
   }
   if(sprite->tile.packed==D_80082EA4) {
    func_80171810(state,motion,sprite,actor);
    return;
   }
   if(!(actor->unk_46 & 0x8000)) {
    if((!(dungeonStatus.flags & 0x2000) || (dungeonCheckEntityRelation(actor,((CB_8017102C_S_8017102C_3 *)D_800814A8)->unk_58+0x20)<<16)==0)
       && (func_80172298(state,motion,sprite,0)<<16)!=0) {
     flags=actor->unk_46 | 0x4000;
     actor->unk_46=flags;
     if(!(flags & 0x8000)) {
      func_80171810(state,motion,sprite,actor);
      return;
     }
    } else return;
   }
   switch(actor->unk_46 & 0x3FFF) {
   case 8: case 9:
    if((func_80171FBC(state,motion,sprite,actor)<<16)==0)
     func_80172180(state,motion,sprite,actor);
    return;
   case 5: case 6: case 7:
    actor->unk_2A=dungeonGetRoundedFacingAndRoundingFlag(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY,&terrain_flags);
    if(((CB_8017102C_S_8017102C_3 *)D_800814A8)->unk_9A==17) {
     dungeonBeginActorSpellAction(state,motion,sprite,D_801752EC,func_8017102C);
     return;
    }
    /* A failed pursuit falls through to the same completion path as action 12. */
   case 12:
    func_800A9A0C(actor);
    return;
   case 1: case 2: case 3:
    dungeonBeginActorSpellAction(state,motion,sprite,D_801752EC,func_8017102C);
    return;
   default:
    func_80171810(state,motion,sprite,actor);
    return;
   }
  }
  actor_flags=actor->unk_1C;
  if(!(actor_flags & 0x2000) && ((s8)room<0 || !(((CB_8017102C_S_8017102C_5 *)((u8 *)D_800E2970+(s8)room*20))->unk_0C & 2)) && !(actor_flags & 0x430)) {
   if((dungeonCompareMonsterNeighborValues(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY)<<16)!=0)
    actor->unk_2A=dungeonGetRoundedFacingAndRoundingFlag(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY,&terrain_flags);
  }
  if((dungeonStatus.flags & 0x2000) || (sprite->unk_14 & 0x40)) return;
  frames=D_801752B4;
  if(sprite->unk_2C==frames) return;
 }
 sprite->unk_2C=frames;
 func_80047784(sprite,*((((gameWork.view.viewAngle+actor->unk_2A+0x100)>>9)&7)+frames),0);
}
