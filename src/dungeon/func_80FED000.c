/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#if 0 /* rowbase_rename_reverify precondition marker: dead declaration, never
         seen by the real compiler; satisfies the tool's textual defines()
         check for the proven-region rename of func_8015E800. */
void func_8015E800(void);
#endif

typedef struct DungeonSub2 DungeonSub2;
typedef struct DungeonSub1 DungeonSub1;
typedef struct DungeonNode DungeonNode;
typedef union DungeonArgBits DungeonArgBits;

union DungeonArgBits {
    void *p;
    s32 i;
};

struct DungeonSub2 {
    u8 pad00[0x24];
    s8 field24;
    s8 field25;
    u8 pad26[6];
    void *field2c;
};

struct DungeonNode {
    u8 pad00[8];
    void *field08;
    DungeonSub2 *field0c;
    void *field10;
    u8 pad14[0x0c];
};

struct DungeonSub1 {
    u8 pad00[0x13];
    s8 field13;
    s32 field14;
    u8 pad18[4];
    s32 field1c;
    u8 pad20[0x6c];
    void *field8c;
    u8 pad90[0x0a];
    u8 field9a;
    u8 pad9b[1];
    s8 field9c;
};

void *func_8003FD64();
M2C_UNK func_8004491C();
M2C_UNK func_800A48F0();
s32 func_800A6D30();
M2C_UNK func_800A9C18();
M2C_UNK func_800AA36C();
extern M2C_UNK D_80045340;
extern M2C_UNK D_80083498;
extern u8 D_8015EA7C[];
extern M2C_UNK D_8015EEA8;
extern M2C_UNK D_80162038;
extern M2C_UNK D_80162088;

#ifdef __mips__
extern void *func_8015E8A8(s32, s8, s8, s16);
extern void *func_8015F2B8(void);
extern void *func_8015F2E4(void);
extern void *func_8015F264(void);
extern void *func_8015F1F4(void);
extern void *func_8015F1E4(void);
extern void *func_8015F2A8(void);
extern void *func_80160AC4(void);
extern void *func_80160ABC(void);
extern void *func_80160AB4(void);
extern void *func_80160ACC(void);
extern void *func_80160A74(void);
extern void *func_80160A6C(void);
extern void *func_80160A64(void);

static const u32 data_prefix[] __asm__("func_8015E800")
    __attribute__((section(".text.func_8015E800"), aligned(4))) = {
    (u32)func_8015E8A8,
    (u32)D_8015EA7C,
    (u32)func_8015F2B8,
    (u32)func_8015F2B8,
    (u32)func_8015F2B8,
    (u32)func_8015F2E4,
    (u32)func_8015F264,
    (u32)func_8015F264,
    (u32)func_8015F264,
    (u32)func_8015F1F4,
    (u32)func_8015F1E4,
    (u32)func_8015F2E4,
    (u32)func_8015F2E4,
    (u32)func_8015F2A8,
    (u32)func_80160AC4,
    (u32)func_80160ABC,
    (u32)func_80160AB4,
    (u32)func_80160ACC,
    (u32)func_80160A74,
    (u32)func_80160A6C,
    (u32)func_80160A64,
    0x89824081,
    0x40819382,
    0x93829082,
    0x83829982,
    0x85828882,
    0x7C818482,
    0x90829582,
    0x00004481,
    0x92824081,
    0x96828582,
    0x81828582,
    0x85828C82,
    0x40818482,
    0x94828982,
    0x40819382,
    0x92829482,
    0x85829582,
    0x90824081,
    0x97828F82,
    0x92828582,
    0x74004481,
};
__asm__(".globl func_8015E800\n"
        ".size func_8015E800, 636");
#define BODY_NAME func_8015E8A8
#define BODY_ATTR __attribute__((section(".text.func_8015E800")))
#else
#define BODY_NAME func_8015E800
#define BODY_ATTR
#endif

