struct S_80083178Vector
{
  short x;
  short y;
  short z;
  short pad;
};
struct S_80083178State
{
  struct S_80083178Vector v[4];
};
struct S_80083178
{
  char pad0[2];
  unsigned short unk2;
  char pad4[6];
  unsigned short unkA;
  char padC[0x94 - 0xC];
  struct S_80083178State state_94;
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
extern struct S_80083178State D_80083CE8;
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef struct 
{
  void *next;
  u8 pad04[0x0D - 4];
  u8 field0D;
  u8 pad0E[0x14 - 0x0E];
  s16 state;
  s16 count;
  u16 flags;
  s16 phase;
} S_800BB14C;
typedef struct 
{
  u8 pad00[0x0C];
  s8 valueC;
  s8 valueD;
  s8 valueE;
  u8 pad0F[0x1E - 0x0F];
  u16 amount;
} S_800BB14C_TARGET;
extern s32 D_800814A0[3];
void func_800BB14C(void *arg0, register S_800BB14C *arg1, S_800BB14C_TARGET *arg2)
{
  s16 state;
  arg1 = (S_800BB14C *) arg0;
  state = arg1->state;
  if (state == 1)
  {
    goto check_status;
  }
  if (state < 2)
  {
    if (state == 0)
    {
      goto state_zero;
    }
    goto update_values;
  }
  if (state == 2)
  {
    goto state_two;
  }
  goto update_values;
  state_zero:
  {
    s16 phase = arg1->phase;
    u16 amount = arg2->amount + (phase * 0x10);
    arg2->amount = amount;
    if (amount < 0x4001U)
    {
      arg2->amount = 0x4000;
      arg1->state = ((s16) arg1->state) + 1;
    }
  }

  goto check_status;
  check_status:
  if ((((S_800BB14C_TARGET *) arg1->next)->amount & 0x8000) == 0)
  {
    goto update_values;
  }

  arg1->count = 4;
  arg1->state = 2;
  goto update_values;
  state_two:
  {
    s16 count = arg1->count;
    if (count != 0)
    {
      u16 amount = arg2->amount;
      arg2->amount = amount - (((s32) amount) / count);
    }
  }

  {
    s16 count = ((u16) arg1->count) - 1;
    arg1->count = count;
    if (count < 0)
    {
      u16 value = ((volatile u16 *) arg1)[-1];
      ((u16 *) arg1)[-1] = value | 0x8000;
      D_800814A0[0] = D_800814A0[0] | 0x8000;
      goto done;
    }
  }
  goto update_values;
  update_values:
  {
    u16 phase;
    s8 value;
    u8 phase_low;
    phase = arg1->phase;
    phase += 1;
    value = (arg1->field0D - 4) & 0xBF;
    do
    {
      arg1->phase = phase;
    }
    while (0);
    arg1->field0D = value;
    do
    {
      phase_low = arg1->phase;
    }
    while (0);
    phase_low &= 0x1F;
    if ((phase & 0x20) != 0)
    {
      value = 0x30 - phase_low;
    }
    else
    {
      value = phase_low + 0x10;
    }
    if (arg1->flags & 1)
    {
      arg2->valueC = value;
    }
    if (arg1->flags & 2)
    {
      arg2->valueD = value;
    }
    if (arg1->flags & 4)
    {
      arg2->valueE = value;
    }
  }

  done:
  return;
}
