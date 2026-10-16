#include "common.h"
#include "m2c_compat.h"
void func_80173E40(void *, void *, void *, s32);   
typedef struct S_80174320_0_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_80174320_0_pre;   /* the 0x8 bytes before var_s0 in func_80174320, addressed as var_s0[-1] */

typedef struct S_80174320_1 {
    u8 pad_00[0x8];
    void *unk_08;
    void *unk_0C;
} S_80174320_1;   /* temp_a2 in func_80174320 */

/* extern */

/* Render every point in the linked effect chain. */
s32 func_80174320(void *point, void *position, void *color) {
 void *next;
 for (;;) {
  func_80173E40(point,position,color,0);
  next=((S_80174320_0_pre *)point)[-1].unk_00;
  point=next+0x20;
  if(next==0) break;
  position=((S_80174320_1 *)next)->unk_08;
  color=((S_80174320_1 *)next)->unk_0C;
 }
 return 0;
}
