#include "common.h"
#define U8(p,o) (*(u8 *)((u8 *)(p)+(o)))
#define S16(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U16(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define U32(p,o) (*(u32 *)((u8 *)(p)+(o)))
#define P32(p,o) (*(void **)((u8 *)(p)+(o)))
extern s32 func_800A6D30(void); extern s32 func_800A48F0(); extern void func_800C5BBC();
extern void func_800A56E0(s32); extern void func_80099844(); extern void func_800CC0AC(void); extern void func_800CC160(void);
extern u8 D_800E3D40; extern u8 D_800E1BBC[];
s32 func_800CC058(void *p) {
 s32 r=0, q, i; void *x;
 if (!D_800E3D40) {
  q=func_800A6D30()&0xffff;
  if (U8(p,3)) {
   register s32 remainder ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
   remainder=q%U8(p,3);
   ASM_KEEP(remainder);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
   func_800CC0AC();
   return remainder;
  }
 }
 i=0;
 ASM_KEEP(i);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
 if (i<0x30 && (func_800A48F0(p,7,-0x10)<<16)>=0) {
  x=P32(p,-0x14); if (!(U16(x,0x14)&0x8000)) { func_800C5BBC((U8(x,0x24)<<6)|0x20,(U8(x,0x25)<<6)|0x20,S16(p,0x88),0x202020,0x40,0); func_800A56E0(0x615); }
  if (U32(p,0x14)&0x4000) { func_80099844(p,D_800E1BBC); func_800CC160(); return r; }
 } else {
  i=U8(p,0x13)==0;
  ASM_KEEP(i);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
  r=i;
 }
 i=r;
 ASM_KEEP(i);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
 if (i) func_800A6508(); return 1;
}
/* MECHANISM: The natural p/r lifetimes produce the 0x28 frame with s0/s1/ra saves.
   Split v0 temporaries plus ASM_KEEP restore the three-word gate and two merge copies.
   A guarded v1 remainder pin with a void tail call yields mfhi v1; j; move v0,v1. */
