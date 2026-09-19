#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80083160.h"

typedef struct S_80089588_3 {
    s32 unk_00;
} S_80089588_3;   /* temp_s1 in func_80089588 */

typedef struct S_80089588_4 {
    u8 pad_00[0x8D0];
    void * unk_8D0;
} S_80089588_4;   /* ((S_80089588_3 *)temp_s1)->unk_00 in func_80089588 */



typedef struct S_80089588_1 {
    u8 pad_00[0x3];
    volatile s8 unk_03;
    volatile s32 unk_04;
    volatile s16 unk_08;
    volatile u16 unk_0A;
    union { s16 s; volatile s16 u; } unk_0C;   /* accessed as both */
    volatile u16 unk_0E;
    volatile s16 unk_10;
    volatile s16 unk_12;
    volatile s16 unk_14;
    volatile s16 unk_16;
} S_80089588_1;   /* temp_s2 in func_80089588 */

typedef struct S_80089588_2 {
    s32 unk_00;
} S_80089588_2;   /* temp_s1 in func_80089588 */


struct S_8003E2D8; typedef struct S_8003E2D8 S_8003E2D8;
extern struct S_8003E2D8 *D_80083160;
extern u8 D_801C9E40[16];
M2C_UNK func_8006658C(void *, void *);
M2C_UNK func_80067E2C();
M2C_UNK func_80067EF4();
M2C_UNK func_80067F20();

/* Queue draw settings and horizontal strips for both ordering tables. */
void func_80089588(void) {
    s32 draw_area[2];
    s32 alternate_buffer;
    s16 saved_alternate;
    u16 strip_y;
    u16 other_strip_y;
    void *packet;
    register u32 context_slot ASM_REG("$17");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    alternate_buffer = (s32) D_80083160 != (s32) D_801C9E40;
    packet = ((Rec_D_80083160 *)D_80083160)->unk_8D0;
    func_80067E2C(packet, D_80083160);
    func_8006658C((u8 *)D_80083160 + 0x7B0, packet);
    packet += 0xC;
    func_80067E2C(packet, D_80083160);
    func_8006658C((u8 *)D_80083160 + 0x830, packet);
    packet += 0xC;
    func_80067EF4(packet, 0, 0);
    func_8006658C((u8 *)D_80083160 + 0x830, packet);
    packet += 0xC;
    {
        s32 cmd_value;
        cmd_value = 0x2A000000;
        (*(s32 *)((u8 *)packet + 4)) = cmd_value;
        cmd_value = 1;
        (*(s16 *)((u8 *)packet + 0x10)) = cmd_value;
        (*(s16 *)((u8 *)packet + 8)) = cmd_value;
        cmd_value = 0x100;
        (*(s16 *)((u8 *)packet + 0x14)) = cmd_value;
        (*(s16 *)((u8 *)packet + 0xC)) = cmd_value;
    }
    context_slot = (u32) &D_80083160;
    saved_alternate = alternate_buffer;
    {
        register s32 strip_top;
        if (alternate_buffer != 0) {
            (*(u16 *)((u8 *)packet + 0xE)) = 0xE0;
        } else {
            (*(u16 *)((u8 *)packet + 0xE)) = 0x1C0;
        }
    }
    strip_y = (*(u16 *)((u8 *)packet + 0xE));
    (*(s8 *)((u8 *)packet + 3)) = 5;
    (*(u16 *)((u8 *)packet + 0xA)) = strip_y;
    (*(s16 *)((u8 *)packet + 0x16)) = strip_y + 0xE;
    (*(s16 *)((u8 *)packet + 0x12)) = strip_y + 0xE;
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0x18;
    {
        s32 cmd_value;
        cmd_value = 0x2A000000;
        (*(s32 *)((u8 *)packet + 4)) = cmd_value;
        cmd_value = 1;
        (*(s16 *)((u8 *)packet + 0x10)) = cmd_value;
        (*(s16 *)((u8 *)packet + 8)) = cmd_value;
        cmd_value = 0x100;
        (*(s16 *)((u8 *)packet + 0x14)) = cmd_value;
        (*(s16 *)((u8 *)packet + 0xC)) = cmd_value;
    }
    {
        s32 strip_top;
        strip_top = saved_alternate;
        if (strip_top != 0) {
            (*(u16 *)((u8 *)packet + 0xE)) = 0xE0;
        } else {
            (*(u16 *)((u8 *)packet + 0xE)) = 0x1C0;
        }
    }
    other_strip_y = (*(u16 *)((u8 *)packet + 0xE));
    (*(s8 *)((u8 *)packet + 3)) = 5;
    (*(u16 *)((u8 *)packet + 0xA)) = other_strip_y;
    (*(s16 *)((u8 *)packet + 0x16)) = other_strip_y + 0xE;
    (*(s16 *)((u8 *)packet + 0x12)) = other_strip_y + 0xE;
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x7B0, packet);
    packet += 0x18;
    func_80067EF4(packet, 0, 1);
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0xC;
    func_80067F20(packet, 0, 0, 0x20, 0);
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x7B0, packet);
    packet += 0xC;
    func_80067F20(packet, 0, 0, 0x20, 0);
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0xC;
    draw_area[0] = 0x01C00000;
    draw_area[1] = 0x100100;
    func_80067E2C(packet, (s32) draw_area);
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x7B0, packet);
    packet += 0xC;
    func_80067E2C(packet, (s32) draw_area);
    func_8006658C(((S_80089588_2 *)context_slot)->unk_00 + 0x830, packet);
    packet += 0xC;
    ((S_80089588_4 *)(((S_80089588_3 *)context_slot)->unk_00))->unk_8D0 = packet;
}
