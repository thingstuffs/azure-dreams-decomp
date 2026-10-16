#ifndef DUNGEON_OVL_7F469800_P03_H
#define DUNGEON_OVL_7F469800_P03_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80172CC0_arg0.h"

typedef struct T_80172CC0_S_80172CC0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    u8 pad_49[0x28];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} T_80172CC0_S_80172CC0_0;   /* state in func_80172CC0 */


typedef struct T_80172CC0_S_80172CC0_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} T_80172CC0_S_80172CC0_2;   /* entry in func_80172CC0 */


typedef struct T_80172CC0_S_80172CC0_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} T_80172CC0_S_80172CC0_4;   /* (u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s in func_80172CC0 */





#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct T_80172F58_S_80172F58_1 {
    u8 pad_00[0x12];
    u8 unk_12;
    u8 pad_13[0x1];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x19];
    u8 unk_45;
    u16 unk_46;
    u8 pad_48[0x25];
    union { u8 u; s8 s; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
} T_80172F58_S_80172F58_1;   /* arg3 in func_80172F58 */

typedef struct T_80172F58_S_80172F58_2 {
    u8 pad_00[0x24];
    union {
        struct { u8 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
    } unk_24;   /* overlapping accesses */
    union { s8 s; u8 u; } unk_26;   /* accessed as both */
} T_80172F58_S_80172F58_2;   /* arg2 in func_80172F58 */

typedef struct T_80172F58_S_80172F58_3_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} T_80172F58_S_80172F58_3_pre;   /* the 0x14 bytes before found in func_80172F58, addressed as found[-1] */

typedef struct T_80172F58_S_80172F58_3 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} T_80172F58_S_80172F58_3;   /* found in func_80172F58 */

typedef struct T_80172F58_S_80172F58_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} T_80172F58_S_80172F58_4;   /* object in func_80172F58 */


typedef struct T_80172F58_S_80172F58_9 {
    u8 pad_00[0xC];
    u16 unk_0C;
} T_80172F58_S_80172F58_9;   /* kind_table + kind * 0x14 in func_80172F58 */

typedef struct T_80172F58_S_80172F58_10 {
    u8 pad_00[0x98];
    u16 unk_98;
    u8 pad_9A[0x2];
    union { s8 s; u8 u; } unk_9C;   /* accessed as both */
} T_80172F58_S_80172F58_10;   /* arg0 in func_80172F58 */

typedef struct T_80172F58_S_80172F58_11 {
    u16 unk_00;
} T_80172F58_S_80172F58_11;   /* &D_80082EA4 in func_80172F58 */

typedef struct T_80172F58_S_80172F58_13 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} T_80172F58_S_80172F58_13;   /* arg3 + (((T_80172F58_S_80172F58_1 *)arg3)->unk_71.u & 0x7F) in func_80172F58 */







typedef struct T_80173678_S_80173678_1 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
} T_80173678_S_80173678_1;   /* arg3 in func_80173678 */





typedef struct T_80173734_S_80173734_0 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 unk_48;
    u8 pad_49[0x17];
    void * unk_60;
    u8 pad_64[0x6];
    u16 unk_6A;
    u8 pad_6C[0x1];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x10];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x2];
    s16 unk_88;
} T_80173734_S_80173734_0;   /* arg3 in func_80173734 */

typedef struct T_80173734_S_80173734_1 {
    u8 pad_00[0x2];
    u16 unk_02;
} T_80173734_S_80173734_1;   /* flags in func_80173734 */

typedef struct T_80173734_S_80173734_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} T_80173734_S_80173734_2;   /* arg2 in func_80173734 */

typedef struct T_80173734_S_80173734_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
    s16 unk_AC;
} T_80173734_S_80173734_3;   /* arg0 in func_80173734 */

typedef struct T_80173734_S_80173734_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} T_80173734_S_80173734_4_pre;   /* the 0x14 bytes before ((T_80173734_S_80173734_0 *)arg3)->unk_60 in func_80173734, addressed as ((T_80173734_S_80173734_0 *)arg3)->unk_60[-1] */






typedef struct T_80173B48_S_80173B48_0 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    u8 pad_49[0x17];
    void * unk_60;
    u8 pad_64[0x6];
    u16 unk_6A;
    u8 pad_6C[0x1];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x10];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x2];
    s16 unk_88;
} T_80173B48_S_80173B48_0;   /* arg3 in func_80173B48 */

typedef struct T_80173B48_S_80173B48_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
    s16 unk_AC;
} T_80173B48_S_80173B48_1;   /* arg0 in func_80173B48 */

typedef struct T_80173B48_S_80173B48_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} T_80173B48_S_80173B48_2;   /* arg2 in func_80173B48 */

typedef struct T_80173B48_S_80173B48_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} T_80173B48_S_80173B48_3_pre;   /* the 0x14 bytes before ((T_80173B48_S_80173B48_0 *)arg3)->unk_60 in func_80173B48, addressed as ((T_80173B48_S_80173B48_0 *)arg3)->unk_60[-1] */




extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 dungeonCheckMovementClearanceAndHeight();
extern s16 dungeonGetRoundedFacingAndRoundingFlag();
extern s32 dungeonCheckEntityRelation();
extern s32 dungeonCheckDiagonalSideHeight();
extern s32 dungeonCompareMonsterNeighborValues();
extern s16 dungeonGetActorHeightDifference();
extern void * dungeonFindValidMonsterNeighbor();
extern void * dungeonPlaceActorAtDirectionalNeighbor();
extern void dungeonRebuildMonsterReachableTiles();
extern void dungeonUpdateActorProximityFlag();
extern s32 func_800A6D30();
extern void func_800A9A0C();
extern s16 func_800BCB04();
extern void dungeonResolveAttackDamageAndEffects(void *, void *, s16, s16);
extern void dungeonPrepareDirectionalAttack(void *, void *, s16, s16, void *);
extern s16 dungeonGetTileChebyshevDistance(void *, void *);
extern void * dungeonScanMonsterAlongHeading(void *, u8, u8, s16, s32);
extern s32 func_800A2B5C(void *);
extern s32 func_800A2CB8(void *, void *);
extern void dungeonSetupObjectWithinPlanarRange(void *, s32, s32, s16, s32, s32);
extern void dungeonApplyCameraOffsetAndSelectTarget(void *, s32, s32, s32);
extern s32 D_80175DC4;
extern s32 D_80175DCC;
extern s32 D_80175DD4;
extern s16 D_8006CD00[];
extern u8 D_80175E9C[];
extern u8 D_80175EA4[];
extern u8 D_80175EAC[];
extern u16 D_800DCEAC[];
extern u16 D_800DCEBC[];
void func_80172CC0(void *movement, s32 actor_index, void *actor, void *path_state);
void dungeonSelectAndAdvanceActorMove(u8 *move_input, void *action_context, u8 *position, u8 *actor);
void dungeonResetActorDirectionalAnimation(Rec_func_80172CC0_arg0 *state, s32 unused, Rec_D_80082E80 *display, T_80173678_S_80173678_1 *entity);
s32 dungeonCheckAndPrepareActorMove(void *action_state, s32 facing, void *origin, void *actor);
void dungeonPrepareActorPathMovement(void *action_input, s32 x_offset_input, void *position_input, void *actor_input);
#endif
