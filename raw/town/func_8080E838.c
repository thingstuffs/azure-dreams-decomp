#include "common.h"

typedef struct {
    s32 words[4];
} Copy16;

extern void *func_800373DC(s32);
extern void func_8003BC18(void *, void *);
extern void func_8023FA58(void *, void *, void *);

extern u8 D_8003C558[];
extern u8 D_8052643C[];
extern u8 D_80529594[];
extern s32 D_805300F4[];

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

void func_8080E838(void *arg0, void *arg1) {
    void *obj;
    void *result;
    register void *source ASM_REG("$17");
    register void *initial ASM_REG("$19");
    register u8 *payload ASM_REG("$18");
    register u8 *part ASM_REG("$3");
    register u8 *held ASM_REG("$20");
    register Copy16 *copy_src ASM_REG("$6");
    register Copy16 *copy_dst ASM_REG("$7");
    register Copy16 *copy_end ASM_REG("$8");
    register s32 loop0 ASM_REG("$2");
    register s32 loop1 ASM_REG("$3");
    register s32 loop2 ASM_REG("$4");
    register s32 loop3 ASM_REG("$5");
    register s32 word0 ASM_REG("$2");
    register s32 word1 ASM_REG("$6");
    register s32 word2 ASM_REG("$7");
    register s32 word3 ASM_REG("$8");
    register u8 *call_data ASM_REG("$5");
    register s32 *table_base ASM_REG("$1");

    source = arg0;
    ASM_KEEP_NV(source);
    initial = arg1;
    ASM_KEEP_NV(initial);
    result = func_800373DC(0x136);
    held = D_8052643C;
    ASM_KEEP_NV(held);
    obj = result;
    payload = (u8 *)obj + 0x20;
    if (obj != 0) {
        copy_dst = (Copy16 *)payload;
        copy_src = (Copy16 *)source;
        copy_end = (Copy16 *)((u8 *)source + 0x50);
        do {
            loop0 = FIELD(copy_src, s32, 0);
            loop1 = FIELD(copy_src, s32, 4);
            loop2 = FIELD(copy_src, s32, 8);
            loop3 = FIELD(copy_src, s32, 0xC);
            FIELD(copy_dst, s32, 0) = loop0;
            FIELD(copy_dst, s32, 4) = loop1;
            FIELD(copy_dst, s32, 8) = loop2;
            FIELD(copy_dst, s32, 0xC) = loop3;
            ASM_SCHED_BARRIER();
            copy_src++;
            copy_dst++;
        } while (copy_src != copy_end);
        word0 = FIELD(copy_src, s32, 0);
        loop1 = FIELD(copy_src, s32, 4);
        FIELD(copy_dst, s32, 0) = word0;
        FIELD(copy_dst, s32, 4) = loop1;
        ASM_SCHED_BARRIER();
        loop2 = (s32)obj;
        ASM_KEEP(loop2);
        call_data = D_8003C558;
        ASM_KEEP(call_data);
        part = FIELD(obj, u8 *, 8);
        ASM_KEEP(part);
        word0 = (s32)D_80529594;
        ASM_KEEP(word0);
        FIELD(obj, s32, 0x10) = word0;
        word0 = FIELD(initial, s32, 0);
        word1 = FIELD(initial, s32, 4);
        word2 = FIELD(initial, s32, 8);
        word3 = FIELD(initial, s32, 0xC);
        FIELD(part, s32, 0) = word0;
        FIELD(part, s32, 4) = word1;
        FIELD(part, s32, 8) = word2;
        FIELD(part, s32, 0xC) = word3;
        word0 = FIELD(initial, s32, 0x10);
        word1 = FIELD(initial, s32, 0x14);
        FIELD(part, s32, 0x10) = word0;
        FIELD(part, s32, 0x14) = word1;
        func_8003BC18((void *)loop2, call_data);

        word1 = 0x800000;
        ASM_KEEP(word1);
        part = FIELD(obj, u8 *, 0xC);
        word0 = 0x1000;
        FIELD(part, s16, 0x1E) = word0;
        FIELD(part, s16, 0x1C) = word0;
        word0 = FIELD(source, s16, 0x54);
        ASM_KEEP(word0);
        word1 |= 0x8080;
        ASM_KEEP(word1);
        word0 <<= 2;
        table_base = (s32 *)0x80530000;
        table_base = (s32 *)((s32)table_base - -word0);
        loop3 = FIELD(table_base, s32, 0x130);
        ASM_KEEP(loop3);
        word0 = FIELD(part, u16, 0x14);
        FIELD(part, u8, 4) = 0;
        FIELD(part, u8, 5) = 0;
        ASM_SCHED_BARRIER();
        FIELD(part, s32, 0xC) = word1;
        word0 |= 0x80;
        FIELD(part, u16, 0x14) = word0;
        ASM_KEEP(word0);
        FIELD(part, s32, 8) = loop3;
        FIELD(payload, void *, 0x50) = held;
        ASM_KEEP_NV(payload);
        call_data = FIELD(obj, u8 *, 8);
        ASM_KEEP(call_data);
        word1 = (s32)D_805300F4;
        ASM_KEEP(word1);
        func_8023FA58(payload + 8, call_data, (void *)word1);
    }
}
