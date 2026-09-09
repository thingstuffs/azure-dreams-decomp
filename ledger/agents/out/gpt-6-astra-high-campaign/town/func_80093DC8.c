
struct S_80083178
{
  char pad0[2];
  unsigned short unk2;
  char pad4[6];
  unsigned short unkA;
  char padC[0x94];
  short f_A0;
  char pad_a2[2];
  short f_A4;
  short f_A6;
  short f_A8;
  char pad_aa[0xB4 - 0xAA];
  void (*callback)(void);
  void *field_B8;
  char pad_bc[(0xD8 - 0xB8) - 4];
  void *ptr;
  char pad_dc[0x1C4 - 0xDC];
};
typedef struct 
{
  unsigned char data[24];
} MonsterInitialStats;
typedef struct 
{
  unsigned char data[12];
} Trap;
typedef struct 
{
  unsigned char data[8];
} StatGrowth;
extern int D_800814C8;
extern int D_80081550;
extern int D_80081558;
extern int D_80081554;
extern unsigned char D_80071298[];
extern volatile int D_80071250[];
extern int D_800712B4[];
extern int D_80084130[3];
extern short D_80084808[8];
extern struct S_80083178 D_80083178;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern s32 func_80033B2C(s32 arg0);
extern s32 func_800374F4(s32 arg0);
extern s32 func_8003BD84(s32 arg0, s32 arg1);
extern void func_8008B158(s32 arg0);
extern void func_80093D48(void *arg0, void *arg1, s32 arg2);
extern void func_80093E18(void *arg0, void *arg1, s32 arg2);
extern void func_80093ED8(void *arg0, void *arg1, s32 arg2);
extern void func_80094088(void *arg0, void *arg1, s32 arg2);
extern void func_800942B0(void *arg0, void *arg1, s32 arg2);
extern void func_80094378(void *arg0, void *arg1, s32 arg2);
extern void func_800943B8(void *arg0, void *arg1, s32 arg2);
extern void func_800944BC(void *arg0, void *arg1, s32 arg2);
extern void func_8009451C(void *arg0, void *arg1, s32 arg2);
extern void func_80094944(s16 arg0, s32 arg1);
extern void func_80094C1C(void *arg0);
extern void func_8009503C(void *arg0);
extern void func_800951B4(void *arg0);
extern s32 func_8009567C(void *arg0);
extern s32 func_80095840(void *arg0, void *arg1);
extern s16 func_80095978(void *arg0, void *arg1);
extern void func_80095A94(void *arg0, s16 arg1, void *arg2);
extern void func_80095C80(void *arg0);
extern void func_80097844(void *arg0, s32 arg1);
extern void func_80098868(void *arg0, void *arg1, s32 arg2);
extern u8 D_80083160[];
extern s32 D_800CFCB4;
extern u8 D_800CFCEF;
extern u8 D_800FE488[];
/* Updates the actor and dispatches town actions from input and interaction state. */
void func_80091528(void *action_state, void *actor, s32 context)
{
  u8 *input_state = D_80083160;
  register s32 saved_context;
  u8 *map_work;
  u8 *menu_state;
  s16 sampled_height;
  u16 timer;
  s32 buttons;
  s32 action_result;
  func_80095C80(actor);
  func_800951B4(actor);
  map_work = D_800FE488;
  sampled_height = func_80095978(actor, map_work);
  if ((sampled_height - (*((s16 *) (((u8 *) actor) + 0xA)))) >= 4)
  {
    if (D_800CFCEF == 0)
    {
      func_80094378(action_state, actor, context);
      return;
    }
  }
  else
    if (D_800CFCEF == 0)
  {
    func_80095A94(actor, sampled_height, map_work);
  }
  timer = (*((u16 *) (((u8 *) action_state) + 0xA))) - 1;
  *((u16 *) (((u8 *) action_state) + 0xA)) = timer;
  if (((s16) timer) <= 0)
  {
    timer = func_800374F4(4) + 6;
    *((u16 *) (((u8 *) action_state) + 0xA)) = timer;
    func_80097844(actor, ((u16) func_800374F4(2)) + 2);
  }
  buttons = *((s32 *) (input_state + 0x10));
  if (buttons & 0x10)
  {
    func_800942B0(action_state, actor, context);
    return;
  }
  if (buttons & 0x40)
  {
    action_result = func_80095840(action_state, &D_800CFCB4);
    if (action_result != 0)
    {
      if (action_result == 2)
      {
        func_8009451C(action_state, actor, context);
        return;
      }
      func_800944BC(action_state, actor, context);
      return;
    }
    if (func_80033B2C(0xA4) != 0)
    {
      func_80094088(action_state, actor, context);
      return;
    }
    return;
  }
  menu_state = (u8 *) (&D_800CFCB4);
  action_result = func_8009567C(menu_state);
  if (action_result != 0)
  {
    if (action_result == (-1))
    {
      func_80094C1C(action_state);
      func_80098868(action_state, actor, context);
      *((s32 *) (((u8 *) action_state) + 0x2C)) = 0;
      func_8008B158(*((s32 *) (menu_state + 0x10)));
      return;
    }
    func_800943B8(action_state, actor, context);
    return;
  }
  buttons = *((s32 *) (input_state + 8));
  if (!(buttons & 0x20))
  {
    func_80093ED8(action_state, actor, context);
    goto finish;
  }
  if (buttons & 0xF000)
  {
    timer = (*((u16 *) (((u8 *) action_state) + 0x3E))) - 1;
    *((u16 *) (((u8 *) action_state) + 0x3E)) = timer;
    func_80094944((s16) timer, 8);
finish:
    func_80094C1C(action_state);
    func_8009503C(actor);
    return;
  }
  action_result = func_8003BD84(*((s32 *) (((u8 *) actor) + 0xC)), *((s32 *) (((u8 *) actor) + 0x10)));
  if (action_result > 0xFFFFF)
  {
    func_80093E18(action_state, actor, context);
    return;
  }
  func_80093D48(action_state, actor, context);
}
