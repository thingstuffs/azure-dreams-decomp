#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif
/*
 * This header contains macros emitted by m2c in "valid syntax" mode,
 * which can be enabled by passing `--valid-syntax` on the command line.
 *
 * In this mode, unhandled types and expressions are emitted as macros so
 * that the output is compilable without human intervention.
 */


/* Unknown types */
typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

typedef struct {
    u8 bytes[0x20];
} LocalPoints;

typedef struct {
    s16 x;
    u16 y;
} LocalPoint;

typedef struct {
    u16 x;
    u16 y;
    u16 z;
} Offset;

/* Unknown field access, like `*(type_ptr) &expr->unk_offset` */
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

/* Bitwise (reinterpret) cast */
#define M2C_BITWISE(type, expr) ((type)(expr))

/* Unaligned reads */
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)

/* Unhandled instructions */
#define M2C_ERROR(desc) (0)
#define M2C_TRAP_IF(cond) (0)
#define M2C_BREAK() (0)
#define M2C_SYNC() (0)

#define GLUE_F64(a, b) (0.0)
#define MULT_HI(a, b) (0)
#define MULTU_HI(a, b) (0)
#define DMULT_HI(a, b) (0)
#define DMULTU_HI(a, b) (0)
#define CLZ(x) (0)
#define REVERSE_BITS(x) (0)
#define ROTATE_RIGHT(x, shift) (0)
#define ARM_RRX(x, carry) (0)
#define BSWAP32(x) (0)
#define BSWAP16(x) (0)
#define BSWAP16X2(x) (0)

/* Carry/overflow bits from partially-implemented instructions */
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)

/* Memcpy patterns */
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

/* cfail-repair: tf7-phase1-cache-v3 */
extern LocalPoints D_80024004;
extern u8 D_800DEC00[];
extern s16 D_80025338[5];
extern s32 D_8008346C[];
extern s32 D_800814A0[3];
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
void func_80024F14() __attribute__((noreturn));     /* extern */
void func_8002512C(void) __attribute__((noreturn));     /* extern */
void func_8002515C(void) __attribute__((noreturn));     /* extern */
void func_80025228(void) __attribute__((noreturn));     /* extern */
void func_800252A8(void) __attribute__((noreturn));     /* extern */
void func_8002530C() __attribute__((noreturn));     /* extern */
s32 func_8003DF74(s32, void *, Offset *, s32);     /* extern */
u8 *func_8003FC64();   /* extern */
M2C_UNK func_800A56E0();                     /* extern */
extern M2C_UNK D_800246DC;

void func_818154FC(void *arg0, void *arg1, void *arg2) {
    Offset offset;
    LocalPoints points;
    LocalPoint *point_base;
    M2C_UNK *var_v0_2;
    s16 temp_a0_4;
    s32 temp_v1;
    s32 var_v0;
    register s32 mode3_value ASM_REG("$2");
    s8 temp_v0_4;
    u16 temp_a0;
    u16 temp_a0_3;
    u16 temp_v0;
    u16 temp_v0_2;
    u16 temp_v1_4;
    u16 angle;
    u8 *temp_a2;
    u8 *temp_a2_2;
    u8 *temp_v0_3;
    u8 *var_a2;
    u8 temp_v1_2;
    void *temp_a0_2;
    void *temp_a0_5;
    void *temp_a0_6;
    void *temp_a1;
    void *temp_s1;
    void *temp_s2;
    void *temp_s4;
    void *temp_v1_3;
    void *var_a0;
    void *var_a1;

    temp_s1 = M2C_FIELD(arg0, void **, 0);
    var_a2 = (u8 *)&D_80024004;
    points = *(LocalPoints *)var_a2;
    point_base = (LocalPoint *)&points;
    temp_v1 = M2C_FIELD(arg0, s16 *, 0xA);
    temp_s2 = temp_s1 - 0x20;
    temp_s4 = M2C_FIELD(temp_s2, void **, 8);
    M2C_FIELD(arg0, u16 *, 0x82) = (u16) (M2C_FIELD(arg0, u16 *, 0x82) + 1);
    if (temp_v1 == 1) {
        goto block_10;
    }
    if (temp_v1 < 2) {
        if (temp_v1 == 0)
            goto block_state0;
        func_8002530C();
        return;
    }
    ASM_SCHED_BARRIER();
    if (temp_v1 == 2)
        goto block_state2;
    if (temp_v1 == 3) {
        mode3_value = 0x63;
        goto block_state3;
    }
    func_8002530C();
    return;

block_state0:
    M2C_FIELD(arg2, s32 *, 0xC) = 0x00808080;
    M2C_FIELD(arg2, s16 *, 0x1E) = 0x1000;
    M2C_FIELD(arg2, s16 *, 0x1C) = 0x1000;
    func_8003DB94(arg2, D_800DEC00, 0, arg2);
    angle = M2C_FIELD(temp_s1, u16 *, 0x2A);
    D_80025338[0] = 1;
    M2C_FIELD(arg0, s16 *, 0x7E) = (s16) ((angle >> 9) & 7);
    M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);

