#include "common.h"
void func_80088EDC(void *a, void *b, void *c) {
 void *s=*(void**)a; s16 st;
 if (*(u16*)((char*)s+0x26)&1) *(s16*)((char*)a+8)=255;
 st=*(s16*)((char*)a+8);
 if(st==16) goto state16;
 if(st<17){if(st==1)goto state1;if(st<2)goto done;if(st==2)goto state2;goto done;}
 if(st==33)goto state33;
 if(st<34){if(st==32)goto state32;goto done;}
 if(st==255)goto state255;goto done;
state1:
 {u16 t=*(u16*)((char*)a+0xa)-1;*(u16*)((char*)a+0xa)=t;if((s32)(t<<16)<=0){*(s32*)b=*(s32*)b+*(s32*)((char*)b+0xc);*(s32*)((char*)b+0xc)=*(s32*)((char*)b+0xc)-0x10000;if(*(s32*)((char*)b+0xc)==0){*(u16*)((char*)a+0xa)=4;*(s16*)((char*)a+8)=2;}}}goto done;
state2:
 {u16 t;*(s16*)((char*)b+2)=*(u16*)((char*)b+2)+((160-*(s16*)((char*)b+2))>>1);t=*(u16*)((char*)a+0xa)-1;*(u16*)((char*)a+0xa)=t;if((s32)(t<<16)<=0)*(s16*)((char*)a+8)=16;}goto done;
state16:
 *(s16*)((char*)b+2)=160;if(*(s16*)((char*)s+0x20)==32){if(*(s16*)((char*)s+0x24)==*(s16*)((char*)a+0xc))*(s16*)((char*)a+8)=32;else{*(s32*)((char*)b+0xc)=0xfff80000;*(s16*)((char*)a+8)=33;}}goto done;
state32:
 if((*(u16*)((char*)s+0x22)>>3)&1)*(u16*)((char*)c+0x14)|=0x80;else*(u16*)((char*)c+0x14)&=0xff7f;goto done;
state33:
 {s32 e=*(s32*)b;if(e<=0x1ffffff){*(s32*)b=e+*(s32*)((char*)b+0xc);*(s32*)((char*)b+0xc)=*(s32*)((char*)b+0xc)+0x20000;}}goto done;
state255:
 {s32 *base=(s32 *)0x80080000;*(u16*)((char*)a-2)|=0x8000;base[0x14a0/4]|=0x8000;}goto done;
done:;
}
