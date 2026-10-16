#ifndef DUNGEON_OVL_1936800_H
#define DUNGEON_OVL_1936800_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80024600_arg1.h"
#include "records/Rec_func_80024E80_arg1.h"
#include "shared/entity.h"
#include "shared/dir_step.h"
/* cfail-repair: tf7-phase1-cache-v3 */

typedef struct Row_81916800_S_81916800_1 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} Row_81916800_S_81916800_1;   /* timer in func_80024024 */

typedef struct Row_81916800_S_81916800_2 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} Row_81916800_S_81916800_2;   /* temp_v1 in func_80024024 */

typedef struct Row_81916800_S_81916800_3 {
    union { u8 u; s8 s; } unk_00;   /* accessed as both */
} Row_81916800_S_81916800_3;   /* flag in func_80024024 */

typedef struct Row_81916800_S_81916800_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} Row_81916800_S_81916800_4;   /* (*(void **)((u8 *)arg0 + 0xC)) in func_80024024 */

/* Smooth shared state toward tracked target values and advance countdowns. */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    void *field_B8;
    s32 unkBC;
    char padC0[4];
    s32 unkC4;
    char padC8[4];
    s32 unkCC;
    s32 unkD0;
    char padD4[4];
    void *ptr;
    s16 unkDC;
    s16 unkDE;
    s32 unkE0;
} Row_8191696C_S_8191696C_state;

/* Initializes a dispatch request and reports changes to its identifier and prior mode. */
/* Advance motion counters and position, and set completion flags past the lifetime. */
typedef s32 Row_81916AEC_unk32;

typedef struct Row_81916AEC_Copy6 {
    s32 word[6];
} Row_81916AEC_Copy6;

#ifndef NULL
#define NULL 0
extern void (*const D_80024000)(Row_81917C08_ActionState *action, Row_81917C08_EffectMotion *motion, Row_81917C08_EffectVisual *visual);
#endif

typedef struct Row_81916AEC_S_800242EC_0 {
    u8 pad_00[0x8];
    Row_81916AEC_Copy6 * unk_08;
    void * unk_0C;
    Row_81916AEC_unk32 * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} Row_81916AEC_S_800242EC_0;   /* temp_v0 in func_800242EC */

typedef struct Row_81916AEC_S_800242EC_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    u16 unk_0A;
} Row_81916AEC_S_800242EC_1;   /* temp_v1 in func_800242EC */

typedef struct Row_81916AEC_S_800242EC_2 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} Row_81916AEC_S_800242EC_2;   /* arg2 in func_800242EC */

typedef struct Row_81916AEC_S_800242EC_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} Row_81916AEC_S_800242EC_3;   /* temp_s0 in func_800242EC */

/* Creates an object, initializes its visual state, and copies the initial data. */
typedef struct Row_81916C1C_Prim81916C1C {
    u8 pad0[4];
    s8 x0;
    s8 x1;
    u8 y0;
    u8 flags;
    s16 x2;
    s16 y2;
    s16 x3;
    s16 y3;
} Row_81916C1C_Prim81916C1C;

typedef struct Row_81916C1C_State81916C1C {
    u8 pad0[0x8D0];
    Row_81916C1C_Prim81916C1C *next;
} Row_81916C1C_State81916C1C;

typedef struct Row_81916C1C_Inner81916C1C {
    u8 pad0[0x14];
    u16 counter;
} Row_81916C1C_Inner81916C1C;

typedef struct Row_81916C1C_Arg81916C1C {
    u8 pad0[5];
    s8 count;
} Row_81916C1C_Arg81916C1C;

/* Queue a full-screen primitive and mark completion when the countdown expires. */
typedef struct Row_81916D2C_S_8002452C_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} Row_81916D2C_S_8002452C_1;   /* temp_v0 in func_8002452C */

typedef struct Row_81916D2C_S_8002452C_2 {
    u8 pad_00[0x5];
    s8 unk_05;
} Row_81916D2C_S_8002452C_2;   /* ((Row_81916D2C_S_8002452C_1 *)temp_v0)->unk_0C in func_8002452C */

typedef struct Row_81916D2C_S_8002452C_0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} Row_81916D2C_S_8002452C_0;   /* temp_v0 in func_8002452C */

/* Creates a type 0x212 object and initializes its handler, mode, and value. */
/* Updates the target and records object counts and flags from its status. */
typedef struct Row_81916E00_Copy24 {
    s32 words[6];
} Row_81916E00_Copy24;

#ifndef NULL
#define NULL 0
extern void (*const D_80024000)(Row_81917C08_ActionState *action, Row_81917C08_EffectMotion *motion, Row_81917C08_EffectVisual *visual);
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct Row_81916E00_S_80024600_0 {
    u8 pad_00[0x8];
    Row_81916E00_Copy24 * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
    s16 unk_24;
} Row_81916E00_S_80024600_0;   /* temp_v0 in func_80024600 */

