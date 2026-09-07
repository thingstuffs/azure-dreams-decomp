#include "common.h"

typedef void *(*SpawnFunc)(s32, s32, s32, s32);

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

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))
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
    register u32 flag_bits ASM_REG("$3");
    u16 flags;
    u8 type;
    u8 existing_type;
    register u8 store_type ASM_REG("$5");
    register u8 spawn_variant ASM_REG("$2");
    register u8 spawn_marker ASM_REG("$3");
    void *object;

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
                    FIELD(object, u8, 0x43) = 0xFF;
                    FIELD(object, s8, 0x12) = 0;
                    initial_value = initial[(s8)meta[i].unk2];
                    FIELD(object, u32, 0x18) = initial_value;
                    if (initial_value >= (u32)limits[FIELD(object, u8, 0x11)]) {
                        register u8 *loop_page ASM_REG("$2");
                        register s32 *loop_limits ASM_REG("$17");
                        loop_page = PAGE_8008;
                        ASM_KEEP_NV(loop_page);
                        loop_limits = (s32 *)(loop_page + 0x35E8);
                        ASM_KEEP(loop_limits);
                        do {
                            func_800A1D4C(object, 0);
                        } while ((u32)loop_limits[FIELD(object, u8, 0x11)] <=
                                 FIELD(object, u32, 0x18));
                    }
                    FIELD(object, s8, 0x43) = func_800A6D30();
                }
            }
            *(s32 *)&meta[i] = 0;
        }
        i++;
    } while (i < 0x20);

    {
        register u8 *config_page ASM_REG("$2");
        config_page = PAGE_8008;
        ASM_KEEP_NV(config_page);
        config = config_page + 0x1468;
    }
    if (FIELD(config, s16, 6) == 1) {
        spawn_limit = (func_800A6D30() & 3) + 4;
        ASM_KEEP_NV(spawn_limit);
        ASM_TAILSLOT_PIN(spawn_limit);
        func_8001F0AC();
        return;
    }

    spawn_limit = FIELD(config, s16, 6) / 2 + (func_800A6D30() & 3);
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
            ASM_SCHED_BARRIER();
            {
                register s32 tail_s0 ASM_REG("$16") = meta[i].type;
                register s32 tail_v0 ASM_REG("$2") = meta[i].unk2;
                register s32 tail_v1 ASM_REG("$3") = meta[i].unk3;
                register s32 tail_a2 ASM_REG("$6") = -0x400;
                ASM_KEEP4(tail_s0, tail_v0, tail_v1, tail_a2);
                ASM_TAILSLOT_PIN(tail_a2);
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
            ASM_KEEP_NV(store_type);
            flags = *(u16 *)(D_800735C4[0] + (type * 0xC));
            flag_bits = flags & 0x3000;
            if (flag_bits != 0x3000) {
                register u32 shifted_flag_bits ASM_REG("$4");
                register u32 scaled_flag_bits ASM_REG("$2");
                shifted_flag_bits = flag_bits << 16;
                ASM_KEEP_NV(shifted_flag_bits);
                scaled_flag_bits = shifted_flag_bits >> 26;
                ASM_KEEP_NV(scaled_flag_bits);
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
                        ASM_KEEP_DEP_NV(spawn_variant, spawn_marker);
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
                            register u32 lookup_index ASM_REG("$3");
                            register u8 *lookup_base ASM_REG("$2");
                            lookup_index = type;
                            lookup_base = D_800DF258;
                            ASM_KEEP_DEP_NV(lookup_index, lookup_base);
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
