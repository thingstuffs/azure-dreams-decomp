#include "common.h"
typedef struct { u8 pad[0x3714]; u16 flags; } SysPage;
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef s32 M2C_UNK;
typedef struct S_80048A44_Obj S_80048A44_Obj;


typedef struct S_8008C7B4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8008C7B4_0;   /* arg0 in begin_player_wait_turn */


extern void func_80048A44(S_80048A44_Obj *obj, s16 frame_group, s16 frame_index, s32 slot_index);
extern void append_packed_action_record();
extern s32 check_action_available_without_nearby_actor(void);
extern u8 D_800DCFB0;
extern M2C_UNK D_800DD0B8;

/* Reset state, update control flags, and select the entity's directional sprite. */
void begin_player_wait_turn(void *state, s32 mode, void *sprite, EntityRec *entity) {
    void *entity_arg;
    GameWork *flags;
    s32 initial_state;

    initial_state = 0x1C;
    ((S_8008C7B4_0 *)state)->unk_9A = initial_state;
    flags = &g_game_work;
    ((S_8008C7B4_0 *)state)->unk_9B = 0;
    ((S_8008C7B4_0 *)state)->unk_8C = 0;
    if ((((SysPage *)0x80010000)->flags & 2) || ((flags->buttons & 0x20) && check_action_available_without_nearby_actor() != 0)) {
        g_dungeon_status.flags = (u16)(g_dungeon_status.flags | 0x80);
    }
    entity_arg = entity;
    append_packed_action_record(entity_arg, 0x10, 0, 0);
    {
        u8 *direction_table;

        if (entity->flags1C & 0x100000) {

            direction_table = (u8 *)&D_800DD0B8;
        } else {

            direction_table = &D_800DCFB0;
        }
        (*(u8 **)((u8 *)sprite + 0x2C)) = direction_table;
        {
            u8 *direction_entry;

            initial_state = ((s32)(g_game_work.view.viewAngle + entity->facing + 0x100) >> 9) & 7;
            direction_entry = direction_table + initial_state;
            func_80048A44(sprite, *direction_entry, 0, 1);
        }
    }
}
