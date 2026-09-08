#include "common.h"

typedef struct {
    u8 pad0[0x8D0];
    void *nextPrim;
} RenderState;

typedef struct {
    u8 pad0[0x3160];
    RenderState *state;
} DungeonGlobals;

typedef struct {
    u8 pad0[4];
    s32 field4;
    s16 field8;
    s16 fieldA;
    s16 fieldC;
    s16 fieldE;
} Primitive;

typedef struct {
    u8 pad0[0x4A];
    s16 phase;
    u16 counter;
    u8 pad50[4];
    s16 count;
    u8 pad54[0x14];
    u8 *handle;
} DungeonObject;

typedef struct {
    u8 pad0[8];
    s32 field8;
    u8 padC[8];
    s32 field14;
} MotionState;

typedef struct {
    u8 pad0[0xC];
    u8 fieldC;
    u8 fieldD;
    u8 fieldE;
    u8 padF[0xD];
    u16 field1C;
} EffectState;

typedef struct {
    s32 field18;
    s32 field1C;
    s16 field20;
    s16 field22;
} StackData;

extern RenderState *D_80083160;
extern u8 D_801C9E40[16];
extern u8 D_80083780[12];
extern u8 D_80082E80[];
extern void *D_800E3D7C[];
extern u8 D_800DD0F8[];
extern s16 D_80083228[5];
extern s16 D_800814E8;
extern u8 D_80083120[];
extern u16 D_80082E76;

extern void func_8006658C();
extern void func_800667BC();
extern void func_80067E2C();
extern s32 func_80069EF8();
extern void func_80091934();
extern s32 func_8003F794();
extern void func_80048A44();
extern void func_800945E8();
extern void func_800948BC();
extern void func_800B8FC8();
extern void func_80041094();

/* Draws randomized vertical streaks and advances the object's motion and fade sequence. */
void func_800C0404(DungeonObject *obj, MotionState *motion, EffectState *effect) {
    StackData draw_data;
    s32 use_alt_buffer;
    u32 buffer_diff;
    RenderState **render_state_slot;
    RenderState *render_state;
    RenderState *call_state;
    Primitive *prim;
    u8 *prim_list;
    s32 index_or_phase;
    register s32 area_origin ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    register Primitive *first_prim ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */

    area_origin = 0x01800340;
    draw_data.field18 = area_origin;
    draw_data.field1C = 0x00400040;
    render_state_slot = &D_80083160;
    render_state = *render_state_slot;
    do {
        prim = (Primitive *)render_state->nextPrim;
    } while (0);
    prim_list = (u8 *)render_state + 0x8B0;
    first_prim = prim;
    render_state->nextPrim = (u8 *)prim + 0xC;
    buffer_diff = (u32)render_state ^ (u32)D_801C9E40;
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    call_state = *(RenderState *volatile *)&D_80083160;
    use_alt_buffer = buffer_diff != 0;
    func_80067E2C(first_prim, call_state, render_state);
    func_8006658C(prim_list, prim);
    ASM_USE_NV(prim_list);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    if (obj->count > 0) {
        index_or_phase = 0;
        do {
            RenderState *streak_state;
            streak_state = *render_state_slot;
            prim = (Primitive *)streak_state->nextPrim;
            streak_state->nextPrim = (u8 *)prim + 0x10;
            prim->fieldC = (func_80069EF8() & 0x3F) + 0x340;
            prim->field8 = prim->fieldC;
            {
                s32 y_offset = func_80069EF8() & 0x3F;
                s32 bottom_y;
                prim->fieldA = 0x180 - y_offset;
                ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
                bottom_y = 0x1BF - y_offset;
                prim->fieldE = bottom_y;
                if (use_alt_buffer) {
                    bottom_y -= 0xE0;
                    prim->fieldE = bottom_y;
                    prim->fieldA -= 0xE0;
                }
                ASM_USE_NV(use_alt_buffer);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
            }
            prim->field4 = 0;
            func_800667BC(prim);
            func_8006658C(prim_list, prim);
            index_or_phase += 1;
        } while (index_or_phase < obj->count);
    }

    if (obj->count < 0x60) {
        obj->count = (u16)obj->count + 1;
    }

    {
        RenderState *area_state;
        area_state = *render_state_slot;
        prim = (Primitive *)area_state->nextPrim;
        area_state->nextPrim = (u8 *)prim + 0xC;
        func_80067E2C(prim, &draw_data.field18);
        func_8006658C(prim_list, prim);
    }
    draw_data.field20 = 0x360;
    draw_data.field22 = 0x1B8;
    func_800B8FC8(obj->handle, &draw_data.field18, &draw_data.field20, 1, 0);

    {
        u16 frame_count = obj->counter + 1;
        index_or_phase = (s16)obj->phase;
        obj->counter = frame_count;
        if (index_or_phase == 0) {
            if ((s16)frame_count >= 0x21) {
                if (obj->handle[0x13] == 0) {
                    u8 *dungeon_state;
                    func_80091934(obj->handle, D_80083780, D_80082E80, 0);
                    ((u8 *)D_800E3D7C[0])[0x9B] = 0x11;
                    dungeon_state = *(u8 *volatile *)D_800E3D7C;
                    *(u8 * volatile *)(D_80082E80 + 0x2C) = D_800DD0F8;
                    func_80048A44(
                        D_80082E80,
                        D_800DD0F8[((s32)(*D_80083228 + *(s16 *)(dungeon_state + 0x2A)) + 0x100 >> 9) & 7],
                        1,
                        1);
                }
                obj->phase = (u16)obj->phase + 1;
            } else {
                return;
            }
        } else if (index_or_phase == 1) {
            MotionState *parent_motion;
            effect->fieldC = effect->fieldC - (effect->fieldC >> 3);
            effect->fieldD = effect->fieldD - (effect->fieldD >> 3);
            effect->fieldE = effect->fieldE - (effect->fieldE >> 3);
            effect->field1C = effect->field1C + ((0x400 - effect->field1C) >> 2);
            parent_motion = *(MotionState **)((u8 *)obj - 0x18);
            motion->field8 = motion->field8 + motion->field14;
            parent_motion->field8 = motion->field8;
            motion->field14 = motion->field14 + 0xFFFC0000;
            if (obj->handle[0x13] == 0 &&
                (*(u16 *)(*(u8 **)((u8 *)D_800E3D7C[0] - 0x14) + 0x14) & 0x6000)) {
                s16 entry_index = func_8003F794(6, 0x20);
                u8 *entry_table = D_80083120;
                s16 *entry_flag;
                void *active_dungeon;
                D_800814E8 = entry_index;
                entry_flag = (s16 *)(entry_table + (((s32)(entry_index << 16)) >> 0xD) + 6);
                active_dungeon = D_800E3D7C[0];
                *entry_flag = index_or_phase;
                func_800945E8(active_dungeon);
                func_800948BC();
                D_80082E76 = 0x8000;
                func_80041094(6, 0, 0, 0, 0x8000);
                obj->phase = (u16)obj->phase + 1;
            }
        }
    }
}
