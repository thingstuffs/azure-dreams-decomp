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
typedef union
{
  s32 coord;
  u8 *object;
} CoordOrObject;
typedef union
{
  s32 w[5];
  s16 h[10];
} SpBuf;
extern void strcpy(void *, s32);
extern s32 strlen(void *);
extern void func_8008F074(void *, s32, void *);
extern void *func_800BDB20(s32 *, void *, s32);
extern void *func_800BDBD0(s32 *, void *, s32, s32);
extern void func_800BDC98(s16, s16, s16, s16);
extern void func_800BDDD0(s16, s16, s16);
extern s16 func_800C2AE8(s32 *);
extern s16 D_8006CCD8[][2];
extern s16 D_8006CCE8[][2];
extern u8 *D_80073600[];
extern u8 D_800BDE7C[];
extern u8 D_800BDF98[];
extern u8 D_800BDFA0[];
extern u8 D_800BE0D4[];
extern u8 D_800BE214[];
extern s32 D_800D2134[][2];
extern s32 D_800D214C[][2];
extern s32 D_800D215C[];
extern s32 D_800D216C[][2];
extern s32 D_800D219C[][3];
extern s32 D_800D21B4[];
extern s8 D_800D2238[];
extern u8 D_800D225C[];
extern u8 D_80112070[];
extern void strcpy(void *, s32);
extern s32 strlen(void *);
extern void func_8008F074(void *, s32, void *);

