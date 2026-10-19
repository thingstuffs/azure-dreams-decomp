#ifndef DUNGEON_OVL_7F511800_P04_H
#define DUNGEON_OVL_7F511800_P04_H
#include "common.h"
#include "shared/object_flags.h"

   /* arg1 in func_80173FF4 */

typedef struct T_80173FF4_S_80173FF4_1 {
    u16 unk_00;
    u8 pad_02[0x1A];
    u16 unk_1C;
} T_80173FF4_S_80173FF4_1;   /* arg0 in func_80173FF4; pointer addresses record offset 0x2 */




#include "shared/object_node.h"
#include "shared/slus_callbacks.h"



typedef struct T_8017406C_S_8017406C_0 {
    u8 pad_00[0x1];
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x24];
    s32 unk_40;
    s32 unk_44;
} T_8017406C_S_8017406C_0;   /* temp_s0 in func_8017406C */

typedef struct T_8017406C_S_8017406C_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    u8 unk_20;
} T_8017406C_S_8017406C_1;   /* temp_v0 in func_8017406C */

typedef struct T_8017406C_S_8017406C_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} T_8017406C_S_8017406C_2;   /* temp_s1 in func_8017406C */

typedef struct T_8017406C_S_8017406C_3 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    u8 pad_08[0x2];
    u16 unk_0A;
} T_8017406C_S_8017406C_3;   /* temp_s3 in func_8017406C */

typedef struct T_8017406C_S_8017406C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_8017406C_S_8017406C_4;   /* temp_v1 in func_8017406C */


s32 rand();


#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct T_801741A0_S_801741A0_0_pre {
    u16 unk_00;
} T_801741A0_S_801741A0_0_pre;   /* the 0x2 bytes before arg0 in func_801741A0, addressed as arg0[-1] */

typedef struct T_801741A0_S_801741A0_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    u16 unk_1E;
    s16 unk_20;
    u8 pad_22[0x1E];
    s32 unk_40;
    s32 unk_44;
} T_801741A0_S_801741A0_0;   /* arg0 in func_801741A0 */


s32 rand();                                /* extern */


#include "records/Rec_func_80173CFC_arg1.h"
#include "shared/dungeon_delay_views.h"

typedef struct T_80174374_S_80174374_0 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[0x17];
    s16 unk_1A;
    u8 pad_1C[0x2];
    s16 unk_1E;
    u8 pad_20[0x20];
    s32 unk_40;
    s32 unk_44;
} T_80174374_S_80174374_0;   /* work in func_80174374 */

typedef struct T_80174374_S_80174374_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} T_80174374_S_80174374_1;   /* obj in func_80174374 */

typedef struct T_80174374_S_80174374_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} T_80174374_S_80174374_2;   /* part in func_80174374 */


typedef struct T_80174374_S_80174374_4 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_80174374_S_80174374_4;   /* pos in func_80174374 */


extern s32 rand(void);


extern s32 func_800478B8();
extern s32 func_8003DB94();
extern s32 func_8004491C();
extern s32 func_800644B8();
extern s32 func_80064584();
extern s32 D_800DEC70;
extern s32 D_800DEC00;
void advance_record_state_and_set_completion_flags(void *record_data, DelayMotionZ *state, s32 update_arg);
void create_tinted_sprite_effect_supplied_position(void *unused, void *position_data, void *unused_primitive);
void update_orbit_height_and_fade_effect(void *effect, EntityRec *position, Rec_D_80082E80 *primitive);
void create_angular_offset_effect(void *unused_context, Rec_func_80173CFC_arg1 *origin, s32 unused_param_2, s32 unused_param_3,
    s16 angle, u16 height_offset);
#endif
