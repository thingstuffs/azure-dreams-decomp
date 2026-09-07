#include "common.h"

typedef void *(*SpawnFunc)(s32, s32, s32, s32);

typedef struct S_8001EF0C_0 {
    u8 pad_00[0x11];
    u8 unk_11;
    s8 unk_12;
    u8 pad_13[0x5];
    u32 unk_18;
    u8 pad_1C[0x27];
    union { u8 s; s8 u; } unk_43;   /* accessed as both */
} S_8001EF0C_0;   /* object in func_8001EF0C */

typedef struct S_8001EF0C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
} S_8001EF0C_1;   /* config in func_8001EF0C */


typedef struct {
    u8 type;
    u8 state;
    u8 unk2;
    u8 unk3;
} SpawnMeta;

typedef struct {
    u8 pad0[6];
    u8 x;
    u8 y;
    s32 value;
    s32 zero;
    s16 unk10;
    s16 unk12;
    u16 flags;
    u16 pad16;
} SpawnPosition;

typedef struct {
    u32 initial[1];
    s32 limits[1];
} SpawnTables;

extern s16 D_80081468[3];
extern s16 D_8008146C[];
extern SpawnTables D_800835E4[];
extern s32 D_800835E8[];
extern SpawnMeta D_800E3648[];
extern SpawnPosition D_800E39C8[];
extern s32 D_800E296C[];
extern s32 D_800E3D6C[];
extern u8 *D_800735C4[];
extern u8 D_800DF258[];

extern void func_8001F0AC(void) __attribute__((noreturn));
extern void func_8001F230(void) __attribute__((noreturn));
extern void func_8001F2E8(void) __attribute__((noreturn));
extern void func_8003DB94(void *, s32, s32);
extern void func_80042640(void *, s32);
extern void func_8009A21C(s32, s32, s32);
extern SpawnFunc func_800A0B94(s32, s32, s32);
extern void func_800A152C(s32, s32);
extern s32 func_800A1618(s32, s32);
extern void func_800A1D4C(void *, s32);
extern s32 func_800A4E2C(u8 *, u8 *);
extern s32 func_800A6D30(void);
extern u8 func_800A6DA4(s32, s32);
extern s16 func_800BCB04(s32, s32, s32);

__asm__(".set D_800835E8, 0x800835E8");

#ifdef NON_MATCHING
#define PAGE_8008 ((u8 *)D_800835E8 - 0x35E8)
#else
#define PAGE_8008 ((u8 *)0x80080000)
#endif

