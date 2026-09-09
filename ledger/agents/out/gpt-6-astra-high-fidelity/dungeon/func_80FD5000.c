/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80FD5000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80FD5000_0;   /* temp_s1 in BODY_NAME */

typedef struct S_80FD5000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    u16 unk_AE;
} S_80FD5000_1;   /* var_s0 in BODY_NAME */

typedef struct S_80FD5000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FD5000_2;   /* temp_s6 in BODY_NAME */

typedef struct S_80FD5000_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u8 pad_14[0x10];
    s8 unk_24;
    s8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80FD5000_3;   /* temp_s2 in BODY_NAME */


void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800673A0();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
void *func_8014C984();
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
    void *pin_arg0;
    s8 pin_arg1;
    s8 pin_arg2;
    s16 pin_arg3;
    void *temp_s1;
    S_80FD5000_3 *temp_s2;
    S_80FD5000_2 *temp_s6;
    void *var_s7;
    S_80FD5000_1 *var_s0;

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
        ((S_80FD5000_0 *)temp_s1)->unk_10 = &D_8014CB40;
        var_s0->unk_13 = 0x27;
        func_8004491C(temp_s1, &D_80045340);
        temp_s6 = ((S_80FD5000_0 *)temp_s1)->unk_08;
        temp_s6->unk_0A = pin_arg3;
        temp_s2 = ((S_80FD5000_0 *)temp_s1)->unk_0C;
        temp_v1 = (s32) pin_arg0 & 3;
        temp_s2->unk_25 = pin_arg2;
        temp_s2->unk_2C = &D_80151258;
        temp_s2->unk_24 = pin_arg1;
        if (temp_v1 == 1) {
            return func_8014C984();
        }
        if (temp_v1 >= 2) {
            var_s0->unk_14 = (s32) (var_s0->unk_14 | 0x2000);
            goto finish_kind;
        }
        if ((((s32) pin_arg0 & ~3) << 0x10) == 0) {
            if (!(var_s0->unk_14 & 0x200)) {
                if (func_800A6D30(temp_s1, temp_s6) & 1) {
                    var_s0->unk_1C = (s32) (var_s0->unk_1C | 0x200);
                    func_800A48F0(var_s0, 1, (func_800A6D30(temp_s1) & 0x3F) | 0x20);
                    temp_s2->unk_2C = &D_80151298;
                }
            }
        }
finish_kind:
        func_800A9C18(temp_s1, temp_s6, temp_s2, (s16) var_s7);
        var_s0->unk_9A = 0xFF;
        var_s0->unk_9C = -1;
        var_s0->unk_8C = &D_8014CF6C;
        var_s0->unk_AE = (u16) temp_s2->unk_12;
        if (*temp_s2->unk_08 & 0x20) {
            return func_8014CA40();
        }
        sp10[2] = 0x100;
        sp10[0] = 0;
        sp10[3] = 1;
        temp_v1_2 = (u16) M2C_FIELD(((0 * 2 * 4) + temp_s2->unk_08), u16 *, 6) >> 6;
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
    s8 arg1_role;
    register s8 arg2_role ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 arg3_role ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    void *created;
    register u8 *work ASM_REG("$16") = 0;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *position;
    register u8 *monster ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    register u8 *actor ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 call_id ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register void *call_definition ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    s32 kind;
    Rect rect;

    call_id = 0x112;
    arg1_role = arg1;
    ASM_KEEP_DEP_NV(arg1_role, call_id);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    call_definition = &D_80083498;
    ASM_KEEP_DEP_NV(call_definition, arg1_role);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    arg3_role = arg3;
    arg2_role = arg2;
    created = func_8003FD64(call_id, call_definition);
    if (created != 0) {
        register s32 arg0_copy ASM_REG("$23");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        s32 flags0;
        s32 flags1;
        register void *call_created ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        register u8 *call_position ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        s32 value;
        u8 *entry;
        s32 i;
        s32 doubled;
        Rect *rectp;
        u8 *selected;

        work = (u8 *)created + 0x20;
        arg0_copy = (s32)arg0;
        ASM_KEEP(arg0_copy);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
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
            FIELD(work, s32, 0x14) = flags0;
            FIELD(work, s32, 0x1C) = flags1;
            goto finish_kind_args;
        }
        call_created = created;
        if (((s32)arg0 & ~3) << 16 != 0)
            goto have_call_position;
        call_position = position;
        if (FIELD(work, s32, 0x14) & 0x200)
            goto have_call_args;
        value = func_800A6D30(call_created, call_position);
        call_created = created;
        if (!(value & 1))
            goto have_call_position;
        FIELD(work, s32, 0x1C) |= 0x200;
        value = func_800A6D30(created);
        func_800A48F0(work, 1, (value & 0x3F) | 0x20);
        FIELD(monster, Callback, 0x2C) = (Callback)&D_80151298;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

finish_kind_args:
        call_created = created;
have_call_position:
        call_position = position;
have_call_args:
        func_800A9C18(call_created, call_position, monster, (s16)arg0_copy);

        i = 0;
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
            i++;
            goto scan_entry;
        } else {
        }

        rectp = &rect;
        ASM_KEEP(rectp);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        selected = (u8 *)(doubled + i);
        selected = (u8 *)((s32)selected * 4);
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
