#include "common.h"
#include "records/Rec_D_80016000.h"


typedef void (*Callback)(u32);


typedef struct S_806A9100_1 {
    u8 pad_00[0x20];
    void * unk_20;
} S_806A9100_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v in func_806A9100 */


extern u8 D_80016000[];
extern u8 D_80017420[];
extern void *D_800174D4[];

void func_806A9100(void) {
    Callback callback;

    callback = (*(Callback *)((u8 *)(((S_806A9100_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20) + 0x28C));
    D_800174D4[0] = D_80017420;
    callback(1);
    (*(Callback *)((u8 *)(((S_806A9100_1 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20) + 0x290))(1);
}
