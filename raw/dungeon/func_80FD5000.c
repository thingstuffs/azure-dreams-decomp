/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
typedef float f32;
typedef double f64;
typedef long long s64;
typedef unsigned long long u64;
#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;
typedef s8  M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_LWL(expr) (expr)
#define M2C_FIRST3BYTES(expr) (expr)
#define M2C_UNALIGNED32(expr) (expr)
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
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#define M2C_MEMCPY_ALIGNED memcpy
#define M2C_MEMCPY_UNALIGNED memcpy
#define M2C_STRUCT_COPY memcpy

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800673A0();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
void *func_8014C984();
void func_8014C9FC(void) __attribute__((noreturn));
void *func_8014CA40();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern M2C_UNK D_8014CB40;
extern M2C_UNK D_8014CF6C;
extern M2C_UNK D_80151258;
extern M2C_UNK D_80151298;

typedef void (*Callback)(void);
typedef struct {
    Callback callbacks[27];
    u8 config[56];
} ActorDefinition;

extern void func_8014D12C(void);
extern void func_8014D198(void);
extern void func_8014D26C(void);
extern void func_8014D3FC(void);
extern void func_8014D444(void);
extern void func_8014D794(void);
extern void func_8014D7C0(void);
extern void func_8014D740(void);
extern void func_8014D6D8(void);
extern void func_8014D784(void);
extern void func_8014EF08(void);
extern void func_8014EF00(void);
extern void func_8014EEF8(void);
extern void func_8014EF10(void);
extern void func_8014EEB8(void);
extern void func_8014EEB0(void);
extern void func_8014EEA8(void);

#ifdef __mips__
extern void *func_8014C8A4(void *, s8, s8, s16);

static const ActorDefinition extent_prefix
    __asm__("func_8014C800")
    __attribute__((used, section(".text.func_8014C800"), aligned(4))) = {
    {
        (Callback)func_8014C8A4,
        (Callback)&D_8014CB40,
        func_8014D12C,
        func_8014D198,
        func_8014D26C,
        func_8014D3FC,
        func_8014D444,
        0,
        func_8014D794,
        func_8014D794,
        func_8014D794,
        func_8014D7C0,
        func_8014D740,
        func_8014D740,
        func_8014D740,
        func_8014D6D8,
        func_8014D6D8,
        func_8014D7C0,
        func_8014D7C0,
        func_8014D784,
        func_8014EF08,
        func_8014EF00,
        func_8014EEF8,
        func_8014EF10,
        func_8014EEB8,
        func_8014EEB0,
        func_8014EEA8,
    },
    {
        0x40, 0x03, 0x00, 0x01, 0x40, 0x00, 0x80, 0x00,
        0x81, 0x40, 0x82, 0x8C, 0x82, 0x85, 0x82, 0x84,
        0x81, 0x40, 0x82, 0x81, 0x81, 0x40, 0x82, 0x8D,
        0x82, 0x85, 0x82, 0x92, 0x82, 0x92, 0x82, 0x99,
        0x81, 0x40, 0x82, 0x84, 0x82, 0x81, 0x82, 0x8E,
        0x82, 0x83, 0x82, 0x85, 0x81, 0x44, 0x00, 0x00,
        0x40, 0x03, 0x00, 0x01, 0x40, 0x00, 0x40, 0x00,
    },
};
__asm__(".globl func_8014C800\n"
        ".size func_8014C800, 832");
#define BODY_NAME func_8014C8A4
#else
#define BODY_NAME func_8014C800
#endif

