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
    register u8 *entity ASM_REG("$19") = arg1;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *base = (u8 *)&D_80083460;
    s32 count = ((S_800A504C_0 *)base)->unk_0A.s;
    s32 offset;
    s32 saved5c;
    s32 saved58;
    s32 angle;
    s32 global_flags;
    u16 role_flags;
    u16 remaining_count;
    u32 call_index;
    register s32 mask ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 first_value ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    register s32 tail_zero ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *global_page;
    register u8 *mode_page ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register u8 *first_mask_call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 first_mask_call_zero;
    s32 first_store_value;
    register u8 *second_mask_call_arg ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 second_mask_call_zero ASM_REG("$6");   /* UNRESOLVED C shape (pin): removing it changes the callee-saved set / frame layout; the source shape that makes it unnecessary has not been found */
    register s32 second_zero_delay ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 second_zero_kind;
    register s32 first_zero_delay ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 first_two_delay;
    register s32 second_two_delay ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    u8 *spawned;
    register u8 *role1 ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
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

    role1 = (u8 *)0x800E0000;
    if (!(((S_800A504C_1 *)entity)->unk_14 & 0x4000)) {
        goto second_dispatch;
    }
    if (((S_800A504C_2_pre *)role1)[-1].unk_00 == count) {
        goto first_equal;
    }
    if (((S_800A504C_2_pre *)role1)[-1].unk_00 < 2) {
        if (((S_800A504C_2_pre *)role1)[-1].unk_00 == 0) {
            goto first_zero;
        }
        return func_800A566C();
    }
    if (((S_800A504C_2_pre *)role1)[-1].unk_00 == 2) {
        goto first_two;
    }
    return func_800A566C();

first_zero:
    first_zero_delay = 0;
    ASM_KEEP(first_zero_delay);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    if (func_80053EF0(4) != 0) {
        return 0;
    }
    spawned = (u8 *)func_800A1618(((S_800A504C_1 *)entity)->unk_13, 2);
    if (spawned == NULL) {
        return 0;
    }
    call_index = ((S_800A504C_1 *)entity)->unk_13;
    func_80047DB8(call_index);
    ASM_SET(call_index);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    return func_800A53E0(call_index, spawned);

first_equal:
    if (D_800E3E40[0] != 0) {
        func_80047E30();
        return func_800A5448();
    }
    return 0;

first_two:
    first_two_delay = 0;
    ASM_KEEP(first_two_delay);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    spawned = (u8 *)func_800A1618(((S_800A504C_1 *)entity)->unk_13, 2);
    if (spawned == NULL) {
        goto done;
    }
    role1 = ((S_800A504C_1_pre *)entity)[-1].unk_00;
    spawn = func_800A0B94(((S_800A504C_1 *)entity)->unk_13, spawned, 1);
    spawned = spawn(6, role1[0x24], role1[0x25],
                    (s16)(((S_800A504C_1 *)entity)->unk_88 - 0x20));
    if (spawned == NULL) {
        goto done;
    }
    base = entity;
    tail_dst = spawned;
    ASM_KEEP4_NV(base, tail_dst, entity, spawned);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    saved5c = ((S_800A504C_3 *)tail_dst)->unk_5C;
    saved58 = ((S_800A504C_3 *)tail_dst)->unk_58;
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
    ((S_800A504C_4 *)spawned)->unk_5C = saved5c;
    ((S_800A504C_4 *)spawned)->unk_58 = saved58;
    func_80042640(spawned, ((S_800A504C_4 *)spawned)->unk_10.at03.v);

    first_mask_call_arg = spawned;
    first_mask_call_zero = 0;
    first_store_value = 0x1000;
    ASM_KEEP4_NV(first_mask_call_arg, first_mask_call_zero,
                 first_store_value, spawned);
    role1 = ((S_800A504C_4_pre *)spawned)[-1].unk_00;
    ASM_SET(mask);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ((S_800A504C_2 *)role1)->unk_1C = first_store_value;
    ((S_800A504C_2 *)role1)->unk_1E = first_store_value;
    mask = -8;
    ((S_800A504C_4 *)spawned)->unk_14 &= mask;
    ((S_800A504C_4 *)spawned)->unk_1C &= mask;
    ((S_800A504C_4 *)spawned)->unk_14 |= ((S_800A504C_1 *)entity)->unk_14 & 7;
    ((S_800A504C_4 *)spawned)->unk_1C |= ((S_800A504C_1 *)entity)->unk_1C & 7;
    func_800424E0(first_mask_call_arg, ((S_800A504C_4 *)spawned)->unk_10.at03.v,
                  first_mask_call_zero, mask);
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
    func_8009A3D0(role1[0x24], role1[0x25], 0x300);
    func_8009A028(spawned);
    spawned -= 0x20;
    func_80044A50(spawned);
    first_value = 0x80000000;
    tail_zero = ((S_800A504C_4 *)spawned)->unk_10.at00.v;
    global_page = (u8 *)0x80080000;
    ((S_800A504C_4 *)spawned)->unk_10.at00.v = tail_zero | first_value;
    first_value = ((S_800A504C_1_pre *)entity)[-1].unk_12;
    ASM_SET(mode_page);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    mode_page = (u8 *)0x800E0000;
    ((S_800A504C_1_pre *)entity)[-1].unk_12 = first_value | 0x8000;
    first_value = ((S_800A504C_6 *)global_page)->unk_14A0;
    ASM_SET(tail_zero);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    tail_zero = 0;
    ASM_KEEP(tail_zero);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ((S_800A504C_7_pre *)mode_page)[-1].unk_00 = 0;
    ((S_800A504C_6 *)global_page)->unk_14A0 = first_value | 0x8000;
    return func_800A566C();

