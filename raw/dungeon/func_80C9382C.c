#include "common.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
M2C_UNK func_80047784(void *, u8, M2C_UNK);         /* extern */
s32 func_8009A180(void *, s32);                     /* extern */
s32 func_8009FB34(s32, s32);                           /* extern */
s32 func_8009FD7C(u8, u8, u8, u8);                  /* extern */
s32 func_800A0818(s16, s16, s16, s16, u16 *);       /* extern */
s32 func_800A1C58(void *);                          /* extern */
M2C_UNK func_800A9A0C(void *);                      /* extern */
M2C_UNK func_800AA258(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800AA6B4(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
M2C_UNK func_800AA79C(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_800AA888(void *, M2C_UNK, void *, void *); /* extern */
s32 func_800AA924(void *, M2C_UNK, void *, M2C_UNK *); /* extern */
s32 func_800AAB10(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_800AAF00(void *, M2C_UNK, void *, M2C_UNK *, void (*)(void *, M2C_UNK, void *, void *)); /* extern */
void func_80171590(void *,void *,void *,void *);                            /* extern */
M2C_UNK func_80171810(void *, M2C_UNK, void *, void *); /* extern */
s32 func_80171FBC(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_80172180(void *, M2C_UNK, void *, void *); /* extern */
s32 func_80172298(void *, M2C_UNK, void *, M2C_UNK); /* extern */
M2C_UNK func_80173A38(void *, M2C_UNK, void *, void *); /* extern */
M2C_UNK func_80174B3C(void *, M2C_UNK, void *, void *); /* extern */
extern void *D_800814A8;

extern u16 D_80082EA4;


extern u8 D_800E2970[];
extern u8 D_801752B4[8];
extern u8 D_801752BC[8];
extern u8 D_801752EC[8];
extern u8 D_801752F4[8];
extern u8 D_801752FC[8];


typedef struct S_8017102C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    s8 unk_9B;
} S_8017102C_0;   /* arg0 in func_8017102C */

typedef struct S_8017102C_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_8017102C_1;   /* arg3 in func_8017102C */

typedef struct S_8017102C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 x; u8 y; } bytes; u16 packed; } tile;
    s8 unk_26;
    u8 pad_27[0x5];
    u8 *unk_2C;
} S_8017102C_2;   /* arg2 in func_8017102C */

typedef struct S_8017102C_3 {
    u8 pad_00[0x58];
    s32 unk_58;
    u8 pad_5C[0x3E];
    u8 unk_9A;
} S_8017102C_3;   /* D_800814A8 in func_8017102C */

typedef struct S_8017102C_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017102C_4;   /* &D_80082E80 in func_8017102C */

typedef struct S_8017102C_5 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_8017102C_5;   /* ((temp_v0 * 0x14) + &D_800E2970) in func_8017102C */

/* Advance the action dispatcher and select the actor's next movement or animation state. */
void func_8017102C(S_8017102C_0 *state, void *motion, S_8017102C_2 *sprite, S_8017102C_1 *actor) {
 u16 terrain_flags;
 u8 *frames;
 s32 room;
 s32 actor_flags;
 u16 flags;
 if(dungeonStatus.flags & 0x1000) {
  state->unk_9A=14;
  func_80171590(state,motion,sprite,actor);
  return;
 }
 if(actor->unk_25==0) {
  func_800AA79C(state,motion,sprite,actor);
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
   if(func_800AA924(state,motion,sprite,D_801752F4)!=0) return;
  }
  if(!(dungeonStatus.flags & 0x2000)) {
   if(actor->unk_1C & 0x100) {
    func_800AA258(state,motion,sprite,actor);
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
   if(actor->unk_64!=0 && func_800AA6B4(state,motion,sprite,D_801752BC)!=0) return;
   if(actor->unk_1C & 0x80000) {
    func_800AA888(state,motion,sprite,actor);
    func_80173A38(state,motion,sprite,actor);
    return;
   }
   if((func_800A1C58(actor)<<16)!=0 && (func_800AAB10(state,motion,sprite,actor)<<16)!=0)
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
    if((!(dungeonStatus.flags & 0x2000) || (func_8009A180(actor,((S_8017102C_3 *)D_800814A8)->unk_58+0x20)<<16)==0)
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
    actor->unk_2A=func_800A0818(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY,&terrain_flags);
    if(((S_8017102C_3 *)D_800814A8)->unk_9A==17) {
     func_800AAF00(state,motion,sprite,D_801752EC,func_8017102C);
     return;
    }
    /* A failed pursuit falls through to the same completion path as action 12. */
   case 12:
    func_800A9A0C(actor);
    return;
   case 1: case 2: case 3:
    func_800AAF00(state,motion,sprite,D_801752EC,func_8017102C);
    return;
   default:
    func_80171810(state,motion,sprite,actor);
    return;
   }
  }
  actor_flags=actor->unk_1C;
  if(!(actor_flags & 0x2000) && ((s8)room<0 || !(((S_8017102C_5 *)(D_800E2970+(s8)room*20))->unk_0C & 2)) && !(actor_flags & 0x430)) {
   if((func_8009FD7C(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY)<<16)!=0)
    actor->unk_2A=func_800A0818(sprite->tile.bytes.x,sprite->tile.bytes.y,D_80082E80.tileX,D_80082E80.tileY,&terrain_flags);
  }
  if((dungeonStatus.flags & 0x2000) || (sprite->unk_14 & 0x40)) return;
  frames=D_801752B4;
  if(sprite->unk_2C==frames) return;
 }
 sprite->unk_2C=frames;
 func_80047784(sprite,*((((gameWork.view.viewAngle+actor->unk_2A+0x100)>>9)&7)+frames),0);
}