#if 0
void *BODY_NAME(void *arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 unksp28;
    s32 sp28;
    s16 sp10[4];
    s16 temp_v0_2;
    s32 temp_v1;
    u32 temp_v1_2;
    register void *pin_arg0 ASM_REG("$19");
    register s8 pin_arg1 ASM_REG("$21");
    register s8 pin_arg2 ASM_REG("$20");
    register s16 pin_arg3 ASM_REG("$18");
    register void *temp_s1 ASM_REG("$17");
    register void *temp_s2 ASM_REG("$18");
    register void *temp_s6 ASM_REG("$22");
    register void *var_s7 ASM_REG("$23");
    register void *var_s0 ASM_REG("$16");

    pin_arg0 = arg0;
    pin_arg1 = arg1;
    pin_arg2 = arg2;
    pin_arg3 = arg3;
    var_s0 = NULL;
    unksp28 = (s32) *(s8 *)-0x1158;
    temp_s1 = func_8003FD64(0x112, &D_80083498);
    if (temp_s1 != NULL) {
        var_s7 = pin_arg0;
        var_s0 = temp_s1 + 0x20;
        M2C_FIELD(temp_s1, M2C_UNK **, 0x10) = &D_8014CB40;
        M2C_FIELD(var_s0, s8 *, 0x13) = 0x27;
        func_8004491C(temp_s1, &D_80045340);
        temp_s6 = M2C_FIELD(temp_s1, void **, 8);
        M2C_FIELD(temp_s6, s16 *, 0xA) = pin_arg3;
        temp_s2 = M2C_FIELD(temp_s1, void **, 0xC);
        temp_v1 = (s32) pin_arg0 & 3;
        M2C_FIELD(temp_s2, s8 *, 0x25) = pin_arg2;
        M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_80151258;
        M2C_FIELD(temp_s2, s8 *, 0x24) = pin_arg1;
        if (temp_v1 == 1) {
            return func_8014C984();
        }
        if (temp_v1 >= 2) {
            M2C_FIELD(var_s0, s32 *, 0x14) = (s32) (M2C_FIELD(var_s0, s32 *, 0x14) | 0x2000);
            return func_8014C9FC();
        }
        if ((((s32) pin_arg0 & ~3) << 0x10) == 0) {
            if (!(M2C_FIELD(var_s0, s32 *, 0x14) & 0x200)) {
                if (func_800A6D30(temp_s1, temp_s6) & 1) {
                    M2C_FIELD(var_s0, s32 *, 0x1C) = (s32) (M2C_FIELD(var_s0, s32 *, 0x1C) | 0x200);
                    func_800A48F0(var_s0, 1, (func_800A6D30(temp_s1) & 0x3F) | 0x20);
                    M2C_FIELD(temp_s2, M2C_UNK **, 0x2C) = &D_80151298;
                }
            }
        }
        func_800A9C18(temp_s1, temp_s6, temp_s2, (s16) var_s7);
        M2C_FIELD(var_s0, s8 *, 0x9A) = 0xFF;
        M2C_FIELD(var_s0, s8 *, 0x9C) = -1;
        M2C_FIELD(var_s0, M2C_UNK **, 0x8C) = &D_8014CF6C;
        M2C_FIELD(var_s0, u16 *, 0xAE) = (u16) M2C_FIELD(temp_s2, u16 *, 0x12);
        if (*M2C_FIELD(temp_s2, u8 **, 8) & 0x20) {
            return func_8014CA40();
        }
        sp10[2] = 0x100;
        sp10[0] = 0;
        sp10[3] = 1;
        temp_v1_2 = (u16) M2C_FIELD(((0 * 2 * 4) + M2C_FIELD(temp_s2, u8 **, 8)), u16 *, 6) >> 6;
        sp10[1] = (s16) temp_v1_2;
        func_800673A0(sp10, 0, temp_v1_2 - 1);
        sp10[2] = 0x10;
        sp10[0] = 0x30;
        sp10[1] -= 1;
        do {
            func_800673A0(sp10, sp10[0] - 0x30, (s16) sp10[1]);
            temp_v0_2 = (u16) sp10[0] + 0x40;
            sp10[0] = temp_v0_2;
        } while (temp_v0_2 < 0x100);
        func_800AA36C(var_s0, temp_s6, temp_s2, var_s0);
        return var_s0;
    }
    return var_s0;
}
#endif

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

#define FIELD(p, type, offset) (*(type *)((u8 *)(p) + (offset)))

