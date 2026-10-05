#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

typedef struct S_800BE6F0_0_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0xE];
    u16 unk_16;
} S_800BE6F0_0_pre;   /* the 0x18 bytes before arg0 in func_800BE6F0, addressed as arg0[-1] */


typedef struct S_800BE6F0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BE6F0_1;   /* record1 in func_800BE6F0 */

typedef struct S_800BE6F0_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_800BE6F0_3;   /* record2 in func_800BE6F0 */

typedef struct S_800BE6F0_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800BE6F0_5;   /* state_base2 in func_800BE6F0 */


s32 func_80042900();
s32 func_8008D330();
s32 func_80098B38();
s32 func_800990FC();
s32 func_80099194();
s32 func_80099290();
s32 func_80099368();
s32 func_80099734();
s32 func_8009A028();
s32 func_8009A3D0();
s32 func_800A32A4();
s32 func_800A5720();
s32 func_800A5F38();
s32 func_800A63B8();
s32 func_800A6620();
s32 func_800A6D30();
s32 func_800A90E8();
s32 func_800B8228();

extern u8 D_80089360[];
extern u8 D_800E1095[0x1E];
extern u8 D_800E10B3[];

/* Handles entity removal, displays its message, and updates dungeon state. */
s32 func_800BE6F0(void *entity, s32 source, s16 reason)
{
    u8 spawn_data[4];
    s32 text_buffer;
    s32 text_end;
    s32 entity_index;
    s32 linked_entity;
    s32 tile_mask;
    u8 entity_type;
    s32 spawn_type;
    u8 tile_x;
    u8 tile_y;
    S_800BE6F0_1 *position;
    S_800BE6F0_3 *map_position;
    s32 *entity_table;
    s32 cleared_selection;
    u8 *entity_base;

    if (entity == ((u8 *)D_800E3D7C)) {
        ((EntityRec *)entity)->unk_110 = source;
        func_8008D330(entity, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFF) {
        func_800A63B8(entity, source, reason);
    }

    if (((EntityRec *)entity)->flags14 & 0x4000) {
        text_buffer = func_800990FC();
        if ((u32)((*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3)) - 3) < 0x2B) {
            text_end = func_80099734(entity, text_buffer);
            text_end = func_80099194(D_800E1095, text_end);
        } else {
            text_end = func_80099734(entity, text_buffer);
            text_end = func_80099194(D_800E10B3, text_end);
            text_end = func_80099368(source, text_end);
            text_end = func_80099194(D_80089360, text_end);
        }
        func_80099290(text_end);
        func_800A5720(text_buffer);
    }

    entity_type = (*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3));
    if ((u32)(entity_type - 3) < 0x2B) {
        spawn_data[0] = entity_type;
        spawn_type = (*(u8 *)((u8 *)&((EntityRec *)entity)->unk_10 + 3));
        if ((spawn_type == 3) || (spawn_type == 5) || (spawn_type == 7) ||
            (spawn_type == 9) || (spawn_type == 0xB) || (spawn_type == 0xD) ||
            (spawn_type == 0xF) || (spawn_type == 0x11) || (spawn_type == 0x13)) {
            spawn_data[0]++;
        }
        spawn_data[1] = 0x12;
        spawn_data[2] = (func_800A6D30() & 0xF) + 0xA;
        spawn_data[3] = 0;
        func_800A90E8(spawn_data);

        position = ((S_800BE6F0_0_pre *)entity)[-1].unk_00;
        func_800B8228(
            position->unk_02,
            position->unk_06,
            position->unk_0A,
            spawn_data);

        spawn_type = (s32)dungeonStatus.unk_10;
        if (spawn_type == (s32)((u8 *)entity - 0x20)) {
            cleared_selection = spawn_type & 0x7FFFFFFF;
            dungeonStatus.unk_10 = (void *)cleared_selection;
        }

        linked_entity = func_800A32A4(entity);
        if (linked_entity != 0) {
            entity_index = func_800A6620(linked_entity, 0);
            if (entity_index < 0x40) {
                entity_table = (s32 *)0x80010980;
                entity_base = (u8 *)0x80010000;
                entity_base[entity_index * 0x54 + 0xA93] = 0;
                entity_table[entity_index] = 0;
            }
        }

        if ((func_80042900(entity, 0x1B) << 16) == 0) {
            map_position = ((S_800BE6F0_0_pre *)entity)[-1].unk_04;
            tile_x = map_position->unk_24;
            tile_y = map_position->unk_25;
            tile_mask = 0x3000;
            if (((EntityRec *)entity)->flags1C & 0x2000) {
                tile_mask = 0x300;
            }
            func_8009A3D0(tile_x, tile_y, tile_mask);
        }

        func_8009A028(entity);
        ((S_800BE6F0_0_pre *)entity)[-1].unk_16 |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    } else {
        func_800A5F38(entity, source);
        return 1;
    }
    func_80098B38(source);
    dungeonStatus.unk_0A--;
    return 1;
}

/* 2.7.2-cdk-G0: symbols by name; the cdk cell splits each address itself. */
