#include "common.h"
#define F(p,t,o) (*(t *)((u8 *)(p)+(o)))
extern u8 *D_800E3D7C;
extern u8 D_80082E80[],D_80083780[],D_800893D8[],D_800E16E3[],D_800E1713[],D_800E39C8[];
extern s32 D_80083460;
extern s16 func_800B60B8(s32,s32,s16,s32,s32);
extern s32 func_800C30B0(void),func_800C7380(s32,s32,s16,s32,s32),func_800990FC(void),func_80099368(void *,s32),func_80099194(void *,s32),func_80099734(void *,s32),func_800999B0(s32);
extern void func_8008D344(void *, void *, void *, void *);
extern void func_80098B38(void *);
extern void func_80099290(s32);
extern void func_800997FC(void *);
extern void func_8009A21C(u8, u8, s32);
extern void func_800A56E0(s32);
extern void func_800A5720(s32);
extern void func_800C8CD8(void *, s32, s32);
s32 func_800C2F2C(void *arg0,u8 *arg1,s16 arg2) {
    s16 x; register s32 a ASM_REG("$5"); s32 b, r; s32 *counter_base; void *p; u8 *q; u8 *base;
    if(arg0==D_800E3D7C){F(arg0,u8 *,0x110)=arg1;func_8008D344(arg0,D_80083780,D_80082E80,arg0);func_800C30B0();return 0;}
    p=F(arg0,void **,-0x14); r=func_800C7380(F(p,u8,0x24),F(p,u8,0x25),F(arg0,s16,0x88),-1,*arg1);
    if(r!=0){func_800A56E0(0x60D);x=func_800B60B8(F(p,u8,0x24),F(p,u8,0x25),F(arg0,s16,0x88),5,r);q=(u8 *)r+0x20;ASM_KEEP(q);base=D_800E39C8;F(q,s16,0x20)=x;F(base+x*0x18,s32,8)=0;a=func_800990FC();ASM_KEEP(a);b=a;
        if(arg2==0xD){func_80099290(func_800999B0(func_80099194(D_800893D8,func_80099734(arg0,func_80099194(D_800E1713,func_80099368(arg1,a))))));func_800A5720(b);}
        func_800997FC(D_800E16E3);func_800C8CD8(arg0,0x100,0x10);func_8009A21C(F(p,u8,0x24),F(p,u8,0x25),0x10);func_80098B38(arg1);counter_base=&D_80083460;F(counter_base,u16,0xA)--;return 1;}return 0;
}
/* MECHANISM: The 48-byte frame follows from the three held args, entity, and object handle.
   Guarded v1/a1 runtime holds preserve the split object-field address and handle-copy schedule.
   A held counter base restores the tail addiu and collapses the branch displacement cascade. */
