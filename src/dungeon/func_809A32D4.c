#include "common.h"

typedef struct S_80174AD4_0 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80174AD4_0;   /* dungeon0 in func_80174AD4 */

typedef struct S_80174AD4_1 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80174AD4_1;   /* dungeon1 in func_80174AD4 */

typedef struct S_80174AD4_2 {
    u8 pad_00[0x3];
    s8 unk_03;
    s32 unk_04;
    u16 unk_08;
    s16 unk_0A;
    s32 unk_0C;
} S_80174AD4_2;   /* packet1 in func_80174AD4 */

typedef struct S_80174AD4_3 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80174AD4_3;   /* dungeon2 in func_80174AD4 */

typedef struct S_80174AD4_4 {
    u8 pad_00[0xC];
    u8 unk_0C;
} S_80174AD4_4;   /* arg2 in func_80174AD4 */

typedef struct S_80174AD4_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80174AD4_5;   /* actor->field1C in func_80174AD4 */

typedef struct S_80174AD4_6 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_80174AD4_6;   /* actor in func_80174AD4 */

typedef struct S_80174AD4_7 {
    u16 unk_00;
} S_80174AD4_7;   /* ((S_80174AD4_6 *)actor)->unk_0C in func_80174AD4 */


typedef struct {
    u16 x;
    s16 y;
    s16 w;
    s16 h;
    s16 u;
    s16 v;
} LocalArgs;

typedef struct {
    u8 pad00[0xC];
    u16 *field0C;
    u8 *field10;
    u8 pad14[2];
    u8 field16;
    u8 state;
    u8 pad18[4];
    void *field1C;
} Actor;

typedef struct {
    u8 pad00[2];
    u16 field02;
    u8 pad04[2];
    u16 field06;
    u8 pad08[2];
    s16 field0A;
} Output;

extern void func_8004491C(void *, void *);
extern void func_8006658C(void *, void *);
extern void func_80067E2C(void *, void *);
extern void func_80174FC0(void *, s32, s32);
extern void func_801750E4(s32, s32, s32, s32, s32, s32, void *, void *, void *, s32, s32);

extern s32 D_800814A0;
typedef struct {
    u8 *ptr;
} PagePtr;

extern PagePtr D_80083160;
extern s32 D_800CEEFC[3];
extern u8 D_801C9E40[16];

#define DUNGEON_INITIAL (D_80083160.ptr)
#define DUNGEON_FROM_PAGE (D_80083160.ptr)

/* Updates the actor rendering state, effect level, and output position. */
void func_80174AD4(u8 *actor_data, u8 *output_data, u8 *effect_data)
{
    LocalArgs draw_region;
    Actor *actor;
    Output *output;
    u8 *initial_page;
    u8 *rect_page;
    u8 *region_page;
    u8 *base_page;
    u8 *packet_list;
    void *page_packet;
    void *rect_packet;
    void *region_packet;
    u8 alternate_page;
    u8 adjust_y;
    s16 steps_left;
    s16 next_steps;
    s32 draw_y;
    s32 texture_u;
    s32 packed_size;
    s32 state;
    u8 decay_level;
    u8 rise_level;

    actor = (Actor *)actor_data;
    output = (Output *)output_data;
    initial_page = DUNGEON_INITIAL;
    base_page = D_801C9E40;
    state = actor->state;
    alternate_page = initial_page != base_page;
    packet_list = initial_page + 0xB0;

    if (state == 0) {
        page_packet = ((S_80174AD4_0 *)initial_page)->unk_8D0;
        ((S_80174AD4_0 *)initial_page)->unk_8D0 = (u8 *)page_packet + 0xC;
        func_80067E2C(page_packet, DUNGEON_FROM_PAGE);
        func_8006658C(packet_list, page_packet);

        draw_y = 0x110;
        draw_region.x = 0x340;
        draw_region.y = 0x100;
        draw_region.w = 0x20;
        draw_region.h = 0x20;
        texture_u = 0x350;
        draw_region.u = texture_u;
        adjust_y = alternate_page;
        if (adjust_y != 0) {
            draw_y = 0x30;
        }
        draw_region.v = draw_y;

        func_801750E4(0x10, 0x10, 0, 0, texture_u, draw_region.v,
                     actor, (u8 *)actor + 4, packet_list, 0, 0x20);

        rect_page = DUNGEON_FROM_PAGE;
        rect_packet = ((S_80174AD4_1 *)rect_page)->unk_8D0;
        ((S_80174AD4_1 *)rect_page)->unk_8D0 = (u8 *)rect_packet + 0x10;
        ((S_80174AD4_2 *)rect_packet)->unk_04 = 0x60000000;
        ((S_80174AD4_2 *)rect_packet)->unk_03 = 3;
        ((S_80174AD4_2 *)rect_packet)->unk_08 = draw_region.x;
        draw_y = draw_region.y;
        if (adjust_y != 0) {
            draw_y -= 0xE0;
        }
        packed_size = *(s32 *)&draw_region.w;
        ((S_80174AD4_2 *)rect_packet)->unk_0A = draw_y;
        ((S_80174AD4_2 *)rect_packet)->unk_0C = packed_size;
        func_8006658C(packet_list, rect_packet);

        region_page = DUNGEON_FROM_PAGE;
        region_packet = ((S_80174AD4_3 *)region_page)->unk_8D0;
        ((S_80174AD4_3 *)region_page)->unk_8D0 = (u8 *)region_packet + 0xC;
        func_80067E2C(region_packet, (void *)&draw_region);
        func_8006658C(packet_list, region_packet);
    } else if (state == 1) {
        func_8004491C((u8 *)actor - 0x20, D_800CEEFC);
    } else if (state == 3) {
        decay_level = ((S_80174AD4_4 *)effect_data)->unk_0C;
        if (decay_level != 0) {
            decay_level -= 8;
            ((S_80174AD4_4 *)effect_data)->unk_0C = decay_level;
            if (decay_level == 0) {
                (*(u16 *)((u8 *)actor + -2)) |= 0x8000;
                D_800814A0 |= 0x8000;
            }
        }
        goto update_output;
    } else {
        rise_level = ((S_80174AD4_4 *)effect_data)->unk_0C;
        if (rise_level < 0xC0) {
            ((S_80174AD4_4 *)effect_data)->unk_0C = rise_level + 0x20;
        }
        if (actor->field16 == *actor->field10) {
            goto update_output;
        }
    }
    actor->state++;
update_output:
    steps_left = 4;
    if (actor->state != 3) {
        output->field02 = ((S_80174AD4_5 *)(actor->field1C))->unk_02;
        output->field06 = ((S_80174AD4_5 *)(actor->field1C))->unk_06;
        output->field0A = ((S_80174AD4_5 *)(actor->field1C))->unk_0A - 0xC;
        do {
            func_80174FC0((u8 *)actor - 0x20, (((S_80174AD4_7 *)(((S_80174AD4_6 *)actor)->unk_0C))->unk_00 >> 9) & 7, 0xFF);
            next_steps = steps_left - 1;
            steps_left = next_steps;
        } while ((next_steps << 16) > 0);
    }
}
