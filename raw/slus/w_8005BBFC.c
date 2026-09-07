#include "common.h"

/* func_8005BBFC — SPU voice dispatch: validates the channel slot, walks the
 * sample table, fills a request record (req) and the voice record
 * (D_80085458[idx]), computes L/R volumes from the pan curve, and hands the
 * request to func_8005EC0C.  Byte-exact under gcc 2.7.2-cdk -O2 aspsx=2.56.
 *
 * Match notes (receipts: work/mainexe_audit_20260818/solve_T_bbfc/):
 *  - v40/v48/v50 are genuine u16 LOCALS (not struct fields): each is a
 *    cross-block call-crossing 2-ref u16 pseudo with no REG_EQUIV, so reload
 *    spills all three to fresh 8-byte-aligned frame slots 0x50/0x58/0x60
 *    (reg_max_ref_width=4 via the (s16) casts forces align=-1), reloaded
 *    through $t2 = potential_reload_regs[0].
 *  - The ASM_USE_NV(a3c) third reference lifts a3c's allocno priority above
 *    v40 so the register-less trio is exactly v40/v48/v50.
 *  - Scheduling is pinned by sched1's birthing boost (LAUNCH_PRIORITY,
 *    sched.c): a boosted insn needs reg_n_sets==1, so no ASM_SET/ASM_KEEP_NV
 *    may touch a1c or fd — either would un-boost their defining insns and
 *    misplace the $s5 pair (block 0) / the f20 store (block 14).  The
 *    a1c-before-a3c preamble order and f20-before-f14 store order break the
 *    remaining backward-scheduler LUID ties.
 */
