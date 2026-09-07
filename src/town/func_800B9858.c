#include "common.h"

typedef struct S_800B6FB8_0 {
    u8 pad_00[0x14];
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_800B6FB8_0;   /* draw in func_800B6FB8 */

typedef struct S_800B6FB8_1 {
    u8 pad_00[0x16];
    u16 unk_16;
} S_800B6FB8_1;   /* status in func_800B6FB8 */

typedef struct S_800B6FB8_2 {
    u8 pad_00[0x1DC];
    void * unk_1DC;
} S_800B6FB8_2;   /* base in func_800B6FB8 */

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
((S_800B6FB8_0 *)draw)->unk_14=7;
((S_800B6FB8_0 *)draw)->unk_18=color;
((S_800B6FB8_0 *)draw)->unk_1C=width;
seven=7;
((S_800B6FB8_0 *)draw)->unk_16=seven;
((S_800B6FB8_0 *)draw)->unk_1A=color;
((S_800B6FB8_0 *)draw)->unk_1E=width;
status=D_80082E60;
D_80111FA8[0]=0x328;
image[1]=0x80;
eight=8;
image[2]=eight;
image[3]=0x80;
((S_800B6FB8_1 *)status)->unk_16&=0xFFFE;
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
((S_800B6FB8_2 *)base)->unk_1DC=next;
func_800B73D0();
func_80046E38(0,D_8012F004);
}
