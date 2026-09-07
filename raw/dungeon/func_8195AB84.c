#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

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
    register void **objects_base ASM_REG("$19");
    void **slot;
    void *header;
    void *node;
    register void *tail ASM_REG("$3");
    u8 *table_base;
    register u8 *global_page ASM_REG("$20");
    register s32 constant ASM_REG("$2");
    register s16 held_arg0 ASM_REG("$21");
    register s16 held_arg1 ASM_REG("$22");
    register s16 held_arg2 ASM_REG("$23");
    register s16 held_arg3 ASM_REG("$18");
    register void *global_addr ASM_REG("$8");
    register u16 flags ASM_REG("$3");
    register void **cleanup ASM_REG("$5");
    register u16 cleanup_flags ASM_REG("$4");
    register void *call_arg ASM_REG("$5");
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
        ASM_KEEP(constant);
        table_base = (u8 *)constant - 0x7D98;
        ASM_KEEP(table_base);
        global_page = (u8 *)0x80080000;
        objects_base = objects;
        slot = objects_base;
        do {
            constant = (s32)0x80080000;
            if (i != 0) {
                call_arg = objects[0];
                ASM_KEEP(call_arg);
                func_800263FC();
            }
            call_arg = (void *)(constant + 0x3498);
            ASM_KEEP_NV(call_arg);
            constant = (s32)func_8003FD64(18, call_arg);
            *slot = (void *)constant;
            if (constant != 0) {
                global_addr = &D_80025C80;
                FIELD((void *)constant, void *, 0x10) = global_addr;
                header = FIELD(*slot, void *, 8);
                FIELD(header, s16, 2) = held_arg0;
                FIELD(header, s16, 6) = held_arg1;
                FIELD(header, s16, 0xA) = held_arg2;
                node = FIELD(*slot, void *, 0xC);
                FIELD(node, s16, 0x16) = 0x400;
                FIELD(node, s16, 0x1A) = held_arg3 + 0x400;
                constant = 0x1000;
                FIELD(node, s16, 0x20) = constant;
                FIELD(node, s16, 0x1E) = constant;
                FIELD(node, s16, 0x1C) = constant;
                flags = FIELD(node, u16, 0x14);
                FIELD(node, void *, 8) = (void *)((u32)(i * 0x10) + (u32)table_base);
                FIELD(node, s16, 0x10) = 0x20;
                FIELD(node, u16, 0x14) = flags | 0xC;
                constant = (s32)*slot;
                tail = (u8 *)constant + 0x20;
                if (i != 0) {
                    ASM_KEEP(tail);
                    FIELD(tail, void *, 0x20) = objects[0];
                }
                ASM_KEEP(tail);
                FIELD(tail, s16, 0x30) = 0x10;
                FIELD(tail, s16, 0x34) = held_arg3;
                FIELD(tail, s16, 0x36) = 7;
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
                        cleanup_flags = FIELD((void *)constant, u16, 0x1E);
                        global_value |= 0x8000;
                        *(s32 *)(global_page + 0x14A0) = global_value;
                        cleanup_flags |= 0x8000;
                        FIELD((void *)constant, u16, 0x1E) = cleanup_flags;
                    } while (i >= 0);
                }
call_26514:
                constant = 0;
                ASM_TAILSLOT_PIN_TIED(constant);
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
