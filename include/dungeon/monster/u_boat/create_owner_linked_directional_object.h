#ifndef MODULE_DUNGEON_OVL_D5B0B8_H
#define MODULE_DUNGEON_OVL_D5B0B8_H

#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"

typedef struct S_80D3B0B8_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x68];
    u16 unk_94;
    s16 unk_96;
    u8 pad_98[0x14];
    u8 * unk_AC;
} S_80D3B0B8_0;   /* temp_s3 in func_801708B8 */

typedef struct S_80D3B0B8_1 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 * unk_0C;
    void * unk_10;
} S_80D3B0B8_1;   /* temp_v0 in func_801708B8 */

typedef struct S_80D3B0B8_2 {
    u8 pad_00[0x2A];
    union { u16 s; s16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x84];
    u8 unk_B0;
} S_80D3B0B8_2;   /* saved_arg0 in func_801708B8 */

typedef struct S_80D3B0B8_3 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80D3B0B8_3;   /* temp_s1 in func_801708B8 */

typedef struct S_80D3B0B8_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D3B0B8_5;   /* temp_v1 in func_801708B8 */

typedef struct S_80D3B0B8_6 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80D3B0B8_6;   /* saved_arg1 in func_801708B8 */

typedef struct S_80D3B0B8_7 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_80D3B0B8_7;   /* saved_arg2 in func_801708B8 */


typedef struct Copy16 {
    s32 word[4];
} Copy16;


typedef struct { Copy16 block[3]; } Copy48;

extern void *allocate_list_node(s32, void *);
extern void *func_8003FD64(s32, void *);
extern void register_node(void *, void *);
extern void func_8004491C(void *, void *);
extern void select_sprite_entry(void *, u8, s32);
extern void func_80047784(void *, u8, s32);
extern void create_tracked_effect(void *, s32, void *, void *);

extern u8 D_800D5594[];
extern s8 D_800DCECC[];
extern u8 D_800E23F0[];

/* Creates an owner-linked object with copied position and direction-adjusted sprite data. */
#endif
