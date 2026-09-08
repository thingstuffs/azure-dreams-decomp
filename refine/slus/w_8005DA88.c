
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
inline u8 *inline_fn_8005DA88(S_8005DA88_buf *params)
{
  return (u8 *) params;
}

/* Update reverb mode, depth, delay and feedback, optionally clearing its work area. */
s32 func_8005DA88(S_8005DA88 *settings, s32 unused_1, s32 *unused_2, s32 unused_3)
{
  S_8005DA88_buf reverb_params;
  s32 flags;
  s32 update_all;
  u32 mode;
  s32 delay_changed;
  s32 mode_changed;
  s32 feedback_changed;
  s32 reverb_enabled;
  s32 clear_work_area;
  s32 mode_bytes;
  u8 *mode_src;
  u8 *mode_dst;
  s32 delay_bytes;
  u8 *delay_src;
  u8 *delay_dst;
  s32 feedback_bytes;
  u8 *feedback_src;
  u8 *feedback_dst;
  s32 delay;
  s32 feedback;
  s32 delay_offset;
  u16 spu_control;
  reverb_enabled = 0;
  mode_changed = 0;
  delay_changed = 0;
  clear_work_area = 0;
  flags = settings->unk00;
  feedback_changed = 0;
  update_all = flags == 0;
  reverb_params.unk00 = 0;
  if (update_all || (flags & 1))
  {
    mode = settings->unk04;
    if (mode & 0x100)
    {
      mode &= ~0x100;
      clear_work_area = 1;
    }
    if (mode >= 0xAU)
    {
      return -1;
    }
    if (func_8005D9DC(D_800799C0[mode]) != 0)
    {
      return -1;
    }
    mode_changed = 1;
    D_80079508[0] = mode;
    D_80079500[0] = D_800799C0[D_80079508[0]];
    mode_src = inline_fn_8005DA88(&D_80079A10[D_80079508[0]]);
    mode_dst = inline_fn_8005DA88(&reverb_params);
    mode_bytes = 0x43;
    do
    {
      *(mode_dst++) = *(mode_src++);
      mode_bytes--;
    }
    while (mode_bytes != (-1));
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
  if (update_all || (flags & 8))
  {
    if (D_80079508[0] < 9)
    {
      if (D_80079508[0] >= 7)
      {
        delay_changed = 1;
        if (!mode_changed)
        {
          delay_src = inline_fn_8005DA88(&D_80079A10[D_80079508[0]]);
          delay_dst = inline_fn_8005DA88(&reverb_params);
          delay_bytes = 0x43;
          do
          {
            *(delay_dst++) = *(delay_src++);
            delay_bytes--;
          }
          while (delay_bytes != (-1));
          reverb_params.unk00 = 0x0C011C00;
        }
        delay = settings->unk0C;
        D_80079510[0] = delay;
        delay_offset = (delay << 12) / 127;
        reverb_params.unk18 = (s16) (((delay << 13) / 127) - reverb_params.unk04);
        reverb_params.unk1A = (s16) (delay_offset - reverb_params.unk06);
        reverb_params.unk1C = (s16) (reverb_params.unk1E + delay_offset);
        reverb_params.unk24 = (s16) (reverb_params.unk26 + delay_offset);
        reverb_params.unk38 = (s16) (reverb_params.unk3C + delay_offset);
        reverb_params.unk3A = (s16) (reverb_params.unk3E + delay_offset);
      }
    }
  }
  if (update_all || (flags & 0x10))
  {
    if ((double) (D_80079508[0] < 9))
    {
      if (D_80079508[0] >= 7)
      {
        feedback_changed = 1;
        if (!mode_changed)
        {
          if (!delay_changed)
          {
            feedback_src = inline_fn_8005DA88(&D_80079A10[D_80079508[0]]);
            feedback_dst = inline_fn_8005DA88(&reverb_params);
            feedback_bytes = 0x43;
            do
            {
              *(feedback_dst++) = *(feedback_src++);
              feedback_bytes--;
            }
            while (feedback_bytes != (-1));
            reverb_params.unk00 = 0x80;
          }
          else
          {
            reverb_params.unk00 |= 0x80;
          }
        }
        feedback = settings->unk10;
        D_80079514[0] = feedback;
        reverb_params.unk12 = (s16) ((feedback * 0x8100) / 127);
      }
    }
  }
  if (mode_changed)
  {
    reverb_enabled = (D_80079958->field_1AA >> 7) & 1;
    if (reverb_enabled)
    {
      spu_control = D_80079958->field_1AA;
      spu_control &= 0xFF7F;
      D_80079958->field_1AA = spu_control;
    }
    goto clear_depth;
  }
  if (update_all || (flags & 2))
  {
    D_80079958->field_184 = settings->unk08;
    D_8007950C[0] = settings->unk08;
  }
  if (update_all || (flags & 4))
  {
    D_80079958->field_186 = settings->unk0A;
    D_8007950E[0] = settings->unk0A;
  }
  goto apply_params;
clear_depth:
  D_80079958->field_184 = 0;
  D_80079958->field_186 = 0;
  D_8007950C[0] = 0;
  D_8007950E[0] = 0;
apply_params:
  if ((mode_changed || delay_changed) || feedback_changed)
  {
    func_8005DF80(&reverb_params);
  }
  if (clear_work_area)
  {
    func_8005E7E0(D_80079508[0]);
  }
  if (mode_changed)
  {
    func_8005D550(0xD1, D_80079500[0], 0);
    if (reverb_enabled)
    {
      spu_control = D_80079958->field_1AA;
      spu_control |= 0x80;
      D_80079958->field_1AA = spu_control;
    }
  }
  return 0;
}
