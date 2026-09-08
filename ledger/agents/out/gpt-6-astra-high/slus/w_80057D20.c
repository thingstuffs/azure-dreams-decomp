
#include "common.h"
typedef struct S_80084960
{
  s32 f00;
  s32 f04;
  s32 f08;
  s32 f0c;
  s32 f10;
  s32 f14;
  s32 f18;
  s32 f1c;
  s32 f20;
  s32 f24;
  s32 f28;
  s32 f2c;
  s8 f30;
  u8 pad31[7];
  s16 f38;
  s16 f3a;
  u8 pad3c[4];
  s16 f40;
  u8 pad42[2];
  s32 f44;
  s32 f48;
  s8 f4c;
  u8 f4d;
  s8 f4e;
  u8 pad4f[1];
  s16 f50;
  u8 pad52[11];
  s8 f5d;
  u8 pad5e[1];
  s8 f5f;
  s8 f60;
  s8 f61;
  u8 pad62[2];
  s32 f64;
  s32 f68;
  s8 f6c;
  s8 f6d;
  s8 f6e;
  u8 pad6f[1];
  s32 f70;
  u8 pad74[4];
  s8 f78;
  u8 pad79[1];
  s8 f7a;
  s8 f7b;
  s8 f7c;
  u8 pad7d[3];
  s32 f80;
  s32 f84;
  s8 f88;
  s8 f89;
  s8 f8a;
  u8 pad8b[1];
  s32 f8c;
  u8 pad90[4];
  s32 f94;
  s8 f98;
  u8 pad99[3];
} S_80084960;
typedef struct S_80085458
{
  s16 f00;
  s16 f02;
  s16 f04;
  u16 f06;
  u8 pad08[8];
  u16 f10;
  u16 f12;
  u8 pad14[4];
  s16 f18;
  u16 f1a;
  u8 f1c;
  u8 f1d;
  u8 pad1e[0x5A];
} S_80085458;
typedef struct S_80073738
{
  s16 f0;
  s16 pad[7];
} S_80073738;
extern s32 D_80073734; /* scalar: MEM_IN_STRUCT_P == 0, needs -G0 */
extern S_80073738 D_80073738;
extern s32 D_80073740[64];
extern S_80084960 D_80084960[16];
extern S_80085458 D_80085458[64];
extern void func_80055E7C();
extern void func_800564A8();
extern void func_80056654(S_80085458 *e, s32 arg1);
extern void func_80057A94(S_80084960 *e);
extern void func_800561D8(S_80085458 *e, S_80084960 *rec);
extern s32 func_800563B0(s32 a0, u16 a1, u16 a2);
extern void func_80056A08(void);
extern void func_8005E97C(s32 a0, s32 a1);
extern s32 func_8005EB78(s32 a0);
extern void *jtbl_80032F04[];
/* Applies a channel control change and updates affected voices. */
void func_80057D20(u8 channel, u8 control, u32 value)
{
  S_80084960 *settings = &D_80084960[channel];
  s32 refresh_notes = 0;
  s32 stopped_voices = 0;
  s32 voice_idx;
  u32 control_value;
  s32 entry_idx;
  s32 voice_status;
  s32 control_index;
  static void *const case_labels[] = {
    &&L_case_1, &&L_case_2, &&L_case_3, &&L_case_4, &&L_case_5, &&L_case_7,
    &&L_case_10, &&L_case_11, &&L_case_12, &&L_case_20, &&L_case_21, &&L_case_22,
    &&L_case_23, &&L_case_25, &&L_case_26, &&L_case_27, &&L_case_28, &&L_case_30,
    &&L_case_64, &&L_case_91, &&L_case_6, &&L_case_98, &&L_case_99, &&L_case_120,
    &&L_case_121, &&L_case_123, &&L_case_126,
    &&L_default
  };
  (void)case_labels;
  control_value = value;
  control_index = (s32)control - 1;
  if ((u32)control_index >= 0x7E)
  {
    goto after_switch;
  }
  goto *jtbl_80032F04[control_index];
  {
  L_case_1:
    if (((u32) settings->f48) < 0x40)
    {
      settings->f08 = control_value & 0xFF;
      settings->f40 = ((u8) control_value) << 1;
      if ((settings->f44 != 0) && (settings->f40 != 0))
      {
        settings->f38 = ((u32) settings->f40 << 2) / settings->f44;
      }
      else
      {
        settings->f3a = 0;
        for (voice_idx = 0; voice_idx < D_80073734; voice_idx++)
        {
          if (D_80085458[voice_idx].f06 == channel)
          {
            func_80056654(&D_80085458[voice_idx], 1);
          }
        }
      }
      if (((control_value & 0xFF) == 0) || (settings->f38 == 0))
      {
        settings->f3a = 0;
        for (voice_idx = 0; voice_idx < D_80073734; voice_idx++)
        {
          if (D_80085458[voice_idx].f06 == channel)
          {
            func_80056654(&D_80085458[voice_idx], 1);
          }
        }
      }
    }
    else
    {
      settings->f08 = control_value & 0xFF;
      settings->f44 = control_value & 0xFF;
      if (((control_value & 0xFF) != 0) && (settings->f40 != 0))
      {
        settings->f38 = (settings->f40 / (control_value & 0xFF)) << 1;
      }
      else
      {
        settings->f3a = 0;
        for (voice_idx = 0; voice_idx < D_80073734; voice_idx++)
        {
          if (D_80085458[voice_idx].f06 == channel)
          {
            func_80056654(&D_80085458[voice_idx], 1);
          }
        }
      }
      if (((control_value & 0xFF) == 0) || (settings->f38 == 0))
      {
        settings->f3a = 0;
        for (voice_idx = 0; voice_idx < D_80073734; voice_idx++)
        {
          if (D_80085458[voice_idx].f06 == channel)
          {
            func_80056654(&D_80085458[voice_idx], 1);
          }
        }
      }
    }
    func_80055E7C(4, channel, settings->f08);
    goto after_switch;

  L_case_2:
    if (((u32) settings->f48) < 0x40)
    {
      settings->f44 = control_value & 0xFF;
    }
    else
    {
      ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      settings->f40 = (control_value & 0xFF) << 1;
    }
    goto after_switch;

  L_case_3:
    settings->f48 = control_value & 0xFF;
    goto after_switch;

  L_case_4:
    settings->f28 = control_value & 0xFF;
    goto after_switch;

  L_case_5:
    settings->f50 = control_value & 0xFF;
    goto after_switch;

  L_case_7:
    {
      register s32 refresh_flag ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      settings->f0c = control_value & 0xFF;
      refresh_flag = 1;
      ASM_KEEP(refresh_flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      func_80055E7C(3, channel, control_value & 0xFF, refresh_notes = refresh_flag);
      goto after_switch;
    }

  L_case_10:
    {
      register s32 refresh_flag ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      settings->f04 = ((control_value & 0xFF) == 0) ? (1) : (control_value & 0xFF);
      refresh_flag = 1;
      ASM_KEEP(refresh_flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      func_80055E7C(2, channel, settings->f04, refresh_notes = refresh_flag);
      goto after_switch;
    }

  L_case_11:
    {
      register s32 refresh_flag ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      settings->f14 = control_value & 0xFF;
      refresh_flag = 1;
      ASM_KEEP(refresh_flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      func_80055E7C(5, channel, control_value & 0xFF, refresh_notes = refresh_flag);
      goto after_switch;
    }

  L_case_12:
    {
      register s32 refresh_flag ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      settings->f2c = control_value & 0xFF;
      refresh_flag = 1;
      ASM_KEEP(refresh_flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      refresh_notes = refresh_flag;
      goto after_switch;
    }

  L_case_20:
    settings->f6c = control_value << 1;
    goto after_switch;

  L_case_21:
    settings->f6e = control_value;
    goto after_switch;

  L_case_22:
    settings->f68 = (control_value & 0xFF) << 4;
    settings->f64 = (control_value & 0xFF) << 4;
    settings->f6d = 0;
    settings->f5d = 1;
    goto after_switch;

  L_case_23:
    settings->f6d = control_value;
    if (((control_value & 0xFF) != 0) && (settings->f68 != 0))
    {
      settings->f70 = settings->f68 / (control_value & 0xFF);
      if (settings->f70 == 0)
      {
        settings->f70 = 1;
      }
    }
    goto after_switch;

  L_case_25:
    settings->f88 = control_value << 1;
    goto after_switch;

  L_case_26:
    settings->f8a = control_value;
    goto after_switch;

  L_case_27:
    settings->f84 = (control_value & 0xFF) << 7;
    settings->f80 = (control_value & 0xFF) << 7;
    settings->f89 = 0;
    settings->f78 = 1;
    goto after_switch;

  L_case_28:
    settings->f89 = control_value;
    if (((control_value & 0xFF) != 0) && (settings->f84 != 0))
    {
      settings->f8c = settings->f84 / (control_value & 0xFF);
      if (settings->f8c == 0)
      {
        settings->f8c = 1;
      }
    }
    goto after_switch;

  L_case_30:
    D_80073738.f0 = control_value & 0xFF;
    func_800564A8();
    goto after_switch;

  L_case_64:
    for (entry_idx = 0; entry_idx < D_80073734; entry_idx++)
    {
      if (channel == D_80085458[entry_idx].f06)
      {
        if (((u32) (control_value & 0xFF)) < 0x40)
        {
          for (voice_idx = 0; voice_idx < D_80073734; voice_idx++)
          {
            if (((D_80085458[voice_idx].f06 == channel) && (D_80085458[voice_idx].f1d != 0)) && (D_80085458[voice_idx].f1c & 0x80))
            {
              {
                register s32 voice_mask ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                register s32 merged_mask ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                voice_mask = D_80073740[voice_idx];
                merged_mask = stopped_voices;
                ASM_KEEP_DEP_NV(merged_mask, voice_mask);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                merged_mask |= voice_mask;
                stopped_voices = merged_mask;
              }
              do
              {
                func_8005E97C(0, D_80073740[voice_idx]);
                voice_status = func_8005EB78(D_80073740[voice_idx]);
              }
              while ((voice_status != 2) && (voice_status != 0));
              D_80085458[voice_idx].f1d = 0;
              D_80085458[voice_idx].f1a = 0;
            }
          }

          D_80085458[entry_idx].f1d = 0;
        }
        else
        {
          D_80085458[entry_idx].f1d = 1;
        }
      }
    }

    if (((u32) (control_value & 0xFF)) < 0x40)
    {
      D_80084960[channel].f18 = 0;
    }
    else
    {
      D_80084960[channel].f18 = 1;
    }
    goto after_switch;

  L_case_91:
    settings->f30 = control_value & 0x7F;
    goto after_switch;

  L_case_6:
    settings->f4e = control_value;
    if ((settings->f4d != 0x14) && (settings->f4d != 0x1E))
    {
      func_80057A94(settings);
    }
    goto after_switch;

  L_case_98:
    settings->f4c = control_value;
    goto after_switch;

  L_case_99:
    settings->f4d = control_value;
    goto after_switch;

  L_case_120:

  L_case_121:

  L_case_123:
    func_80056A08();
    goto after_switch;

  L_case_126:
    settings->f98 = control_value;
    goto after_switch;

  L_default:
    goto after_switch;
  }
after_switch: ;

  {
    register s32 pending_voices ASM_REG("$7") = stopped_voices;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (pending_voices)
    {
      func_8005E97C(0, pending_voices);
    }
  }
  {
    register s32 pending_refresh ASM_REG("$7") = refresh_notes;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(pending_refresh);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    if (pending_refresh)
    {
      for (entry_idx = 0; entry_idx < D_80073734; entry_idx++)
      {
        if ((channel == D_80085458[entry_idx].f06) && (D_80085458[entry_idx].f1a != 0))
        {
          func_800561D8(&D_80085458[entry_idx], &D_80084960[channel]);
          func_800563B0(entry_idx, D_80085458[entry_idx].f10, D_80085458[entry_idx].f12);
        }
      }
    }
  }
}
