#include "common.h"

#ifndef NULL
#define NULL 0
#endif


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

typedef struct S_800A504C_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x80];
    s32 unk_8C;
    s32 unk_90;
    u16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_800A504C_0;   /* base in func_800A504C */

typedef struct S_800A504C_1_pre {
    u8 * unk_00;
    u8 pad_04[0xE];
    u16 unk_12;
} S_800A504C_1_pre;   /* the 0x14 bytes before entity in func_800A504C, addressed as entity[-1] */

typedef struct S_800A504C_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    u16 unk_88;
    u8 pad_8A[0x6];
    s32 unk_90;
} S_800A504C_1;   /* entity in func_800A504C */

typedef struct S_800A504C_2_pre {
    s16 unk_00;
    u8 pad_02[0x30A0];
} S_800A504C_2_pre;   /* the 0x30A2 bytes before role1 in func_800A504C, addressed as role1[-1] */

typedef struct S_800A504C_2 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0xF];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    void * unk_2C;
} S_800A504C_2;   /* role1 in func_800A504C */

typedef struct S_800A504C_3 {
    u8 pad_00[0x58];
    s32 unk_58;
    s32 unk_5C;
    u8 pad_60[0x2C];
    s32 unk_8C;
    s32 unk_90;
    u16 unk_94;
    u8 pad_96[0x2];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_800A504C_3;   /* tail_dst in func_800A504C */

typedef struct S_800A504C_4_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_800A504C_4_pre;   /* the 0x14 bytes before spawned in func_800A504C, addressed as spawned[-1] */

typedef struct S_800A504C_4 {
    u8 pad_00[0x10];
    union { struct { s32 v; } at00; struct { u8 pad[0x3]; u8 v; } at03; } unk_10;   /* overlapping accesses */
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x23];
    union { volatile u8 v; u8 n; } unk_43;   /* accessed as both */
    u8 pad_44[0x8];
    s32 unk_4C;
    s32 unk_50;
    u8 pad_54[0x4];
    s32 unk_58;
    s32 unk_5C;
} S_800A504C_4;   /* spawned in func_800A504C */

typedef struct S_800A504C_5 {
    u8 pad_00[0xAC];
    u8 * unk_AC;
    u8 pad_B0[0x20];
    u8 * unk_D0;
} S_800A504C_5;   /* record in func_800A504C */

typedef struct S_800A504C_6 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} S_800A504C_6;   /* global_page in func_800A504C */

typedef struct S_800A504C_7_pre {
    s16 unk_00;
    u8 pad_02[0x30A0];
} S_800A504C_7_pre;   /* the 0x30A2 bytes before mode_page in func_800A504C, addressed as mode_page[-1] */


extern s32 func_8003E188();
extern s32 Control_CD();
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

