
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
  u8 pad0[0xC];
  u16 flags;
  u8 padE[6];
} DungeonRecord;
typedef void (*DungeonCallback)(void *, void *, void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void *func_800A04F0(void *, s32, s32, s32);
extern s32 func_800C7F68(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, DungeonCallback);
extern void func_801715F0(void *, void *, void *, void *);
extern void func_80171848(void *, void *, void *, void *);
extern s32 func_80171FF4(void *, void *, void *, void *);
extern void func_801721B8(void *, void *, void *, void *);
extern void func_801722E0(void *, void *, void *, void *);
extern s32 func_80172414(void *, void *, void *, s32);
extern void func_80173834(void *, void *, void *, void *);
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174880[];
extern u8 D_80174890[];
extern u8 D_801748C8;
extern u8 D_801748D8[];
extern u8 D_801748E0[];
extern DungeonRecord D_800E2970[];
extern void *D_80170808[];
void func_80171058(void *, void *, void *, void *);
void func_80171058(void *arg0, void *arg1, void *arg2, void *arg3)
{
  s32 scratch;
  s8 result;
  u16 state;
  void *new_var;
  u32 initial_flags = D_80083462;
  if (initial_flags & 0x1000)
  {
    *((u8 *) (((u8 *) arg0) + 0x9A)) = 0xE;
    func_801715F0(arg0, arg1, arg2, arg3);
    goto row_epilogue;
  }
  if ((*((u8 *) (((u8 *) arg3) + 0x25))) == 0)
  {
    void *table;
    func_800AA79C(arg0, arg1, arg2, arg3);
    if ((*((void **) (((u8 *) arg2) + 0x2C))) == D_801748E0)
    {
      return;
    }
    table = D_801748D8;
    *((void **) (((u8 *) arg2) + 0x2C)) = table;
    func_80047784(arg2, ((u8 *) table)[(((D_80083228 + (*((s16 *) (((u8 *) arg3) + 0x2A)))) + 0x100) >> 9) & 7], 0);
    goto row_epilogue;
  }
  new_var = arg2;
  if ((*((u32 *) (((u8 *) arg3) + 0x1C))) & 0x200)
  {
    if ((*((void **) (((u8 *) new_var) + 0x2C))) == D_801748E0)
    {
      *((u8 *) (((u8 *) arg0) + 0x9A)) = 0xD;
      *((u8 *) (((u8 *) arg0) + 0x9B)) = 1;
      *((s32 *) (((u8 *) arg0) + 0x8C)) = 0;
      *((u32 *) (((u8 *) arg3) + 0x1C)) &= 0xFFFBFFFF;
      goto row_epilogue;
    }
    if (func_800AA924(arg0, arg1, new_var, D_801748D8) != 0)
    {
      return;
    }
  }
  if (!(D_80083462 & 0x2000))
  {
    if ((*((u32 *) (((u8 *) arg3) + 0x1C))) & 0x100)
    {
      func_800AA258(arg0, arg1, new_var, arg3);
      goto row_epilogue;
    }
    {
      register void *current;
      void *table;
      switch (*((u8 *) (((u8 *) arg0) + 0x9A)))
      {
        case 0xE:
          break;

        default:
          *((u8 *) (((u8 *) arg0) + 0x9A)) = 0xE;
          break;

      }

      current = *((void **) (((u8 *) new_var) + 0x2C));
      table = D_80174880;
      if (current != table)
      {
        *((void **) (((u8 *) new_var) + 0x2C)) = table;
        func_80047784(new_var, ((u8 *) table)[(((D_80083228 + (*((s16 *) (((u8 *) arg3) + 0x2A)))) + 0x100) >> 9) & 7], 0);
        *((u8 *) (((u8 *) new_var) + 5)) = 1;
        *((s16 *) (((u8 *) arg0) + 0xA6)) = 0;
        *((s16 *) (((u8 *) arg0) + 0xB2)) = 0;
      }
    }
    *((u32 *) (((u8 *) arg3) + 0x1C)) |= 0x40000;
    *((u16 *) (((u8 *) arg0) + 0x98)) &= 0xFFF7;
    if ((*((s16 *) (((u8 *) arg3) + 0x64))) != 0)
    {
      if (func_800AA6B4(arg0, arg1, new_var, D_80174890) != 0)
      {
        return;
      }
    }
    if ((*((u32 *) (((u8 *) arg3) + 0x1C))) & 0x80000)
    {
      s16 delta;
      func_800AA888(arg0, arg1, new_var, arg3);
      delta = (*((u16 *) (((u8 *) arg0) + 0x92))) - (*((u16 *) (((u8 *) arg0) + 0xA6)));
      *((s16 *) (((u8 *) arg0) + 0xA6)) = 0;
      *((s16 *) (((u8 *) arg0) + 0xB2)) = 0;
      *((s16 *) (((u8 *) arg0) + 0x92)) = delta;
      func_80173834(arg0, arg1, new_var, arg3);
      goto row_epilogue;
    }
    if ((func_800A1C58(arg3) << 16) != 0)
    {
      func_800AAB10(arg0, arg1, new_var, arg3);
    }
  }
  result = func_8009FB34(*((u8 *) (((u8 *) new_var) + 0x24)), *((u8 *) (((u8 *) new_var) + 0x25)));
  *((u8 *) (((u8 *) new_var) + 0x26)) = result;
  if ((*((s8 *) (((u8 *) arg3) + 0x6D))) > 0)
  {
    if ((*((u32 *) (((u8 *) arg3) + 0x1C))) & 0x20)
    {
      goto special_cleanup;
    }
    if ((*((u16 *) (((u8 *) new_var) + 0x24))) == (*((u16 *) (&D_80082EA4))))
    {
      goto ordinary_cleanup;
    }
    if (!((*((u16 *) (((u8 *) arg3) + 0x46))) & 0x8000))
    {
      if (D_80083462 & 0x2000)
      {
        if ((func_8009A180(arg3, ((u8 *) (*((void **) (((u8 *) D_800814A8) + 0x58)))) + 0x20) << 16) != 0)
        {
          return;
        }
      }
      if ((func_80172414(arg0, arg1, new_var, 0) << 16) == 0)
      {
        return;
      }
      state = (*((u16 *) (((u8 *) arg3) + 0x46))) | 0x4000;
      *((u16 *) (((u8 *) arg3) + 0x46)) = state;
      if (!(state & 0x8000))
      {
        goto ordinary_cleanup;
      }
    }
    state = (*((u16 *) (((u8 *) arg3) + 0x46))) & 0x3FFF;
    if (((u32) (state - 1)) >= 12)
    {
      goto ordinary_cleanup;
    }
    switch (state - 1)
    {
      case 0:

      case 1:

      case 2:
        goto aaf_cleanup;

      case 3:
        goto ordinary_cleanup;

      case 4:

      case 5:

      case 6:
        goto coords_case;

      case 7:
        goto handler_case;

      case 8:
        goto case8_case;

      case 9:

      case 10:
        goto ordinary_cleanup;

      case 11:
        goto special_cleanup;

      default:
        goto ordinary_cleanup;

    }

    case8_case:
    {
      void *object = func_800A04F0(arg3, *((u8 *) (((u8 *) new_var) + 0x24)), *((u8 *) (((u8 *) new_var) + 0x25)), *((s16 *) (((u8 *) arg3) + 0x2A)));
      *((void **) (((u8 *) arg0) + 0xA8)) = object;
      if (object == 0)
      {
        goto ordinary_cleanup;
      }
      if (func_800C7F68(object) != 0)
      {
        goto ordinary_cleanup;
      }
      if ((*((u8 *) (((u8 *) (*((void **) (((u8 *) arg0) + 0xA8)))) + 0x13))) < 0x33)
      {
        func_801722E0(arg0, arg1, new_var, arg3);
        goto row_epilogue;
      }
      goto ordinary_cleanup;
    }

    handler_case:
    if ((func_80171FF4(arg0, arg1, new_var, arg3) << 16) != 0)
    {
      return;
    }

    func_801721B8(arg0, arg1, new_var, arg3);
    goto row_epilogue;
    coords_case:
    {
      u8 *origin = D_80082E80;
      void *player;
      s16 coordinate;
      coordinate = func_800A0818(*((u8 *) (((u8 *) new_var) + 0x24)), *((u8 *) (((u8 *) new_var) + 0x25)), *((u8 *) (((u8 *) origin) + 0x24)), *((u8 *) (((u8 *) origin) + 0x25)), &scratch);
      player = D_800814A8;
      *((s16 *) (((u8 *) arg3) + 0x2A)) = coordinate;
      if ((*((u8 *) (((u8 *) player) + 0x9A))) == 0x11)
      {
        goto aaf_cleanup;
      }
    }

    special_cleanup:
    func_800A9A0C(arg3);

    goto row_epilogue;
    aaf_cleanup:
    func_800AAF00(arg0, arg1, new_var, &D_801748C8, func_80171058);

    goto row_epilogue;
    ordinary_cleanup:
    func_80171848(arg0, arg1, new_var, arg3);

    goto row_epilogue;
  }
  if (!((*((u32 *) (((u8 *) arg3) + 0x1C))) & 0x2000))
  {
    s32 index = result;
    if ((index < 0) || (!(D_800E2970[index].flags & 2)))
    {
      if (!((*((u32 *) (((u8 *) arg3) + 0x1C))) & 0x430))
      {
        u8 *origin = D_80082E80;
        if ((func_8009FD7C(*((u8 *) (((u8 *) new_var) + 0x24)), *((u8 *) (((u8 *) new_var) + 0x25)), *((u8 *) (((u8 *) origin) + 0x24)), *((u8 *) (((u8 *) origin) + 0x25))) << 16) != 0)
        {
          *((s16 *) (((u8 *) arg3) + 0x2A)) = func_800A0818(*((u8 *) (((u8 *) new_var) + 0x24)), *((u8 *) (((u8 *) new_var) + 0x25)), *((u8 *) (((u8 *) origin) + 0x24)), *((u8 *) (((u8 *) origin) + 0x25)), &scratch);
        }
      }
    }
  }
  row_epilogue:
  return;

}
