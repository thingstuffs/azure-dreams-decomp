#include "common.h"
extern int abs(int);

typedef s32 M2C_UNK;
typedef void (*Callback)();

#ifdef NON_MATCHING
typedef union {
    long long value;
    struct { u32 low; s32 high; } word;
} DivProduct;
#else
typedef union {
    long long value;
    struct { s32 high; u32 low; } word;
} DivProduct;
#endif


extern void func_800353F4();
extern void func_80047738();
extern void func_800478B8();
extern void func_800A020C();
extern s32 func_800A9E70();
extern void func_800AA36C();
extern s16 func_800BCB04();

extern u16 D_80013714;
extern s16 D_80083228;
extern u16 D_80083462;
extern s16 D_8008346A;
extern u8 *D_800E3D7C[];
extern M2C_UNK D_80171514;
extern Callback D_80173EF4[];
extern M2C_UNK D_80173FC8[];


typedef struct S_8017112C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x41];
    union { u8 n; volatile u8 v; s8 n2; } unk_6D;   /* accessed as both */
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x16];
    u16 unk_88;
    u8 pad_8A[0x11];
    u8 unk_9B;
    u8 pad_9C[0x1F];
    u8 unk_BB;
} S_8017112C_0;   /* actor in func_8017112C */

typedef struct S_8017112C_1 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8017112C_1;   /* slot in func_8017112C */

typedef struct S_8017112C_2_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_8017112C_2_pre;   /* the 0x14 bytes before node in func_8017112C, addressed as node[-1] */

typedef struct S_8017112C_3 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8017112C_3;   /* record in func_8017112C */

typedef struct S_8017112C_4 {
    s32 unk_00;
    u8 pad_04[0x4];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_08;   /* overlapping accesses */
    s32 unk_0C;
    s32 unk_10;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_14;   /* overlapping accesses */
} S_8017112C_4;   /* motion in func_8017112C */

typedef struct S_8017112C_5 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_8017112C_5;   /* monster in func_8017112C */

