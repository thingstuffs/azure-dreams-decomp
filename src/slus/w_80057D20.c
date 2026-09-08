
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
void func_80057D20(u8 idx, u8 type, u32 val)
{
  S_80084960 *e = &D_80084960[idx];
  s32 flag14 = 0;
  s32 flag18 = 0;
  s32 i;
  u32 new_var;
  s32 k;
  s32 r;
  s32 x;
  s32 sel;
  static void *const keepalive[] = {
    &&L_case_1, &&L_case_2, &&L_case_3, &&L_case_4, &&L_case_5, &&L_case_7,
    &&L_case_10, &&L_case_11, &&L_case_12, &&L_case_20, &&L_case_21, &&L_case_22,
    &&L_case_23, &&L_case_25, &&L_case_26, &&L_case_27, &&L_case_28, &&L_case_30,
    &&L_case_64, &&L_case_91, &&L_case_6, &&L_case_98, &&L_case_99, &&L_case_120,
    &&L_case_121, &&L_case_123, &&L_case_126,
    &&L_default
  };
  (void)keepalive;
  new_var = val;
  sel = (s32)type - 1;
  if ((u32)sel >= 0x7E)
  {
    goto after_switch;
  }
  goto *jtbl_80032F04[sel];
  {
    L_case_1:
      if (((u32) e->f48) < 0x40)
    {
      e->f08 = new_var & 0xFF;
      e->f40 = ((u8) new_var) << 1;
      if ((e->f44 != 0) && (e->f40 != 0))
      {
        e->f38 = ((u32) e->f40 << 2) / e->f44;
      }
      else
      {
        e->f3a = 0;
        for (i = 0; i < D_80073734; i++)
        {
          if (D_80085458[i].f06 == idx)
          {
            func_80056654(&D_80085458[i], 1);
          }
        }

      }
      if (((new_var & 0xFF) == 0) || (e->f38 == 0))
      {
        e->f3a = 0;
        for (i = 0; i < D_80073734; i++)
        {
          if (D_80085458[i].f06 == idx)
          {
            func_80056654(&D_80085458[i], 1);
          }
        }

      }
    }
    else
    {
      e->f08 = new_var & 0xFF;
      e->f44 = new_var & 0xFF;
      if (((new_var & 0xFF) != 0) && (e->f40 != 0))
      {
        e->f38 = (e->f40 / (new_var & 0xFF)) << 1;
      }
      else
      {
        e->f3a = 0;
        for (i = 0; i < D_80073734; i++)
        {
          if (D_80085458[i].f06 == idx)
          {
            func_80056654(&D_80085458[i], 1);
          }
        }

      }
      if (((new_var & 0xFF) == 0) || (e->f38 == 0))
      {
        e->f3a = 0;
        for (i = 0; i < D_80073734; i++)
        {
          if (D_80085458[i].f06 == idx)
          {
            func_80056654(&D_80085458[i], 1);
          }
        }

      }
    }
      func_80055E7C(4, idx, e->f08);
      goto after_switch;

    L_case_2:
      if (((u32) e->f48) < 0x40)
    {
      e->f44 = new_var & 0xFF;
    }
    else
    {
      ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      e->f40 = (new_var & 0xFF) << 1;
    }
      goto after_switch;

    L_case_3:
      e->f48 = new_var & 0xFF;
      goto after_switch;

    L_case_4:
      e->f28 = new_var & 0xFF;
      goto after_switch;

    L_case_5:
      e->f50 = new_var & 0xFF;
      goto after_switch;

    L_case_7:
    {
      register s32 call_flag ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      e->f0c = new_var & 0xFF;
      call_flag = 1;
      ASM_KEEP(call_flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      func_80055E7C(3, idx, new_var & 0xFF, flag14 = call_flag);
      goto after_switch;
    }

    L_case_10:
    {
      register s32 call_flag ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      e->f04 = ((new_var & 0xFF) == 0) ? (1) : (new_var & 0xFF);
      call_flag = 1;
      ASM_KEEP(call_flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      func_80055E7C(2, idx, e->f04, flag14 = call_flag);
      goto after_switch;
    }

    L_case_11:
    {
      register s32 call_flag ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      e->f14 = new_var & 0xFF;
      call_flag = 1;
      ASM_KEEP(call_flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      func_80055E7C(5, idx, new_var & 0xFF, flag14 = call_flag);
      goto after_switch;
    }

    L_case_12:
    {
      register s32 call_flag ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      e->f2c = new_var & 0xFF;
      call_flag = 1;
      ASM_KEEP(call_flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      flag14 = call_flag;
      goto after_switch;
    }

    L_case_20:
      e->f6c = new_var << 1;
      goto after_switch;

    L_case_21:
      e->f6e = new_var;
      goto after_switch;

    L_case_22:
      e->f68 = (new_var & 0xFF) << 4;
      e->f64 = (new_var & 0xFF) << 4;
      e->f6d = 0;
      e->f5d = 1;
      goto after_switch;

    L_case_23:
      e->f6d = new_var;
      if (((new_var & 0xFF) != 0) && (e->f68 != 0))
    {
      e->f70 = e->f68 / (new_var & 0xFF);
      if (e->f70 == 0)
      {
        e->f70 = 1;
      }
    }
      goto after_switch;

    L_case_25:
      e->f88 = new_var << 1;
      goto after_switch;

    L_case_26:
      e->f8a = new_var;
      goto after_switch;

    L_case_27:
      e->f84 = (new_var & 0xFF) << 7;
      e->f80 = (new_var & 0xFF) << 7;
      e->f89 = 0;
      e->f78 = 1;
      goto after_switch;

    L_case_28:
      e->f89 = new_var;
      if (((new_var & 0xFF) != 0) && (e->f84 != 0))
    {
      e->f8c = e->f84 / (new_var & 0xFF);
      if (e->f8c == 0)
      {
        e->f8c = 1;
      }
    }
      goto after_switch;

    L_case_30:
      D_80073738.f0 = new_var & 0xFF;
      func_800564A8();
      goto after_switch;

    L_case_64:
      for (k = 0; k < D_80073734; k++)
    {
      if (idx == D_80085458[k].f06)
      {
        if (((u32) (new_var & 0xFF)) < 0x40)
        {
          for (i = 0; i < D_80073734; i++)
          {
            if (((D_80085458[i].f06 == idx) && (D_80085458[i].f1d != 0)) && (D_80085458[i].f1c & 0x80))
            {
              {
                register s32 v ASM_REG("$2");   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                register s32 acc ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                v = D_80073740[i];
                acc = flag18;
                ASM_KEEP_DEP_NV(acc, v);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
                acc |= v;
                flag18 = acc;
              }
              do
              {
                func_8005E97C(0, D_80073740[i]);
                r = func_8005EB78(D_80073740[i]);
              }
              while ((r != 2) && (r != 0));
              D_80085458[i].f1d = 0;
              D_80085458[i].f1a = 0;
            }
          }

          D_80085458[k].f1d = 0;
        }
        else
        {
          D_80085458[k].f1d = 1;
        }
      }
    }

      if (((u32) (new_var & 0xFF)) < 0x40)
    {
      D_80084960[idx].f18 = 0;
    }
    else
    {
      D_80084960[idx].f18 = 1;
    }
      goto after_switch;

    L_case_91:
      e->f30 = new_var & 0x7F;
      goto after_switch;

    L_case_6:
      e->f4e = new_var;
      if ((e->f4d != 0x14) && (e->f4d != 0x1E))
    {
      func_80057A94(e);
    }
      goto after_switch;

    L_case_98:
      e->f4c = new_var;
      goto after_switch;

    L_case_99:
      e->f4d = new_var;
      goto after_switch;

    L_case_120:

    L_case_121:

    L_case_123:
      func_80056A08();
      goto after_switch;

    L_case_126:
      e->f98 = new_var;
      goto after_switch;

    L_default:
      goto after_switch;

  }
  after_switch: ;

  {
    register s32 pending_flag ASM_REG("$7") = flag18;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    if (pending_flag)
    {
      func_8005E97C(0, pending_flag);
    }
  }
  {
    register s32 pending_flag ASM_REG("$7") = flag14;   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(pending_flag);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    if (pending_flag)
    {
      for (k = 0; k < D_80073734; k++)
      {
        if ((idx == D_80085458[k].f06) && (D_80085458[k].f1a != 0))
        {
          func_800561D8(&D_80085458[k], &D_80084960[idx]);
          func_800563B0(k, D_80085458[k].f10, D_80085458[k].f12);
        }
      }

    }
  }
}
