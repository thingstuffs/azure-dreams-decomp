#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern s32 func_80042900(void *arg0, s32 arg1);

typedef struct S_800A2CB8_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x78];
    u16 unk_98;
} S_800A2CB8_0;   /* arg0 in func_800A2CB8 */

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
    if (((S_800A2CB8_0 *)entity)->unk_1C & 0x410) {
        return 1;
    }
    if (((S_800A2CB8_0 *)entity)->unk_13 == 0x2B &&
        (((S_800A2CB8_0 *)entity)->unk_98 & 0x8000)) {
        return 1;
    }
    if ((other_entity->unk_14 & 0x4000) &&
        (((S_800A2CB8_0 *)entity)->unk_14 & 0x4000)) {
        return ((u16)func_80042900(entity, 0xC) << 16) != 0;
    }
    return (((((S_800A2CB8_0 *)entity)->unk_1C ^
              other_entity->unk_1C) & 0x2000) << 16) >> 16;
}