block_10:
  {
    register u16 position_z ASM_REG("$3");
    register u16 final_z ASM_REG("$2");
    register u16 delta_z ASM_REG("$3");

    temp_a1 = M2C_FIELD(temp_s2, void **, 0xC);
    if ((func_8003DF74(M2C_FIELD(temp_a1, s32 *, 8), temp_a1, &offset, 0) != 0) || (M2C_FIELD(M2C_FIELD(temp_s2, void **, 0xC), u16 *, 0x14) & 0x8000)) {
        M2C_FIELD(arg1, u16 *, 2) = (u16) M2C_FIELD(temp_s4, u16 *, 2);
        M2C_FIELD(arg1, u16 *, 6) = (u16) M2C_FIELD(temp_s4, u16 *, 6);
        position_z = M2C_FIELD(temp_s4, u16 *, 0xA);
        M2C_FIELD(arg1, u16 *, 0xA) = position_z;
        if (!(M2C_FIELD(M2C_FIELD(temp_s2, void **, 0xC), u16 *, 0x14) & 0x8000)) {
            M2C_FIELD(arg1, u16 *, 2) = (u16) (M2C_FIELD(arg1, u16 *, 2) + offset.x);
            M2C_FIELD(arg1, u16 *, 6) = (u16) (M2C_FIELD(arg1, u16 *, 6) + offset.y);
            ASM_SCHED_BARRIER();
            final_z = M2C_FIELD(arg1, u16 *, 0xA);
            delta_z = offset.z;
            final_z += delta_z;
            ASM_TAILSLOT_PIN(final_z);
            func_80024F14();
            return;
        }
        ASM_SCHED_BARRIER();
        final_z = position_z - 0x40;
        M2C_FIELD(arg1, u16 *, 0xA) = final_z;
        {
            register s32 copy_value ASM_REG("$2");

            copy_value = M2C_FIELD(arg1, s32 *, 0);
            M2C_FIELD(arg0, s32 *, 0xB0) = copy_value;
            copy_value = M2C_FIELD(arg1, s32 *, 4);
            M2C_FIELD(arg0, s32 *, 0xB4) = copy_value;
            copy_value = M2C_FIELD(arg1, s32 *, 8);
            M2C_FIELD(arg0, s32 *, 0xB8) = copy_value;
        }
        if (*M2C_FIELD(arg0, u16 **, 4) & 0x80) {
            M2C_FIELD(arg0, u16 *, 0x84) = 0U;
            M2C_FIELD(arg0, s16 *, 0xA) = (s16) ((u16) M2C_FIELD(arg0, s16 *, 0xA) + 1);
            func_800A56E0(0x300);
            func_8002530C();
        }
    }
    goto block_end;
  }