void func_800BE4D4(s16 *arg0, s16 arg1, s32 arg2)
{
  SpBuf sp10;
  s16 temp_a1;
  s16 temp_t0;
  s32 temp_a3;
  CoordOrObject var_s3;
  CoordOrObject var_s4;
  s32 *var_s0;
  s32 *case13_row;
  s32 temp_a1_2;
  s32 var_s1;
  s32 var_s2;
  u16 var_v0;
  u16 var_v0_2;
  u8 *var_a0;
  u8 *temp_s0_2;
  var_s2 = 0;
  temp_a3 = arg2;
  temp_a1 = arg1 - 1;
  temp_a1_2 = temp_a1 << 16;
  var_s3.coord = arg0[0] + 8;
  var_s4.coord = arg0[1] + 8;
  sp10.w[2] = -0x800000;
  switch (temp_a1_2 >> 16)
  {
    case 0:

    case 1:
      do
    {
      func_800BDC98(var_s3.coord, var_s4.coord, arg1, temp_a3);
    }
    while (0);
      return;

    case 7:
      func_800BDDD0(var_s3.coord, var_s4.coord, temp_a3);
      return;

    case 15:
      var_s2++;

    case 14:
      var_s2++;

    case 13:
      temp_t0 = arg0[3];
      if (temp_t0 < 2)
    {
      var_s3.coord++;
    }
      if (temp_t0 == 1)
    {
      var_s4.coord++;
    }
      sp10.w[0] = ((var_s3.coord << 6) - (D_8006CCE8[temp_t0][0] << 3)) << 16;
      sp10.w[1] = ((var_s4.coord << 6) + (D_8006CCD8[temp_t0][0] << 3)) << 16;
      sp10.w[2] = 0;
      case13_row = D_800D2134[var_s2];
      var_s3.object = func_800BDBD0(sp10.w, D_800BDE7C, temp_t0 << 10, *case13_row);
      var_s4.object = var_s3.object + 0x20;
      *((s32 **) (var_s4.object + 0xA0)) = case13_row;
      break;

    case 5:
      var_s2++;

    case 6:
      var_s1 = 1;
      sp10.w[0] = var_s3.coord << 22;
      sp10.w[1] = var_s4.coord << 22;
      sp10.w[2] = -0x80000;
      do
    {
      func_800BDBD0(sp10.w, D_800BDF98, 0, D_800D214C[var_s2][var_s1]);
      var_s1--;
    }
    while (var_s1 >= 0);
      return;

    case 8:
    {
      var_s2 = 3;
      sp10.w[0] = var_s3.coord << 22;
      sp10.w[1] = var_s4.coord << 22;
      sp10.w[2] = -0x80000;
      do
    {
      func_800BDBD0(sp10.w, D_800BDF98, 0, D_800D215C[var_s2]);
      var_s2--;
    }
    while (var_s2 >= 0);
      sp10.w[0] = (var_s3.coord << 22) + 0x01000000;
      sp10.w[1] = (var_s4.coord << 22) + 0x01600000;
      sp10.h[5] = 0;
    {
      s32 sh8 = arg1 << 16;
      u8 *tbl8 = (u8 *) D_800D21B4;
      var_s3.object = func_800BDB20(sp10.w, D_800BDF98, *((s32 *) (tbl8 + (sh8 >> 14))));
    }
      var_s4.object = var_s3.object + 0x20;
      *((s16 *) (((u8 *) (*((void **) (var_s3.object + 0xC)))) + 6)) = 0x18;
      break;
    }

    case 3:

    case 9:

    case 16:

    case 29:

    case 30:
      sp10.w[0] = (var_s3.coord << 22) + 0x200000;
      sp10.w[1] = (var_s4.coord << 22) + 0x200000;
      sp10.h[5] = func_800C2AE8(sp10.w);
      if (sp10.w[2] > 0)
    {
      sp10.w[2] = 0;
    }
      var_s3.object = func_800BDB20(sp10.w, D_800BDF98, D_800D21B4[arg1]);
      var_s4.object = var_s3.object + 0x20;
      if (arg1 == 0xA)
    {
      var_a0 = *((void **) (var_s3.object + 0xC));
      *((s16 *) (((u8 *) var_a0) + 6)) = 0x20;
    }
      break;

    case 19:
      var_s2++;

    case 18:
      var_s2++;

    case 21:
      var_s2++;

    case 4:
      var_s2++;

    case 2:
      sp10.w[0] = (var_s3.coord << 22) + 0x200000;
      sp10.w[1] = (var_s4.coord << 22) + 0x200000;
      sp10.h[5] = func_800C2AE8(sp10.w);
      var_s3.object = func_800BDB20(sp10.w, D_800BDFA0, D_800D21B4[(s16) arg1]);
      var_s4.object = var_s3.object + 0x20;
      *((s32 *) (var_s4.object + 0xA0)) = D_800D216C[var_s2][0];
      *((s32 *) (var_s4.object + 0xA4)) = D_800D216C[var_s2][1];
      if (arg1 == 0x13)
    {
      var_a0 = *((void **) (var_s3.object + 0xC));
      var_v0 = *((u16 *) (((u8 *) var_a0) + 0x14));
      *((s16 *) (((u8 *) var_a0) + 0x10)) = 0;
      *((u16 *) (((u8 *) var_a0) + 0x14)) = var_v0 | 0xC;
    }
      break;

    case 20:
      var_s2++;

    case 22:
      sp10.w[0] = (var_s3.coord << 22) + 0x200000;
      sp10.w[1] = (var_s4.coord << 22) + 0x200000;
      sp10.h[5] = func_800C2AE8(sp10.w);
      var_s3.object = func_800BDB20(sp10.w, D_800BE0D4, D_800D21B4[(s16) arg1]);
      var_s4.object = var_s3.object + 0x20;
      *((s32 *) (var_s4.object + 0xA0)) = D_800D219C[var_s2][0];
      *((s32 *) (var_s4.object + 0xA4)) = D_800D219C[var_s2][1];
      *((s32 *) (var_s4.object + 0xA8)) = D_800D219C[var_s2][2];
      if (arg1 == 0x17)
    {
      var_a0 = *((void **) (var_s3.object + 0xC));
      var_v0_2 = *((u16 *) (((u8 *) var_a0) + 0x14));
      *((s16 *) (((u8 *) var_a0) + 0x10)) = 0x20;
      *((u16 *) (((u8 *) var_a0) + 0x14)) = var_v0_2 | 0xC;
    }
      break;

    case 17:
      sp10.w[0] = (var_s3.coord << 22) + 0x200000;
      sp10.w[1] = (var_s4.coord << 22) + 0x200000;
      sp10.h[5] = func_800C2AE8(sp10.w);
    {
      s32 sh17 = arg1 << 16;
      u8 *tbl17 = (u8 *) D_800D21B4;
      var_s3.object = func_800BDB20(sp10.w, D_800BE214, *((s32 *) (tbl17 + (sh17 >> 14))));
    }
      var_s4.object = var_s3.object + 0x20;
      *((s32 *) (var_s4.object + 0xA0)) = sp10.h[5];
      break;

    default:
      return;

  }

  temp_s0_2 = D_80112070 + (arg1 * 0x82);
  strcpy(temp_s0_2, *((s32 *) ((D_80073600[0] + (arg1 * 0x14)) + 8)));
  var_s2 = strlen(temp_s0_2);
  temp_s0_2[var_s2] = 0x11;
  var_s2++;
  temp_s0_2[var_s2] = 1;
  *((void **) (((u8 *) var_s4.object) + 0x48)) = temp_s0_2;
  var_s0 = (s32 *) var_s4.object;
  func_8008F074(var_s0, *((s32 *) (var_s3.object + 8)), D_800D225C + (D_800D2238[arg1] * 0x18));

}
