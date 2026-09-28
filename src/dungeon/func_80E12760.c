#include "shared/game_work.h"
#include "shared/slus_callbacks.h"
#include "shared/dir_step.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef struct 
{
  u32 words[6];
} Copy24;
typedef struct 
{
  u16 x;
  u16 y;
  u16 z;
} Vec3u16;
extern void *func_8003FC64(s32 size);
extern void func_8004491C(void *object, void *callback);
extern void func_80047784(void *object, s32 kind, s32 arg2);
extern void *func_8003DE58(void *arg0, void *arg1, Vec3u16 *out, s32 arg3);
extern u8 D_80175978;
/* Create a render object and initialize its position and motion toward a directional target. */
void *func_80175F60(void *emitter, Copy24 *position, void *source)
{
  void *emitter_copy;
  Copy24 target_position;
  Vec3u16 position_offset;
  u16 direction_flags;
  s32 direction_offset;
  Copy24 *position_data;
  void *object;
  void *transform;
  void *source_copy;
  void *render;
  void *result;
  position_data = position;
  source_copy = source;
  direction_flags = *((u16 *) (((u8 *) emitter) + 0x2A));
  emitter_copy = emitter;
  target_position = *position_data;
  direction_offset = (direction_flags >> 8) & 0xE;
  *((u16 *) (((u8 *) (&target_position)) + 2)) += ((*((s16 *) (((u8 *) (((u8 *)dirStepX))) + direction_offset))) * (*((s16 *) (((u8 *) emitter) + 0xB2)))) * 0x40;
  *((u16 *) (((u8 *) (&target_position)) + 6)) += ((*((s16 *) (((u8 *) (((u8 *)dirStepY))) + direction_offset))) * (*((s16 *) (((u8 *) emitter_copy) + 0xB2)))) * 0x40;
  object = func_8003FC64(0x312);
  if (object != 0)
  {
    *((void **) (((u8 *) object) + 0x10)) = &D_80175978;
    func_8004491C(object, func_80045340);
    render = *((void **) (((u8 *) object) + 0xC));
    *((s32 *) (((u8 *) render) + 0x28)) = *((s32 *) (((u8 *) source_copy) + 0x28));
    *((s16 *) (((u8 *) render) + 0x1E)) = 0x800;
    *((s16 *) (((u8 *) render) + 0x1C)) = 0x800;
    *((u32 *) (((u8 *) render) + 0xC)) = 0x00808080;
    *((u16 *) (((u8 *) render) + 0x14)) |= 0xC;
    *((u16 *) (((u8 *) render) + 0x10)) |= 0x20;
    func_80047784(render, 0x47, 0);
    transform = *((void **) (((u8 *) object) + 8));
    *((Copy24 *) (((u8 *) object) + 0x24)) = *position_data;
    position_data = (Copy24 *) (((u8 *) object) + 0x20);
    position_offset.z = 0;
    position_offset.y = 0;
    position_offset.x = 0;
    if (func_8003DE58(*((void **) (((u8 *) source_copy) + 8)), source_copy, &position_offset, 1) != 0)
    {
      *((u16 *) (((u8 *) position_data) + 6)) += position_offset.x;
      *((u16 *) (((u8 *) transform) + 2)) = *((u16 *) (((u8 *) position_data) + 6));
      *((u16 *) (((u8 *) position_data) + 0xA)) += position_offset.y;
      *((u16 *) (((u8 *) transform) + 6)) = *((u16 *) (((u8 *) position_data) + 0xA));
      *((u16 *) (((u8 *) position_data) + 0xE)) += position_offset.z;
      *((u16 *) (((u8 *) transform) + 0xA)) = *((u16 *) (((u8 *) position_data) + 0xE));
    }
    *((s32 *) (((u8 *) position_data) + 0x10)) = (((s32) target_position.words[0]) - (*((s32 *) (((u8 *) position_data) + 4)))) / 0x20;
    *((s32 *) (((u8 *) position_data) + 0x14)) = (((s32) target_position.words[1]) - (*((s32 *) (((u8 *) position_data) + 8)))) / 0x20;
    result = object;
    return result;
  }
  if (position_data || source)
  {
    return 0;
  }
  else
  {
    return 0;
  }
}
