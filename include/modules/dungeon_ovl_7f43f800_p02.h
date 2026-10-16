#ifndef DUNGEON_OVL_7F43F800_P02_H
#define DUNGEON_OVL_7F43F800_P02_H
#include "common.h"
#ifndef NULL
#define NULL 0
extern void dungeonUpdateActorBehaviorAndDirection();
extern void dungeonCreateTimedOffsetMotionEffect();
#endif
#include "shared/object_flags.h"

typedef struct T_80170F0C_S_func_80D1170C_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 pad_03[1];
    union {
        s32 unk_04;
        struct {
            s8 unk_04;
            s8 unk_05;
            s8 unk_06;
            u8 pad_07[1];
        } bytes;
    } unk_04;
    s32 unk_08;
    u8 pad_0C[0x26];
    union {
        s16 unk_32;
        u16 unk_32_u;
    } unk_32;
    s16 unk_34;
    u8 pad_36[0xA];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[8];
    s32 unk_54;
} T_80170F0C_S_func_80D1170C_1;

typedef struct T_80170F0C_S_func_80D1170C_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} T_80170F0C_S_func_80D1170C_2;

typedef struct T_80170F0C_S_func_80D1170C_3 {
    u16 unk_00;
} T_80170F0C_S_func_80D1170C_3;



#include "shared/entity.h"

typedef struct T_80171020_S_80171020_4 {
    u8 pad_00[0x8];
    void * unk_08;
} T_80171020_S_80171020_4;   /* temp_v0 in func_80171020 */


typedef struct T_80171020_S_80171020_6 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} T_80171020_S_80171020_6;   /* ((T_80171020_S_80171020_4 *)temp_v0)->unk_08 in func_80171020 */

typedef struct T_80171020_S_80171020_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_80171020_S_80171020_7;   /* ((Rec_D_800E3D7C *)arg0)->unk_08.at00_pv.v in func_80171020 */


s32 rand();

typedef struct T_80171020_S_80171020_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} T_80171020_S_80171020_0;   /* temp_v0 in func_80171020 */

typedef struct T_80171020_S_80171020_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x8];
    s16 unk_14;
    u8 pad_16[0x1C];
    s16 unk_32;
    s16 unk_34;
    u8 pad_36[0xA];
    s32 unk_40;
    s32 unk_44;
    s32 unk_48;
    u8 pad_4C[0x8];
    s32 unk_54;
} T_80171020_S_80171020_1;   /* temp_s0 in func_80171020 */

typedef struct T_80171020_S_80171020_2 {
    s32 unk_00;
} T_80171020_S_80171020_2;   /* temp_a2 in func_80171020 */

typedef struct T_80171020_S_80171020_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} T_80171020_S_80171020_3;   /* temp_a2_2 in func_80171020 */


#include "shared/object_node.h"
#include "shared/slus_callbacks.h"



typedef struct T_80171190_S_80171190_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} T_80171190_S_80171190_0;   /* obj in func_80171190 */

typedef struct T_80171190_S_80171190_1 {
    u8 pad_00[0xA];
    s16 unk_0A;
} T_80171190_S_80171190_1;   /* part_a in func_80171190 */

typedef struct T_80171190_S_80171190_2 {
    u8 pad_00[0x24];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} T_80171190_S_80171190_2;   /* part_b in func_80171190 */


typedef struct T_80171190_Work {
    u8 pad0[0x13];
    s8 byte13;
    s32 flags14;
    u8 pad18[4];
    s32 flags1c;
    u8 pad20[0x6C];
    void *ptr8c;
    u8 pad90[0xA];
    u8 byte9a;
    u8 pad9b;
    s8 byte9c;
} T_80171190_Work;


extern void * func_8003FD64();
extern s32 func_8004491C();
extern s32 func_800A6D30();
extern void func_800A48F0();
extern void func_800A9C18();
extern void func_800AA36C();
extern u8 D_80171358[];
extern u8 D_80174E88[];
extern u8 D_80174EF0[];
void dungeonMoveFadeAndAccelerateEffect(T_80170F0C_S_func_80D1170C_1 *effect, T_80170F0C_S_func_80D1170C_2 *position);
void dungeonSpawnRandomVelocityOffsetEffect(EntityRec *parent, s16 effect_id, s32 effect_param, s32 unused, s16 x_offset,
    s16 y_offset, s16 z_offset);
void * func_80171190(s16 flags, s16 kind_id, s16 variant, s16 spawn_value);
extern void dungeonUpdateActorBehaviorAndDirection();
extern void dungeonCreateTimedOffsetMotionEffect();
#endif
