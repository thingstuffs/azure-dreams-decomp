#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_8195AB84_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_8195AB84_0;   /* (void *)constant in func_8195AB84 */

typedef struct S_8195AB84_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_8195AB84_1;   /* *slot in func_8195AB84 */

typedef struct S_8195AB84_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8195AB84_2;   /* header in func_8195AB84 */

typedef struct S_8195AB84_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    s16 unk_16;
    u8 pad_18[0x2];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_8195AB84_3;   /* node in func_8195AB84 */

typedef struct S_8195AB84_4 {
    u8 pad_00[0x20];
    void * unk_20;
    u8 pad_24[0xC];
    s16 unk_30;
    u8 pad_32[0x2];
    s16 unk_34;
    s16 unk_36;
} S_8195AB84_4;   /* tail in func_8195AB84 */



extern void func_80025B5C();
extern void func_800263FC();
extern void func_800264F0() __attribute__((noreturn));
extern void func_80026514();
extern s32 func_8003FA44(s32);
extern void *func_8003FD64(s32, void *);

extern s32 D_80025C80;
extern u8 D_80028268[];
extern s32 D_800814A0;
extern s32 D_80083498;

/* Create 18 linked objects at the given position and angle, marking them for cleanup on failure. */
void *func_8195AB84(s16 x, s16 y, s16 z, s16 angle)
{
    void *objects[18];
    s32 object_index;
    register void **objects_base ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    void **slot;
    S_8195AB84_2 *position;
    S_8195AB84_3 *transform;
    S_8195AB84_4 *object_state;
    u8 *entry_table;
    u8 *state_page;
    register s32 scratch ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s16 saved_x;
    register s16 saved_y ASM_REG("$22");   /* MATCH pin: keeps a constant in a register as retail does */
    register s16 saved_z ASM_REG("$23");   /* MATCH pin: keeps a constant in a register as retail does */
    s16 saved_angle;
    register void *callback_addr ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    u16 transform_flags;
    void **cleanup_slot;
    u16 object_flags;
    void *call_context;
    s32 state_flags;
    static void *const loop_label_ref[] = { &&loop_continue };

    saved_x = x;
    saved_y = y;
    saved_z = z;
    saved_angle = angle;
    scratch = func_8003FA44(18);
    object_index = 0;
    if (scratch != 0) {
        scratch = (s32)0x80030000;
        ASM_KEEP(scratch);   /* MATCH pin: load-bearing for the whole function shape */
        entry_table = (u8 *)scratch - 0x7D98;
        state_page = (u8 *)0x80080000;
        objects_base = objects;
        slot = objects_base;
        do {
            scratch = (s32)0x80080000;
            if (object_index != 0) {
                call_context = objects[0];
                ASM_KEEP(call_context);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                func_800263FC();
            }
            call_context = (void *)(scratch + 0x3498);
            ASM_KEEP_NV(call_context);   /* MATCH pin: keeps a statement from moving across a call/branch */
            scratch = (s32)func_8003FD64(18, call_context);
            *slot = (void *)scratch;
            if (scratch != 0) {
                callback_addr = &D_80025C80;
                ((S_8195AB84_0 *)((void *)scratch))->unk_10 = callback_addr;
                position = ((S_8195AB84_1 *)(*slot))->unk_08;
                position->unk_02 = saved_x;
                position->unk_06 = saved_y;
                position->unk_0A = saved_z;
                transform = ((S_8195AB84_1 *)(*slot))->unk_0C;
                transform->unk_16 = 0x400;
                transform->unk_1A = saved_angle + 0x400;
                scratch = 0x1000;
                transform->unk_20 = scratch;
                transform->unk_1E = scratch;
                transform->unk_1C = scratch;
                transform_flags = transform->unk_14;
                transform->unk_08 = (void *)((u32)(object_index * 0x10) + (u32)entry_table);
                transform->unk_10 = 0x20;
                transform->unk_14 = transform_flags | 0xC;
                scratch = (s32)*slot;
                object_state = (u8 *)scratch + 0x20;
                if (object_index != 0) {
                    ASM_KEEP(object_state);   /* MATCH pin: keeps a constant in a register as retail does */
                    object_state->unk_20 = objects[0];
                }
                object_state->unk_30 = 0x10;
                object_state->unk_34 = saved_angle;
                object_state->unk_36 = 7;
                func_800264F0(transform);
            } else {
                object_index--;
                if (object_index >= 0) {
                    scratch = object_index * 4;
                    cleanup_slot = (void **)((u32)scratch + (u32)objects_base);
                    do {
                        scratch = (s32)*cleanup_slot;
                        cleanup_slot--;
                        object_index--;
                        state_flags = *(s32 *)(state_page + 0x14A0);
                        object_flags = ((S_8195AB84_0 *)((void *)scratch))->unk_1E;
                        state_flags |= 0x8000;
                        *(s32 *)(state_page + 0x14A0) = state_flags;
                        object_flags |= 0x8000;
                        ((S_8195AB84_0 *)((void *)scratch))->unk_1E = object_flags;
                    } while (object_index >= 0);
                }
call_26514:
                scratch = 0;
                ASM_TAILSLOT_PIN_TIED(scratch);   /* MATCH pin: retail delay-slot contents depend on it */
                func_80026514();
                goto loop_continue;
            }
loop_continue:
            object_index++;
            slot++;
        } while (object_index < 18);
        func_80025B5C(objects[0], saved_angle);
        return objects[0];
    } else {
        goto call_26514;
    }
}

extern void func_800263FC(void) __attribute__((noreturn));
extern void func_800264F0(void) __attribute__((noreturn));
extern void func_80026514(void) __attribute__((noreturn));
