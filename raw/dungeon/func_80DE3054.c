#include "common.h"
typedef void (*ActorAction)(void *,void *,void *,void *);
typedef struct {
 u8 pad00[0x13]; u8 kind; s32 flags14; u8 pad18[4]; s32 flags1C;
 u8 pad20[0x6C]; ActorAction handler;
} SpawnActor;
typedef struct {
 u8 pad00[0x8C]; ActorAction handler; u8 pad90[0xA]; u8 action_id;
 u8 pad9B; s8 direction;
} SpawnState;
typedef struct { u8 pad00[0xA]; s16 height; } SpawnMotion;
typedef struct { u8 pad00[0x24]; u8 tile_x,tile_y; u8 pad26[6]; u8 *frames; } SpawnSprite;
typedef struct { u8 pad00[8]; SpawnMotion *motion; SpawnSprite *sprite; void (*update)(void *,void *,void *); } SpawnObject;
extern SpawnObject *func_8003FD64(s32,void *);
extern void func_8004491C(void *,void *);
extern s32 func_800A6D30(void);
extern void func_800A48F0(void *,s32,s32);
extern void func_800A9C18(void *,void *,void *,s16);
extern void func_800AA36C(void *,void *,void *,void *);
extern void func_80170A58(void *,void *,void *);
extern void func_80170E5C(void *,void *,void *,void *);
extern void func_80045340(void *,void *,void *);
extern u8 D_80083498[];
extern u8 D_80174510[8],D_80174538[8];
/* Allocate an actor, initialize its action and sprite views, then apply spawn flags. */
void *func_80170854(s16 flags,s16 attr_x,s16 attr_y,s16 attr_height) {
 SpawnActor *actor=0;
 SpawnObject *object;
 SpawnMotion *motion;
 s16 saved_flags;
 s32 kind;
 s8 tile_x; s16 height; s8 tile_y;
 {
 SpawnSprite *sprite;
 SpawnState *state;
 tile_x=attr_x; height=attr_height; tile_y=attr_y;
 object=func_8003FD64(0x112,D_80083498);
 saved_flags=flags;
 if(object) {
  actor=(SpawnActor *)((u8 *)object+0x20);
  actor->kind=0x1C;
  func_8004491C(object,func_80045340);
  motion=object->motion;
  kind=flags&3;
  motion->height=height;
  sprite=object->sprite;
  sprite->tile_x=tile_x;
  sprite->tile_y=tile_y;
  state=(SpawnState *)actor;
  if(kind==1) {
   actor->handler=func_80170E5C;
   actor->flags14|=0x6000;
   actor->flags1C|=0x6000;
   sprite->frames=D_80174510;
  } else if(kind>=2) {
   actor->handler=func_80170E5C;
   actor->flags14|=0x2000;
   actor->flags1C|=0x2000;
   sprite->frames=D_80174510;
  } else if((s16)(flags&~3)==0) {
   if(!(actor->flags14&0x200) && (func_800A6D30()&1)) {
    func_800A48F0(actor,1,(func_800A6D30()&0x3F)|0x20);
    sprite->frames=D_80174538;
   }
   state->handler=func_80170E5C;
   sprite->frames=D_80174510;
  } else { actor->handler=func_80170E5C;
   sprite->frames=D_80174510;
  }
  object->update=func_80170A58;
  func_800A9C18(object,motion,sprite,saved_flags);
  state->action_id=0xFF;
  state->direction=-1;
  func_800AA36C(state,motion,sprite,actor);
 }
 }
 return actor;
}