block_state2:
    temp_v0_2 = M2C_FIELD(arg0, u16 *, 0x84) + 1;
    M2C_FIELD(arg0, u16 *, 0x84) = temp_v0_2;
    if (temp_v0_2 & 1) {
        register u8 *node ASM_REG("$6");

        node = func_8003FC64(0x12);
        ASM_KEEP(node);
        if (node != NULL) {
            register u8 *work ASM_REG("$5");
            register u8 *map ASM_REG("$4");
            s32 index;

            work = node + 0x20;
            ASM_KEEP(work);
            {
                register s16 *entry ASM_REG("$2");

                index = M2C_FIELD(arg0, s16 *, 0x7E);
                entry = (s16 *)((u8 *)point_base + index * 4);
                M2C_FIELD(work, s32 *, 0x58) = (s32)entry[0] << 16;
            }
            {
                register u16 *entry ASM_REG("$2");

                index = M2C_FIELD(arg0, s16 *, 0x7E);
                entry = (u16 *)((u8 *)point_base + index * 4);
                M2C_FIELD(work, s32 *, 0x5C) = (s32)entry[1] << 16;
            }
            M2C_FIELD(work, void **, 0x2C) = temp_s1;
            M2C_FIELD(work, s32 *, 0x30) = M2C_FIELD(temp_s1, s32 *, 0x60);
            M2C_FIELD(work, s16 *, 0xA) =
                (M2C_FIELD(arg0, s16 *, 0x84) - 1) / 2;
            M2C_FIELD(work, u8 *, 0x15) = M2C_FIELD(arg0, u8 *, 9);
            M2C_FIELD(work, u16 *, 0x16) = M2C_FIELD(arg0, u16 *, 0x7E);

            {
                u8 *table_base = (u8 *)D_8006CCD8;

                index = M2C_FIELD(arg0, s16 *, 0x7E) * 2;
                map = M2C_FIELD(temp_s1, u8 **, -0x14);
                ASM_KEEP(map);
                M2C_FIELD(arg0, u8 *, 0xA8) =
                    M2C_FIELD(map, u8 *, 0x24) + table_base[index];
            }
            {
                u8 *table_base = (u8 *)D_8006CCE8;

                index = M2C_FIELD(arg0, s16 *, 0x7E) * 2;
                M2C_FIELD(arg0, u8 *, 0xA9) =
                    M2C_FIELD(map, u8 *, 0x25) + table_base[index];
            }

            if (M2C_FIELD(temp_s1, void **, 0x60) != NULL) {
                register s32 difference ASM_REG("$2");
                register s32 compare_one ASM_REG("$2");
                register u8 *motion ASM_REG("$3");
                register s32 result ASM_REG("$2");
                register s32 other_z ASM_REG("$3");

                M2C_FIELD(work, s16 *, 8) = 1;
                if (M2C_FIELD(temp_s1, s8 *, 0x72) !=
                    M2C_FIELD(map, u8 *, 0x24)) {
                    difference = M2C_FIELD(temp_s1, s8 *, 0x72) -
                                 M2C_FIELD(map, u8 *, 0x24);
                } else {
                    difference = M2C_FIELD(temp_s1, s8 *, 0x73);
                    difference -= M2C_FIELD(map, u8 *, 0x25);
                }
                if (difference < 0)
                    difference = -difference;
                M2C_FIELD(work, s16 *, 2) = difference * 2;
                ASM_MEM_BARRIER();

                compare_one = 1;
                ASM_KEEP(compare_one);
                motion = M2C_FIELD(M2C_FIELD(temp_s1, u8 **, 0x60), u8 **, -0x18);
                if (M2C_FIELD(arg0, s16 *, 0x84) == compare_one) {
                    register s32 duration ASM_REG("$4");

                    duration = M2C_FIELD(work, s16 *, 2);
                    if (duration != 0) {
                        result = M2C_FIELD(motion, s32 *, 8);
                        other_z = M2C_FIELD(arg1, s32 *, 8);
                        result -= other_z;
                        result -= 0x200000;
                        other_z = duration - 1;
                        result /= other_z;
                        M2C_FIELD(work, s32 *, 0x60) = result;
                        M2C_FIELD(arg1, s32 *, 0x14) = result;
                        func_8002512C();
                    }
                    goto block_32;
                }
                result = M2C_FIELD(arg1, s32 *, 0x14);
                M2C_FIELD(work, s32 *, 0x60) = result;
                func_8002512C();
            } else {
                M2C_FIELD(work, s16 *, 2) = 8;
                M2C_FIELD(work, s16 *, 8) = 0;
            }
block_32:
            if (M2C_FIELD(arg0, s16 *, 0x84) == 9) {
                if (M2C_FIELD(temp_s1, void **, 0x60) != NULL) {
                    register u16 end_time ASM_REG("$2");

                    end_time = M2C_FIELD(work, u16 *, 2);
                    end_time += 0x28;
                    ASM_TAILSLOT_PIN(end_time);
                    func_8002515C();
                }
                ASM_SCHED_BARRIER();
                M2C_FIELD(arg0, s16 *, 0x86) = 0x1E;
            }
            temp_a0_5 = M2C_FIELD(node, void **, 8);
            M2C_FIELD(node, M2C_UNK **, 0x10) = &D_800246DC;
            M2C_FIELD(temp_a0_5, s32 *, 0) = M2C_FIELD(arg0, s32 *, 0xB0);
            M2C_FIELD(temp_a0_5, s32 *, 4) = M2C_FIELD(arg0, s32 *, 0xB4);
            M2C_FIELD(temp_a0_5, s32 *, 8) = M2C_FIELD(arg0, s32 *, 0xB8);
            temp_v1_3 = M2C_FIELD(node, void **, 0xC);
            M2C_FIELD(temp_v1_3, u8 *, 0xE) = 0x80;
            M2C_FIELD(temp_v1_3, u8 *, 0xD) = 0x80;
            M2C_FIELD(temp_v1_3, u8 *, 0xC) = 0x80;
            M2C_FIELD(temp_v1_3, s16 *, 0x1E) = 0x1000;
            M2C_FIELD(temp_v1_3, s16 *, 0x1C) = 0x1000;
            if ((s16) M2C_FIELD(arg0, u16 *, 0x84) == 1) {
                M2C_FIELD(arg0, u8 **, 0x90) = node;
                M2C_FIELD(arg0, void **, 0x94) = temp_a0_5;
                M2C_FIELD(arg0, s16 *, 0x88) = 0x63;
            }
            goto block_39;
        }
    }
