#ifndef SHARED_DUNGEON_DELAY_VIEWS_H
#define SHARED_DUNGEON_DELAY_VIEWS_H
#include "common.h"
#include "m2c_compat.h"
/* One shared game-view inventory for the delayed-effect producers and callbacks. */
typedef struct {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
} DelayPosition;

typedef struct DelayStatusPrefix {
    u16 unk_00;
} DelayStatusPrefix;   /* the 0x2 bytes before r_arg0 in func_800247D8, addressed as r_arg0[-1] */

typedef struct DelayParticle {
    void * unk_00;
    u8 pad_04[0x44];
    u16 unk_48;
    u8 pad_4A[0x2];
    union { u16 u; s16 s; } unk_4C;   /* accessed as both */
} DelayParticle;   /* r_arg0 in func_800247D8 */

typedef struct DelayOwner {
    u8 pad_00[0x52];
    u16 unk_52;
} DelayOwner;   /* temp_v1 in func_800247D8 */

typedef struct DelaySpriteColor {
    u8 pad_00[0xC];
    union {
        struct { u8 v; } at00;
        struct { s32 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
    } unk_0C;   /* overlapping accesses */
} DelaySpriteColor;   /* arg2 in func_800247D8 */

typedef struct DelayMotion {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x8];
    s32 unk_14;
} DelayMotion;   /* arg1 in func_800247D8 */

typedef struct DelayObject {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} DelayObject;   /* temp_v0_4 in func_800247D8 */

typedef struct DelayMotionZ {
    u8 pad_00[0x8];
    s32 unk_08;
} DelayMotionZ;   /* child in func_800247D8 */

typedef struct DelaySprite {
    u8 * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} DelaySprite;   /* temp_s0 in func_800247D8 */


typedef struct DelayParticleTimers {
    u8 pad_00[0x48];
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
} DelayParticleTimers;   /* temp_v1_3 in func_800247D8 */

typedef struct DelayVelocity {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} DelayVelocity;   /* ((DelayObject *)temp_v0_4)->unk_08 in func_800247D8 */


#endif
