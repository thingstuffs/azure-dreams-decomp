#include "modules/dungeon_ovl_197e800.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

   /* obj in func_8002401C */


   /* the 0x18 bytes before source in func_8002401C, addressed as source[-1] */

   /* display in func_8002401C */

   /* ((S_8002401C_0 *)obj)->unk_04 in func_8002401C */



extern s32 D_80027328;
extern u8 D_80027374[];
extern u8 D_800273BE;


/* The module's entry pointer: the first word of its read-only data, at the row's own address
 * (retail 0x80024000, the row symbol dungeonAddFlagAdjustedTargetValue).  The switch table follows it at 0x80024008
 * (gcc's .align 3 for jump tables), and the code starts after the table. */
void (*const dungeon_197e800_entry)(void *) = func_8002401C;

/* Advances the object's state and draws its 7-by-7 grid. */
void func_8002401C(void *object)
{
    u8 *object_bytes = object;
    GameWork *palette = &gameWork;
    u8 *source;
    s32 *row;
    s32 *clear_row;
    s32 *clear_cell;
    s16 rect[4];
    s32 row_index;
    s32 col_index;
    s32 y;
    s32 cell_value;
    s32 cell_size;
    s32 direction_offset;
    EntityRec *map_data;
    u8 config_byte;
    void *created_obj;
    void *display;
    void *source_obj;
    s32 dependency_scratch;
    s32 state;

    state = ((S_8002401C_0 *)object_bytes)->unk_0A.s;
    switch (state) {
    case 0:
        row_index = 0;
        D_800273BC.value = 1;
        config_byte = ((S_8002401C_0 *)object_bytes)->unk_09;
        D_80027328 = 0;
        source_obj = ((S_8002401C_0 *)object_bytes)->unk_00.s;
        D_800273BE = config_byte;
        D_800273C0 = ((S_8002401C_0 *)object_bytes)->unk_00.s;
        D_8002732C = source_obj;

        D_800814A8->unk_F4 = 0;
        D_800814A8->unk_102 = 1;
        D_800814A8->unk_A8 = ((S_8002401C_0 *)object_bytes)->unk_08;

        clear_row = D_800274DC[0];
        do {
            col_index = 6;
            clear_cell = clear_row + 6;
            do {
                *clear_cell = 0;
                clear_cell--;
                col_index--;
            } while (col_index >= 0);
            row_index++;
            if (row_index >= 7) {
                break;
            }
            clear_row += 8;
        } while (1);

        D_800273A8 = 0;
        map_data = (u8 *)D_800E3D7C;
        direction_offset = (((u16)map_data->facing) >> 8) & 0xE;
        dungeonFlagNearbySevenBySevenTiles(
            (s16)(D_80082E80.tileX +
                  (dirStepX[direction_offset >> 1] * 4)),
            (s16)(D_80082E80.tileY +
                  (dirStepY[direction_offset >> 1] * 4)));
        ((S_8002401C_0 *)object_bytes)->unk_0A.u++;
                        /* fallthrough */

    case 1:
        if ((((S_8002401C_4 *)(((S_8002401C_0 *)object_bytes)->unk_04))->unk_00 & 0x80) != 0) {
            source = ((S_8002401C_0 *)object_bytes)->unk_00.u;
            created_obj = func_8002453C(((S_8002401C_2_pre *)source)[-1].unk_00, source);
            ((S_8002401C_0 *)object_bytes)->unk_0C = created_obj;
            if (created_obj != 0) {
                display = D_800814A8;
                ((S_8002401C_0 *)object_bytes)->unk_1C.s = 0x10;
                ((S_8002401C_3 *)display)->unk_A6--;
                ((S_8002401C_0 *)object_bytes)->unk_0A.u++;
            }
        }
        break;

    case 2:
        ((S_8002401C_0 *)object_bytes)->unk_1C.u--;
        if (((S_8002401C_0 *)object_bytes)->unk_1C.s >= 0) {
            break;
        }
        func_800A56E0(0x300);
        ((S_8002401C_0 *)object_bytes)->unk_0A.u++;
                            /* fallthrough */

    case 3:
        if ((s16)D_800273BC.value == 0) {
            func_80025C8C();
            ((S_8002401C_0 *)object_bytes)->unk_0A.u++;
        }
        break;

    case 4:
        if ((s16)D_80027330 == 0) {
            dungeonStatus.unk_0C = 0;
            dungeonStatus.unk_0A--;
            (*(u16 *)((u8 *)object_bytes + -2)) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        break;
    }

    rect[0] = 0x340;
    rect[1] = 0x180;
    rect[2] = 0x70;
    rect[3] = 0x70;
    dungeonDrawTexturedEllipse(D_80027398, rect, 0, 2);

    for (row_index = 0, cell_size = 0x10, row = D_800274DC[0], y = 0x180;
         row_index < 7; row_index++) {
        for (col_index = 0; col_index < 7;) {
            rect[0] = 0x340 + col_index * 0x10;
            rect[1] = y;
            rect[2] = cell_size;
            rect[3] = cell_size;
            cell_value = row[col_index];
            func_80026064(rect, cell_value);
            col_index++;
        }
        row += 8;
        y += 0x10;
    }

    D_80027330 = 0;
    D_80027374[8] = (palette->unk_004 & 0x1F) + 0x80;
    D_80027374[9] = palette->unk_004 & 0x1F;
}
