#include "common.h"

typedef long long s64;
#ifndef NULL
#define NULL 0
#endif
typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80099F70();
s32 func_8009A540();
s32 func_8009B25C();
M2C_UNK func_8009C93C();
M2C_UNK func_8009F644();
s32 func_800A5C70();
extern u16 D_80013714;
extern u8 D_80013186;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern u8 D_80083460[];


typedef struct S_8008C8BC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    union { s32 i; void * p; } unk_60;   /* accessed as both */
    u8 pad_64[0x24];
    u16 unk_88;
} S_8008C8BC_0;   /* held3 in func_8008C8BC */

typedef struct S_8008C8BC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8008C8BC_1;   /* held2 in func_8008C8BC */

typedef struct S_8008C8BC_2 {
    u8 pad_00[0x3186];
    u8 unk_3186;
    u8 pad_3187[0x58D];
    u16 unk_3714;
} S_8008C8BC_2;   /* r4 in func_8008C8BC */

typedef struct S_8008C8BC_3 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8008C8BC_3;   /* temp_v1 in func_8008C8BC */

typedef struct S_8008C8BC_4 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u16 unk_98;
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0xA];
    s16 unk_A6;
    u8 pad_A8[0x5A];
    s8 unk_102;
} S_8008C8BC_4;   /* held0 in func_8008C8BC */

typedef struct S_8008C8BC_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x8];
    void * unk_0C;
} S_8008C8BC_5;   /* state in func_8008C8BC */

/* Selects a target in the facing direction and initializes the entity action state. */
s32 func_8008C8BC(void *actor_state_arg, void *unused, void *position_arg, void *entity_arg) {
    register void *actor_state ASM_REG("$18") = actor_state_arg;
    void *position = position_arg;
    register void *entity = entity_arg;
    s32 direction;
    u8 *page_or_entity;
    s32 target;
    u8 *action_state;

    ASM_KEEP(actor_state);
    direction = ((u16) ((S_8008C8BC_0 *)entity)->unk_2A >> 9) & 7;
    if ((func_8009A540(direction, ((S_8008C8BC_1 *)position)->unk_24, ((S_8008C8BC_1 *)position)->unk_25, (s16) (((S_8008C8BC_0 *)entity)->unk_88 - 0x20)) << 0x10) != 0) {
        target = func_8009B25C(entity, (((S_8008C8BC_1 *)position)->unk_24 + D_8006CCD8[direction]) & 0xFFFF, (((S_8008C8BC_1 *)position)->unk_25 + D_8006CCE8[direction]) & 0xFFFF, (s16) ((S_8008C8BC_0 *)entity)->unk_88);
        ASM_SCHED_BARRIER();
        page_or_entity = (u8 *)0x80010000;
        ((S_8008C8BC_0 *)entity)->unk_60.i = target;
        if (!(((S_8008C8BC_2 *)page_or_entity)->unk_3714 & 1) && (target != 0) && (((S_8008C8BC_3 *)target)->unk_14 & 0x4000)
            && (((S_8008C8BC_2 *)page_or_entity)->unk_3186 & 1) && !(((S_8008C8BC_0 *)entity)->unk_1C & 0x410)) {
            ((S_8008C8BC_0 *)entity)->unk_60.p = NULL;
            return 0;
        }
        page_or_entity = (u8 *)entity;
        func_8009C93C(page_or_entity, position, (s16) ((S_8008C8BC_0 *)entity)->unk_2A, 1, 0);
    } else {
        ((S_8008C8BC_0 *)entity)->unk_60.p = NULL;
    }
    ((S_8008C8BC_4 *)actor_state)->unk_9A = 0x11;
    action_state = D_80083460;
    ((S_8008C8BC_4 *)actor_state)->unk_9B = 0;
    ((S_8008C8BC_4 *)actor_state)->unk_8C = 0;
    ((S_8008C8BC_5 *)action_state)->unk_0C = entity;
    ((S_8008C8BC_4 *)actor_state)->unk_A6 = 0;
    ((S_8008C8BC_4 *)actor_state)->unk_98 = (u16) ((((S_8008C8BC_4 *)actor_state)->unk_98 | 0x2000) & 0xEFFF);
    ((S_8008C8BC_5 *)action_state)->unk_02 = (u16) (((S_8008C8BC_5 *)action_state)->unk_02 | 0x400);
    func_80099F70(((S_8008C8BC_0 *)entity)->unk_5C);
    func_8009F644(entity, 0x18, 0, 0);
    if (func_800A5C70() != 0) {
        ((S_8008C8BC_5 *)action_state)->unk_02 = (u16) (((S_8008C8BC_5 *)action_state)->unk_02 | 0x80);
    }
    ((S_8008C8BC_4 *)actor_state)->unk_96 = 6;
    ((S_8008C8BC_4 *)actor_state)->unk_102 = 0;
    return 0;
}
