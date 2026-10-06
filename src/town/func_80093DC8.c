#include "shared/position_query.h"
#include "shared/game_work.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
extern s32 func_80033B2C(s32 value);
extern s32 func_800374F4(s32 value);
extern s32 func_8003BD84(s32 value, s32 other_value);
extern void func_8008B158(s32 value);
extern void func_80093D48(void *action_state, void *actor, s32 context);
extern void func_80093E18(void *action_state, void *actor, s32 context);
extern void func_80093ED8(void *action_state, void *actor, s32 context);
extern void func_80094088(void *action_state, void *actor, s32 context);
extern void func_800942B0(void *action_state, void *actor, s32 context);
extern void func_80094378(void *action_state, void *actor, s32 context);
extern void func_800943B8(void *action_state, void *actor, s32 context);
extern void func_800944BC(void *action_state, void *actor, s32 context);
extern void func_8009451C(void *action_state, void *actor, s32 context);
extern void func_80094944(s16 timer, s32 limit);
extern void func_80094C1C(void *action_state);
extern void func_8009503C(void *actor);
extern void func_800951B4(void *actor);
extern s32 func_8009567C(void *menu_state);
extern s32 func_80095840(void *action_state, void *menu_state);
extern s16 func_80095978(void *actor, void *map_work);
extern void func_80095A94(void *actor, s16 height, void *map_work);
extern void func_80095C80(void *actor);
extern void func_80097844(void *actor, s32 value);
extern void func_80098868(void *action_state, void *actor, s32 context);
extern s32 D_800CFCB4;
extern u8 D_800CFCEF;
/* Updates the actor and dispatches town actions from input and interaction state. */
void func_80091528(void *action_state, void *actor, s32 context)
{
    u8 *input_state = ((u8 *)(&gameWork));
    register s32 saved_context;
    u8 *map_work;
    u8 *menu_state;
    s16 sampled_height;
    u16 timer;
    s32 buttons;
    s32 action_result;
    func_80095C80(actor);
    func_800951B4(actor);
    map_work = ((u8 *)&D_800FE488);
    sampled_height = func_80095978(actor, map_work);
    if ((sampled_height - (*((s16 *) (((u8 *) actor) + 0xA)))) >= 4) {
        if (D_800CFCEF == 0) {
            func_80094378(action_state, actor, context);
            return;
        }
    }
    else
        if (D_800CFCEF == 0) {
            func_80095A94(actor, sampled_height, map_work);
        }
    timer = (*((u16 *) (((u8 *) action_state) + 0xA))) - 1;
    *((u16 *) (((u8 *) action_state) + 0xA)) = timer;
    if (((s16) timer) <= 0) {
        timer = func_800374F4(4) + 6;
        *((u16 *) (((u8 *) action_state) + 0xA)) = timer;
        func_80097844(actor, ((u16) func_800374F4(2)) + 2);
    }
    buttons = *((s32 *) (input_state + 0x10));
    if (buttons & 0x10) {
        func_800942B0(action_state, actor, context);
        return;
    }
    if (buttons & 0x40) {
        action_result = func_80095840(action_state, &D_800CFCB4);
        if (action_result != 0) {
            if (action_result == 2) {
                func_8009451C(action_state, actor, context);
                return;
            }
            func_800944BC(action_state, actor, context);
            return;
        }
        if (func_80033B2C(0xA4) != 0) {
            func_80094088(action_state, actor, context);
            return;
        }
        return;
    }
    menu_state = (u8 *) (&D_800CFCB4);
    action_result = func_8009567C(menu_state);
    if (action_result != 0) {
        if (action_result == (-1)) {
            func_80094C1C(action_state);
            func_80098868(action_state, actor, context);
            *((s32 *) (((u8 *) action_state) + 0x2C)) = 0;
            func_8008B158(*((s32 *) (menu_state + 0x10)));
            return;
        }
        func_800943B8(action_state, actor, context);
        return;
    }
    buttons = *((s32 *) (input_state + 8));
    if (!(buttons & 0x20)) {
        func_80093ED8(action_state, actor, context);
        func_80094C1C(action_state);
        func_8009503C(actor);
        return;
    }
    if (buttons & 0xF000) {
        timer = (*((u16 *) (((u8 *) action_state) + 0x3E))) - 1;
        *((u16 *) (((u8 *) action_state) + 0x3E)) = timer;
        func_80094944((s16) timer, 8);
        func_80094C1C(action_state);
        func_8009503C(actor);
        return;
    }
    action_result = func_8003BD84(*((s32 *) (((u8 *) actor) + 0xC)), *((s32 *) (((u8 *) actor) + 0x10)));
    if (action_result > 0xFFFFF) {
        func_80093E18(action_state, actor, context);
        return;
    }
    func_80093D48(action_state, actor, context);
}