typedef struct Row_81916E00_S_80024600_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} Row_81916E00_S_80024600_1;   /* temp_s0 in func_80024600 */

/* Creates an object with default rendering settings and copies its initial data. */
/* extern */
                             /* extern */

typedef struct Row_81916F10_S_80024710_0 {
    void * unk_00;
    u8 pad_04[0xA];
    s16 unk_0E;
    s16 unk_10;
} Row_81916F10_S_80024710_0;   /* arg0 in func_80024710 */

typedef struct Row_81916F10_S_80024710_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} Row_81916F10_S_80024710_1;   /* temp_v1 in func_80024710 */

typedef struct Row_81916F10_S_80024710_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} Row_81916F10_S_80024710_2;   /* arg1 in func_80024710 */

/* Advance the object counter and offset the position using its two angles. */
#ifndef NULL
#define NULL 0
extern void (*const D_80024000)(Row_81917C08_ActionState *action, Row_81917C08_EffectMotion *motion, Row_81917C08_EffectVisual *visual);
#endif

typedef struct Row_81917004_Copy24 {
    s32 word[6];
} Row_81917004_Copy24;

typedef struct Row_81917004_S_80024804_0 {
    u8 pad_00[0x8];
    Row_81917004_Copy24 * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} Row_81917004_S_80024804_0;   /* obj in func_80024804 */

typedef struct Row_81917004_S_80024804_1 {
    s32 unk_00;
    u8 pad_04[0xA];
    u16 unk_0E;
    u16 unk_10;
} Row_81917004_S_80024804_1;   /* held_arg0 in func_80024804 */

typedef struct Row_81917004_S_80024804_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    s8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} Row_81917004_S_80024804_2;   /* part in func_80024804 */

typedef struct Row_81917004_S_80024804_3 {
    u8 pad_00[0xE];
    union { u16 u; s16 s; } unk_0E;   /* accessed as both */
    union { u16 u; s16 s; } unk_10;   /* accessed as both */
} Row_81917004_S_80024804_3;   /* work in func_80024804 */

/* Creates an effect with scaled parts and offsets it from the origin using the source orientation. */
typedef struct Row_81917234_S_80024A34_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} Row_81917234_S_80024A34_0;   /* temp_a0 in func_80024A34 */

/* Initialize the object's visual state and apply a random spherical position offset. */
typedef struct Row_8191740C_S_80024C0C_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u8 pad_06[0x8];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} Row_8191740C_S_80024C0C_0;   /* arg0 in func_80024C0C */

typedef struct Row_8191740C_S_80024C0C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u16 unk_16;
} Row_8191740C_S_80024C0C_1;   /* object in func_80024C0C */

/* Move the effect toward its target, then expand and fade it until completion. */
typedef struct Row_81917680_S_80024E80_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} Row_81917680_S_80024E80_0;   /* obj in func_80024E80 */

typedef struct Row_81917680_S_80024E80_1 {
    s32 unk_00;
    u8 pad_04[0x1C];
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
} Row_81917680_S_80024E80_1;   /* arg0 in func_80024E80 */

typedef struct Row_81917680_S_80024E80_2 {
    u8 pad_00[0x4];
    s16 unk_04;
    u8 pad_06[0x8];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
} Row_81917680_S_80024E80_2;   /* work in func_80024E80 */

typedef struct Row_81917680_S_80024E80_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x3];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} Row_81917680_S_80024E80_3;   /* control in func_80024E80 */

typedef struct Row_81917680_S_80024E80_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Row_81917680_S_80024E80_4;   /* points in func_80024E80 */

typedef struct Row_81917680_S_80024E80_6 {
    u8 pad_00[0x14];
    s32 unk_14;
} Row_81917680_S_80024E80_6;   /* slot in func_80024E80 */

typedef struct Row_81917680_SixWords {
    s32 word[6];
} Row_81917680_SixWords;

/* Creates an oriented effect between the supplied position and its owner. */
/* extern */
                      /* extern */
                             /* extern */
                             /* extern */

typedef struct Row_81917894_S_80025094_0_pre {
    u16 unk_00;
} Row_81917894_S_80025094_0_pre;   /* the 0x2 bytes before arg0 in func_80025094, addressed as arg0[-1] */

typedef struct Row_81917894_S_80025094_0 {
    void * unk_00;
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    union { u16 u; s16 s; } unk_06;   /* accessed as both */
    s16 unk_08;
    u16 unk_0A;
    s16 unk_0C;
} Row_81917894_S_80025094_0;   /* arg0 in func_80025094 */

typedef struct Row_81917894_S_80025094_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} Row_81917894_S_80025094_1;   /* temp_v1 in func_80025094 */

/* Advances the effect phase, brightness, scale, and position until its lifetime ends. */
typedef struct Row_81917A70_Copy24 {
    s32 word0;
    s32 word4;
    s32 word8;
    s32 wordC;
    s32 word10;
    s32 word14;
} Row_81917A70_Copy24;

