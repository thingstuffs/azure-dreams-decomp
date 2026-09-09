#include "common.h"

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

void func_8017112C(void *arg0, void *arg1, void *arg2)
{
    void *entity = arg0;
    void *motion = arg1;
    void *monster = arg2;
    void *actor = entity;
    register s16 state_direction ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register u8 raw_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register void *call_entity ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *call_motion ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register void *call_monster ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register s32 normalized_state ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 current_state;
    register s32 direction_calc ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    register s32 next_current ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    Callback callback;
    Callback active_callback;
    s16 floor;
    s32 target;
    register s32 current_raw ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    s32 current;
    s32 distance;
    u16 global_flags;
    u16 *flag_word;
    register s32 delta ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 position;
    s32 division_magic;
    s32 quotient;
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

    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    flag_word = &D_80013714;
    global_flags = *flag_word;
    if (global_flags & 8) {
        s32 i = 1;
        slot = D_800E3D7C[0] + 4;
        do {
            node = ((S_8017112C_1 *)slot)->unk_AC;
            if (node != 0) {
                record = ((S_8017112C_2_pre *)node)[-1].unk_00;
                ((S_8017112C_3 *)record)->unk_14 &= 0xFFBF;
            }
            i--;
            slot -= 4;
        } while (i >= 0);
    }

    if (D_80083462 & 0x2000) {
        callback = (*(Callback *)((u8 *)entity + (0x8C)));
        if (callback == (Callback)&D_80171514) {
            callback(entity, motion, monster, actor);
            return;
        }
        ((S_8017112C_0 *)actor)->unk_71 &= 0x7F;
        return;
    }

    call_entity = entity;
    call_motion = motion;
    call_monster = monster;
    raw_state = ((S_8017112C_0 *)actor)->unk_6D.v;
    state_direction = ((s32)raw_state << 24) >> 24;
    if (func_800A9E70(call_entity, call_motion, call_monster, actor) != 0) {
        return;
    }

    active_callback = (*(Callback *)((u8 *)entity + (0x8C)));
    if (active_callback != 0) {
        active_callback(entity, motion, monster, actor);
    }
    D_80173EF4[(*(u8 *)((u8 *)entity + (0x9A)))](entity, motion, monster, actor);

    normalized_state = (s32)state_direction << 16;
    current_state = ((S_8017112C_0 *)actor)->unk_6D.n2;
    normalized_state >>= 16;
    if (normalized_state != current_state) {
        func_800AA36C(entity, motion, monster, actor);
    }

    ((S_8017112C_4 *)motion)->unk_00 += ((S_8017112C_4 *)motion)->unk_0C;
    (*(s32 *)((u8 *)motion + (4))) += ((S_8017112C_4 *)motion)->unk_10;

    direction_calc = D_80083228 + ((S_8017112C_0 *)actor)->unk_2A + 0x100;
    state_direction = (direction_calc >> 9) & 7;
    if ((*(s16 *)((u8 *)entity + (0x94))) != state_direction) {
        func_80047738(monster,
                     *((u8 *)((S_8017112C_5 *)monster)->unk_2C + state_direction),
                     ((S_8017112C_5 *)monster)->unk_04);
        (*(s16 *)((u8 *)entity + (0x94))) = state_direction;
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

    if ((*(s16 *)((u8 *)entity + (0xB8))) == 1) {
        target = ((S_8017112C_4 *)motion)->unk_14.at02.v;
        ASM_KEEP_NV(target);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        current = ((S_8017112C_4 *)motion)->unk_08.at02.v;
        ASM_KEEP_NV(current);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        current_raw = ((S_8017112C_4 *)motion)->unk_08.at02u.v;
        ASM_KEEP_NV(current_raw);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (target > current) {
            distance = target - current;
            if (distance < 0) {
                distance = -distance;
            }
            division_magic = 0x66660000;
            if (distance >= 0x65) {
                next_current = current_raw + 8;
                ((S_8017112C_4 *)motion)->unk_08.at02.v = next_current;
            } else {
                ASM_KEEP_NV(division_magic);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                delta = ((S_8017112C_4 *)motion)->unk_14.at00.v;
                position = ((S_8017112C_4 *)motion)->unk_08.at00.v;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                division_magic |= 0x6667;
                ASM_KEEP_NV(division_magic);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                delta -= position;
                if (delta < 0) {
                    delta = -delta;
                }
                ASM_KEEP_NV(delta);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                product.value = (long long)delta * division_magic;
                quotient = (product.word.high >> 2) - (delta >> 31);
                position += quotient;
                ((S_8017112C_4 *)motion)->unk_08.at00.v = position;
            }
        }
    }

    if ((*(s16 *)((u8 *)entity + (0xB8))) == 2 && ((S_8017112C_4 *)motion)->unk_08.at02.v >= -0x3EF) {
        ((S_8017112C_4 *)motion)->unk_08.at02.v = ((S_8017112C_4 *)motion)->unk_08.at02u.v - 4;
    }

    if (((S_8017112C_0 *)actor)->unk_1C & 0x40000000) {
        ((S_8017112C_0 *)actor)->unk_1C &= 0xBFFFFFFF;
        floor = func_800BCB04((((S_8017112C_5 *)monster)->unk_24 << 6) | 0x20,
                              (((S_8017112C_5 *)monster)->unk_25 << 6) | 0x20,
                              (s16)(((S_8017112C_0 *)actor)->unk_88 - 0x20));
        if (floor < 0x200) {
            (*(u16 *)((u8 *)entity + (0x92))) += ((S_8017112C_0 *)actor)->unk_88 - floor;
            ((S_8017112C_0 *)actor)->unk_88 = floor;
        }
    }

    ((S_8017112C_5 *)monster)->unk_14 |= 0x40;
    ASM_KEEP(entity);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(motion);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(actor);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
}
