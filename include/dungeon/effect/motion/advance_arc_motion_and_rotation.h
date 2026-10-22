#ifndef DUNGEON_OVL_18BE820_H
#define DUNGEON_OVL_18BE820_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/object_flags.h"
typedef struct Row_8189E820_S_8189E820_0_pre {
    u16 unk_00;
} Row_8189E820_S_8189E820_0_pre;   /* the 0x2 bytes before arg0 in func_80024020, addressed as arg0[-1] */

typedef struct Row_8189E820_S_8189E820_0 {
    s16 unk_00;
    s16 unk_02;
    s32 unk_04;
    void * unk_08;
} Row_8189E820_S_8189E820_0;   /* arg0 in func_80024020 */

typedef struct Row_8189E820_S_8189E820_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} Row_8189E820_S_8189E820_1;   /* temp_v1 in func_80024020 */

typedef struct Row_8189E820_S_8189E820_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Row_8189E820_S_8189E820_2;   /* arg1 in func_80024020 */

typedef struct Row_8189E820_S_8189E820_3 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} Row_8189E820_S_8189E820_3;   /* arg2 in func_80024020 */

/* Advances arcing motion and rotation, then flags completion when the duration expires. */
s32 func_800644B8();

void advance_arcing_effect_motion(void *state, Row_8189E820_S_8189E820_2 *motion, Row_8189E820_S_8189E820_3 *rotation);
#endif
