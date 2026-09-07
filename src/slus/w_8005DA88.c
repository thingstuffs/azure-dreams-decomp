
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct 
{
  s32 unk00;
  u32 unk04;
  u16 unk08;
  u16 unk0A;
  s32 unk0C;
  s32 unk10;
} S_8005DA88;
typedef struct 
{
  s32 unk00;
  u16 unk04;
  u16 unk06;
  u8 pad08[0x0A];
  s16 unk12;
  u8 pad14[0x04];
  s16 unk18;
  s16 unk1A;
  s16 unk1C;
  u16 unk1E;
  u8 pad20[0x04];
  s16 unk24;
  u16 unk26;
  u8 pad28[0x10];
  s16 unk38;
  s16 unk3A;
  u16 unk3C;
  u16 unk3E;
  u8 pad40[0x04];
} S_8005DA88_buf;
typedef struct 
{
  u8 pad000[0x184];
  u16 field_184;
  u16 field_186;
  u8 pad188[0x22];
  volatile u16 field_1AA;
} S_80079958;
typedef struct 
{
  S_80079958 *ptr;
  u32 pad[2];
} S_80079958_hdr;
extern s32 D_80079500[];
extern s32 D_80079508[];
extern u16 D_8007950C[];
extern u16 D_8007950E[];
extern s32 D_80079510[];
extern s32 D_80079514[];
extern S_80079958 *D_80079958;
extern s32 D_800799C0[];
extern S_8005DA88_buf D_80079A10[];
extern s32 func_8005D9DC(s32 handle);
extern void func_8005DF80(void *buf);
extern void func_8005E7E0(s32 idx);
extern void func_8005D550(s32 a0, s32 handle, s32 a2);
inline u8 *inline_fn_8005DA88(S_8005DA88_buf *arg0)
{
  return (u8 *) arg0;
}

s32 func_8005DA88(S_8005DA88 *arg0, s32 arg1, s32 *arg2, s32 arg3)
{
  S_8005DA88_buf buf;
  s32 flags;
  s32 isZero;
  u32 idx;
  s32 didC;
  s32 didInit;
  s32 didFp;
  s32 s7flag;
  s32 clearFlag;
  s32 i;
  u8 *src;
  u8 *dst;
  s32 i2;
  u8 *src2;
  u8 *dst2;
  s32 i3;
  u8 *src3;
  u8 *dst3;
  s32 temp;
  s32 temp2;
  s32 X;
  u16 rmw;
  s7flag = 0;
  didInit = 0;
  didC = 0;
  clearFlag = 0;
  flags = arg0->unk00;
  didFp = 0;
  isZero = flags == 0;
  buf.unk00 = 0;
  if (isZero || (flags & 1))
  {
    idx = arg0->unk04;
    if (idx & 0x100)
    {
      idx &= ~0x100;
      clearFlag = 1;
    }
    if (idx >= 0xAU)
    {
      return -1;
    }
    if (func_8005D9DC(D_800799C0[idx]) != 0)
    {
      return -1;
    }
    didInit = 1;
    D_80079508[0] = idx;
    D_80079500[0] = D_800799C0[D_80079508[0]];
    src = inline_fn_8005DA88(&D_80079A10[D_80079508[0]]);
    dst = inline_fn_8005DA88(&buf);
    i = 0x43;
    do
    {
      *(dst++) = *(src++);
      i--;
    }
    while (i != (-1));
    switch (D_80079508[0])
    {
      case 7:
        D_80079514[0] = 0x7F;
        D_80079510[0] = 0x7F;
        break;

      case 8:
        D_80079514[0] = 0;
        D_80079510[0] = 0x7F;
        break;

      default:
        D_80079514[0] = 0;
        D_80079510[0] = 0;
        break;

    }

  }
  if (isZero || (flags & 8))
  {
    if (D_80079508[0] < 9)
    {
      if (D_80079508[0] >= 7)
      {
        didC = 1;
        if (!didInit)
        {
          src2 = inline_fn_8005DA88(&D_80079A10[D_80079508[0]]);
          dst2 = inline_fn_8005DA88(&buf);
          i2 = 0x43;
          do
          {
            *(dst2++) = *(src2++);
            i2--;
          }
          while (i2 != (-1));
          buf.unk00 = 0x0C011C00;
        }
        temp = arg0->unk0C;
        D_80079510[0] = temp;
        X = (temp << 12) / 127;
        buf.unk18 = (s16) (((temp << 13) / 127) - buf.unk04);
        buf.unk1A = (s16) (X - buf.unk06);
        buf.unk1C = (s16) (buf.unk1E + X);
        buf.unk24 = (s16) (buf.unk26 + X);
        buf.unk38 = (s16) (buf.unk3C + X);
        buf.unk3A = (s16) (buf.unk3E + X);
      }
    }
  }
  if (isZero || (flags & 0x10))
  {
    if ((double) (D_80079508[0] < 9))
    {
      if (D_80079508[0] >= 7)
      {
        didFp = 1;
        if (!didInit)
        {
          if (!didC)
          {
            src3 = inline_fn_8005DA88(&D_80079A10[D_80079508[0]]);
            dst3 = inline_fn_8005DA88(&buf);
            i3 = 0x43;
            do
            {
              *(dst3++) = *(src3++);
              i3--;
            }
            while (i3 != (-1));
            buf.unk00 = 0x80;
          }
          else
          {
            buf.unk00 |= 0x80;
          }
        }
        temp2 = arg0->unk10;
        D_80079514[0] = temp2;
        buf.unk12 = (s16) ((temp2 * 0x8100) / 127);
      }
    }
  }
  if (didInit)
  {
    s7flag = (D_80079958->field_1AA >> 7) & 1;
    if (s7flag)
    {
      rmw = D_80079958->field_1AA;
      rmw &= 0xFF7F;
      D_80079958->field_1AA = rmw;
    }
    goto clears;
  }
  if (isZero || (flags & 2))
  {
    D_80079958->field_184 = arg0->unk08;
    D_8007950C[0] = arg0->unk08;
  }
  if (isZero || (flags & 4))
  {
    D_80079958->field_186 = arg0->unk0A;
    D_8007950E[0] = arg0->unk0A;
  }
  goto after_clears;
clears:
  D_80079958->field_184 = 0;
  D_80079958->field_186 = 0;
  D_8007950C[0] = 0;
  D_8007950E[0] = 0;
after_clears:
  if ((didInit || didC) || didFp)
  {
    func_8005DF80(&buf);
  }
  if (clearFlag)
  {
    func_8005E7E0(D_80079508[0]);
  }
  if (didInit)
  {
    func_8005D550(0xD1, D_80079500[0], 0);
    if (s7flag)
    {
      rmw = D_80079958->field_1AA;
      rmw |= 0x80;
      D_80079958->field_1AA = rmw;
    }
  }
  return 0;
}