typedef struct 
{
  s16 f00;
  u8 pad02[2];
  u8 *f04;
  u8 pad08[8];
  s32 f10;
  u8 pad14[4];
  u8 f18;
  u8 pad19[2];
  u8 f1b;
} S_80086A40;
typedef struct 
{
  s16 f00;
  s16 f02;
  u16 f04;
  u16 f06;
  s16 f08;
  u16 f0a;
  u8 pad0c[4];
  s16 f10;
  u16 f12;
  u8 f14;
  u8 f15;
  u8 f16;
  u8 f17;
  s16 f18;
  u16 f1a;
  u8 pad1c[4];
  u8 f20;
  u8 f21;
  u8 f22;
  u8 f23;
  u8 pad24[0x38];
  u16 f5c;
  u8 pad5e[2];
  s32 f60;
  s32 f64;
  u8 pad68[0x10];
} S_80085458;
typedef struct 
{
  u8 f00;
  u8 f01;
  u8 f02;
  u8 f03;
  u8 f04;
  u8 f05;
  u8 f06;
  u8 f07;
  u8 pad08[4];
  u8 f0c;
  u8 f0d;
  u8 pad0e[2];
  u16 f10;
  u16 f12;
  u8 pad14[2];
  s16 f16;
} S_8005BBFC_rec;
typedef struct 
{
  s32 f00;
  s32 f04;
  s16 f08;
  u16 f0a;
  s16 f0c;
  s16 f0e;
  u8 pad10[6];
  s16 f16;
  s16 f18;
  u8 pad1a[2];
  s32 f1c;
  s32 f20;
  s32 f24;
  u8 pad28[0x12];
  u16 f3a;
  u16 f3c;
  u8 pad3e[2];
} S_8005BBFC_req;
extern s32 D_80073734[4];
extern s32 D_80073740[64];
extern S_80085458 D_80085458[64];
extern s32 D_80085F98[4];
extern S_80086A40 D_80086A40[16];
extern void func_80056DB4(s32 arg0);
extern void func_8005E97C(s32 a0, s32 a1);
extern s32 func_8005EB78(s32 a0);
extern void func_8005EC0C(void *a0);
extern s32 func_8005E4A0(s32 a0, s32 a1);
enum E_u16 { E_u16_zero = 0, E_u16_max = 0xFFFF } __attribute__((packed));
s32 func_8005BBFC(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7)
s32 arg0;
s32 arg1;
s32 arg2;
s32 arg3;
volatile s32 arg4;
s32 arg5;
enum E_u16 arg6;
enum E_u16 arg7;
{
  S_8005BBFC_req req;
  u16 v40;
  u16 v48;
  u16 v50;
  s32 idx;
  s16 a1c;
  s16 a3c;
  u8 *buf;
  u8 *s6;
  S_8005BBFC_rec *rec;
  u16 t10;
  u16 t12;
  s32 col;
  s32 s7v;
  s32 *q;
  s32 v0;
  s32 acc;
  s16 lim;
  register s32 i ASM_REG("$6");
  u16 *ptr;
  register s32 sum ASM_REG("$3");
  register s32 tot ASM_REG("$2");
  s32 a0v;
  s32 a1v;
  s32 a2v;
  u8 fv;
  s32 t;
  s32 t2;
  u8 fd;
  s32 a4;
  register s32 a5 ASM_REG("$9");
  idx = (s16) arg0;
  a4 = arg4;
  a1c = arg1;
  a5 = arg5;
  v40 = arg2;
  v48 = arg6;
  a3c = arg3;
  v50 = arg7;
  D_80085F98[0] = 1;
  if ((D_80073734[0] - 1) < idx)
  {
    idx = -1;
  }
  if (idx != (-1))
  {
    buf = D_80086A40[(s16) arg1].f04;
    col = ((s32) (arg2 << 0x10)) >> 0xC;
    s6 = buf + (col + 0x20);
    s7v = (((s16) a4) << 8) + ((s16) a5);
    rec = (S_8005BBFC_rec *) (buf + (((col + ((s16) arg3)) << 5) + 0x820));
    if ((((s16) a4) >= ((s32) rec->f06)) && (((s32) rec->f07) >= ((s16) a4)))
    {
      ASM_USE_NV(a5);
      func_80056DB4(idx);
      { s32 *qb = D_80073740; q = qb + idx; }
      do
      {
        func_8005E97C(0, *q);
        v0 = func_8005EB78(*q);
        if (v0 == 2)
        {
          break;
        }
      }
      while (v0 != 0);
      i = 0;
      acc = i;
      lim = rec->f16;
      ptr = (u16 *) ((D_80086A40[(s16) a1c].f04 + ((*((u16 *) (buf + 0x12))) << 9)) + 0x820);
      if (lim > 0)
      {
        do
        {
          acc += *ptr;
          ptr += 1;
          i += 1;
        }
        while (i < lim);
      }
      req.f04 = 0x701EF;
      req.f0c = 0;
      req.f0e = 0;
      req.f00 = D_80073740[idx];
      acc <<= 3;
      req.f1c = D_80086A40[(s16) a1c].f10 + acc;
      t10 = rec->f10;
      req.f3a = t10;
      D_80085458[idx].f60 = t10;
      t12 = rec->f12;
      req.f3c = t12;
      D_80085458[idx].f64 = t12;
      if (rec->f10 & 0x80)
      {
        req.f24 = 5;
      }
      else
      {
        req.f24 = 1;
      }
      req.f20 = req.f1c;
      D_80085458[idx].f22 = rec->f04;
      D_80085458[idx].f23 = rec->f05;
      D_80085458[idx].f21 = rec->f0c;
      fd = rec->f0d;
      D_80085458[idx].f00 = idx;
      D_80085458[idx].f04 = v40;
      D_80085458[idx].f0a = (s16) (s7v >> 8);
      D_80085458[idx].f06 = 0x11;
      D_80085458[idx].f08 = a3c;
      ASM_USE_NV(a3c);
      D_80085458[idx].f1a = 1;
      D_80085458[idx].f20 = fd;
      D_80085458[idx].f14 = s6[1];
      D_80085458[idx].f16 = s6[4];
      ASM_USE_NV(s6);
      D_80085458[idx].f15 = rec->f02;
      D_80085458[idx].f17 = rec->f03;
      D_80085458[idx].f5c = a1c;
      tot = (D_80086A40[(s16) a1c].f1b + D_80085458[idx].f16) + D_80085458[idx].f17;
      sum = tot - 0x80;
      if (sum < 0)
      {
        sum = 0;
      }
      if (!(sum < 0x80))
      {
        sum = 0x7F;
      }
      D_80085458[idx].f18 = sum;
      a0v = ((s32) ((D_80086A40[(s16) a1c].f18 * D_80085458[idx].f14) * D_80085458[idx].f15)) >> 7;
      if (sum >= 0x40)
      {
        a2v = a0v;
        a1v = ((s32) ((0x40 - (sum & 0x3F)) * (a2v << 1))) >> 7;
      }
      else
      {
        a1v = a0v;
        a2v = ((s32) (sum * (a1v << 1))) >> 7;
      }
      fv = D_80086A40[(s16) a1c].f18;
      a1v = ((s32) (a1v * fv)) >> 7;
      a2v = ((s32) (a2v * fv)) >> 7;
      t = a1v * ((s16) v48);
      t2 = a2v * ((s16) v50);
      D_80085458[idx].f10 = (s16) (t >> 7);
      D_80085458[idx].f12 = (u16) (t2 >> 7);
      req.f08 = (s16) D_80085458[idx].f10;
      req.f0a = D_80085458[idx].f12;
      req.f16 = s7v;
      ASM_USE_NV(s7v);

      if (rec->f05 != 0)
      {
        req.f18 = (((u8 *) rec)[-0x1C] << 8) | (0x7F - rec->f05);
      }
      else
      {
        req.f18 = rec->f05 | (rec->f04 << 8);
      }
      func_8005EC0C(&req);
      if (rec->f01 & 4)
      {
        func_8005E4A0(1, D_80073740[idx]);
      }
      else
      {
        func_8005E4A0(0, D_80073740[idx]);
      }
    }
    else
    {
      idx = -1;
    }
  }
  D_80085F98[0] = 0;
  return idx;
}
