#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_800E3D7C.h"

struct S_800E3E48 {
    u8 pad00[0x14];
    s32 unk14;
    u8 pad18[0x1C - 0x18];
    s32 unk1C;
    u8 pad20[0x8C - 0x20];
};
typedef struct S_800E3E48 S_800E3E48;

typedef struct {
    u8 bytes[4];
} Unaligned4;

extern volatile s16 D_80013714[8];
extern s32 D_800E3DF0[];
extern S_800E3E48 D_800E3E48[];
extern void *D_80010248[];
extern s32 D_800E3D74;
extern s16 D_800DCED4[];
extern u8 D_800E045C[];
extern M2C_UNK D_8001024B;
extern volatile u8 D_800121E0;
extern volatile u8 D_800121E1;

extern M2C_UNK func_80041E28();
extern M2C_UNK func_800424E0();
extern M2C_UNK func_80035208();
extern M2C_UNK func_80042560();
extern M2C_UNK func_80042640();
extern M2C_UNK func_80042984();
extern M2C_UNK func_800429E4();
extern M2C_UNK func_80094A64();
extern M2C_UNK func_80094AE8();
extern M2C_UNK func_80094B54();
extern M2C_UNK func_80094B94();
extern M2C_UNK func_80094BD0();
extern M2C_UNK func_800982A8();
extern M2C_UNK func_80098614();
extern s32 func_8009B88C();
extern void *(*func_800A0B94())(M2C_UNK, s16, s16, s16);
extern M2C_UNK func_800A152C();
extern s32 func_800A1618();
extern s32 func_800A4E2C();
extern M2C_UNK func_800A6A9C();
extern M2C_UNK func_800C542C();

typedef struct S_80094988_0 {
    u8 pad_00[0x2D50];
    u16 unk_2D50;
    u8 pad_2D52[0x6];
    s32 unk_2D58;
    u8 pad_2D5C[0x9B8];
    s16 unk_3714;
} S_80094988_0;   /* page in func_80094988 */

typedef struct S_80094988_1 {
    u8 pad_00[0xF8];
    u16 unk_F8;
    u8 pad_FA[0x2];
    s32 unk_FC;
} S_80094988_1;   /* dungeon in func_80094988 */

typedef struct S_80094988_2 {
    u8 pad_00[0x2238];
    u8 unk_2238;
    u8 pad_2239[0x13];
    u8 unk_224C;
} S_80094988_2;   /* src_ptr in func_80094988 */

typedef struct S_80094988_3 {
    s32 unk_00;
} S_80094988_3;   /* table_ptr in func_80094988 */

typedef struct S_80094988_4 {
    u8 pad_00[0x29C];
    s32 unk_29C;
} S_80094988_4;   /* save_page + scaled_i in func_80094988 */

typedef struct S_80094988_5 {
    u8 pad_00[0x2D52];
    u8 unk_2D52;
} S_80094988_5;   /* var_v1_2 in func_80094988 */

typedef struct S_80094988_6 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_80094988_6;   /* var_a0 in func_80094988 */

typedef struct S_80094988_7 {
    u8 pad_00[0x21E0];
    volatile u8 unk_21E0;
    volatile u8 unk_21E1;
} S_80094988_7;   /* (void *)probe in func_80094988 */

typedef struct S_80094988_8 {
    u8 pad_00[0x21E0];
    volatile u8 unk_21E0;
    volatile u8 unk_21E1;
} S_80094988_8;   /* dispatch_ptr in func_80094988 */

typedef struct S_80094988_9_pre {
    u8 unk_00;
    u8 pad_01[0x1];
} S_80094988_9_pre;   /* the 0x2 bytes before slot_flags in func_80094988, addressed as slot_flags[-1] */

typedef struct S_80094988_9 {
    u8 unk_00;
} S_80094988_9;   /* slot_flags in func_80094988 */

typedef struct S_80094988_10 {
    u8 pad_00[0xD0];
    s32 unk_D0;
} S_80094988_10;   /* cursor in func_80094988 */


typedef struct S_80094988_12 {
    u8 pad_00[0xAC];
    void * unk_AC;
    u8 pad_B0[0x20];
    void ** unk_D0;
} S_80094988_12;   /* slot_rec in func_80094988 */

typedef struct S_80094988_13 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
} S_80094988_13;   /* spawned in func_80094988 */

typedef struct S_80094988_14 {
    s32 unk_00;
} S_80094988_14;   /* addr_hold in func_80094988 */

typedef struct S_80094988_15 {
    u8 pad_00[0x3714];
    s16 unk_3714;
} S_80094988_15;   /* save_page in func_80094988 */

