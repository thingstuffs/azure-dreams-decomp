#include "common.h"
extern u8 D_80083160[];
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_80065420(void *, void *, void *, void *);
extern s32 func_80066460(s32, s32, s32, s32);
extern void func_80067F20(void *, s32, s32, u16, s32);
void func_8002429C(void *arg0, void *arg1, s16 arg2, s16 arg3)
{
  u8 *arg0p;
  register s32 divshift ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
  register s32 arg2r;
  u32 lomask;
  register s32 phase ASM_REG("$23");   /* MATCH pin: retail immediate-load split depends on it */
  register u8 *sc ASM_REG("$18");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
  u8 *new_var;
  u8 *packet;
  void *p84;
  u8 *work88;
  s32 i = 0;
  s32 shift0;
  arg0p = arg0;
  new_var = (u8 *) D_80083160;
  divshift = (s16) arg3;
  arg2r = (s16) arg2;
  shift0 = arg2r - 1;
  lomask = 0x00FFFFFF;
  phase = 0;
  sc = (u8 *) 0x1F800000;
  *((void **) (((u8 *) sc) + 0x18)) = (*((u8 **) D_80083160)) + 0xB0;
  do
  {
    void **glob = (void **) new_var;
    void *ctx = *glob;
    register s32 value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 q0;
    s32 q1;
    s32 delta;
    s32 scaled;
    s32 average;
    void *arg1use;
    u16 coord;
    packet = *((u8 **) (((u8 *) ctx) + 0x8D0));
    *((u8 **) (((u8 *) ctx) + 0x8D0)) = packet + 0x14;
    *((u8 *) (((u8 *) packet) + 3)) = 4;
    *((u8 *) (((u8 *) packet) + 7)) = 0x52;
    *((u8 *) (((u8 *) packet) + 4)) = *((u8 *) (((u8 *) arg0p) + 0x40));
    *((u8 *) (((u8 *) packet) + 5)) = *((u8 *) (((u8 *) arg0p) + 0x41));
    *((u8 *) (((u8 *) packet) + 6)) = *((u8 *) (((u8 *) arg0p) + 0x42));
    *((u8 *) (((u8 *) packet) + 0xC)) = *((u8 *) (((u8 *) arg0p) + 0x40));
    *((u8 *) (((u8 *) packet) + 0xD)) = *((u8 *) (((u8 *) arg0p) + 0x41));
    *((u8 *) (((u8 *) packet) + 0xE)) = *((u8 *) (((u8 *) arg0p) + 0x42));
    arg1use = *((void * volatile *) (&arg1));
    coord = *((u16 *) (((u8 *) arg1use) + 2));
    *((u16 *) (((u8 *) sc) + 0x6C)) = coord;
    *((u16 *) (((u8 *) sc) + 0x64)) = coord;
    value = ((func_800644B8(phase + (*((s16 *) (((u8 *) arg0p) + 0xA)))) >> 4) * (*((s16 *) (((u8 *) arg0p) + 0xE)))) << 8;
    q0 = value / divshift;
    *((s32 *) (((u8 *) sc) + 0x108)) = value;
    ASM_KEEP_NV(value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    q1 = value / divshift;
    *((u16 *) (((u8 *) sc) + 0x64)) += (q0 * shift0) >> 16;
    *((u16 *) (((u8 *) sc) + 0x6C)) += (q1 * arg2r) >> 16;
    arg1use = *((void * volatile *) (&arg1));
    coord = *((u16 *) (((u8 *) arg1use) + 6));
    *((u16 *) (((u8 *) sc) + 0x6E)) = coord;
    *((u16 *) (((u8 *) sc) + 0x66)) = coord;
    value = ((func_80064584(phase + (*((s16 *) (((u8 *) arg0p) + 0xA)))) >> 4) * (*((s16 *) (((u8 *) arg0p) + 0xE)))) << 8;
    q0 = value / divshift;
    *((s32 *) (((u8 *) sc) + 0x10C)) = value;
    ASM_KEEP_NV(value);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    q1 = value / divshift;
    *((u16 *) (((u8 *) sc) + 0x66)) += (q0 * shift0) >> 16;
    p84 = sc + 0x84;
    *((u16 *) (((u8 *) sc) + 0x6E)) += (q1 * arg2r) >> 16;
    arg1use = *((void * volatile *) (&arg1));
    coord = *((u16 *) (((u8 *) arg1use) + 0xA));
    *((u16 *) (((u8 *) sc) + 0x70)) = coord;
    *((u16 *) (((u8 *) sc) + 0x68)) = coord;
    delta = (((s32) (*((s16 *) (((u8 *) arg0p) + 0x14)))) << 16) - (*((s32 *) (((u8 *) arg1use) + 8)));
    *((s32 *) (((u8 *) sc) + 0x110)) = delta;
    scaled = delta >> divshift;
    *((u16 *) (((u8 *) sc) + 0x68)) += (scaled << shift0) >> 16;
    *((u16 *) (((u8 *) sc) + 0x70)) += (((*((volatile s32 *) (sc + 0x110))) >> divshift) << arg2r) >> 16;
    *((s32 *) (((u8 *) sc) + 0xF4)) = func_80065420(sc + 0x64, sc + 0xD8, p84, sc + 0x88);
    work88 = sc + 0x88;
    *((s32 *) (((u8 *) sc) + 0xF8)) = func_80065420(sc + 0x6C, sc + 0xDC, p84, work88);
    *((u16 *) (((u8 *) packet) + 8)) = *((u16 *) (((u8 *) sc) + 0xD8));
    *((u16 *) (((u8 *) packet) + 0xA)) = *((u16 *) (((u8 *) sc) + 0xDA));
    *((u16 *) (((u8 *) packet) + 0x10)) = *((u16 *) (((u8 *) sc) + 0xDC));
    *((u16 *) (((u8 *) packet) + 0x12)) = *((u16 *) (((u8 *) sc) + 0xDE));
    average = ((*((s32 *) (((u8 *) sc) + 0xF4))) + (*((s32 *) (((u8 *) sc) + 0xF8)))) / 2;
    *((s32 *) (((u8 *) sc) + 0xB4)) = average;
    if (((u32) average) < 0x1E0U)
    {
      u8 *tpage;
      *((u32 *) (((u8 *) packet) + 0)) = ((*((u32 *) (((u8 *) packet) + 0))) & 0xFF000000) | ((*((u32 *) (((u8 *) ((*((u32 **) (((u8 *) sc) + 0x18))) + average)) + 0))) & lomask);
      *((u32 *) (((u8 *) ((*((u32 **) (((u8 *) sc) + 0x18))) + (*((s32 *) (((u8 *) sc) + 0xB4))))) + 0)) = ((*((u32 *) (((u8 *) ((*((u32 **) (((u8 *) sc) + 0x18))) + (*((s32 *) (((u8 *) sc) + 0xB4))))) + 0))) & 0xFF000000) | (((u32) packet) & lomask);
      glob = (void **) new_var;
      ctx = *glob;
      work88 = *((u8 **) (((u8 *) ctx) + 0x8D0));
      *((u8 **) (((u8 *) ctx) + 0x8D0)) = work88 + 0xC;
      func_80067F20(work88, 0, 0, func_80066460(0, *((s16 *) (((u8 *) arg0p) + 0x12)), 0, 0) & 0xFFFF, 0);
      *((u32 *) (((u8 *) work88) + 0)) = ((*((u32 *) (((u8 *) work88) + 0))) & 0xFF000000) | ((*((u32 *) (((u8 *) ((*((u32 **) (((u8 *) sc) + 0x18))) + (*((s32 *) (((u8 *) sc) + 0xB4))))) + 0))) & lomask);
      *((u32 *) (((u8 *) ((*((u32 **) (((u8 *) sc) + 0x18))) + (*((s32 *) (((u8 *) sc) + 0xB4))))) + 0)) = ((*((u32 *) (((u8 *) ((*((u32 **) (((u8 *) sc) + 0x18))) + (*((s32 *) (((u8 *) sc) + 0xB4))))) + 0))) & 0xFF000000) | (((u32) work88) & lomask);
    }
    phase += 0x333;
    i++;
  }
  while (i < 5);
  ASM_KEEP(sc);   /* MATCH pin: load-bearing for the whole function shape */
}
