
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
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;
struct S_80083160;
typedef struct S_80083160 S_80083160;
extern S_80083160 D_80083160;
int abs(int);
s32 func_80065420();
M2C_UNK func_80066640();
M2C_UNK func_800666F4();
M2C_UNK func_800DBA90();
typedef struct
{
  u16 x;
  u16 y;
  u16 z;
  u16 pad;
} E_SVEC;
typedef struct
{
  u16 x;
  u16 y;
} E_DVEC;
typedef struct
{
  void *p0;
  void *p1;
  s16 f08;
  s16 f0A;
  u16 f0C;
  s16 f0E;
  s16 f10;
  s16 f12;
  s16 f14;
  s16 f16;
  s16 f18;
  s16 f1A;
  s32 f1C;
} E_PRIM;
s32 func_819A7320(void *arg0)
{
  E_SVEC sp10;
  s32 otz[6];
  E_DVEC sxy[6];
  E_PRIM prim;
  s32 p;
  s32 var_s3;
  s32 temp_a3;
  s32 var_v1;
  s32 temp_a0_3;
  s32 temp_a0_4;
  S_80083160 *base;
  void *temp_s0;
  void *temp_a0;
  void *obj;
  int new_var;
  u8 temp_v0;
  u8 temp_v0_2;
  u8 temp_v0_3;
  u8 temp_v0_4;
  base = &D_80083160;
  do
  {
    obj = arg0;
    var_s3 = 4;
    do
    {
      otz[var_s3] = (s32) (func_80065420(((u8 *) obj) + ((var_s3 * 8) + 4), &sxy[var_s3], &p, &p) - 8);
      var_s3 -= 1;
    }
    while (var_s3 >= 0);
    sp10.x = *((u16 *) (((s8 *) obj) + 4));
    sp10.y = *((u16 *) (((s8 *) obj) + 6));
    sp10.z = (u16) ((*((u16 *) (((s8 *) obj) + 8))) + 0x30);
    func_80065420(&sp10, &sxy[5], &p, &p);
    sp10.x = 0;
    sp10.z = 0;
    prim.p1 = &sp10;
    prim.p0 = &sp10;
    prim.f0A = 0;
    prim.f08 = 0;
    prim.f14 = 0;
    prim.f12 = 0;
    prim.f10 = 0;
    prim.f1A = 0;
    prim.f18 = 1;
    new_var = (s16) sxy[0].y;
    new_var = new_var - ((s16) sxy[5].y);
    sp10.y = (u16) abs((s32) new_var);
    prim.f0C = *((u16 *) (((s8 *) base) + 0xC8));
    func_800DBA90(&prim, (s16) sxy[5].y);
    for (var_s3 = 0; var_s3 < 4; var_s3++)
    {
      temp_s0 = *((void **) (((s8 *) (*((void **) (((s8 *) base) + 0)))) + 0x8D0));
      *((void **) (((s8 *) (*((void **) (((s8 *) base) + 0)))) + 0x8D0)) = (void *) (((u8 *) temp_s0) + 0x28);
      *((s32 *) (((s8 *) temp_s0) + 4)) = *((s32 *) (((s8 *) obj) + 0x38));
      func_800666F4(temp_s0);
      func_80066640(temp_s0, 1);
      *((u16 *) (((s8 *) temp_s0) + 0x16)) = (u16) (*((u16 *) (((s8 *) obj) + 0x40)));
      *((u16 *) (((s8 *) temp_s0) + 0xE)) = (u16) (*((u16 *) (((s8 *) obj) + 0x42)));
      *((s16 *) (((s8 *) temp_s0) + 8)) = (s16) (sxy[var_s3].x - sp10.x);
      *((s16 *) (((s8 *) temp_s0) + 0x10)) = (s16) (sxy[var_s3 + 1].x - sp10.x);
      *((s16 *) (((s8 *) temp_s0) + 0x18)) = (s16) (sxy[var_s3].x + sp10.x);
      *((s16 *) (((s8 *) temp_s0) + 0x20)) = (s16) (sxy[var_s3 + 1].x + sp10.x);
      *((s16 *) (((s8 *) temp_s0) + 0xA)) = (s16) (sxy[var_s3].y - sp10.y);
      *((s16 *) (((s8 *) temp_s0) + 0x1A)) = (s16) (sxy[var_s3].y + sp10.y);
      *((s16 *) (((s8 *) temp_s0) + 0x12)) = (s16) (sxy[var_s3 + 1].y - sp10.y);
      *((s16 *) (((s8 *) temp_s0) + 0x22)) = (s16) (sxy[var_s3 + 1].y + sp10.y);
      temp_v0 = *((u8 *) (((s8 *) obj) + 0x2C));
      *((u8 *) (((s8 *) temp_s0) + 0x1C)) = temp_v0;
      *((u8 *) (((s8 *) temp_s0) + 0xC)) = temp_v0;
      temp_v0_2 = (u8) (temp_v0 + (*((u8 *) (((s8 *) obj) + 0x30))));
      *((u8 *) (((s8 *) temp_s0) + 0x24)) = temp_v0_2;
      *((u8 *) (((s8 *) temp_s0) + 0x14)) = temp_v0_2;
      temp_v0_3 = *((u8 *) (((s8 *) obj) + 0x2E));
      *((u8 *) (((s8 *) temp_s0) + 0x25)) = temp_v0_3;
      *((u8 *) (((s8 *) temp_s0) + 0x1D)) = temp_v0_3;
      temp_v0_4 = (u8) (temp_v0_3 + (*((u8 *) (((s8 *) obj) + 0x32))));
      *((u8 *) (((s8 *) temp_s0) + 0x15)) = temp_v0_4;
      *((u8 *) (((s8 *) temp_s0) + 0xD)) = temp_v0_4;
      temp_a0_3 = (s32) ((otz[var_s3] + otz[var_s3 + 1]) >> 1);
      p = temp_a0_3;
      if (((u32) temp_a0_3) < 0x1E0U)
      {
        u32 low_mask = 0xFFFFFF;
        u32 high_mask = 0xFF000000;
        temp_a0_4 = temp_a0_3 * 4;
        *((s32 *) (((s8 *) temp_s0) + 0)) = (s32) (((*((s32 *) (((s8 *) temp_s0) + 0))) & high_mask) | ((*((s32 *) (((s8 *) (((u8 *) temp_a0_4) + ((u32) (*((void **) (((s8 *) base) + 0)))))) + 0xB0))) & low_mask));
        *((s32 *) (((s8 *) (((u8 *) temp_a0_4) + ((u32) (*((void **) (((s8 *) base) + 0)))))) + 0xB0)) = (s32) (((*((s32 *) (((s8 *) (((u8 *) temp_a0_4) + ((u32) (*((void **) (((s8 *) base) + 0)))))) + 0xB0))) & high_mask) | (((s32) temp_s0) & low_mask));
      }
    }

    temp_a0 = *((void **) (((s8 *) arg0) + (-8)));
    if (temp_a0 == 0)
    {
      break;
    }
    arg0 = (void *) (((u8 *) temp_a0) + 0x20);
  }
  while (1);
  return 0;
}
