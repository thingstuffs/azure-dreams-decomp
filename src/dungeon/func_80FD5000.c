/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"

typedef struct S_80FD5000_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80FD5000_0;   /* temp_s1 in func_8014C8A4 */

typedef struct S_80FD5000_1 {
    u8 pad_00[0x13];
    s8 unk_13;
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0x6C];
    M2C_UNK * unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 pad_9B[0x1];
    s8 unk_9C;
    u8 pad_9D[0x11];
    s16 unk_AE;
} S_80FD5000_1;   /* var_s0 in func_8014C8A4 */

typedef struct S_80FD5000_2 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_80FD5000_2;   /* temp_s6 in func_8014C8A4 */

typedef struct S_80FD5000_3 {
    u8 pad_00[0x8];
    u8 * unk_08;
    u8 pad_0C[0x6];
    u16 unk_12;
    u8 pad_14[0x10];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    M2C_UNK * unk_2C;
} S_80FD5000_3;   /* temp_s2 in func_8014C8A4 */


typedef struct S_80FD5000_4 {
    u8 unk_00;
    u8 pad_01[0x5];
    u16 unk_06;
} S_80FD5000_4;


void *func_8003FD64();
s32 func_8004491C();
M2C_UNK func_800673A0();
s16 func_800A48F0(); /* extern */
s32 func_800A6D30();
void func_800A9C18();
s32 func_800AA36C(); /* extern */
void *func_8014C984();
void *func_8014CA40();
extern M2C_UNK D_8014CB40;
extern M2C_UNK D_8014CF6C;
extern M2C_UNK D_80151258;
extern M2C_UNK D_80151298;

typedef void (*Callback)(void);
typedef struct {
    Callback callbacks[27];
    u8 config[56];
} ActorDefinition;

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

/* Creates a monster actor and initializes its state, placement, and palette. */
void *func_8014C8A4(s16 spawn_flags, s16 tile_x, s16 tile_y, s32 heading)
{
    s32 kind;
    S_80FD5000_1 *actor_state;
    S_80FD5000_0 *created;
    S_80FD5000_2 *position;
    S_80FD5000_3 *monster;
    S_80FD5000_1 *actor;
    Rect palette_strip;
    s32 appearance_id;
    s32 palette_y;
    S_80FD5000_4 *entry;
    s32 entry_index;
    s32 twice_index;
    Rect *palette_rect;
    S_80FD5000_4 *selected;
    S_80FD5000_4 *selected2;
    S_80FD5000_4 *selected3;

    actor_state = 0;
    created = func_8003FD64(0x112, ((M2C_UNK *)&D_80083498.next));
    if (created != 0) {
        actor_state = (S_80FD5000_1 *)((u8 *)created + 0x20);
        created->unk_10 = &D_8014CB40;
        actor_state->unk_13 = 0x27;
        func_8004491C(created, func_80045340);

        position = created->unk_08;
        position->unk_0A = heading;
        monster = created->unk_0C;
        kind = spawn_flags & 3;
        monster->unk_25 = tile_y;
        actor = actor_state;
        monster->unk_2C = &D_80151258;
        monster->unk_24 = tile_x;

        if (kind == 1) {
            actor_state->unk_14 |= 0x6000;
            actor_state->unk_1C |= 0x6000;
        } else if (kind >= 2) {
            actor_state->unk_14 |= 0x2000;
            actor_state->unk_1C |= 0x2000;
        } else if (((spawn_flags & -4) << 16) == 0) {
            if ((actor_state->unk_14 & 0x200) == 0) {
                if ((func_800A6D30() & 1) != 0) {
                    actor_state->unk_1C |= 0x200;
                    func_800A48F0(actor_state, 1, (func_800A6D30() & 0x3F) | 0x20);
                    monster->unk_2C = &D_80151298;
                }
            }
        }


        func_800A9C18(created, position, monster, spawn_flags);

        entry_index = 0;
        appearance_id = monster->unk_12;
        actor->unk_9A = 0xFF;
        actor->unk_9C = -1;
        actor->unk_8C = &D_8014CF6C;
        actor->unk_AE = appearance_id;

        entry = (S_80FD5000_4 *)monster->unk_08;
        while (1) {
            twice_index = entry_index << 1;
            if (!(entry->unk_00 & 0x20)) {
                break;
            }
            entry = (S_80FD5000_4 *)((u8 *)entry + 12);
            entry_index++;
        }

        palette_rect = &palette_strip;
        selected = (S_80FD5000_4 *)(twice_index + entry_index);
        selected2 = (S_80FD5000_4 *)((s32)selected * 4);
        selected3 = (S_80FD5000_4 *)((u8 *)selected2 + (s32)monster->unk_08);
        palette_y = selected3->unk_06 >> 6;
        palette_strip.x = 0;
        palette_strip.y = palette_y;
        palette_strip.w = 0x100;
        palette_strip.h = 1;
        func_800673A0(palette_rect, 0, palette_y - 1);

        palette_strip.w = 0x10;
        palette_strip.x = 0x30;
        palette_strip.y--;
        do {
            func_800673A0(&palette_strip, palette_strip.x - 0x30, palette_strip.y);
            palette_strip.x += 0x40;
        } while (palette_strip.x < 0x100);

        func_800AA36C(actor, position, monster, actor_state);
    }

    return actor_state;
}
