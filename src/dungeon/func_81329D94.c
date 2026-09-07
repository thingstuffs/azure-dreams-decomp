#include "common.h"
#define F(p,t,o) (*(t)((u8 *)(p)+(o)))
extern s16 D_80083228; extern s32 D_80045340, D_80083498, D_801714B0, D_80174C5C; extern void *D_80174CDC[3];
extern void *func_8003FD64(); extern void func_8004491C(); extern void func_80047784(); extern void func_8009A028(); extern void func_8009A3D0(); extern void func_800A9C18();
void func_80171594(u8 x,u8 y,s32 z) {
 register s32 rz ASM_REG("$16")=z;   /* MATCH pin: retail schedule: same instructions, different order without it */
 register u8 rx ASM_REG("$20")=x;   /* MATCH pin: keeps a statement from moving across a call/branch */
 register u8 ry ASM_REG("$21")=y;   /* MATCH pin: keeps a statement from moving across a call/branch */
 void *o,*p ASM_REG("$19"),*a ASM_REG("$17"),*b ASM_REG("$16"); s32 q; u8 bx,by;
 register void *call_o ASM_REG("$4");   /* MATCH pin: retail schedule: same instructions, different order without it */
 ASM_KEEP4_NV(rz,rx,ry,rz);   /* MATCH pin: retail schedule: same instructions, different order without it */
 o=func_8003FD64(0x112,&D_80083498); call_o=o; if(o!=0) {
  register s32 zoff ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
  p=o+0x20; F(p,s8*,0x13)=0x15; F(o,s32**,0x10)=&D_801714B0; func_8004491C(call_o,&D_80045340);
  call_o=o; zoff=rz-0x18; a=F(o,void**,8); F(a,s16*,0xA)=zoff; b=F(o,void**,0xC); F(b,s32**,0x2C)=&D_80174C5C;
  F(b,u8*,0x24)=rx; F(b,u8*,0x25)=ry; F(b,s16*,6)=-4; func_800A9C18(call_o,a,b,0); F(p,s16*,0x2A)=0x200;
  func_80047784(b,((u8 *)F(b,s32**,0x2C))[((D_80083228+0x300)>>9)&7],0); F(b,s16*,0x1E)=0x1800; F(b,s16*,0x1C)=0x1800;
  F(a,u16*,2)-=0x10; F(a,u16*,6)-=0x10; bx=F(b,u8*,0x24); by=F(b,u8*,0x25); q=0x3000; if(F(p,s32*,0x1C)&0x2000) q=0x300;
  func_8009A3D0(bx,by,q); func_8009A028(p); D_80174CDC[0]=o; F(o,s32**,0x10)=(s32 *)((s32)F(o,s32**,0x10)|0x80000000);
 }
}
