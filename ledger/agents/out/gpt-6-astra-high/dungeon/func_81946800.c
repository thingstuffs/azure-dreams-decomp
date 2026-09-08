#include "common.h"


extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
/* Row head: the 884-byte row begins with one raw data word (0x80024004)
 * ahead of the code entry. Landed idiom (overlays/dungeon/first_pass_matched/
 * func_8199A800.c): label the row symbol at the head of the function's own
 * named section, emit the word there, and compile the body into the same
 * section under a renamed assembler symbol so the bytes stay contiguous. */
#ifdef __mips__
__asm__(".section .text.func_81946800,\"a\",@progbits\n.globl func_81946800\n.type func_81946800,@function\nfunc_81946800:\n.size func_81946800, 884");
static const u32 func_81946800_head[] __attribute__((section(".text.func_81946800"))) = {0x80024004};
#endif
extern void func_800242D8(void) __attribute__((noreturn));
extern void func_80024350(s32) __attribute__((noreturn));
extern s32 func_8003DE58(s32, void *, s16 *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, u8, s32);
extern s32 func_80053EF0(s32, void *);
extern void func_800A56E0(s32);
extern s32 D_80024374;
extern s32 D_80045340;
extern s32 D_800814A0;
extern void *D_800814A8;
extern u16 D_80082E94;
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80083498[];
#ifdef __mips__
#define STATE3_PAGE 0x80080000U
#define STATE3_FLAG(page) (*((u16 *) ((page) + 0x2E94)))
#else
#define STATE3_PAGE 0U
#define STATE3_FLAG(page) D_80082E94
#endif
#ifdef __mips__
void func_81946800(void *action_in, void *saved_position) __asm__("func_81946800_body")
    __attribute__((section(".text.func_81946800")));
#endif

