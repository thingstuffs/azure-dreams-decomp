#include "common.h"

typedef struct {
    u8 bytes[4];
} __attribute__((packed)) Copy4;

extern s32 func_80017EB8(void *arg0);
extern s32 func_8001A510(s32 arg0);
extern u8 D_8001B1C0[];
extern u8 D_8001B218[];

void func_80017F3C(void *arg0)
{
    register s32 status ASM_REG("$18");
    s32 i;
    register s32 sum1 ASM_REG("$19");
    register s32 sum2 ASM_REG("$3");
    s32 tag;
    register s32 tag2 ASM_REG("$4");
    register u8 *src;
    register u8 *dst;
    u8 *init_record;
    u8 *loop_base;
    u8 *loop_record;
    u8 *base2;
    u8 *record2;
    register u8 *tail_base ASM_REG("$2");
    register u32 tail_page ASM_REG("$2");
    register u32 tail_offset ASM_REG("$4");
    register u32 end_offset ASM_REG("$3");
    register s32 tail_tag ASM_REG("$3");
    u8 *tail_record;
    register u8 *end_record ASM_REG("$3");

    dst = D_8001B218;
    src = D_8001B1C0;
    *(Copy4 *)dst = *(Copy4 *)src;
    status = 1;
    if (func_8001A510(0x7A0) != 0) {
        status = 2;
        init_record = dst + 4;
        init_record[1] = 0xD;
        dst[4] = 4;
        init_record[3] = 0;
        init_record[2] = 0;
    }

    i = 1;
    loop_base = dst;
    tag = 0x18;
    do {
        sum1 = status + i;
        loop_record = (u8 *)((u32)((sum1 - 1) * 4) + (u32)loop_base);
        loop_record[1] = tag;
        loop_record[0] = i;
        if (func_80017EB8(loop_record) != 0) {
            loop_record[3] |= 0x80;
        }
        i++;
    } while (i < 0x20);

    status = sum1;
    i = 1;
    base2 = D_8001B218;
    tag2 = 0xB;
    do {
        sum2 = status + i;
        ASM_KEEP(sum2);
        record2 = (u8 *)((u32)((sum2 - 1) * 4) + (u32)base2);
        record2[0] = i;
        i++;
        record2[1] = tag2;
    } while (i < 6);

    status = sum2;
    tail_offset = sum2 * 4;
#ifdef NON_MATCHING
    tail_page = (u32)(D_8001B218 + 0x4DE8);
#else
    tail_page = 0x80020000;
#endif
    ASM_KEEP_NV(tail_page);
    ASM_KEEP_NV(status);
    status++;
    ASM_KEEP_NV(status);
    tail_base = (u8 *)(tail_page - 0x4DE8);
    tail_record = (u8 *)(tail_offset + (u32)tail_base);
    ASM_KEEP_NV(tail_record);
    tail_tag = 0x18;
    tail_record[1] = tail_tag;
    tail_tag = 0x20;
    tail_record[0] = tail_tag;
    end_offset = status * 4;
    end_record = (u8 *)(end_offset + (u32)tail_base);
    ASM_KEEP(end_record);
    end_record[1] = 0;
    end_record[0] = 0;
}
