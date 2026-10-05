#include "common.h"

typedef struct {
    u8 bytes[4];
} __attribute__((packed)) Copy4;

extern s32 func_80017EB8(void *position);
extern s32 func_8001A510(s32 arg0);
extern u8 D_8001B1C0[];
extern u8 D_8001B218[];

/* Builds a terminated record list with an optional entry and flags checked records. */
u8 *func_80017F3C(void *unused)
{
    s32 record_count;
    s32 record_id;
    s32 checked_count;
    s32 plain_count;
    s32 checked_tag;
    u32 plain_tag;
    register u8 *seed_record;
    register u8 *records;
    u8 *optional_record;
    u8 *checked_base;
    u8 *checked_record;
    u8 *plain_base;
    u8 *plain_record;
    u8 *tail_base;
    u32 end_offset;
    u8 *end_record;

    records = D_8001B218;
    seed_record = D_8001B1C0;
    *(Copy4 *)records = *(Copy4 *)seed_record;
    record_count = 1;
    if (func_8001A510(0x7A0) != 0) {
        record_count = 2;
        optional_record = records + 4;
        optional_record[1] = 0xD;
        records[4] = 4;
        optional_record[3] = 0;
        optional_record[2] = 0;
    }

    record_id = 1;
    checked_base = records;
    checked_tag = 0x18;
    do {
        {
            checked_count = record_count + record_id;
            checked_record = (u8 *)((u32)((checked_count - 1) * 4) + (u32)checked_base);
            checked_record[1] = checked_tag;
            checked_record[0] = record_id;
            if (func_80017EB8(checked_record) != 0) {
                checked_record[3] |= 0x80;
            }
            record_id++;
        }
    } while (record_id < 0x20);

    record_count = checked_count;
    record_id = 1;
    plain_base = D_8001B218;
    plain_tag = 0xB;
    do {
        {
            plain_count = record_count + record_id;
            plain_record = (u8 *)((u32)((plain_count - 1) * 4) + (u32)plain_base);
            plain_record[0] = record_id;
            record_id++;
            plain_record[1] = plain_tag;
        }
    } while (record_id < 6);

    record_count = plain_count;
    plain_tag = plain_count * 4;
    record_count++;
    tail_base = D_8001B218;
    plain_tag += (u32)tail_base;
    end_record = (u8 *)0x18;
    ((u8 *)plain_tag)[1] = (s32)end_record;
    end_record = (u8 *)0x20;
    ((u8 *)plain_tag)[0] = (s32)end_record;
    end_offset = record_count * 4;
    end_record = (u8 *)(end_offset + (u32)tail_base);
    end_record[1] = 0;
    end_record[0] = 0;
    return tail_base;
}
