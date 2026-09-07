#include "common.h"


typedef struct {
    u8 pad[0xA];
    u16 field_A;
} D_80083460_t;

typedef struct {
    u8 pad[0xC];
    u16 flags;
    u8 pad_E[6];
} DungeonRecord;

extern u8 D_80082E80[];
extern D_80083460_t D_80083460;
extern u8 D_80083780[];
extern u16 D_800DDE84[];
extern u8 D_800E12D6[];
extern u8 D_800E1303[];
extern DungeonRecord D_800E2970[];
extern u8 *D_800E3D7C;

extern void func_8008D344(void *, void *, void *, void *);
extern void func_80098864(s32, s32);
extern void func_80098B38(s32);
extern s32 func_800990FC(void);
extern s32 func_80099194(void *, s32);
extern void func_80099290(s32);
extern void func_800997FC(void *);
extern void func_800A5720(s32);
extern void func_800A5F38(void *, s32);
extern void func_800A6480(void *, s32, s16);
extern s32 func_800AD6FC(void *, s32, s32);
extern s32 func_800BF9B0(void);
extern s32 func_800BF9CC(void);
extern void func_800C4D78(s32, s32);
extern s32 func_800C4EB4(s32, s32, s32, s32, s32);


typedef struct S_800BF7FC_0_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_800BF7FC_0_pre;   /* the 0x14 bytes before arg0 in func_800BF7FC, addressed as arg0[-1] */

typedef struct S_800BF7FC_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x74];
    s16 unk_88;
    u8 pad_8A[0x86];
    s32 unk_110;
} S_800BF7FC_0;   /* arg0 in func_800BF7FC */

typedef struct S_800BF7FC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800BF7FC_1;   /* obj in func_800BF7FC */

s32 func_800BF7FC(void *arg0, u8 *arg1, s16 arg2, s32 arg3)
{
    DungeonRecord *record;
    u8 *obj;
    s32 raw_value;
    s32 value;
    u8 *message;
    register s32 call_value ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    register u32 page ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s8 index;

    if (arg2 == 13) {
        func_80098864((s32)arg1, arg3);
        return func_800BF9CC();
    }

    if (arg0 == D_800E3D7C) {
        ((S_800BF7FC_0 *)arg0)->unk_110 = (s32)arg1;
        func_8008D344(arg0, D_80083780, D_80082E80, arg0);
        func_800BF9CC();
        ASM_SCHED_BARRIER();   /* MATCH pin: retail delay-slot contents depend on it */
        return 0;
    }

    if ((u32)arg0 <= 0x9FFFFFFF) {
        func_800A6480(arg0, (s32)arg1, arg2);
        if (func_800AD6FC(arg0,
                          D_800DDE84[((S_800BF7FC_0 *)arg0)->unk_13] & 3,
                          (s32)arg1) == 0) {
            func_800A5F38(arg0, (s32)arg1);
            func_800BF9CC();
            return 1;
        }
    } else {
        obj = ((S_800BF7FC_0_pre *)arg0)[-1].unk_00;
        index = ((S_800BF7FC_1 *)obj)->unk_26;
        if (index >= 0 && !(D_800E2970[index].flags & 2)) {
            if (func_800C4EB4(((S_800BF7FC_1 *)obj)->unk_24,
                              ((S_800BF7FC_1 *)obj)->unk_25,
                              ((S_800BF7FC_0 *)arg0)->unk_88,
                              arg1[0], index) == 0) {
                func_800BF9CC();
                return 0;
            }

            record = &D_800E2970[((S_800BF7FC_1 *)obj)->unk_26];
            record->flags |= 2;
            func_800C4D78(0x20C0C0, 1);
            raw_value = func_800990FC();
            message = D_800E12D6;
            ASM_KEEP(message);   /* MATCH pin: retail schedule: same instructions, different order without it */
            call_value = raw_value;
            ASM_KEEP_NV(call_value);   /* MATCH pin: retail register colouring depends on it */
            func_80099290(func_80099194(message,
                                         value = call_value));
            func_800A5720(value);
            page = 0x80080000;
            ASM_PAGEBASE_PIN(page);   /* MATCH pin: retail delay-slot contents depend on it */
            return func_800BF9B0();
        }
        func_800997FC(D_800E1303);
    }

    D_80083460.field_A--;
    func_80098B38((s32)arg1);
    return 1;
}

/* MECHANISM: The seed's 0x30 frame, saved-register roles, and CFG remain unchanged.
   The RNG result stays transient while a tied $a0 address precedes a tied $a1 copy;
   nested assignment then places the saved $s0 copy in func_80099194's delay slot. */
