
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
extern void func_8009176C(void);
extern void func_800917C8(void);
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
void func_80091528(void *arg0, void *arg1, s32 arg2)
{
  u8 *state_base = D_80083160;
  register s32 saved_arg2;
  u8 *work;
  u8 *menu_base;
  s16 value;
  u16 timer;
  s32 input;
  s32 result;
  func_80095C80(arg1);
  func_800951B4(arg1);
  work = D_800FE488;
  value = func_80095978(arg1, work);
  if ((value - (*((s16 *) (((u8 *) arg1) + 0xA)))) >= 4)
  {
    if (D_800CFCEF == 0)
    {
      func_80094378(arg0, arg1, arg2);
      func_800917C8();
      return;
    }
  }
  else
    if (D_800CFCEF == 0)
  {
    func_80095A94(arg1, value, work);
  }
  timer = (*((u16 *) (((u8 *) arg0) + 0xA))) - 1;
  *((u16 *) (((u8 *) arg0) + 0xA)) = timer;
  if (((s16) timer) <= 0)
  {
    timer = func_800374F4(4) + 6;
    *((u16 *) (((u8 *) arg0) + 0xA)) = timer;
    func_80097844(arg1, ((u16) func_800374F4(2)) + 2);
  }
  input = *((s32 *) (state_base + 0x10));
  if (input & 0x10)
  {
    func_800942B0(arg0, arg1, arg2);
    func_800917C8();
    return;
  }
  if (input & 0x40)
  {
    result = func_80095840(arg0, &D_800CFCB4);
    if (result != 0)
    {
      if (result == 2)
      {
        func_8009451C(arg0, arg1, arg2);
        func_800917C8();
        return;
      }
      func_800944BC(arg0, arg1, arg2);
      func_800917C8();
      return;
    }
    if (func_80033B2C(0xA4) != 0)
    {
      func_80094088(arg0, arg1, arg2);
      func_800917C8();
      return;
    }
    return;
  }
  menu_base = (u8 *) (&D_800CFCB4);
  result = func_8009567C(menu_base);
  if (result != 0)
  {
    if (result == (-1))
    {
      func_80094C1C(arg0);
      func_80098868(arg0, arg1, arg2);
      *((s32 *) (((u8 *) arg0) + 0x2C)) = 0;
      func_8008B158(*((s32 *) (menu_base + 0x10)));
      func_800917C8();
      return;
    }
    func_800943B8(arg0, arg1, arg2);
    func_800917C8();
    return;
  }
  input = *((s32 *) (state_base + 8));
  if (!(input & 0x20))
  {
    func_80093ED8(arg0, arg1, arg2);
    func_8009176C();
    return;
  }
  if (input & 0xF000)
  {
    timer = (*((u16 *) (((u8 *) arg0) + 0x3E))) - 1;
    *((u16 *) (((u8 *) arg0) + 0x3E)) = timer;
    func_80094944((s16) timer, 8);
    func_80094C1C(arg0);
    func_8009503C(arg1);
    func_800917C8();
    return;
  }
  result = func_8003BD84(*((s32 *) (((u8 *) arg1) + 0xC)), *((s32 *) (((u8 *) arg1) + 0x10)));
  if (result > 0xFFFFF)
  {
    func_80093E18(arg0, arg1, arg2);
    func_800917C8();
    return;
  }
  func_80093D48(arg0, arg1, arg2);
}
