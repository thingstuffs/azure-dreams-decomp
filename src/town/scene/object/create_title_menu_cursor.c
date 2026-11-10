#include "common.h"
#include "town/scene/collection.h"
#include "town/scene/object.h"
#define AZ_FOREIGN_LOCAL_FUNC_80050BFC
#include "town/devkit/old_minigame_imports.h"
#undef AZ_FOREIGN_LOCAL_FUNC_80050BFC

typedef struct S_808106E0_0 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x10];
    union { u16 u16; u32 u32; void * p32; } unk_24;   /* accessed as both */
    union {
        struct { void * v; } at00;
        struct { u32 v; } at00u;
        struct { u8 pad[0x2]; s16 v; } at02;
    } unk_28;   /* overlapping accesses */
    union {
        struct { u16 v; } at00;
        struct { void * v; } at00u;
        struct { s16 v; } at00p;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_2C;   /* overlapping accesses */
    union {
        struct { u32 v; } at00;
        struct { u16 v; } at00u;
        struct { u8 pad[0x2]; u16 v; } at02;
    } unk_30;   /* overlapping accesses */
    s16 unk_34;
    u16 unk_36;
    u16 unk_38;
    u16 unk_3A;
} S_808106E0_0;   /* object in create_title_menu_cursor */

typedef struct S_808106E0_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_808106E0_1;   /* part in create_title_menu_cursor */


typedef struct Triple {
    u32 e[3];
} Triple;

extern Triple D_80526670;
extern Triple D_80526688;
extern u8 menu_entry_draw_callback_address[];
extern u8 menu_cursor_object_template[];
extern u8 D_8052B5A4[];
extern u8 D_8052BAAC[];
extern u8 D_8052BB00[];
extern u8 D_8052BB98[];

extern void func_80050BFC(s32, void *); /* Unprototyped: this site's argument count or types differ from the foreign program's import prototype */

/* Build the title-screen menu: the cursor object plus the two rows of three entries, linked to the shared anchor. */
s32 create_title_menu_cursor(void)
{
    u8 *anchor = 0;
    Triple positions0 = D_80526670;
    Triple positions1 = D_80526688;
    S_808106E0_0 *object;
    s32 shared_part_y;
    s32 i;
    s32 y_second;

    func_80050BFC(0x552, &D_80526688);
    func_8003F8A8(7);
    func_800351A8(0x3E, 0);

    object = func_800374FC(0x136, &scene_object_factory_data);
    i = 2;
    if (object != 0) {
        anchor = (u8 *)object + 0x20;
        object->unk_10 = D_8052B5A4;
        object->unk_28.at02.v = 0x1E;
        object->unk_24.u16 = func_80071494() & 3;
        object->unk_2C.at00.v |= 4;
    }

    shared_part_y = 0xD0;
    do {
        object = func_800374FC(1, &scene_object_factory_data);
        if (object != 0) {
            object->unk_10 = D_8052BAAC;
            func_8003BC18(object, menu_entry_draw_callback_address);
            object->unk_36 = 0xB4;
            object->unk_38 = 3;
            object->unk_3A = 0x7C80;
            object->unk_34 = shared_part_y;
            object->unk_30.at00.v = 0x00808080;
            object->unk_24.u32 = positions0.e[i];
            object->unk_2C.at00u.v = anchor;
        }
        i--;
        shared_part_y -= 0x58;
    } while (i >= 0);

    i = 2;
    y_second = 0xD8;
    do {
        object = func_800374FC(1, &scene_object_factory_data);
        if (object != 0) {
            object->unk_10 = D_8052BB00;
            func_8003BC18(object, menu_entry_draw_callback_address);
            object->unk_36 = 0xC4;
            object->unk_38 = 3;
            object->unk_3A = 0x7C80;
            object->unk_34 = y_second;
            object->unk_30.at00.v = 0x00808080;
            object->unk_24.u32 = positions1.e[i];

            shared_part_y = (s32)object + 0x20;
            switch (i) {
            case 0:
                object->unk_28.at00.v = anchor + 6;
                break;
            case 2:
                object->unk_28.at00.v = anchor + 10;
                break;
            case 1:
                object->unk_28.at00.v = anchor + 8;
                break;
            }
            ((S_808106E0_1 *)shared_part_y)->unk_0C = anchor;
        }
        i--;
        y_second -= 0x58;
    } while (i >= 0);

    i = 2;
    shared_part_y = 0xCC;
    do {
        object = func_800374FC(1, &scene_object_factory_data);
        i--;
        if (object != 0) {
            object->unk_10 = D_8052BB98;
            func_8003BC18(object, menu_cursor_object_template);
            object->unk_2C.at02.v = 0xB0;
            object->unk_30.at00u.v = 0x50;
            object->unk_30.at02.v = 0x20;
            object->unk_2C.at00p.v = shared_part_y;
            object->unk_34 = 2;
            object->unk_28.at00u.v = 0x00404040;
            object->unk_24.p32 = anchor;
            object->unk_36 |= 1;
        }
        shared_part_y -= 0x58;
    } while (i >= 0);

    return 0;
}

/* MECHANISM: Declare the held s3 anchor before two independent 12-byte stack locals to match the 0x48 prologue.
   The three-way selection is a switch: gcc 2.7.2 emits the balanced tree (beq ==1, slti 2, beq ==0,
   beq ==2) retail shows, case 1 last so its addiu falls into the join; each case stores its own
   anchor offset and the join stores the anchor (the old default arm's jump is now the missing-default fall-out).
   The switch's end label also ends the fall-through extended block, so shared_part_y stays
   s2+0xC instead of CSE-folding to s0+0x2C - no keep needed. */