/* Updates actor behavior, movement, facing, and height. */
void func_8017112C(void *entity_arg, void *motion_arg, void *monster_arg)
{
    void *motion = motion_arg;
    void *monster = monster_arg;
    void *actor = entity_arg;
    register s16 state_direction ASM_REG("$17");
    register u8 raw_state ASM_REG("$2");
    register void *call_entity ASM_REG("$4");
    register void *call_motion ASM_REG("$5");
    register void *call_monster ASM_REG("$6");
    register s32 saved_state ASM_REG("$2");
    s32 current_state;
    register s32 view_angle ASM_REG("$2");
    register s32 next_height ASM_REG("$2");
    Callback callback;
    Callback active_callback;
    s16 floor_height;
    s32 target_height;
    register s32 height_bits ASM_REG("$4");
    s32 height;
    s32 height_gap;
    u16 global_flags;
    u16 *flag_word;
    s32 height_delta;
    s32 height_fixed;
    s32 divisor_magic;
    s32 height_step;
    DivProduct product;
    u8 *slot;
    void *node;
    void *record;

    if (((S_8017112C_0 *)actor)->unk_BB == 0 && D_8008346A == 0) {
        ((S_8017112C_0 *)actor)->unk_BB = 1;
        func_800353F4(D_80173FC8);
        ((S_8017112C_0 *)actor)->unk_6D.n = 0;
        ((S_8017112C_0 *)actor)->unk_9B = 0;
    }

    ASM_MEM_BARRIER();
    flag_word = &D_80013714;
    global_flags = *flag_word;
    if (global_flags & 8) {
        s32 slot_index = 1;
        slot = D_800E3D7C[0] + 4;
        do {
            node = ((S_8017112C_1 *)slot)->unk_AC;
            if (node != 0) {
                record = ((S_8017112C_2_pre *)node)[-1].unk_00;
                ((S_8017112C_3 *)record)->unk_14 &= 0xFFBF;
            }
            slot_index--;
            slot -= 4;
        } while (slot_index >= 0);
    }

    if (D_80083462 & 0x2000) {
        callback = (*(Callback *)((u8 *)entity_arg + (0x8C)));
        if (callback == (Callback)&D_80171514) {
            callback(entity_arg, motion, monster, actor);
            return;
        }
        ((S_8017112C_0 *)actor)->unk_71 &= 0x7F;
        return;
    }

    call_entity = entity_arg;
    call_motion = motion;
    call_monster = monster;
    raw_state = ((S_8017112C_0 *)actor)->unk_6D.v;
    state_direction = ((s32)raw_state << 24) >> 24;
    if (func_800A9E70(call_entity, call_motion, call_monster, actor) != 0) {
        return;
    }

    active_callback = (*(Callback *)((u8 *)entity_arg + (0x8C)));
    if (active_callback != 0) {
        active_callback(entity_arg, motion, monster, actor);
    }
    D_80173EF4[(*(u8 *)((u8 *)entity_arg + (0x9A)))](entity_arg, motion, monster, actor);

    saved_state = (s32)state_direction << 16;
    current_state = ((S_8017112C_0 *)actor)->unk_6D.n2;
    saved_state >>= 16;
    if (saved_state != current_state) {
        func_800AA36C(entity_arg, motion, monster, actor);
    }

    ((S_8017112C_4 *)motion)->unk_00 += ((S_8017112C_4 *)motion)->unk_0C;
    (*(s32 *)((u8 *)motion + (4))) += ((S_8017112C_4 *)motion)->unk_10;

    view_angle = D_80083228 + ((S_8017112C_0 *)actor)->unk_2A + 0x100;
    state_direction = (view_angle >> 9) & 7;
    if ((*(s16 *)((u8 *)entity_arg + (0x94))) != state_direction) {
        func_80047738(monster,
                     *((u8 *)((S_8017112C_5 *)monster)->unk_2C + state_direction),
                     ((S_8017112C_5 *)monster)->unk_04);
        (*(s16 *)((u8 *)entity_arg + (0x94))) = state_direction;
    }

    ((S_8017112C_5 *)monster)->unk_14 &= 0xFFFE;
    func_800A020C(((S_8017112C_0 *)actor)->unk_1C, (u8 *)monster + 0xC);

    if (!(((S_8017112C_0 *)actor)->unk_1C & 0x20)) {
        if (!(((S_8017112C_5 *)monster)->unk_14 & 0x40)) {
            func_800478B8(monster);
        }
    } else {
        ((S_8017112C_5 *)monster)->unk_14 |= 0x7000;
        ((S_8017112C_0 *)actor)->unk_1C &= 0xFFFBFFFF;
    }

    if ((*(s16 *)((u8 *)entity_arg + (0xB8))) == 1) {
        target_height = ((S_8017112C_4 *)motion)->unk_14.at02.v;
        ASM_KEEP_NV(target_height);
        height = ((S_8017112C_4 *)motion)->unk_08.at02.v;
        ASM_KEEP_NV(height);
        height_bits = ((S_8017112C_4 *)motion)->unk_08.at02u.v;
        ASM_KEEP_NV(height_bits);
        if (target_height > height) {
            height_gap = target_height - height;
            height_gap = abs(height_gap);
            divisor_magic = 0x66660000;
            if (height_gap >= 0x65) {
                next_height = height_bits + 8;
                ((S_8017112C_4 *)motion)->unk_08.at02.v = next_height;
            } else {
                height_delta = ((S_8017112C_4 *)motion)->unk_14.at00.v;
                height_fixed = ((S_8017112C_4 *)motion)->unk_08.at00.v;
                divisor_magic |= 0x6667;
                height_delta -= height_fixed;
                height_delta = abs(height_delta);
                product.value = (long long)height_delta * divisor_magic;
                height_step = (product.word.high >> 2) - (height_delta >> 31);
                height_fixed += height_step;
                ((S_8017112C_4 *)motion)->unk_08.at00.v = height_fixed;
            }
        }
    }

    if ((*(s16 *)((u8 *)entity_arg + (0xB8))) == 2 && ((S_8017112C_4 *)motion)->unk_08.at02.v >= -0x3EF) {
        ((S_8017112C_4 *)motion)->unk_08.at02.v = ((S_8017112C_4 *)motion)->unk_08.at02u.v - 4;
    }

    if (((S_8017112C_0 *)actor)->unk_1C & 0x40000000) {
        ((S_8017112C_0 *)actor)->unk_1C &= 0xBFFFFFFF;
        floor_height = func_800BCB04((((S_8017112C_5 *)monster)->unk_24 << 6) | 0x20,
                              (((S_8017112C_5 *)monster)->unk_25 << 6) | 0x20,
                              (s16)(((S_8017112C_0 *)actor)->unk_88 - 0x20));
        if (floor_height < 0x200) {
            (*(u16 *)((u8 *)entity_arg + (0x92))) += ((S_8017112C_0 *)actor)->unk_88 - floor_height;
            ((S_8017112C_0 *)actor)->unk_88 = floor_height;
        }
    }

    ((S_8017112C_5 *)monster)->unk_14 |= 0x40;
    ASM_KEEP(motion);
}