void *BODY_NAME(s32 arg0, s8 arg1, s8 arg2, s16 arg3) BODY_ATTR;

void *BODY_NAME(s32 arg0, s8 arg1, s8 arg2, s16 arg3) {
    s32 unksp24;
    s32 unksp28;
    s32 sp24;
    s32 sp28;
    s32 temp_v1;
    register s32 call_count ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *call_target ASM_REG("$5");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register void *check_obj ASM_REG("$4");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s8 saved_arg1;
    s16 saved_arg3;
    s8 saved_arg2;
    DungeonSub2 *temp_s2;
    register void *temp_s4 ASM_REG("$20");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    DungeonNode *temp_v0;
    DungeonSub1 *var_s0;
    DungeonSub1 *temp_s5;
    register void *arg0_alias ASM_REG("$19");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    DungeonArgBits temp_s7;
    s32 temp_flag0;
    register s32 temp_flag1 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register s32 temp_mask ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */

    var_s0 = NULL;
    call_count = 0x112;
    saved_arg1 = arg1;
    call_target = &D_80083498;
    saved_arg3 = arg3;
    saved_arg2 = arg2;
    ASM_KEEP_DEP_NV(saved_arg1, call_count);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP_DEP_NV(saved_arg3, call_target);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP_DEP_NV(saved_arg2, call_target);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    unksp28 = (s32) *(s8 *)0xA64;
    unksp24 = (s32) *(s8 *)-0xD58;
    temp_v0 = func_8003FD64(call_count, call_target);
    if (temp_v0 != NULL) {
        arg0_alias = (void *) arg0;
        do {
            temp_s7.p = (void *) arg0;
        } while (0);
        var_s0 = (DungeonSub1 *)((u8 *)temp_v0 + 0x20);
        temp_v0->field10 = &D_8015EA7C;
        var_s0->field13 = 0x28;
        func_8004491C(temp_v0, &D_80045340);
        temp_s4 = temp_v0->field08;
        *(s16 *)((u8 *)temp_s4 + 0x0a) = saved_arg3;
        temp_s2 = temp_v0->field0c;
        temp_v1 = (s32) arg0_alias & 3;
        temp_s2->field25 = saved_arg2;
        temp_s5 = var_s0;
        temp_s2->field2c = &D_80162038;
        temp_s2->field24 = saved_arg1;
        if (temp_v1 == 1) {
            temp_flag0 = var_s0->field14;
            temp_flag1 = var_s0->field1c;
            temp_flag0 |= 0x6000;
            temp_flag1 |= 0x6000;
            goto store_flags;
        }
        else if (temp_v1 >= 2) {
            temp_flag0 = var_s0->field14;
            temp_flag1 = var_s0->field1c;
            temp_flag0 |= 0x2000;
            temp_flag1 |= 0x2000;
store_flags:
            var_s0->field14 = temp_flag0;
            var_s0->field1c = temp_flag1;
            goto final_call;
        }
        temp_mask = ((s32) arg0_alias & ~3) << 0x10;
        if (temp_mask == 0) {
            check_obj = temp_v0;
            if (!(var_s0->field14 & 0x200)) {
                call_target = temp_s4;
                ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot contents depend on it */
                if (func_800A6D30(check_obj, call_target) & 1) {
                    var_s0->field1c |= 0x200;
                    func_800A48F0(var_s0, 1, (func_800A6D30(check_obj) & 0x3F) | 0x20);
                    temp_s2->field2c = &D_80162088;
                }
            }
        }
final_call:
        func_800A9C18(temp_v0, temp_s4, temp_s2, (s16) temp_s7.i);
        temp_s5->field9a = 0xff;
        temp_s5->field9c = -1;
        temp_s5->field8c = &D_8015EEA8;
        func_800AA36C(temp_s5, temp_s4, temp_s2, var_s0);
    }
    return var_s0;
}
