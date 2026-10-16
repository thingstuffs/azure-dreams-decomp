#ifndef DUNGEON_OVL_7F43F800_P01_H
#define DUNGEON_OVL_7F43F800_P01_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

typedef long long long long;

typedef struct T_80170AD0_S_80170AD0_0 {
    u8 pad_00[0x94];
    s16 unk_94;
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0xA];
    s16 unk_A2;
    u8 pad_A4[0x4];
    void * unk_A8;
} T_80170AD0_S_80170AD0_0;   /* arg0 in func_80170AD0 */

typedef struct T_80170AD0_S_80170AD0_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
} T_80170AD0_S_80170AD0_1;   /* effect in func_80170AD0 */

typedef struct T_80170AD0_S_80170AD0_2 {
    u8 pad_00[0x3];
    s8 unk_03;
    u8 pad_04[0x7];
    u8 unk_0B;
} T_80170AD0_S_80170AD0_2;   /* stats in func_80170AD0 */

typedef struct T_80170AD0_S_80170AD0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_80170AD0_S_80170AD0_3;   /* coords in func_80170AD0 */

typedef struct T_80170AD0_S_80170AD0_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} T_80170AD0_S_80170AD0_4;   /* other in func_80170AD0 */




typedef struct {
    u16 xyz[3];
    u16 pad;
    long long out18;
    s32 out20;
    s32 out24;
} T_80170AD0_StackWork;

extern void func_800478B8();
extern s32 func_80065420();
extern s8 D_800DCECC[8];
void func_80170AD0(void *state, void *position, void *effect_arg);
#endif