typedef struct Row_81917A70_S_80025270_0 {
    u8 pad_00[0x8];
    Row_81917A70_Copy24 * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} Row_81917A70_S_80025270_0;   /* temp_v0 in func_80025270 */

typedef struct Row_81917A70_S_80025270_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x12];
    s32 unk_20;
    s32 unk_24;
    s32 unk_28;
} Row_81917A70_S_80025270_1;   /* temp_a0_2 in func_80025270 */

typedef struct Row_81917A70_S_80025270_3 {
    s32 unk_00;
    s32 unk_04;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} Row_81917A70_S_80025270_3;   /* temp_v1 in func_80025270 */

/* Creates an attached effect with copied transform data and a randomized angle. */
/* Payload of the action object. The entity and motion data are separate objects. */
typedef struct Row_81917C08_ActionState {
    EntityRec *actor;
    u16 *flags;
    u8 reserved_08;
    u8 event_id;
    s16 phase;
    s16 reserved_0C;
    s16 direction;
    s16 ticks;
    s16 reserved_12;
    s16 pending;
    s16 completed_a;
    s16 completed_b;
} Row_81917C08_ActionState;

typedef struct Row_81917C08_EffectMotion {
    Fixed1616 x, y, z;
    s32 next_x, next_y, next_z;
} Row_81917C08_EffectMotion;

typedef struct Row_81917C08_EffectVisual {
    u8 reserved_00[0xC];
    u32 color;
} Row_81917C08_EffectVisual;

typedef struct Row_81917C08_ActorVisual {
    u8 reserved_00[8];
    void *resource;
    u8 reserved_0C[8];
    u16 flags;
    u8 reserved_16[0xE];
    u8 tile_x, tile_y;
} Row_81917C08_ActorVisual;

typedef struct Row_81917C08_ActionSlot { s32 value; } Row_81917C08_ActionSlot;

/* Advance the seven-stage action and its attached movement/effects.
 * Every finished stage clears the tick counter and steps to the next phase in place
 * (the compiler merges the identical stage tails into one copy). */
void D_80024024(void);
M2C_UNK func_800478B8();
s32 func_800644B8();
s32 func_80064584();
void func_8003DB94(void *, void *, s32);
void func_8004491C(void *, void *);
void func_800667A8(void *, s32);
void func_8006658C(void *, void *);
void *func_8003FD64();
s32 func_80069EF8();
s32 rand();
int abs(int);
s32 func_800647A0();
s16 func_80065F90();
s32 func_8003DE58(void *, void *, void *, s32);
s16 func_800A44E0(u16, u16, s16, s16);
s32 func_800BCB04(u16, u16, s16);
void func_800A56E0(s32);
void func_8009CE1C(void *, s32, s32, s32, s16, void *, s32);
extern u8 D_80025B1C[16];

extern Row_81916AEC_unk32 D_800241E4;
extern Row_81916AEC_unk32 D_800DEC70;
extern M2C_UNK D_8002441C;
extern M2C_UNK D_8002457C;
extern M2C_UNK D_800DEC50;
extern s32 D_80024710;
extern s32 D_80025B10;
extern s32 D_800DEDB0[3];
extern u8 D_80024C0C[];
extern u8 D_800DE39C[];
extern s32 D_800DEB70;
extern M2C_UNK D_80025094;
extern u8 D_800DDC40[];
extern Row_81917C08_ActionSlot D_8008346C;
void func_80024024(void *tracker);
s32 func_8002416C(s32 unused, s32 request_id, s32 request_value, s16 request_param);
void func_800241E4(void *motion, void *position, M2C_UNK update_context);
void *func_800242EC(s32 object_id, void *initial_data, Row_81916AEC_S_800242EC_2 *source);
void func_8002441C(void *context, s32 unused, Row_81916C1C_Arg81916C1C *countdown);
void func_8002452C(s32 initial_value);
void func_8002457C(void *object_slot, void *unused, void *target);
void *func_80024600(s32 *owner_data, Row_81916E00_Copy24 *initial_data);
void func_80024710(Row_81916F10_S_80024710_0 *object, Row_81916F10_S_80024710_2 *position);
void *func_80024804(void *source, Row_81917004_Copy24 *origin, s16 size_step);
void func_80024A34(void *object, Rec_func_80024600_arg1 *position, Rec_D_80082E80 *visual);
void func_80024C0C(void *motion, void *position, void *effect);
void *func_80024E80(void *owner, Rec_func_80024E80_arg1 *start_pos);
void func_80025094(void *effect, void *transform, void *visual);
s32 func_80025270(void *object, Row_81917A70_Copy24 *src_transform, s16 effect_index);
void func_80025408(Row_81917C08_ActionState *action, Row_81917C08_EffectMotion *motion, Row_81917C08_EffectVisual *visual);
extern u8 D_800E3D20[];
extern void (*const D_80024000)(Row_81917C08_ActionState *action, Row_81917C08_EffectMotion *motion, Row_81917C08_EffectVisual *visual);
#endif
