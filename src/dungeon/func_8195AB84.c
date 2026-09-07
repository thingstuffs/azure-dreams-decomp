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

void *func_8195AB84(s16 arg0, s16 arg1, s16 arg2, s16 arg3)
{
    void *objects[18];
    s32 i;
    register void **objects_base ASM_REG("$19");   /* MATCH pin: retail register colouring depends on it */
    void **slot;
    S_8195AB84_2 *header;
    S_8195AB84_3 *node;
    S_8195AB84_4 *tail;
    u8 *table_base;
    u8 *global_page;
    register s32 constant ASM_REG("$2");   /* MATCH pin: keeps a constant in a register as retail does */
    s16 held_arg0;
    register s16 held_arg1 ASM_REG("$22");   /* MATCH pin: keeps a constant in a register as retail does */
    register s16 held_arg2 ASM_REG("$23");   /* MATCH pin: keeps a constant in a register as retail does */
    s16 held_arg3;
    register void *global_addr ASM_REG("$8");   /* MATCH pin: retail register colouring depends on it */
    u16 flags;
    void **cleanup;
    u16 cleanup_flags;
    void *call_arg;
    s32 global_value;
    static void *const keepalive[] = { &&loop_continue };

    held_arg0 = arg0;
    held_arg1 = arg1;
    held_arg2 = arg2;
    held_arg3 = arg3;
    constant = func_8003FA44(18);
    i = 0;
    if (constant != 0) {
        constant = (s32)0x80030000;
        ASM_KEEP(constant);   /* MATCH pin: load-bearing for the whole function shape */
        table_base = (u8 *)constant - 0x7D98;
        global_page = (u8 *)0x80080000;
        objects_base = objects;
        slot = objects_base;
        do {
            constant = (s32)0x80080000;
            if (i != 0) {
                call_arg = objects[0];
                ASM_KEEP(call_arg);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
                func_800263FC();
            }
            call_arg = (void *)(constant + 0x3498);
            ASM_KEEP_NV(call_arg);   /* MATCH pin: keeps a statement from moving across a call/branch */
            constant = (s32)func_8003FD64(18, call_arg);
            *slot = (void *)constant;
            if (constant != 0) {
                global_addr = &D_80025C80;
                ((S_8195AB84_0 *)((void *)constant))->unk_10 = global_addr;
                header = ((S_8195AB84_1 *)(*slot))->unk_08;
                header->unk_02 = held_arg0;
                header->unk_06 = held_arg1;
                header->unk_0A = held_arg2;
                node = ((S_8195AB84_1 *)(*slot))->unk_0C;
                node->unk_16 = 0x400;
                node->unk_1A = held_arg3 + 0x400;
                constant = 0x1000;
                node->unk_20 = constant;
                node->unk_1E = constant;
                node->unk_1C = constant;
                flags = node->unk_14;
                node->unk_08 = (void *)((u32)(i * 0x10) + (u32)table_base);
                node->unk_10 = 0x20;
                node->unk_14 = flags | 0xC;
                constant = (s32)*slot;
                tail = (u8 *)constant + 0x20;
                if (i != 0) {
                    ASM_KEEP(tail);   /* MATCH pin: keeps a constant in a register as retail does */
                    tail->unk_20 = objects[0];
                }
                tail->unk_30 = 0x10;
                tail->unk_34 = held_arg3;
                tail->unk_36 = 7;
                func_800264F0(node);
            } else {
                i--;
                if (i >= 0) {
                    constant = i * 4;
                    cleanup = (void **)((u32)constant + (u32)objects_base);
                    do {
                        constant = (s32)*cleanup;
                        cleanup--;
                        i--;
                        global_value = *(s32 *)(global_page + 0x14A0);
                        cleanup_flags = ((S_8195AB84_0 *)((void *)constant))->unk_1E;
                        global_value |= 0x8000;
                        *(s32 *)(global_page + 0x14A0) = global_value;
                        cleanup_flags |= 0x8000;
                        ((S_8195AB84_0 *)((void *)constant))->unk_1E = cleanup_flags;
                    } while (i >= 0);
                }
call_26514:
                constant = 0;
                ASM_TAILSLOT_PIN_TIED(constant);   /* MATCH pin: retail delay-slot contents depend on it */
                func_80026514();
                goto loop_continue;
            }
loop_continue:
            i++;
            slot++;
        } while (i < 18);
        func_80025B5C(objects[0], held_arg3);
        return objects[0];
    } else {
        goto call_26514;
    }
}

extern void func_800263FC(void) __attribute__((noreturn));
extern void func_800264F0(void) __attribute__((noreturn));
extern void func_80026514(void) __attribute__((noreturn));