/* Rebuild the dungeon's slot tables from the 0x80010000 save page: relink each of the 0x14 entries with its 0x8C record, re-point the two dispatch slots, then spawn and register an actor for every flagged party member. */
void func_80094988(S_80094988_1 *dungeon, Rec_D_800E3D7C *actor, u16 base_x, u16 base_y) {
    s16 place_x;
    s16 place_y;
    u8 rand_x;
    u8 rand_y;
    u16 spawn_x;
    u16 spawn_y;
    u16 flag_was_set;
    u8 *slot_flags;
    u8 *page_base;
    u8 *entry_dst;
    u8 *tile_ptr;
    u8 *src_ptr;
    register u8 *rec_src ASM_REG("$12");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *table_ptr;
    s32 kind;
    u32 scratch;
    s32 slot_i;
    s32 i;
    register s32 probe_i ASM_REG("$9");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    u8 *slot_ptr;
    S_80094988_12 *slot_rec;
    S_80094988_13 *spawned;
    void *cursor;
    u8 *cursor_ptr;
    s16 entry_idx;
    u32 entry_idx32;
    void *entry_addr;
    s32 ff;
    register u8 *addr_hold ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *save_page;
    void **dispatch_table;
    s32 ff2;
    s32 scaled_i;
    register u32 probe ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    u8 *dispatch_ptr;
    u32 dispatch_slot;
    s32 sign_shift;   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    s32 slot_index;
    s32 slot_offset;

    cursor_ptr = (u8 *)0x80010000;
    flag_was_set = (s16)((S_80094988_0 *)cursor_ptr)->unk_3714 & 2;
    ((S_80094988_0 *)cursor_ptr)->unk_3714 =
        (s16)((u16)((S_80094988_0 *)cursor_ptr)->unk_3714 | 2);
    spawn_x = base_x;
    spawn_y = base_y;
    func_800A6A9C();
    func_80041E28(actor, (s32)cursor_ptr | 0x2194);
    i = 0;
    ff = 0xFF;
    do {
        addr_hold = (u8 *)0x800E0000;
    } while (0);
    table_ptr = D_800E3DF0;
    src_ptr = cursor_ptr;
    rec_src = src_ptr;
    addr_hold = (u8 *)0x800E0000;
    ASM_KEEP(addr_hold);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    scratch = (u32)(addr_hold + 0x3E48);
    entry_dst = (u8 *)scratch;
    dungeon->unk_F8 = (u16)((S_80094988_0 *)cursor_ptr)->unk_2D50;
    tile_ptr = src_ptr;
    dungeon->unk_FC = (s32)((S_80094988_0 *)cursor_ptr)->unk_2D58;

loop_1:
    (*(Unaligned4 *)((u8 *)tile_ptr + 0x248)) =
        (*(Unaligned4 *)((u8 *)tile_ptr + 0x21E8));
    cursor_ptr = (u8 *)(((S_80094988_2 *)src_ptr)->unk_2238);
    if (((u8)cursor_ptr) != ff) {
        (*(s32 *)((u8 *)tile_ptr + 0x29C)) =
            (s32)((void **)0x80010248 + ((u8)cursor_ptr));
    } else {
        (*(s32 *)((u8 *)tile_ptr + 0x29C)) = 0;
    }
    (*(S_800E3E48 *)((u8 *)entry_dst + 0)) =
        (*(S_800E3E48 *)((u8 *)rec_src + 0x2260));
    entry_idx = ((S_80094988_2 *)src_ptr)->unk_224C;
    if (entry_idx != ff) {
        entry_idx32 = entry_idx;
        entry_addr = (void *)((u32)(entry_idx32 * sizeof(S_800E3E48)) +
                             (u32)scratch);
        ((S_80094988_3 *)table_ptr)->unk_00 = (s32)entry_addr;
        table_ptr += 4;
        src_ptr += 1;
        rec_src += 0x8C;
    } else {
        ((S_80094988_3 *)table_ptr)->unk_00 = 0;
        table_ptr += 4;
        src_ptr += 1;
        rec_src += 0x8C;
    }
    entry_dst += 0x8C;
    i += 1;
    tile_ptr += 4;
    if (i < 0x14) {
        goto loop_1;
    }

    save_page = (u8 *)0x80010000;
    scaled_i = i * 4;
    ((S_80094988_4 *)(save_page + scaled_i))->unk_29C = 0;
    i = 0;
    page_base = save_page;
    ff2 = 0xFF;
    dispatch_table = (void **)(save_page + 0x248);
    dispatch_ptr = dungeon;
    loop_0: {
        entry_idx32 = (s32)((u8 *)(i + (u32)page_base));
        cursor_ptr = (u8 *)(((S_80094988_5 *)(u8 *)entry_idx32)->unk_2D52);
        if (((u8)cursor_ptr) != ff2) {
            ((S_80094988_6 *)dispatch_ptr)->unk_D0 =
                (s32)((((u8)cursor_ptr) * 4) + (u32)dispatch_table);
        } else {
            ((S_80094988_6 *)dispatch_ptr)->unk_D0 = 0;
        }
        i += 1;
        dispatch_ptr += 4;
    } if (i < 2) goto loop_0;

    probe = 0x80010000;
    probe = ((S_80094988_7 *)((void *)probe))->unk_21E0;
    if (probe != 0xFF) {
        dispatch_ptr = (u8 *)0x80010000;
        probe = (u32)dispatch_ptr;
        dispatch_slot = ((S_80094988_8 *)dispatch_ptr)->unk_21E0;
        probe |= 0x248;
        dispatch_slot <<= 2;
        slot_ptr = (u8 *)(dispatch_slot + probe);
    } else {
        slot_ptr = NULL;
    }
    func_800982A8(actor, slot_ptr);
    probe = 0x80010000;
    probe = ((S_80094988_7 *)((void *)probe))->unk_21E1;
    if (probe != 0xFF) {
        dispatch_ptr = (u8 *)0x80010000;
        probe = (u32)dispatch_ptr;
        dispatch_slot = ((S_80094988_8 *)dispatch_ptr)->unk_21E1;
        probe |= 0x248;
        dispatch_slot <<= 2;
        slot_ptr = (u8 *)(dispatch_slot + probe);
    } else {
        slot_ptr = NULL;
    }
    func_80098614(actor, slot_ptr);
    slot_ptr = (u8 *)0x80010248;
    slot_i = 0;
    slot_flags = (u8 *)0x8001024B;
            do {
                if (((S_80094988_9_pre *)slot_flags)[-1].unk_00 == 0x13) {
                    probe_i = 0;
                    if (((S_80094988_9 *)slot_flags)->unk_00 & 0x20) {
                        scratch = 0;
                        cursor = dungeon;
                        loop_1_: {
                            if (((S_80094988_10 *)cursor)->unk_D0 == slot_ptr) {
                                scratch = probe_i + 1;
                            }
                            probe_i += 1;
                            cursor += 4;
                        } if (probe_i < 2) goto loop_1_;
                        if ((scratch << 0x10) != 0) {
                            scratch -= 1;
                            kind = func_800A1618(*slot_ptr, 3);
                            if (kind != 0) {
                                if ((func_8009B88C(0, (s16)spawn_x, (s16)spawn_y,
                                                   &place_x, &place_y) << 0x10) == 0) {
                                    do {
                                    } while ((func_800A4E2C(&rand_x, &rand_y) << 16) < 0);
                                    place_x = (s16)rand_x;
                                    place_y = (s16)rand_y;
                                }
                                spawned = func_800A0B94(*slot_ptr, kind, 1)(
                                    1, place_x, place_y,
                                    actor->unk_88.as_s16);
                                sign_shift = scratch << 16;
                                slot_index = sign_shift >> 16;
                                slot_offset = slot_index * 4;
                                slot_rec = (void *)((u32)slot_offset +
                                                     (u32)dungeon);
                                slot_rec->unk_AC = spawned;
                                if (spawned != NULL) {
                                    func_80042640(spawned,
                                                  spawned->unk_13);
                                    func_800424E0(spawned,
                                                  spawned->unk_13,
                                                  slot_ptr);
                                    slot_rec->unk_D0 = slot_ptr;
                                    ((S_80094988_9 *)slot_flags)->unk_00 =
                                        (u8)(((S_80094988_9 *)slot_flags)->unk_00 | 0x20);
                                    addr_hold =
                                        (u8 *)&D_800E3D74 + slot_offset;
                                    ((S_80094988_14 *)addr_hold)->unk_00 = 0;
                                    if (spawned->unk_25 == 0) {
                                        spawned->unk_1C =
                                            (s32)(spawned->unk_1C | 8);
                                    }
                                    D_800E3DF0[((S_80094988_9 *)slot_flags)->unk_00 & 0x1F] =
                                        (s32)spawned;
                                    func_80042984(spawned);
                                    func_800A152C(*slot_ptr, 3);
                                    func_80042560(spawned);
                                    func_800C542C(
                                        spawned,
                                        D_800DCED4[func_800429E4(spawned)],
                                        slot_index, 1);
                                }
                            }
                        }
                    }
                }
                slot_i += 1;
                slot_flags += 4;
                slot_ptr += 4;
            } while (slot_i < 0x14);
            if (flag_was_set == 0) {
                save_page = (u8 *)0x80010000;
                ((S_80094988_15 *)save_page)->unk_3714 =
                    (s16)((u16)((S_80094988_15 *)save_page)->unk_3714 & 0xFFFD);
            }
            func_80035208(D_800E045C);
            return;
}