void *BODY_NAME(void *arg0, s8 arg1, s8 arg2, s16 arg3)
{
    register s8 arg1_role ASM_REG("$21");
    register s8 arg2_role ASM_REG("$20");
    register s16 arg3_role ASM_REG("$18");
    register void *created ASM_REG("$17");
    register u8 *work ASM_REG("$16") = 0;
    register u8 *position ASM_REG("$22");
    register u8 *monster ASM_REG("$18");
    register u8 *actor ASM_REG("$20");
    register s32 call_id ASM_REG("$4");
    register void *call_definition ASM_REG("$5");
    s32 kind;
    Rect rect;

    call_id = 0x112;
    arg1_role = arg1;
    ASM_KEEP_DEP_NV(arg1_role, call_id);
    call_definition = &D_80083498;
    ASM_KEEP_DEP_NV(call_definition, arg1_role);
    arg3_role = arg3;
    arg2_role = arg2;
    created = func_8003FD64(call_id, call_definition);
    if (created != 0) {
        register s32 arg0_copy ASM_REG("$23");
        register s32 flags0 ASM_REG("$2");
        register s32 flags1 ASM_REG("$3");
        register void *call_created ASM_REG("$4");
        register u8 *call_position ASM_REG("$5");
        s32 value;
        u8 *entry;
        register s32 i ASM_REG("$5");
        register s32 doubled ASM_REG("$6");
        register Rect *rectp ASM_REG("$4");
        register u8 *selected ASM_REG("$2");

        work = (u8 *)created + 0x20;
        arg0_copy = (s32)arg0;
        ASM_KEEP(arg0_copy);
        FIELD(created, Callback, 0x10) = (Callback)&D_8014CB40;
        FIELD(work, s8, 0x13) = 0x27;
        func_8004491C(created, &D_80045340);

        position = FIELD(created, u8 *, 8);
        FIELD(position, s16, 0xA) = arg3_role;
        monster = FIELD(created, u8 *, 0xC);
        FIELD(monster, u8, 0x25) = arg2_role;
        actor = work;
        FIELD(monster, Callback, 0x2C) = (Callback)&D_80151258;
        FIELD(monster, u8, 0x24) = arg1_role;

        kind = (s32)arg0 & 3;
        if (kind == 1) {
            flags0 = FIELD(work, s32, 0x14) | 0x6000;
            flags1 = FIELD(work, s32, 0x1C) | 0x6000;
            goto finish_kind;
        }
        if (kind >= 2) {
            flags0 = FIELD(work, s32, 0x14) | 0x2000;
            flags1 = FIELD(work, s32, 0x1C) | 0x2000;
finish_kind:
            ASM_KEEP(flags0);
            FIELD(work, s32, 0x14) = flags0;
            FIELD(work, s32, 0x1C) = flags1;
            func_8014C9FC();
        }
        call_created = created;
        if (((s32)arg0 & ~3) << 16 != 0)
            goto have_call_position;
        call_position = position;
        if (FIELD(work, s32, 0x14) & 0x200)
            goto have_call_args;
        ASM_KEEP(call_created);
        ASM_KEEP(call_position);
        value = func_800A6D30(call_created, call_position);
        call_created = created;
        if (!(value & 1))
            goto have_call_position;
        FIELD(work, s32, 0x1C) |= 0x200;
        value = func_800A6D30(created);
        func_800A48F0(work, 1, (value & 0x3F) | 0x20);
        FIELD(monster, Callback, 0x2C) = (Callback)&D_80151298;
        ASM_SCHED_BARRIER();

        call_created = created;
        ASM_KEEP(call_created);
have_call_position:
        call_position = position;
have_call_args:
        func_800A9C18(call_created, call_position, monster, (s16)arg0_copy);

        i = 0;
        ASM_KEEP(i);
        value = FIELD(monster, u16, 0x12);
        FIELD(actor, u8, 0x9A) = 0xFF;
        FIELD(actor, s8, 0x9C) = -1;
        FIELD(actor, Callback, 0x8C) = (Callback)&D_8014CF6C;
        FIELD(actor, s16, 0xAE) = value;

        entry = FIELD(monster, u8 *, 8);
scan_entry:
        doubled = i << 1;
        if (*entry & 0x20) {
            entry += 12;
            ASM_KEEP(entry);
            i++;
            goto scan_entry;
        } else {
            ASM_SCHED_BARRIER();
        }

        rectp = &rect;
        ASM_KEEP(rectp);
        selected = (u8 *)(doubled + i);
        ASM_KEEP(selected);
        selected = (u8 *)((s32)selected * 4);
        ASM_KEEP(selected);
        selected += (s32)FIELD(monster, u8 *, 8);
        value = FIELD(selected, u16, 6) >> 6;
        rect.x = 0;
        rect.y = value;
        rect.w = 0x100;
        rect.h = 1;
        func_800673A0(rectp, 0, value - 1);

        rect.w = 0x10;
        rect.x = 0x30;
        rect.y--;
        do {
            func_800673A0(&rect, rect.x - 0x30, rect.y);
            rect.x += 0x40;
        } while (rect.x < 0x100);

        func_800AA36C(actor, position, monster, work);
    }
    return work;
}
