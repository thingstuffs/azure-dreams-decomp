#include "common.h"
#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
extern void func_80046E38(); extern void func_80067014(); extern void func_8006733C(); extern void func_800B73D0();
extern u8 D_80082E60[], D_80083160[], D_80110EC8[], D_801116C8[], D_80111EC8[], D_8012F004[], D_80162004[]; extern u16 D_80111FA8[];
void func_800B6FB8(void)
{
u8 *base,*status;u16 *image,*arg0,*third;u8 *arg1;void *draw;s32 width,color,seven;u16 eight;void *next;
image=D_80111FA8;
arg0=image;
arg1=D_80110EC8;
base=D_80083160;
draw=base+0x1DC;
color=0x7F;
width=0x2000;
FIELD(draw,s16,0x14)=7;
FIELD(draw,s16,0x18)=color;
FIELD(draw,s16,0x1C)=width;
seven=7;
FIELD(draw,s16,0x16)=seven;
FIELD(draw,s16,0x1A)=color;
FIELD(draw,s16,0x1E)=width;
status=D_80082E60;
D_80111FA8[0]=0x328;
image[1]=0x80;
eight=8;
image[2]=eight;
image[3]=0x80;
FIELD(status,u16,0x16)&=0xFFFE;
func_8006733C(arg0,arg1);
D_80111FA8[0]=0x330;
image[1]=0x80;
image[2]=eight;
image[3]=0x80;
func_8006733C(image,D_801116C8);
third=D_80111FA8;
D_80111FA8[0]=0;
third[1]=0x1FB;
third[2]=0x40;
third[3]=1;
func_8006733C(third,D_80111EC8);
func_80067014(0);
next=D_80162004;
FIELD(base,void *,0x1DC)=next;
func_800B73D0();
func_80046E38(0,D_8012F004);
}