void func_8001EF0C(void) {
    u8 x;
    u8 y;
    u8 *config;
    SpawnPosition *position;
    SpawnMeta *meta;
    s32 *limits;
    u32 *initial;
    s32 i;
    s32 spawn_limit;
    s32 budget;
    s32 cost;
    s32 value;
    s32 availability;
    s32 saved_type;
    s16 height;
    u32 initial_value;
    register u32 flag_bits ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */
    u16 flags;
    u8 type;
    u8 existing_type;
    register u8 store_type ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    u8 spawn_variant;
    u8 spawn_marker;
    S_8001EF0C_0 *object;

    i = 0;
    initial = D_800835E4->initial;
    limits = (s32 *)(initial + 1);
    meta = D_800E3648;
    position = D_800E39C8;
    do {
        if (meta[i].state == 0x13) {
            existing_type = meta[i].type;
            availability = func_800A1618(existing_type, 1);
            if (availability != 0) {
                object = func_800A0B94(existing_type, availability, 1)
                             (0, position[i].x, position[i].y, -0x400);
                if (object != 0) {
                    func_800A152C(existing_type, 1);
                    func_80042640(object, existing_type);
                    object->unk_43.s = 0xFF;
                    object->unk_12 = 0;
                    initial_value = initial[(s8)meta[i].unk2];
                    object->unk_18 = initial_value;
                    if (initial_value >= (u32)limits[object->unk_11]) {
                        u8 *loop_page;
                        s32 *loop_limits;
                        loop_page = PAGE_8008;
                        ASM_KEEP_NV(loop_page);   /* MATCH pin: keeps a statement from moving across a call/branch */
                        loop_limits = (s32 *)(loop_page + 0x35E8);
                        do {
                            func_800A1D4C(object, 0);
                        } while ((u32)loop_limits[object->unk_11] <=
                                 object->unk_18);
                    }
                    object->unk_43.u = func_800A6D30();
                }
            }
            *(s32 *)&meta[i] = 0;
        }
        i++;
    } while (i < 0x20);

    {
        u8 *config_page;
        config_page = PAGE_8008;
        ASM_KEEP_NV(config_page);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        config = config_page + 0x1468;
    }
    if (((S_8001EF0C_1 *)config)->unk_06 == 1) {
        spawn_limit = (func_800A6D30() & 3) + 4;
        ASM_TAILSLOT_PIN(spawn_limit);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_8001F0AC();
        return;
    }

    spawn_limit = ((S_8001EF0C_1 *)config)->unk_06 / 2 + (func_800A6D30() & 3);
    if (spawn_limit >= 0x21) {
        spawn_limit = 0x20;
    }

    value = func_800A6D30();
    i = 0;
    saved_type = 0x15;
    position = D_800E39C8;
    budget = D_8008146C[0] / 2 + (value & 0x3F);
    meta = D_800E3648;

    do {
        if (meta[i].state == saved_type) {
            x = position[i].x;
            y = position[i].y;
            ASM_SCHED_BARRIER();   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            {
                register s32 tail_s0 ASM_REG("$16") = meta[i].type;   /* MATCH pin: retail register colouring depends on it */
                s32 tail_v0 = meta[i].unk2;
                register s32 tail_v1 ASM_REG("$3") = meta[i].unk3;   /* MATCH pin: load-bearing for the whole function shape */
                register s32 tail_a2 ASM_REG("$6") = -0x400;   /* MATCH pin: retail register colouring depends on it */
                ASM_KEEP4(tail_s0, tail_v0, tail_v1, tail_a2);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                ASM_TAILSLOT_PIN(tail_a2);   /* MATCH pin: load-bearing for the whole function shape */
                func_8001F230();
            }
            return;
        }

        if (!(D_800E3D6C[0] & 8) && i < spawn_limit) {
            meta[i].state = 0;
            meta[i].type = 0;
            budget += func_800A6D30() & 0xF;
            store_type = func_800A6DA4(1, 0x13);
            type = store_type;
            flags = *(u16 *)(D_800735C4[0] + (type * 0xC));
            flag_bits = flags & 0x3000;
            if (flag_bits != 0x3000) {
                register u32 shifted_flag_bits ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
                register u32 scaled_flag_bits ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                shifted_flag_bits = flag_bits << 16;
                ASM_KEEP_NV(shifted_flag_bits);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                scaled_flag_bits = shifted_flag_bits >> 26;
                cost = scaled_flag_bits + 4;
                if (budget >= cost) {
                    budget -= cost;
                    if ((D_800E296C[0] & 0x20000000) ||
                        ((u8)(type - 0xF) >= 2)) {
                        meta[i].state = saved_type;
                        meta[i].type = store_type;
                        do {
                        } while ((s16)func_800A4E2C(&x, &y) < 0);
                        position[i].x = x;
                        position[i].y = y;
                        spawn_variant = (func_800A6D30() & 7) | 4;
                        spawn_marker = 0x80;
                        ASM_KEEP_DEP_NV(spawn_variant, spawn_marker);   /* MATCH pin: keeps a statement from moving across a call/branch */
                        meta[i].unk2 = spawn_variant;
                        meta[i].unk3 = spawn_marker;
                        height = func_800BCB04((x << 6) | 0x20,
                                               (y << 6) | 0x20,
                                               -0x400);
                        position[i].unk12 = height;
                        position[i].unk10 = height;
                        position[i].flags = 0;
                        func_8009A21C(x, y, 0x20);
                        {
                            u32 lookup_index;
                            register u8 *lookup_base ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
                            lookup_index = type;
                            lookup_base = D_800DF258;
                            ASM_KEEP_DEP_NV(lookup_index, lookup_base);   /* MATCH pin: retail schedule: same instructions, different order without it */
                            value = *(s32 *)(lookup_base + (lookup_index << 2));
                        }
                        if (value < 0) {
                            func_8003DB94(&position[i], value, 0);
                            flags = position[i].flags;
                            position[i].flags = flags | 0x840;
                            if (value & 0x20000000) {
                                position[i].flags = flags | 0x940;
                                func_8001F2E8();
                                return;
                            }
                        } else {
                            if (value != 0) {
                                position[i].value = value | 0x80000000;
                            }
                            position[i].flags |= 0x800;
                        }
                        position[i].zero = 0;
                    }
                }
            }
        }
        i++;
    } while (i < 0x20);
}