/* Advance a timed action, spawn its effect, and update completion flags. */
void func_81946800(void *action_in, void *saved_position)
{
  void *action;
  void *owner_work;   /* MATCH pin: retail schedule: same instructions, different order without it */
  register u8 *owner ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
  register void *effect ASM_REG("$17");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
  void *effect_part;
  void *offset_part;
  void *source_part;
  void *position;
  void *shared_data;
  u8 *effect_work;
  u8 *shared_state;
  s16 offsets[3];
  s32 state;
  s32 timer;
  u16 action_flags;
  s32 event_code;
  s32 color_index;
  u8 *colors;
  u32 state3_page;
  action = action_in;
  timer = (*((u16 *) (((u8 *) action) + 0x50))) - 1;
  owner_work = *((void **) (((u8 *) action) + 0));
  state = *((s16 *) (((u8 *) action) + 0xA));
  owner = ((u8 *) owner_work) - 0x20;
  *((u16 *) (((u8 *) action) + 0x50)) = timer;
  if (state == 1)
  {
    goto state_1;
    func_80024350(timer);
  }
  if (state < 2)
  {
    if (state == 0)
    {
      goto state_0;
    }
    func_80024350(timer);
    return;
  }
  ASM_SCHED_BARRIER();   /* MATCH pin: keeps a statement from moving across a call/branch */
  if (state == 2)
  {
    goto state_2;
  }
  state3_page = 3;
  if (state == state3_page)
  {
    state3_page = STATE3_PAGE;
    goto state_3;
  }
  state3_page = STATE3_PAGE;
  func_80024350(timer);
  return;
  state_0:
  *((s32 *) (((u8 *) D_800814A8) + 0xF4)) = 0;

  *((s32 *) (((u8 *) saved_position) + 0)) = *((s32 *) (((u8 *) (*((void **) (((u8 *) owner) + 8)))) + 0));
  *((s32 *) (((u8 *) saved_position) + 4)) = *((s32 *) (((u8 *) (*((void **) (((u8 *) owner) + 8)))) + 4));
  *((s32 *) (((u8 *) saved_position) + 8)) = *((s32 *) (((u8 *) (*((void **) (((u8 *) owner) + 8)))) + 8));
  (*((u16 *) (((u8 *) action) + 0xA)))++;
  state_1:
  if (((*((u16 *) (((u8 *) (*((void **) (((u8 *) action) + 4)))) + 0))) & 0x80) == 0)
  {
    return;
  }

  shared_data = D_800814A8;
  *((u16 *) (((u8 *) action) + 0x50)) = 10;
  (*((u16 *) (((u8 *) shared_data) + 0xA6)))--;
  *((u8 *) (((u8 *) shared_data) + 0xA8)) = *((u8 *) (((u8 *) action) + 8));
  effect = func_8003FD64(0x312, D_80083498);
  if (effect != 0)
  {
    offset_part = *((void **) (((u8 *) owner) + 0xC));
    if (func_8003DE58(*((s32 *) (((u8 *) offset_part) + 8)), offset_part, offsets, 0) == 0)
    {
      offsets[2] = 0;
      offsets[1] = 0;
      offsets[0] = 0;
    }
    *((void **) (((u8 *) effect) + 0x10)) = &D_80024374;
    *((void **) (((u8 *) effect) + 0x20)) = action;
    func_8004491C(effect, &D_80045340);
    source_part = *((void **) (((u8 *) owner_work) + (-0x14)));
    effect_part = *((void **) (((u8 *) effect) + 0xC));
    *((s32 *) (((u8 *) effect_part) + 0x28)) = *((s32 *) (((u8 *) source_part) + 0x28));
    *((u16 *) (((u8 *) effect_part) + 0x14)) = (*((u16 *) (((u8 *) source_part) + 0x14))) & 0x97FF;
    colors = *((u8 **) (((u8 *) source_part) + 0x2C));
    *((u8 **) (((u8 *) effect_part) + 0x2C)) = colors;
    color_index = ((D_80083228 + (*((s16 *) (((u8 *) owner_work) + 0x2A)))) + 0x100) >> 9;
    colors += color_index & 7;
    func_80047784(effect_part, *colors, 0);
    *((s16 *) (((u8 *) effect_part) + 0x1E)) = 0x1000;
    *((s16 *) (((u8 *) effect_part) + 0x1C)) = 0x1000;
    *((s32 *) (((u8 *) effect_part) + 0xC)) = 0x80FF;
    effect_work = ((u8 *) effect) + 0x20;
    *((s16 *) (((u8 *) effect_part) + 0x10)) = 0x20;
    *((u16 *) (((u8 *) effect_part) + 0x12)) -= 0x80;
    *((u16 *) (((u8 *) effect_part) + 0x14)) |= 0xC;
    position = *((void **) (((u8 *) owner) + 8));
    *((s32 *) (((u8 *) effect_work) + 0x1C)) = (*((s32 *) (((u8 *) position) + 0))) + (offsets[0] << 16);
    position = *((void **) (((u8 *) owner) + 8));
    *((s32 *) (((u8 *) effect_work) + 0x20)) = (*((s32 *) (((u8 *) position) + 4))) + (offsets[1] << 16);
    position = *((void **) (((u8 *) owner) + 8));
    *((s32 *) (((u8 *) effect_work) + 0x24)) = (*((s32 *) (((u8 *) position) + 8))) + (offsets[2] << 16);
    {
      void *owner_position;
      void *effect_position;
      u16 coord_integer;
      owner_position = *((void **) (((u8 *) owner) + 8));
      effect_position = *((void **) (((u8 *) effect) + 8));
      coord_integer = *((u16 *) (((u8 *) owner_position) + 2));
      *((u16 *) (((u8 *) effect_work) + 0xC)) = coord_integer;
      *((u16 *) (((u8 *) effect_position) + 2)) = coord_integer;
      owner_position = *((void **) (((u8 *) owner) + 8));
      effect_position = *((void **) (((u8 *) effect) + 8));
      coord_integer = *((u16 *) (((u8 *) owner_position) + 6));
      *((u16 *) (((u8 *) effect_work) + 0xE)) = coord_integer;
      *((u16 *) (((u8 *) effect_position) + 6)) = coord_integer;
      owner_position = *((void **) (((u8 *) owner) + 8));
      effect_position = *((void **) (((u8 *) effect) + 8));
      coord_integer = *((u16 *) (((u8 *) owner_position) + 0xA));
      *((u16 *) (((u8 *) effect_work) + 0x10)) = coord_integer;
      *((u16 *) (((u8 *) effect_position) + 0xA)) = coord_integer;
    }
    if (func_80053EF0(4, effect_work) != 2)
    {
      event_code = 0x300;
    }
    else
    {
      event_code = 0x4300;
    }
    func_800A56E0(event_code);
  }
  {
    s32 next_state;
    next_state = (*((u16 *) (((u8 *) action) + 0xA))) + 1;
    ASM_TAILSLOT_PIN(next_state);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    func_800242D8();
  }
  return;
  state_2:
  if (((s32) (timer << 16)) > 0)
  {
    return;
  }

  *((u16 *) (((u8 *) action) + 0x50)) = 8;
  (*((u16 *) (((u8 *) action) + 0xA)))++;
  func_80024350(timer);
  return;
  state_3:
  if (((STATE3_FLAG(state3_page) & 0x8000) == 0) && (((s32) (timer << 16)) >= 0))
  {
    return;
  }

  action_flags = *((u16 *) (((u8 *) action) + 0x52));
  if ((*((s16 *) (((u8 *) action) + 0x52))) & 0x8000)
  {
    *((u16 *) (((u8 *) action) + 0x52)) = action_flags & 0x7FFF;
    func_80024350(timer);
    return;
  }
  shared_state = (u8 *) (&D_80083460);
  *((s32 *) (((u8 *) shared_state) + 0xC)) = 0;
  (*((u16 *) (((u8 *) shared_state) + 0xA)))--;
  *((u16 *) (((u8 *) action) + (-2))) |= 0x8000;
  D_800814A0 |= 0x8000;
}
