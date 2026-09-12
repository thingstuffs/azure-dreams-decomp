#include "common.h"

typedef struct S_800AAF00_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    s16 unk_46;
    u8 pad_48[0x18];
    s32 unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_800AAF00_0;   /* obj in func_800AAF00 */

typedef struct S_800AAF00_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_800AAF00_1;   /* state in func_800AAF00 */

typedef struct S_800AAF00_2 {
    u8 pad_00[0x98];
    union { s32 s32; u16 u16; } unk_98;   /* accessed as both */
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x74];
    void * unk_11C;
} S_800AAF00_2;   /* D_800E3D7C in func_800AAF00 */

typedef struct S_800AAF00_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
} S_800AAF00_3;   /* owner in func_800AAF00 */

typedef struct S_800AAF00_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800AAF00_4;   /* other in func_800AAF00 */

typedef struct S_800AAF00_5 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800AAF00_5;   /* state2 in func_800AAF00 */



extern s32 func_80047784();
extern s32 func_800A05A4();
extern s32 func_800A2B5C();
extern void func_800A4ACC();
extern s32 func_800A6D30();
extern void func_800C77D0();

extern u8 D_8006DE24[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 *D_800E3D7C;

/* Updates the object action state and applies direction data to its target. */
void func_800AAF00(void *actor, s32 effect_param, void *target, u8 *direction_table, s32 next_state) {
    void *object;
    s32 special_action;
    u8 *action_state;
    u8 *updated_state;
    u8 *slot_data;
    u8 *type_data;
    u8 *type_table;
    volatile u16 *slot_flags;
    u16 input_flags;
    s32 slot_offset;
    s32 type_index;

    object = actor;
    ((S_800AAF00_0 *)object)->unk_71 &= 0x7F;
    action_state = (u8 *)&D_80083460;
    input_flags = ((S_800AAF00_1 *)action_state)->unk_02;
    special_action = 0;

    if (!(input_flags & 0x2008)) {
        if ((((S_800AAF00_0 *)object)->unk_1C & 0x2000) &&
            ((((S_800AAF00_0 *)object)->unk_46 & 0x3FFF) >= 5)) {
            special_action = 1;
            if (((((S_800AAF00_2 *)D_800E3D7C)->unk_98.s32 & 0x3000) == 0x2000) &&
                (((S_800AAF00_2 *)D_800E3D7C)->unk_A6 == 0)) {
                ((S_800AAF00_2 *)D_800E3D7C)->unk_98.u16 |= 0x1000;
                ((S_800AAF00_2 *)D_800E3D7C)->unk_A6++;
                ((S_800AAF00_1 *)action_state)->unk_0A++;

                goto shared_body;
            }
            func_800A4ACC(object);
            ((S_800AAF00_0 *)object)->unk_6D--;
            ((S_800AAF00_3 *)actor)->unk_8C = next_state;

            return;
        }

        if (!(input_flags & 8) && ((func_800A2B5C(object) << 16) == 0)) {
            func_800C77D0((u8 *)object - 0x20, effect_param, 8, 0x300);
            if ((func_800A2B5C(object) << 16) == 0) {
shared_body:
                if (!special_action) {
                    if (((S_800AAF00_0 *)object)->unk_1C & 0x400) {
                        register s32 object_flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
                        s32 sign_bit;

                        object_flags = ((S_800AAF00_0 *)object)->unk_14;
                        if (object_flags >= 0) {
                            sign_bit = 0x80000000;
                            ((S_800AAF00_0 *)object)->unk_14 = object_flags | sign_bit;
                            ((S_800AAF00_0 *)object)->unk_2A.u += (func_800A6D30() & 7) << 9;
                        }
                    }

                    slot_flags = (volatile u16 *)((u8 *)object + 0x46);
                    if (!(*slot_flags & 0x4000)) {
                        slot_offset = *slot_flags & 0x3FFF;
                        type_index = slot_offset;
                        type_index--;
                        type_table = D_8006DE24;
                        slot_offset = type_index * 3;
                        slot_data = object;
                        slot_data += slot_offset;
                        type_index = slot_data[8];
                        type_data = type_table + type_index * 20;
                        if ((type_data[0x12] == 2) && (((S_800AAF00_0 *)object)->unk_60 == 0)) {
                            ((S_800AAF00_0 *)object)->unk_60 = func_800A05A4(
                                object,
                                ((S_800AAF00_4 *)target)->unk_24,
                                ((S_800AAF00_4 *)target)->unk_25,
                                ((S_800AAF00_0 *)object)->unk_2A.s,
                                type_data[0x13]);

                        }
                    }
                } else {
                    ((S_800AAF00_2 *)D_800E3D7C)->unk_11C = object;
                }

                ((S_800AAF00_3 *)actor)->unk_9A = 0x12;
                ((S_800AAF00_3 *)actor)->unk_9B = 0;
                ((S_800AAF00_3 *)actor)->unk_8C = 0;
                if (direction_table != 0) {
                    (*(u8 * *)((u8 *)target + 0x2C)) = direction_table;
                    func_80047784(
                        target,
                        direction_table[((D_80083228 + ((S_800AAF00_0 *)object)->unk_2A.s + 0x100) >> 9) & 7],
                        0);
                }
                updated_state = (u8 *)&D_80083460;
                ((S_800AAF00_4 *)target)->unk_14 |= 0x800;
                ((S_800AAF00_5 *)updated_state)->unk_0A++;
            }
        }
    }

       /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
}
