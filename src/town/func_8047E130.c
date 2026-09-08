/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"



typedef struct {
    s32 _0;
    s32 _4;
} M2C_ENTRY;
typedef struct {
    void *_0;
    s32 _4;
    s32 _8;
} M2C_PTR_GLOBAL;

extern M2C_PTR_GLOBAL D_80016000;
extern M2C_UNK D_80016178[3];
extern M2C_UNK D_80017720[3];
extern M2C_PTR_GLOBAL D_8001794C;
extern M2C_UNK D_80017B88[3];



typedef struct S_8047E130_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    void * unk_1C;
    u8 pad_20[0x20];
    void * unk_40;
} S_8047E130_0;   /* p in func_8047E130 */

typedef struct S_8047E130_1 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_8047E130_1;   /* ((S_8047E130_0 *)p)->unk_1C in func_8047E130 */

typedef struct S_8047E130_2 {
    M2C_ENTRY * unk_00;
} S_8047E130_2;   /* ((S_8047E130_0 *)p)->unk_08 * 8 +
                  (s8 *)((S_8047E130_0 *)p)->unk_40 in func_8047E130 */

/* Assign the global, child, and current entry table pointers. */
void func_8047E130(void) {
    do { D_8001794C._0 = &D_80017720[0]; } while (0);
    {
        S_8047E130_0 *context = D_80016000._0;
        ((S_8047E130_1 *)(context->unk_1C))->unk_40 = &D_80017B88[0];
        ((S_8047E130_2 *)(context->unk_08 * 8 +
                  (s8 *)context->unk_40))->unk_00 = (M2C_ENTRY *)&D_80016178[0];
    }
}
