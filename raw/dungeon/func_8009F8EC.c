#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

typedef struct DungeonState {
    u8 pad0[0xA];
    s16 count;
} DungeonState;

typedef struct EntityCopyBlock {
    s32 words[4];
} EntityCopyBlock;

typedef struct EntityCopyTail {
    s32 words[3];
} EntityCopyTail;

typedef struct Table4Entry {
    u8 value;
    u8 pad[3];
} Table4Entry;

typedef struct Table84Entry {
    u8 value;
    u8 pad[0x53];
} Table84Entry;

typedef struct TablePage {
    u8 pad0[0x980];
    Table4Entry table4[64];
    u8 gap[0x13];
    Table84Entry table84[64];
} TablePage;

typedef void *(*SpawnFunc)(s32, u8, u8, s16);

extern s32 func_8003E188();
extern s32 func_8003E4FC();
extern s32 func_8003FA44();
extern s32 func_800424E0();
extern s32 func_80042560();
extern s32 func_80042640();
extern s32 func_80042710();
extern s32 func_80044A50();
extern s32 func_80047738();
extern s32 func_80047DB8();
extern s32 func_80047E30();
extern s32 func_80047FF4();
extern s32 func_80048118();
extern s32 func_80053EF0();
extern s32 func_8009A028();
extern s32 func_8009A3D0();
extern SpawnFunc func_800A0B94();
extern s32 func_800A152C();
extern s32 func_800A1618();
extern s32 func_800A1BD0();
extern s32 func_800A53E0();
extern s32 func_800A5448();
extern s32 func_800A5668();
extern s32 func_800A566C();

extern u8 D_80023000[];
extern u8 D_8003E140[];
extern u8 *D_80080A90;
extern s32 D_80081488;
extern u8 D_8008149C[];
extern s32 D_800814A0;
extern u8 *D_800814A8;
extern s16 D_80083228;
extern DungeonState D_80083460;
extern s8 D_800DCF5C;
extern u8 D_800DCF5E_page[0x30A3] __asm__("D_800DCF5E");
extern u8 D_800E3DF0[];
extern u8 D_800E3E40[];
extern u8 D_8014A000[];

