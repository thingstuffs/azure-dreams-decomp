/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001A1A0_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001A1A0_0;   /* D_80016000[0] in func_8001A1A0 */

typedef struct S_8001A1A0_1 {
    u8 pad_00[0x2D4];
    s32 (*unk_2D4)(M2C_UNK);
} S_8001A1A0_1;   /* ((S_8001A1A0_0 *)(D_80016000[0]))->unk_20 in func_8001A1A0 */




#define M2C_BREAK() ((void)0)
#define M2C_SYNC() ((void)0)

M2C_UNK func_8001A188();
extern void *D_80016000[];


void func_8001A1A0(s32 arg0, s32 *arg1) {
    func_8001A188(arg0, *((((S_8001A1A0_1 *)(((S_8001A1A0_0 *)(D_80016000[0]))->unk_20))->unk_2D4(0)) + arg1));
}
