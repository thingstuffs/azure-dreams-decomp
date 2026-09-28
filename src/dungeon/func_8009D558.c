#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 func_80042900(void *arg0, s32 arg1);


typedef struct S_800A2CB8_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
} S_800A2CB8_1;   /* arg1 in func_800A2CB8 */

/* Checks entity status and shared flags against another entity. */
u32 func_800A2CB8(void *entity, S_800A2CB8_1 *other_entity) {
    if (other_entity == NULL) {
        return 0;
    }
    if (((u32)((EntityRec *)entity)->flags1C) & 0x410) {
        return 1;
    }
    if ((*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3)) == 0x2B &&
        (((EntityRec *)entity)->unk_98 & 0x8000)) {
        return 1;
    }
    if ((other_entity->unk_14 & 0x4000) &&
        (((u32)((EntityRec *)entity)->flags14) & 0x4000)) {
        return ((u16)func_80042900(entity, 0xC) << 16) != 0;
    }
    return (((((u32)((EntityRec *)entity)->flags1C) ^
              other_entity->unk_1C) & 0x2000) << 16) >> 16;
}
