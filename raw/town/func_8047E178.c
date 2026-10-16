#include "shared/town_pointees.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "m2c_compat.h"


typedef struct {
    s32 _0;
    s32 _4;
} EntryWords;
typedef struct {
    void *_0;
    s32 _4;
    s32 _8;
} PointerRecord;

extern u8 D_800161C0[3];
extern s32 D_80017774[3];
extern PointerRecord D_8001794C;
extern s32 D_80017E66[3];


typedef struct S_8047E178_2 {
    EntryWords * unk_00;
} S_8047E178_2;   /* ((S_8047E178_0 *)p)->unk_08 * 8 +
                  (s8 *)((S_8047E178_0 *)p)->unk_40 in func_8047E178 */

/* Assign the global, child, and current entry table pointers. */
void func_8047E178(void) {
    D_8001794C._0 = &D_80017774[0];
    {
        Rec_D_80016000 *context = D_80016000;
        ((TownPositionState *)context->unk_1C)->unk_40 = &D_80017E66[0];
        ((S_8047E178_2 *)(context->unk_08 * 8 +
                  (s8 *)context->unk_40))->unk_00 = (EntryWords *)&D_800161C0[0];
    }
}
