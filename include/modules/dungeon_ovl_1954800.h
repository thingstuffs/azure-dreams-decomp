#ifndef DUNGEON_OVL_1954800_H
#define DUNGEON_OVL_1954800_H
#include "common.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/slus_callbacks.h"

typedef struct DungeonCell {
    s16 flags;
    u8 pad02[0x12];
} DungeonCell;

typedef struct DungeonGroup {
    u8 pad00[0xC];
    DungeonCell *cells;
    u8 pad10[4];
} DungeonGroup;

typedef struct DungeonObjectEntry {
    u8 column;
    u8 group;
    s8 amount;
    u8 pad03[0x11];
} DungeonObjectEntry;

typedef struct DungeonObject {
    u8 pad00[0x4C];
    DungeonObjectEntry *entry4C;
    DungeonObjectEntry *entry50;
} DungeonObject;

extern DungeonGroup D_80073414[];

/* Decrement eligible entry amounts on flagged cells and return the number changed. */

#ifndef NULL
#define NULL 0
#endif

typedef struct S_81934928_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x1];
    u8 unk_09;
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    union { u16 s; s16 u; } unk_0C;   /* accessed as both */
    union { s16 s; u16 u; } unk_0E;   /* accessed as both */
    union { u16 s; s16 u; } unk_10;   /* accessed as both */
    union { u16 s; s16 u; } unk_12;   /* accessed as both */
    u16 unk_14;
} S_81934928_0;   /* self in func_80024128 */

typedef struct S_81934928_2 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81934928_2;   /* created in func_80024128 */

typedef struct S_81934928_3 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0xC];
    s16 unk_1E;
    u8 pad_20[0x2];
    s16 unk_22;
    u8 pad_24[0x2];
    s16 unk_26;
} S_81934928_3;   /* part in func_80024128 */

typedef struct S_81934928_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_81934928_4;   /* found in func_80024128 */

typedef struct S_81934928_5 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_81934928_5;   /* owner in func_80024128 */

typedef struct S_81934928_6 {
    u16 unk_00;
} S_81934928_6;   /* ((S_81934928_0 *)self)->unk_04 in func_80024128 */

typedef struct {
    s32 word[6];
} Copy24;

extern s32 D_8002445C[];
extern s32 D_80024740[];

/* Spawns a timed particle effect, processes its midpoint target, and marks completion. */

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_81934C5C_0_pre {
    u16 unk_00;
} S_81934C5C_0_pre;   /* the 0x2 bytes before arg0 in func_8002445C, addressed as arg0[-1] */

typedef struct S_81934C5C_0 {
    void * unk_00;
    u8 pad_04[0x8];
    u16 unk_0C;
    u8 pad_0E[0x2];
    u16 unk_10;
    u8 pad_12[0xA];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_1C;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_20;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_24;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_28;   /* overlapping accesses */
    u8 pad_2C[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_30;   /* overlapping accesses */
    u8 pad_34[0x14];
    union { u16 s; s16 u; } unk_48;   /* accessed as both */
    u8 pad_4A[0x2];
    s16 unk_4C;
} S_81934C5C_0;   /* arg0 in func_8002445C */

typedef struct S_81934C5C_1 {
    u8 pad_00[0xE];
    u16 unk_0E;
} S_81934C5C_1;   /* temp_v1 in func_8002445C */

typedef struct S_81934C5C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_81934C5C_2;   /* temp_v0_3 in func_8002445C */

typedef struct S_81934C5C_3 {
    M2C_UNK * unk_00;
    s8 unk_04;
    s8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_81934C5C_3;   /* temp_s1 in func_8002445C */

typedef struct S_81934C5C_4 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_81934C5C_4;   /* temp_spawn_base in func_8002445C */

typedef struct S_81934C5C_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_81934C5C_5;   /* ((S_81934C5C_2 *)temp_v0_3)->unk_08 in func_8002445C */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80024928;
extern M2C_UNK D_800DEDB0;
extern M2C_UNK D_800DEE38;

/* Updates effect motion and spawns an impact effect on reaching the surface. */

extern void (*const D_80024000)(void *, void *);

s32 dungeonIsLinkedObjectFlagged10000(void);
void *func_8003FD64(s32, void *);
void func_8004491C(void *, void *);
s32 rand(void);
void func_8009CE1C(void *, s32, s32, s32, s32, void *, s32);
void *dungeonFindEligibleNearbyEntry(s32, s32, void *, void *);
void func_800A56E0(s32);
s32 func_80069EF8();
s16 func_800BCB04();
s32 decrementFlaggedItemParameters(DungeonObject *object);
void func_80024128(void *self, void *output);
void func_8002445C(void *effect);
#endif
