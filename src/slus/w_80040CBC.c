#include "common.h"

#ifdef NON_MATCHING
#define PAGE_8008 ((u8 *)&D_8008333C)
#define OFF_333C 0
#else
/* ADDR_ALIAS: retail word 17 materialises the 0x8008 page base in $v0 as a bare
 * `lui` and folds %lo(D_8008333C) into the branch-delay-slot store at word 21,
 * with the D_80080A86 $at macro pair scheduled BETWEEN the two halves.  gcc's
 * own high/lo_sum pair can never be split that way: sched.c's adjust_priority
 * gives every register-BIRTHING insn LAUNCH_PRIORITY the moment it becomes
 * ready, so the `high` is always chosen immediately after its own store, while
 * a plain store is a dependence-graph leaf that can never outrank it.  A page
 * CONSTANT is one insn and one quantity, so it can be pinned and scheduled
 * independently; the two ASM_SCHED_BARRIER()s below are what give it its own
 * ready-list group (see the comment at the site).  */
#define PAGE_8008 ((u8 *)0x80080000)
#define OFF_333C 0x333C
#endif
struct S_8006CE80_ptr
{
  s32 *f0;
  s32 f1;
};
struct S_8006CE80
{
  u16 field0;
  u8 pad2[6];
  struct S_8006CE80_ptr *field8;
};
extern struct S_8006CE80 D_8006CE80[];
struct S_8006CE44
{
  s32 field0;
  s32 *field4;
};
extern struct S_8006CE44 D_8006CE44[];
extern s32 D_8006CE6C[];
struct S_80082E60
{
  s32 field_0;
  s32 field_4;
  u8 pad_8[2];
  u8 field_A;
  u8 pad_B[0x18 - 0xB];
};
extern struct S_80082E60 D_80082E60;
struct S_pad9
{
  s32 field0;
  s32 pad4;
  s32 pad8;
};
extern struct S_pad9 D_8008333C;
extern s32 D_80080A7C[3];
extern s32 D_8008148C[3];
extern s32 D_80189394[3];
extern s32 D_801B8EB8[3];
extern s8 D_80080A86[16];
extern u8 D_800E6000[];
extern u8 D_80126804[];
extern void func_8003F6D4(int a0, int a1, int *a2, int a3);
extern int func_8003E4FC(int a0, void *a1, int a2);
extern void func_8003F320(void);
extern void func_800418B4(void);
void func_80040CBC(s16 arg0)
{
  struct S_8006CE80 *node;
  s32 s5;
  int local_10[2];
  int local_18[2];
  node = &D_8006CE80[arg0];
  s5 = node->field0;
  {
    u8 *page;
    /* Retail: lui $v0,%hi(D_8008333C) / lui $at,%hi(D_80080A86) /
     * sb $zero,%lo(D_80080A86)($at) / beqz / sw $zero,%lo(D_8008333C)($v0).
     * The two barriers put the page insn in a ready-list group of its own:
     * without the trailing one it shares a LAUNCH_PRIORITY group with the
     * `lhu` above and schedule_select swaps them ("greater potential hazard",
     * the load owns the memory function unit).  The pin is what earns $v0 --
     * local-alloc's QTY_CMP_PRI (floor_log2(refs)*refs*size/live_length) always
     * ranks the D_80080A86 high FIRST, since its live range is strictly inside
     * this one's.  The pin needs ASM_KEEP_NV or cse make_regs_eqv deletes the
     * copy and the pin with it. */
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    page = PAGE_8008;
    ASM_KEEP_NV(page);   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
    D_80080A86[0] = 0;
    *(s32 *)(page + OFF_333C) = 0;
  }
  if (s5 != 0)
  {
    if (s5 != 4)
    {
      if (D_80082E60.field_A != s5)
      {
        s32 count;
        s32 *s1;
        s32 s0;
        D_80082E60.field_A = s5;
        count = D_8006CE6C[s5];
        s1 = D_8006CE44[s5].field4;
        s0 = 0;
        if ((count - 0x200) > 0)
        {
          u32 mask;
          int *buf2;
          mask = 0x7FFFFF;
          buf2 = local_18;
          do
          {
            func_8003F6D4(0x100, (s1[0] & mask) + (s0 << 11), local_10, s1[1] + s0);
            func_8003E4FC(6, local_10, 0);
            s0 += 0x100;
            func_8003F6D4(0x100, (s1[0] & mask) + (s0 << 11), buf2, s1[1] + s0);
            func_8003E4FC(6, buf2, 0);
            func_8003F320();
            s0 += 0x100;
          }
          while (s0 < (count - 0x200));
        }
        {
          u32 v = s1[0];
          count = v >> 23;
          if (count != 0)
          {
            func_8003F6D4(count, (v & 0x7FFFFF) + (s0 << 11), local_10, s1[1] + s0);
            func_8003E4FC(6, local_10, 0);
          }
          func_8003F320();
        }
      }
    }
    else
    {
      struct S_8006CE80_ptr *p;
      struct S_8006CE80_ptr *q;
      s32 first;
      s32 second;
      func_800418B4();
      p = node->field8;
      q = p;
      ASM_KEEP_NV(q);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
      second = *p->f0;
      first = q->f1;
      D_80189394[0] = first;
      D_801B8EB8[0] = second;
    }
  }
  {
    s32 value;
    s32 address;
    if (s5 == 2)
    {
      value = 0x18800;
      address = (s32) (&D_800E6000);
    }
    else
    {
      value = 0x38000;
      address = (s32) (&D_80126804);
    }
    D_8008148C[0] = address;
    D_80080A7C[0] = value;
  }
  ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): slus-diff; the source shape that makes it unnecessary has not been found */
  D_80082E60.field_4 = D_8006CE44[s5].field0;
}
