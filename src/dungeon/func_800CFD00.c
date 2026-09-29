#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef s32 M2C_UNK;
extern void func_8003DB94(void *, void *, s32);
extern void *func_8003FC64(s32);
extern void func_800A56E0(s32);
extern M2C_UNK D_800D5294;
extern M2C_UNK D_800DECF8[3];
/* Creates a colored effect at the source object's position. */
void func_800D5460(void *source, s32 color, unsigned short event_id)
{
  DungeonGlobalStatus *effect_state;
  s32 *color_ptr;
  s32 event_code;
  s32 effect_color;
  void *render_setup;
  void *render_data;
  void *effect_data;
  void *render_params;
  void *effect;
  void *position;
  color_ptr = &color;
  effect = func_8003FC64(0x12);
  if (effect != 0)
  {
    effect_data = effect + 0x20;
    *((void **) (((u8 *) effect_data) + 0x24)) = source;
    *((M2C_UNK **) (((u8 *) effect) + 0x10)) = &D_800D5294;
    *((s16 *) (((u8 *) effect_data) + 0x1E)) = 0x32;
    render_setup = *((void **) (((u8 *) effect) + 0xC));
    *((s16 *) (((u8 *) render_setup) + 0x10)) = 0x20;
    *((u16 *) (((u8 *) render_setup) + 0x14)) = (u16) ((*((u16 *) (((u8 *) render_setup) + 0x14))) | 0xC);
    position = *((void **) (((u8 *) effect) + 8));
    *((u16 *) (((u8 *) position) + 2)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 2)));
    *((u16 *) (((u8 *) position) + 6)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 6)));
    *((u16 *) (((u8 *) position) + 0xA)) = (u16) (*((u16 *) (((u8 *) (*((void **) (((u8 *) source) + 8)))) + 0xA)));
    render_data = *((void **) (((u8 *) effect) + 0xC));
    *((u8 *) (((u8 *) render_data) + 0xE)) = 0x80;
    *((u8 *) (((u8 *) render_data) + 0xD)) = 0x80;
    *((u8 *) (((u8 *) render_data) + 0xC)) = 0x80;
    effect_color = *color_ptr;
    *((s16 *) (((u8 *) render_data) + 0x1E)) = 0x1000;
    *((s16 *) (((u8 *) render_data) + 0x1C)) = 0x1000;
    *((s32 *) (((u8 *) render_data) + 0xC)) = effect_color;
    *((s32 *) (((u8 *) effect_data) + 0xC)) = effect_color;
    *((s16 *) (((u8 *) render_data) + 0x12)) = 0x7DCE;
    render_params = D_800DECF8;
    *((u16 *) (((u8 *) render_data) + 0x14)) = (u16) ((*((u16 *) (((u8 *) render_data) + 0x14))) | 0x100);
    func_8003DB94(render_data, render_params, 0);
    event_code = event_id & 0xFFFF;
    if (event_code != 0)
    {
      func_800A56E0(event_code);
    }
    effect_state = &dungeonStatus;
    *((u16 *) (((u8 *) effect_state) + 0xA)) = (u16) ((*((u16 *) (((u8 *) effect_state) + 0xA))) + 1);
  }
}