block_39:
    if (M2C_FIELD(arg0, s16 *, 0x88) == 0x63) {
        register u8 *node ASM_REG("$6");
        register u8 *saved ASM_REG("$4");

        node = M2C_FIELD(arg0, u8 **, 0x90);
        saved = M2C_FIELD(arg0, u8 **, 0x94);
        if (M2C_FIELD(node, u16 *, 0x1E) & 0x8000) {
            M2C_FIELD(arg0, s16 *, 0x88) = 0;
            func_80025228();
        }
        M2C_FIELD(arg1, s32 *, 0) = M2C_FIELD(saved, s32 *, 0);
        M2C_FIELD(arg1, s32 *, 4) = M2C_FIELD(saved, s32 *, 4);
        M2C_FIELD(arg1, s32 *, 8) = M2C_FIELD(saved, s32 *, 8);
        goto block_44;
    }
block_44:
    if ((s16) M2C_FIELD(arg0, u16 *, 0x84) >= 0xB) {
        register u16 old_state ASM_REG("$2");

        old_state = M2C_FIELD(arg0, u16 *, 0xA);
        M2C_FIELD(arg0, u16 *, 0x84) = 0;
        old_state++;
        M2C_FIELD(arg0, u16 *, 0xA) = old_state;
        func_8002530C();
    }
    goto block_end;

block_state3:
    if (M2C_FIELD(arg0, s16 *, 0x88) == mode3_value) {
        register u8 *node ASM_REG("$6");
        register u8 *saved ASM_REG("$4");

        node = M2C_FIELD(arg0, u8 **, 0x90);
        saved = M2C_FIELD(arg0, u8 **, 0x94);
        if (M2C_FIELD(node, u16 *, 0x1E) & 0x8000) {
            M2C_FIELD(arg0, s16 *, 0x88) = 0;
            func_800252A8();
        }
        M2C_FIELD(arg1, s32 *, 0) = M2C_FIELD(saved, s32 *, 0);
        M2C_FIELD(arg1, s32 *, 4) = M2C_FIELD(saved, s32 *, 4);
        M2C_FIELD(arg1, s32 *, 8) = M2C_FIELD(saved, s32 *, 8);
        goto block_52;
    }
block_52:
  {
    u16 old_counter = M2C_FIELD(arg0, u16 *, 0x84);
    s16 new_counter = old_counter + 1;

    M2C_FIELD(arg0, u16 *, 0x84) = new_counter;
    if (M2C_FIELD(arg0, s16 *, 0x86) < new_counter) {
        s32 global_state = D_80025338[0];

        M2C_FIELD(arg0, u16 *, 0x84) = old_counter;
        if (global_state == 0) {
            D_8008346C[0] = 0;
            M2C_FIELD(arg0, u16 *, -2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
            func_8002530C();
        } else {
            D_80025338[0] = 0;
        }
    }
  }

block_end:
    return;
}