/* Advances staged entity loading and replaces the entity while transferring its state. */
s32 func_800A504C(s32 unused, void *source_entity)
{
    register u8 *entity ASM_REG("$19") = source_entity;
    u8 *base = (u8 *)&D_80083460;
    s32 count = ((S_800A504C_0 *)base)->unk_0A.s;
    s32 offset;
    register s32 load_result ASM_REG("$2");
    register u8 *load_spawned ASM_REG("$5");
    s32 saved_word_5c;
    s32 saved_word_58;
    s32 angle;
    s32 global_flags;
    u16 data_flags;
    u16 remaining_count;
    u32 entity_id;
    register s32 flags_mask ASM_REG("$7");
    register s32 update_flags ASM_REG("$3");
    register s32 flags_result ASM_REG("$2");
    u8 *global_page;
    register u8 *mode_page ASM_REG("$4");
    register u8 *copy_call_entity ASM_REG("$4");
    s32 copy_call_zero;
    s32 scale;
    register u8 *replace_call_entity ASM_REG("$4");
    register s32 replace_call_zero ASM_REG("$6");
    s32 load_kind;
    u8 *spawned;
    u8 *entity_data;
    u8 *record;
    u8 *record_data;
    u8 *tail_dst;
    u8 *copy_src;
    u8 *copy_dst;
    u8 *copy_end;
    SpawnFunc spawn;

    if (count != 1) {
        goto done;
    }
    if (func_8003FA44(8) == 0) {
        return 0;
    }

    entity_data = (u8 *)0x800E0000;
    if (!(((S_800A504C_1 *)entity)->unk_14 & 0x4000)) {
        goto dispatch_replace;
    }
    if (((S_800A504C_2_pre *)entity_data)[-1].unk_00 == count) {
        goto wait_copy;
    }
    if (((S_800A504C_2_pre *)entity_data)[-1].unk_00 < 2) {
        if (((S_800A504C_2_pre *)entity_data)[-1].unk_00 == 0) {
            goto load_copy;
        }
        return 0;
    }
    if (((S_800A504C_2_pre *)entity_data)[-1].unk_00 == 2) {
        goto spawn_copy;
    }
    return 0;

load_copy:
    if (func_80053EF0(4) != 0) {
        return 0;
    }
    spawned = (u8 *)func_800A1618(((S_800A504C_1 *)entity)->unk_13, 2);
    if (spawned == NULL) {
        return 0;
    }
    entity_id = ((S_800A504C_1 *)entity)->unk_13;
    load_result = func_80047DB8(entity_id);
    load_spawned = spawned;
    goto start_loading;

wait_copy:
    if (D_800E3E40[0] != 0) {
        func_80047E30();
        goto increment_mode;
    }
    return 0;

spawn_copy:
    spawned = (u8 *)func_800A1618(((S_800A504C_1 *)entity)->unk_13, 2);
    if (spawned == NULL) {
        goto done;
    }
    entity_data = ((S_800A504C_1_pre *)entity)[-1].unk_00;
    spawn = func_800A0B94(((S_800A504C_1 *)entity)->unk_13, spawned, 1);
    spawned = spawn(6, entity_data[0x24], entity_data[0x25],
                    (s16)(((S_800A504C_1 *)entity)->unk_88 - 0x20));
    if (spawned == NULL) {
        goto done;
    }
    base = entity;
    tail_dst = spawned;
    ASM_KEEP4_NV(base, tail_dst, entity, spawned);
    saved_word_5c = ((S_800A504C_3 *)tail_dst)->unk_5C;
    saved_word_58 = ((S_800A504C_3 *)tail_dst)->unk_58;
    copy_dst = tail_dst;
    copy_src = entity;
    copy_end = entity + 0x80;
    do {
        *(EntityCopyBlock *)copy_dst = *(EntityCopyBlock *)copy_src;
        copy_src += sizeof(EntityCopyBlock);
        copy_dst += sizeof(EntityCopyBlock);
    } while (copy_src != copy_end);
    *(EntityCopyTail *)copy_dst = *(EntityCopyTail *)copy_src;
    ((S_800A504C_4 *)spawned)->unk_4C = 0;
    ((S_800A504C_4 *)spawned)->unk_50 = 0;
    ((S_800A504C_4 *)spawned)->unk_5C = saved_word_5c;
    ((S_800A504C_4 *)spawned)->unk_58 = saved_word_58;
    func_80042640(spawned, ((S_800A504C_4 *)spawned)->unk_10.at03.v);

    copy_call_entity = spawned;
    copy_call_zero = 0;
    scale = 0x1000;
    ASM_KEEP4_NV(copy_call_entity, copy_call_zero,
                 scale, spawned);
    entity_data = ((S_800A504C_4_pre *)spawned)[-1].unk_00;
    ASM_SET(flags_mask);
    ((S_800A504C_2 *)entity_data)->unk_1C = scale;
    ((S_800A504C_2 *)entity_data)->unk_1E = scale;
    flags_mask = -8;
    ((S_800A504C_4 *)spawned)->unk_14 &= flags_mask;
    ((S_800A504C_4 *)spawned)->unk_1C &= flags_mask;
    ((S_800A504C_4 *)spawned)->unk_14 |= ((S_800A504C_1 *)entity)->unk_14 & 7;
    ((S_800A504C_4 *)spawned)->unk_1C |= ((S_800A504C_1 *)entity)->unk_1C & 7;
    func_800424E0(copy_call_entity, ((S_800A504C_4 *)spawned)->unk_10.at03.v,
                  copy_call_zero, flags_mask);
    func_80042710(spawned, entity);
    ((S_800A504C_4 *)spawned)->unk_14 &= ~0x4000;

    ((S_800A504C_3 *)tail_dst)->unk_8C = ((S_800A504C_0 *)base)->unk_8C;
    ((S_800A504C_3 *)tail_dst)->unk_90 = ((S_800A504C_0 *)base)->unk_90;
    ((S_800A504C_3 *)tail_dst)->unk_94 = ((S_800A504C_0 *)base)->unk_94;
    ((S_800A504C_3 *)tail_dst)->unk_98 = ((S_800A504C_0 *)base)->unk_98;
    ((S_800A504C_3 *)tail_dst)->unk_9A = ((S_800A504C_0 *)base)->unk_9A;
    ((S_800A504C_3 *)tail_dst)->unk_9B = ((S_800A504C_0 *)base)->unk_9B;

    offset = func_800A1BD0(entity);
    record = D_800814A8;
    offset = (offset << 16) >> 14;
    offset += (s32)record;
    record = (u8 *)offset;
    ((S_800A504C_5 *)record)->unk_AC = spawned;
    func_8009A3D0(entity_data[0x24], entity_data[0x25], 0x300);
    func_8009A028(spawned);
    spawned -= 0x20;
    func_80044A50(spawned);
    update_flags = 0x80000000;
    flags_result = ((S_800A504C_4 *)spawned)->unk_10.at00.v;
    global_page = (u8 *)0x80080000;
    ((S_800A504C_4 *)spawned)->unk_10.at00.v = flags_result | update_flags;
    update_flags = ((S_800A504C_1_pre *)entity)[-1].unk_12;
    ASM_SET(mode_page);
    mode_page = (u8 *)0x800E0000;
    ((S_800A504C_1_pre *)entity)[-1].unk_12 = update_flags | 0x8000;
    update_flags = ((S_800A504C_6 *)global_page)->unk_14A0;
    ASM_SET(flags_result);
    flags_result = 0;
    ((S_800A504C_7_pre *)mode_page)[-1].unk_00 = 0;
    ((S_800A504C_6 *)global_page)->unk_14A0 = update_flags | 0x8000;
    return flags_result;

dispatch_replace:
    if (((S_800A504C_2_pre *)entity_data)[-1].unk_00 == count) {
        goto wait_replacement;
    }
    if (((S_800A504C_2_pre *)entity_data)[-1].unk_00 < 2) {
        if (((S_800A504C_2_pre *)entity_data)[-1].unk_00 == 0) {
            goto load_replacement;
        }
        return 0;
    }
    if (((S_800A504C_2_pre *)entity_data)[-1].unk_00 == 2) {
        goto spawn_replacement;
    }
    return 0;

load_replacement:
    load_kind = 3;
    spawned = (u8 *)func_800A1618(((S_800A504C_1 *)entity)->unk_13 - 1,
                                   load_kind);
    if (spawned == NULL) {
        goto increment_mode;
    }
    ((S_800A504C_1 *)entity)->unk_13--;
    func_8003E188(((S_800A504C_1 *)entity)->unk_13, 0);
    D_80080A90 = D_80023000;
    load_result = func_80048118(((S_800A504C_1 *)entity)->unk_13, D_8008149C);
    load_spawned = spawned;

start_loading:
    D_80081488 = load_result;
    func_800A0B94(((S_800A504C_1 *)entity)->unk_13, load_spawned, 0);
    D_800E3E40[0] = 0;
    Control_CD(0xFF, D_8003E140, D_800E3E40);
    goto increment_mode;

wait_replacement:
    if (D_800E3E40[0] == 0) {
        goto done;
    }
    if (D_80081488 != 0) {
        func_80047FF4(((S_800A504C_1 *)entity)->unk_13, D_80081488);
    }

increment_mode:
    ((S_800A504C_2_pre *)entity_data)[-1].unk_00 = (s16)((u16)((S_800A504C_2_pre *)entity_data)[-1].unk_00 + 1);
    goto done;

spawn_replacement:
    spawned = (u8 *)func_800A1618(((S_800A504C_1 *)entity)->unk_13, 3);
    if (spawned == NULL) {
        goto done;
    }
    entity_data = ((S_800A504C_1_pre *)entity)[-1].unk_00;
    spawn = func_800A0B94(((S_800A504C_1 *)entity)->unk_13, spawned, 1);
    spawned = spawn(1, entity_data[0x24], entity_data[0x25],
                    (s16)(((S_800A504C_1 *)entity)->unk_88 - 0x20));
    if (spawned == NULL) {
        goto done;
    }
    ((S_800A504C_4 *)spawned)->unk_14 |= 0x4000;
    offset = func_800A1BD0(entity);
    record = D_800814A8;
    offset = (offset << 16) >> 14;
    offset += (s32)record;
    record = (u8 *)offset;
    record_data = ((S_800A504C_5 *)record)->unk_D0;
    ((S_800A504C_5 *)record)->unk_AC = spawned;
    record_data[0] = ((S_800A504C_1 *)entity)->unk_13;
    (*(u8 * *)((u8 *)D_800E3DF0 + (record_data[3] & 0x1F) * 4)) = spawned;

    entity_data = ((S_800A504C_4_pre *)spawned)[-1].unk_00;
    ((S_800A504C_2 *)entity_data)->unk_1E = 0x1000;
    ((S_800A504C_2 *)entity_data)->unk_1C = 0x1000;
    func_80042640(spawned, ((S_800A504C_4 *)spawned)->unk_10.at03.v);
    replace_call_entity = spawned;
    replace_call_zero = 0;
    ASM_KEEP4_NV(replace_call_entity, replace_call_zero,
                 spawned, entity_data);
    flags_mask = -8;
    ((S_800A504C_4 *)spawned)->unk_14 &= flags_mask;
    ((S_800A504C_4 *)spawned)->unk_1C &= flags_mask;
    ((S_800A504C_4 *)spawned)->unk_14 |= ((S_800A504C_1 *)entity)->unk_14 & 7;
    ((S_800A504C_4 *)spawned)->unk_1C |= ((S_800A504C_1 *)entity)->unk_1C & 7;
    func_800424E0(replace_call_entity, ((S_800A504C_4 *)spawned)->unk_10.at03.v,
                  replace_call_zero, flags_mask);
    func_80042710(spawned, entity);

    if (((S_800A504C_4 *)spawned)->unk_43.v < 0x40) {
        TablePage *table_page = (TablePage *)0x80010000;
        u8 table_index = ((S_800A504C_4 *)spawned)->unk_43.n;
        u8 table_value = ((S_800A504C_4 *)spawned)->unk_10.at03.v;
        table_page->table84[table_index].value = table_value;
        table_page->table4[table_index].value = table_value;
    }
    func_800A152C(((S_800A504C_4 *)spawned)->unk_10.at03.v, 3);
    func_80042560(spawned);
    angle = ((S_800A504C_1 *)entity)->unk_2A;
    (*(u16 *)((u8 *)spawned + 0x2A)) = angle;
    offset = ((D_80083228 + (s16)angle + 0x100) >> 9) & 7;
    func_80047738(entity_data, ((u8 *)((S_800A504C_2 *)entity_data)->unk_2C)[offset],
                  ((S_800A504C_2 *)entity_data)->unk_04);
    data_flags = ((S_800A504C_2 *)entity_data)->unk_14;
    D_80080A90 = D_8014A000;
    ((S_800A504C_2 *)entity_data)->unk_14 = data_flags & 0xFFFE;
    remaining_count = ((S_800A504C_0 *)base)->unk_0A.u;
    D_800DCF5C = count;
    ((S_800A504C_0 *)base)->unk_0A.s = (s16)(remaining_count - 1);
    (*(u16 *)((u8 *)entity + -2)) |= 0x8000;
    global_flags = D_800814A0;
    ((S_800A504C_1 *)entity)->unk_90 = 0;
    D_800814A0 = global_flags | 0x8000;

done:
    return 0;
}