s32 func_800A504C(s32 unused, void *arg1)
{
    register u8 *entity ASM_REG("$19") = arg1;
    u8 *base = (u8 *)&D_80083460;
    s32 count = FIELD(base, s16, 0xA);
    s32 offset;
    s32 saved5c;
    s32 saved58;
    s32 angle;
    s32 global_flags;
    u16 role_flags;
    u16 remaining_count;
    register u32 call_index ASM_REG("$4");
    register s32 mask ASM_REG("$7");
    register s32 first_value ASM_REG("$3");
    register s32 tail_zero ASM_REG("$2");
    register u8 *global_page ASM_REG("$5");
    register u8 *mode_page ASM_REG("$4");
    register u8 *first_mask_call_arg ASM_REG("$4");
    register s32 first_mask_call_zero ASM_REG("$6");
    register s32 first_store_value ASM_REG("$2");
    register u8 *second_mask_call_arg ASM_REG("$4");
    register s32 second_mask_call_zero ASM_REG("$6");
    register s32 second_zero_delay ASM_REG("$2");
    register s32 second_zero_kind ASM_REG("$5");
    register s32 first_zero_delay ASM_REG("$2");
    register s32 first_two_delay ASM_REG("$2");
    register s32 second_two_delay ASM_REG("$2");
    u8 *spawned;
    register u8 *role1 ASM_REG("$17");
    u8 *record;
    u8 *record_data;
    u8 *tail_dst;
    u8 *copy_src;
    u8 *copy_dst;
    register u8 *copy_end ASM_REG("$8");
    SpawnFunc spawn;

    if (count != 1) {
        goto done;
    }
    if (func_8003FA44(8) == 0) {
        return 0;
    }

    role1 = (u8 *)0x800E0000;
    if (!(FIELD(entity, s32, 0x14) & 0x4000)) {
        goto second_dispatch;
    }
    if (FIELD(role1, s16, -0x30A2) == count) {
        goto first_equal;
    }
    if (FIELD(role1, s16, -0x30A2) < 2) {
        if (FIELD(role1, s16, -0x30A2) == 0) {
            goto first_zero;
        }
        return func_800A566C();
    }
    if (FIELD(role1, s16, -0x30A2) == 2) {
        goto first_two;
    }
    return func_800A566C();

first_zero:
    first_zero_delay = 0;
    ASM_KEEP(first_zero_delay);
    if (func_80053EF0(4) != 0) {
        return 0;
    }
    spawned = (u8 *)func_800A1618(FIELD(entity, u8, 0x13), 2);
    if (spawned == NULL) {
        return 0;
    }
    call_index = FIELD(entity, u8, 0x13);
    func_80047DB8(call_index);
    ASM_SET(call_index);
    return func_800A53E0(call_index, spawned);

first_equal:
    if (D_800E3E40[0] != 0) {
        func_80047E30();
        return func_800A5448();
    }
    return 0;

first_two:
    first_two_delay = 0;
    ASM_KEEP(first_two_delay);
    spawned = (u8 *)func_800A1618(FIELD(entity, u8, 0x13), 2);
    if (spawned == NULL) {
        goto done;
    }
    role1 = FIELD(entity, u8 *, -0x14);
    spawn = func_800A0B94(FIELD(entity, u8, 0x13), spawned, 1);
    spawned = spawn(6, role1[0x24], role1[0x25],
                    (s16)(FIELD(entity, u16, 0x88) - 0x20));
    if (spawned == NULL) {
        goto done;
    }
    base = entity;
    tail_dst = spawned;
    ASM_KEEP4_NV(base, tail_dst, entity, spawned);
    saved5c = FIELD(tail_dst, s32, 0x5C);
    saved58 = FIELD(tail_dst, s32, 0x58);
    ASM_KEEP_NV(entity);
    copy_dst = tail_dst;
    copy_src = entity;
    copy_end = entity + 0x80;
    ASM_KEEP_NV(copy_end);
    do {
        *(EntityCopyBlock *)copy_dst = *(EntityCopyBlock *)copy_src;
        copy_src += sizeof(EntityCopyBlock);
        copy_dst += sizeof(EntityCopyBlock);
    } while (copy_src != copy_end);
    *(EntityCopyTail *)copy_dst = *(EntityCopyTail *)copy_src;
    FIELD(spawned, s32, 0x4C) = 0;
    FIELD(spawned, s32, 0x50) = 0;
    FIELD(spawned, s32, 0x5C) = saved5c;
    FIELD(spawned, s32, 0x58) = saved58;
    func_80042640(spawned, FIELD(spawned, u8, 0x13));

    first_mask_call_arg = spawned;
    first_mask_call_zero = 0;
    first_store_value = 0x1000;
    ASM_KEEP4_NV(first_mask_call_arg, first_mask_call_zero,
                 first_store_value, spawned);
    role1 = FIELD(spawned, u8 *, -0x14);
    ASM_SET(mask);
    FIELD(role1, s16, 0x1C) = first_store_value;
    FIELD(role1, s16, 0x1E) = first_store_value;
    mask = -8;
    FIELD(spawned, s32, 0x14) &= mask;
    FIELD(spawned, s32, 0x1C) &= mask;
    FIELD(spawned, s32, 0x14) |= FIELD(entity, s32, 0x14) & 7;
    FIELD(spawned, s32, 0x1C) |= FIELD(entity, s32, 0x1C) & 7;
    func_800424E0(first_mask_call_arg, FIELD(spawned, u8, 0x13),
                  first_mask_call_zero, mask);
    func_80042710(spawned, entity);
    FIELD(spawned, s32, 0x14) &= ~0x4000;

    FIELD(tail_dst, s32, 0x8C) = FIELD(base, s32, 0x8C);
    FIELD(tail_dst, s32, 0x90) = FIELD(base, s32, 0x90);
    FIELD(tail_dst, u16, 0x94) = FIELD(base, u16, 0x94);
    FIELD(tail_dst, u16, 0x98) = FIELD(base, u16, 0x98);
    FIELD(tail_dst, u8, 0x9A) = FIELD(base, u8, 0x9A);
    FIELD(tail_dst, u8, 0x9B) = FIELD(base, u8, 0x9B);

    offset = func_800A1BD0(entity);
    record = D_800814A8;
    offset = (offset << 16) >> 14;
    offset += (s32)record;
    record = (u8 *)offset;
    FIELD(record, u8 *, 0xAC) = spawned;
    func_8009A3D0(role1[0x24], role1[0x25], 0x300);
    func_8009A028(spawned);
    spawned -= 0x20;
    func_80044A50(spawned);
    first_value = 0x80000000;
    tail_zero = FIELD(spawned, s32, 0x10);
    ASM_SET(global_page);
    global_page = (u8 *)0x80080000;
    FIELD(spawned, s32, 0x10) = tail_zero | first_value;
    first_value = FIELD(entity, u16, -2);
    ASM_SET(mode_page);
    mode_page = (u8 *)0x800E0000;
    FIELD(entity, u16, -2) = first_value | 0x8000;
    first_value = FIELD(global_page, s32, 0x14A0);
    ASM_SET(tail_zero);
    tail_zero = 0;
    ASM_KEEP(tail_zero);
    FIELD(mode_page, s16, -0x30A2) = 0;
    FIELD(global_page, s32, 0x14A0) = first_value | 0x8000;
    return func_800A566C();

second_dispatch:
    if (FIELD(role1, s16, -0x30A2) == count) {
        goto second_equal;
    }
    if (FIELD(role1, s16, -0x30A2) < 2) {
        second_zero_delay = 0;
        if (FIELD(role1, s16, -0x30A2) == 0) {
            goto second_zero;
        }
        return func_800A566C();
    }
    if (FIELD(role1, s16, -0x30A2) == 2) {
        goto second_two;
    }
    return func_800A566C();

second_zero:
    ASM_KEEP(second_zero_delay);
    ASM_SET(second_zero_kind);
    second_zero_kind = 3;
    spawned = (u8 *)func_800A1618(FIELD(entity, u8, 0x13) - 1,
                                   second_zero_kind);
    if (spawned == NULL) {
        goto increment_mode;
    }
    FIELD(entity, u8, 0x13)--;
    func_8003E188(FIELD(entity, u8, 0x13), 0);
    D_80080A90 = D_80023000;
    D_80081488 = func_80048118(FIELD(entity, u8, 0x13), D_8008149C);
    func_800A0B94(FIELD(entity, u8, 0x13), spawned, 0);
    D_800E3E40[0] = 0;
    func_8003E4FC(0xFF, D_8003E140, D_800E3E40);
    return func_800A5448();

second_equal:
    if (D_800E3E40[0] == 0) {
        goto done;
    }
    if (D_80081488 != 0) {
        func_80047FF4(FIELD(entity, u8, 0x13), D_80081488);
    }

increment_mode:
    FIELD(role1, s16, -0x30A2) = (s16)((u16)FIELD(role1, s16, -0x30A2) + 1);
    return func_800A5668();

second_two:
    second_two_delay = 0;
    ASM_KEEP(second_two_delay);
    spawned = (u8 *)func_800A1618(FIELD(entity, u8, 0x13), 3);
    if (spawned == NULL) {
        goto done;
    }
    role1 = FIELD(entity, u8 *, -0x14);
    spawn = func_800A0B94(FIELD(entity, u8, 0x13), spawned, 1);
    spawned = spawn(1, role1[0x24], role1[0x25],
                    (s16)(FIELD(entity, u16, 0x88) - 0x20));
    if (spawned == NULL) {
        goto done;
    }
    FIELD(spawned, s32, 0x14) |= 0x4000;
    offset = func_800A1BD0(entity);
    record = D_800814A8;
    offset = (offset << 16) >> 14;
    offset += (s32)record;
    record = (u8 *)offset;
    record_data = FIELD(record, u8 *, 0xD0);
    FIELD(record, u8 *, 0xAC) = spawned;
    record_data[0] = FIELD(entity, u8, 0x13);
    FIELD(D_800E3DF0, u8 *, (record_data[3] & 0x1F) * 4) = spawned;

    role1 = FIELD(spawned, u8 *, -0x14);
    FIELD(role1, s16, 0x1E) = 0x1000;
    FIELD(role1, s16, 0x1C) = 0x1000;
    func_80042640(spawned, FIELD(spawned, u8, 0x13));
    second_mask_call_arg = spawned;
    second_mask_call_zero = 0;
    ASM_KEEP4_NV(second_mask_call_arg, second_mask_call_zero,
                 spawned, role1);
    mask = -8;
    FIELD(spawned, s32, 0x14) &= mask;
    FIELD(spawned, s32, 0x1C) &= mask;
    FIELD(spawned, s32, 0x14) |= FIELD(entity, s32, 0x14) & 7;
    FIELD(spawned, s32, 0x1C) |= FIELD(entity, s32, 0x1C) & 7;
    func_800424E0(second_mask_call_arg, FIELD(spawned, u8, 0x13),
                  second_mask_call_zero, mask);
    func_80042710(spawned, entity);

    if (FIELD(spawned, volatile u8, 0x43) < 0x40) {
        TablePage *page = (TablePage *)0x80010000;
        u8 index = FIELD(spawned, u8, 0x43);
        u8 value = FIELD(spawned, u8, 0x13);
        page->table84[index].value = value;
        page->table4[index].value = value;
    }
    func_800A152C(FIELD(spawned, u8, 0x13), 3);
    func_80042560(spawned);
    angle = FIELD(entity, u16, 0x2A);
    FIELD(spawned, u16, 0x2A) = angle;
    offset = ((D_80083228 + (s16)angle + 0x100) >> 9) & 7;
    func_80047738(role1, ((u8 *)FIELD(role1, void *, 0x2C))[offset],
                  FIELD(role1, s8, 4));
    role_flags = FIELD(role1, u16, 0x14);
    D_80080A90 = D_8014A000;
    FIELD(role1, u16, 0x14) = role_flags & 0xFFFE;
    remaining_count = FIELD(base, u16, 0xA);
    D_800DCF5C = count;
    FIELD(base, s16, 0xA) = (s16)(remaining_count - 1);
    FIELD(entity, u16, -2) |= 0x8000;
    global_flags = D_800814A0;
    FIELD(entity, s32, 0x90) = 0;
    D_800814A0 = global_flags | 0x8000;

done:
    return 0;
}
