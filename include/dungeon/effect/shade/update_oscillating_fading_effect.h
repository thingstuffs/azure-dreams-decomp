#ifndef DUNGEON_OVL_19134E4_H
#define DUNGEON_OVL_19134E4_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
typedef struct Row_818F34E4_Block24 {
    s32 word[6];
} Row_818F34E4_Block24;

/* cfail-repair: tf7-phase1-cache-v3 */
           /* extern */
 /* extern */

typedef struct Row_818F34E4_S_80024CE4_0 {
    u8 pad_00[0x20];
    u8 * unk_20;
} Row_818F34E4_S_80024CE4_0;   /* temp_s3 in func_80024CE4 */

typedef struct Row_818F34E4_S_80024CE4_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xB];
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} Row_818F34E4_S_80024CE4_1;   /* arg2 in func_80024CE4 */

typedef struct Row_818F34E4_S_80024CE4_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} Row_818F34E4_S_80024CE4_2;   /* temp_s2 in func_80024CE4 */

typedef struct Row_818F34E4_S_80024CE4_3_pre {
    void * unk_00;
    u8 pad_04[0x14];
} Row_818F34E4_S_80024CE4_3_pre;   /* the 0x18 bytes before (*(void **)((u8 *)arg0 + 0x2C)) in func_80024CE4, addressed as (*(void **)((u8 *)arg0 + 0x2C))[-1] */

typedef struct Row_818F34E4_S_80024CE4_4 {
    u8 pad_00[0x9C];
    s16 unk_9C;
} Row_818F34E4_S_80024CE4_4;   /* (*(void **)((u8 *)arg0 + 0x30)) in func_80024CE4 */

/* Updates a timed effect's oscillation, fade, and scale, then marks it finished. */
s32 func_800644B8(s16);
s16 sample_terrain_surface_height(s32, s32, s16);
extern s16 D_800259AC;
void update_oscillating_fading_effect(void *effect, Row_818F34E4_S_80024CE4_2 *position, Row_818F34E4_S_80024CE4_1 *visual, s32 unused);
#endif
