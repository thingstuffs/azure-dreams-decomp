#include "common.h"

typedef struct {
    u8 pad0[0x9B];
    u8 state;
    u8 pad9C[0x100 - 0x9C];
    s16 h100;
} Actor;

typedef struct {
    u8 pad0[2];
    u16 f2;
    u8 pad4[8];
    u32 fC;
    u8 pad10[4];
    u16 f14;
} StructA;

extern StructA D_80083460;
extern u8 D_800E3648[];
extern u8 D_800E0B39[];
extern u8 D_80088B14[];
extern u8 D_800E0B4C[];

extern s32 func_800A2B5C(s32);
extern void func_80096088(Actor *, s32);
extern s32 func_800990FC(s32, s32, s32, s32);
extern s32 func_80099194(void *, s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099978(s32);
extern s32 func_80099368(void *, s32);
extern void func_800998C0(s32, s32);
extern s32 func_800999B0(s32);
extern void func_80099290(s32);
extern void func_800A5720(s32);
extern void func_800954E0(Actor *, s32, s32, s32);
extern s16 func_800B627C(s32, s32, s16, s32);

/* Advance the actor's entry action and clear pending state when it finishes. */
void func_80095DFC(Actor *actor, s32 context_a, s32 context_b, s32 target_arg) {
    register u8 *entry ASM_REG("$3");
    int state = actor->state;
    s32 target = target_arg;
    if (state != 1) {
        if (state >= 2) {
            return;
        }
        if (state != 0) {
            return;
        }
        if (D_80083460.f2 & 0x1000) {
            return;
        }
        if ((s16) func_800A2B5C(target) != 0) {
            return;
        }
        entry = &D_800E3648[actor->h100 * 4];
        if (entry[0] == 0) {
            func_80096088(actor, target);
            D_80083460.fC = 0;
            D_80083460.f14--;
            D_80083460.f2 &= 0xFFF7;
            return;
        }
        if (!(entry[3] & 0x40)) {

            s32 call_actor;
            register s32 call_context_a ASM_REG("$5");
            register s32 call_context_b ASM_REG("$6");
            register s32 call_target ASM_REG("$7");
            s32 cursor;
            s32 buffer_start;
            s32 patch_pos;
            s32 entry_pos;
            ASM_SET(call_actor);
            cursor = func_800990FC(call_actor, call_context_a, call_context_b, call_target);
            buffer_start = cursor;
            cursor = func_80099978(func_80099194(D_800E0B39, func_8009929C(8, cursor)));
            patch_pos = cursor - 2;
            cursor = func_80099194(D_80088B14, cursor);
            entry_pos = cursor;
            cursor = func_80099368(&D_800E3648[actor->h100 * 4], entry_pos);
            func_800998C0(patch_pos, entry_pos);
            func_80099290(func_800999B0(func_80099194(D_800E0B4C, func_8009929C(10, cursor))));
            func_800A5720(buffer_start);
        }
        actor->state++;
        func_800954E0(actor, context_a, context_b, target);
    }
    if (D_800E3648[actor->h100 * 4] == 0) {
        func_80096088(actor, target);
        D_80083460.fC = 0;
        D_80083460.f14--;
        D_80083460.f2 &= 0xFFF7;
        return;
    } else {
        s16 result = (s16) func_800B627C(D_800E3648[actor->h100 * 4], target, actor->h100, 0);
        if (result != 0) {
            D_80083460.fC = 0;
            D_80083460.f14--;
            D_80083460.f2 &= 0xFFF7;
            if (result > 0) {
                func_80096088(actor, target);
            }
            actor->state++;
        }
    }
}