second_dispatch:
    if (((S_800A504C_2_pre *)role1)[-1].unk_00 == count) {
        goto second_equal;
    }
    if (((S_800A504C_2_pre *)role1)[-1].unk_00 < 2) {
        second_zero_delay = 0;
        if (((S_800A504C_2_pre *)role1)[-1].unk_00 == 0) {
            goto second_zero;
        }
        return func_800A566C();
    }
    if (((S_800A504C_2_pre *)role1)[-1].unk_00 == 2) {
        goto second_two;
    }
    return func_800A566C();

second_zero:
    ASM_KEEP(second_zero_delay);   /* UNRESOLVED C shape (pin): removing it drops a computation retail keeps; the source shape that makes it unnecessary has not been found */
    second_zero_kind = 3;
    spawned = (u8 *)func_800A1618(((S_800A504C_1 *)entity)->unk_13 - 1,
                                   second_zero_kind);
    if (spawned == NULL) {
        goto increment_mode;
    }
    ((S_800A504C_1 *)entity)->unk_13--;
    func_8003E188(((S_800A504C_1 *)entity)->unk_13, 0);
    D_80080A90 = D_80023000;
    D_80081488 = func_80048118(((S_800A504C_1 *)entity)->unk_13, D_8008149C);
    func_800A0B94(((S_800A504C_1 *)entity)->unk_13, spawned, 0);
    D_800E3E40[0] = 0;
    func_8003E4FC(0xFF, D_8003E140, D_800E3E40);
    return func_800A5448();

second_equal:
    if (D_800E3E40[0] == 0) {
        goto done;
    }
    if (D_80081488 != 0) {
        func_80047FF4(((S_800A504C_1 *)entity)->unk_13, D_80081488);
    }

increment_mode:
    ((S_800A504C_2_pre *)role1)[-1].unk_00 = (s16)((u16)((S_800A504C_2_pre *)role1)[-1].unk_00 + 1);
    return func_800A5668();

second_two:
    second_two_delay = 0;
    ASM_KEEP(second_two_delay);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
    spawned = (u8 *)func_800A1618(((S_800A504C_1 *)entity)->unk_13, 3);
    if (spawned == NULL) {
        goto done;
    }
    role1 = ((S_800A504C_1_pre *)entity)[-1].unk_00;
    spawn = func_800A0B94(((S_800A504C_1 *)entity)->unk_13, spawned, 1);
    spawned = spawn(1, role1[0x24], role1[0x25],
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

    role1 = ((S_800A504C_4_pre *)spawned)[-1].unk_00;
    ((S_800A504C_2 *)role1)->unk_1E = 0x1000;
    ((S_800A504C_2 *)role1)->unk_1C = 0x1000;
    func_80042640(spawned, ((S_800A504C_4 *)spawned)->unk_10.at03.v);
    second_mask_call_arg = spawned;
    second_mask_call_zero = 0;
    ASM_KEEP4_NV(second_mask_call_arg, second_mask_call_zero,
                 spawned, role1);
    mask = -8;
    ((S_800A504C_4 *)spawned)->unk_14 &= mask;
    ((S_800A504C_4 *)spawned)->unk_1C &= mask;
    ((S_800A504C_4 *)spawned)->unk_14 |= ((S_800A504C_1 *)entity)->unk_14 & 7;
    ((S_800A504C_4 *)spawned)->unk_1C |= ((S_800A504C_1 *)entity)->unk_1C & 7;
    func_800424E0(second_mask_call_arg, ((S_800A504C_4 *)spawned)->unk_10.at03.v,
                  second_mask_call_zero, mask);
    func_80042710(spawned, entity);

    if (((S_800A504C_4 *)spawned)->unk_43.v < 0x40) {
        TablePage *page = (TablePage *)0x80010000;
        u8 index = ((S_800A504C_4 *)spawned)->unk_43.n;
        u8 value = ((S_800A504C_4 *)spawned)->unk_10.at03.v;
        page->table84[index].value = value;
        page->table4[index].value = value;
    }
    func_800A152C(((S_800A504C_4 *)spawned)->unk_10.at03.v, 3);
    func_80042560(spawned);
    angle = ((S_800A504C_1 *)entity)->unk_2A;
    (*(u16 *)((u8 *)spawned + 0x2A)) = angle;
    offset = ((D_80083228 + (s16)angle + 0x100) >> 9) & 7;
    func_80047738(role1, ((u8 *)((S_800A504C_2 *)role1)->unk_2C)[offset],
                  ((S_800A504C_2 *)role1)->unk_04);
    role_flags = ((S_800A504C_2 *)role1)->unk_14;
    D_80080A90 = D_8014A000;
    ((S_800A504C_2 *)role1)->unk_14 = role_flags & 0xFFFE;
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
