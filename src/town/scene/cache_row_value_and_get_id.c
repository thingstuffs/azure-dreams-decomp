#include "common.h"
#include "m2c_compat.h"
#include "town/scene.h"

typedef struct S_8065C17C_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
} S_8065C17C_0;   /* D_800183CC in cache_row_value_and_get_id */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 D_800183D4;
extern S_8065C17C_0 *D_800183CC;

/* Cache the current record's unk_24 value and return its unk_20 value. */
s32 cache_row_value_and_get_id(void) {
    D_800183D4 = D_800183CC->unk_24;
    return D_800183CC->unk_20;
}
