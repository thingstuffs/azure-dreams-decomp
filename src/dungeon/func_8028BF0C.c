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

/* Restore saved spawns and place random traps within the floor budget. */
void func_8001EF0C(void) {
    u8 x;
    u8 y;
    u8 *floor_config;
    SpawnPosition *position;
    SpawnMeta *meta;
    s32 *limits;
    u32 *initial;
    s32 slot;
    s32 spawn_limit;
    s32 trap_budget;
    s32 trap_cost;
    s32 value;
    s32 availability;
    s32 trap_state;
    s16 floor_height;
    u32 initial_value;
    register u32 flag_bits ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 flags;
    u8 trap_type;
    u8 existing_type;
    register u8 store_type ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    u8 spawn_variant;
    u8 spawn_marker;
    s32 spawn_height;
    S_8001EF0C_0 *object;

    slot = 0;
    initial = D_800835E4->initial;
    limits = (s32 *)(initial + 1);
    meta = D_800E3648;
    position = D_800E39C8;
    do {
        if (meta[slot].state == 0x13) {
            existing_type = meta[slot].type;
            availability = func_800A1618(existing_type, 1);
            if (availability != 0) {
                object = func_800A0B94(existing_type, availability, 1)
                             (0, position[slot].x, position[slot].y, -0x400);
                if (object != 0) {
                    func_800A152C(existing_type, 1);
                    func_80042640(object, existing_type);
                    object->unk_43.s = 0xFF;
                    object->unk_12 = 0;
                    initial_value = initial[(s8)meta[slot].unk2];
                    object->unk_18 = initial_value;
                    if (initial_value >= (u32)limits[object->unk_11]) {
                        u8 *loop_page;
                        s32 *loop_limits;
                        loop_page = PAGE_8008;
                        ASM_KEEP_NV(loop_page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                        loop_limits = (s32 *)(loop_page + 0x35E8);
                        do {
                            func_800A1D4C(object, 0);
                        } while ((u32)loop_limits[object->unk_11] <=
                                 object->unk_18);
                    }
                    object->unk_43.u = func_800A6D30();
                }
            }
            *(s32 *)&meta[slot] = 0;
        }
        slot++;
    } while (slot < 0x20);

    {
        u8 *config_page;
        config_page = PAGE_8008;
        ASM_KEEP_NV(config_page);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        floor_config = config_page + 0x1468;
    }
    if (((S_8001EF0C_1 *)floor_config)->unk_06 == 1) {
        spawn_limit = (func_800A6D30() & 3) + 4;
    } else {
        spawn_limit = ((S_8001EF0C_1 *)floor_config)->unk_06 / 2 + (func_800A6D30() & 3);
    }
    if (spawn_limit >= 0x21) {
        spawn_limit = 0x20;
    }

    value = func_800A6D30();
    slot = 0;
    trap_state = 0x15;
    position = D_800E39C8;
    trap_budget = D_8008146C[0] / 2 + (value & 0x3F);
    meta = D_800E3648;

    do {
        if (meta[slot].state == trap_state) {
            x = position[slot].x;
            y = position[slot].y;
               /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
            {
                s32 saved_trap_type = meta[slot].type;
                s32 saved_variant = meta[slot].unk2;
                s32 saved_marker = meta[slot].unk3;
                trap_type = saved_trap_type;
                spawn_variant = saved_variant;
                spawn_marker = saved_marker;
                spawn_height = -0x400;
                goto restore_spawn;
            }
        }

        if (!(D_800E3D6C[0] & 8) && slot < spawn_limit) {
            meta[slot].state = 0;
            meta[slot].type = 0;
            trap_budget += func_800A6D30() & 0xF;
            store_type = func_800A6DA4(1, 0x13);
            trap_type = store_type;
            flags = *(u16 *)(D_800735C4[0] + (trap_type * 0xC));
            flag_bits = flags & 0x3000;
            if (flag_bits != 0x3000) {
                register u32 shifted_flag_bits ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                register u32 scaled_flag_bits ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                shifted_flag_bits = flag_bits << 16;
                ASM_KEEP_NV(shifted_flag_bits);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
                scaled_flag_bits = shifted_flag_bits >> 26;
                trap_cost = scaled_flag_bits + 4;
                if (trap_budget >= trap_cost) {
                    trap_budget -= trap_cost;
                    if ((D_800E296C[0] & 0x20000000) ||
                        ((u8)(trap_type - 0xF) >= 2)) {
                        meta[slot].state = trap_state;
                        meta[slot].type = store_type;
                        do {
                        } while ((s16)func_800A4E2C(&x, &y) < 0);
                        position[slot].x = x;
                        position[slot].y = y;
                        spawn_variant = (func_800A6D30() & 7) | 4;
                        spawn_marker = 0x80;
                           /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
                        spawn_height = -0x400;
                    restore_spawn:
                        meta[slot].unk2 = spawn_variant;
                        meta[slot].unk3 = spawn_marker;
                        floor_height = func_800BCB04((x << 6) | 0x20,
                                               (y << 6) | 0x20,
                                               spawn_height);
                        position[slot].unk12 = floor_height;
                        position[slot].unk10 = floor_height;
                        position[slot].flags = 0;
                        func_8009A21C(x, y, 0x20);
                        {
                            u32 lookup_index;
                            register u8 *lookup_base ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                            lookup_index = trap_type;
                            lookup_base = D_800DF258;
                            ASM_KEEP_DEP_NV(lookup_index, lookup_base);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
                            value = *(s32 *)(lookup_base + (lookup_index << 2));
                        }
                        if (value < 0) {
                            func_8003DB94(&position[slot], value, 0);
                            flags = position[slot].flags;
                            position[slot].flags = flags | 0x840;
                            if (value & 0x20000000) {
                                position[slot].flags = flags | 0x940;
                            }
                        } else {
                            if (value != 0) {
                                position[slot].value = value | 0x80000000;
                            }
                            position[slot].flags |= 0x800;
                        }
                        position[slot].zero = 0;
                    }
                }
            }
        }
        slot++;
    } while (slot < 0x20);
}
