#include "common.h"
#include "shared/game_work.h"


typedef struct StatePair {
    s32 first;
    s32 second;
} StatePair;

extern u8 D_80082E6B;

extern void cardBootSelectChannelMode(s32 mode_enabled);
extern StatePair *cardBootDebounceCardPresence(void);
extern void func_80021904(void);
extern void cardBootSetPairedChoiceSelection(s32 object_addr, s32 value);
extern void cardBootUpdatePairedChoiceAnimations(s32 base_addr, StatePair *display_state, s32 *changed_flags);
extern void cardBootCloseEventsAndResumeTimer(void);
extern void cardBootDestroyCardChooser(void *entry);
extern void func_80040AA0(s32 requested_state);
extern void createDeferredResourceTransitionTask(s32 mode, s32 lookup_id, s32 payload_word_0, s32 payload_word_4);
extern void SD_Call(s32 flags);
extern void func_800A68F4(void);
extern void cardBootPollCardChooserStatus(void);


typedef struct S_8002789C_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8002789C_0;   /* object in cardBootUpdateCardChooserInput */

/* Handles menu input and refreshes the displayed state. */
void cardBootUpdateCardChooserInput(void *menu)
{
    s32 state_changed[2];
    StatePair *state;
    StatePair *display_state;
    s32 buttons;
    s32 button_flags;
    s32 selection_changed;
    s32 selection;

    buttons = gameWork.buttons;
    selection_changed = 0;
    if (buttons != 0) {
        button_flags = ((s32)gameWork.unk_010);
        if (button_flags & 0x20) {
            s32 *object;

            SD_Call(0x515);
            cardBootDestroyCardChooser((u8 *)menu - 0x20);
            cardBootCloseEventsAndResumeTimer();
            if (D_80082E6B == 3) {
                func_80040AA0(3);
            } else {
                createDeferredResourceTransitionTask(0, 0, 0, 0);
                object = (*(s32 * *)((u8 *)menu + 0x14));
                ((S_8002789C_0 *)object)->unk_1E |= 0x2000;
                if ((*(s32 *)((u8 *)menu + 0)) == 2) {
                    func_800A68F4();
                }
            }
        } else if (button_flags & 0x40) {
            SD_Call(0x503);
            cardBootSelectChannelMode((*(s32 *)((u8 *)menu + 0xC)));
            (*(s32 *)((u8 *)menu + 0x34)) = 0;
            (*(void * *)((u8 *)menu + -0x10)) = cardBootPollCardChooserStatus;
            return;
        } else if (buttons & 0xA000) {
            if (buttons & 0x8000) {
                selection = (*(s32 *)((u8 *)menu + 0xC));
                if (selection != 0) {
                    selection_changed = 1;
                }
                (*(s32 *)((u8 *)menu + 0xC)) = 0;
            } else {
                selection = (*(s32 *)((u8 *)menu + 0xC));
                if (selection == 0) {
                    selection_changed = 1;
                }
                (*(s32 *)((u8 *)menu + 0xC)) = 1;
            }
        }

        if (selection_changed != 0) {
            SD_Call(0x502);
            cardBootSetPairedChoiceSelection((*(s32 *)((u8 *)menu + 0x24)), (*(s32 *)((u8 *)menu + 0xC)));
        }
    }

    state = cardBootDebounceCardPresence();
    state_changed[0] = state->first != (*(s32 *)((u8 *)menu + 0x18));
    state_changed[1] = state->second != (*(s32 *)((u8 *)menu + 0x1C));
    display_state = state;
    (*(StatePair *)((u8 *)menu + 0x18)) = *state;
    cardBootUpdatePairedChoiceAnimations((*(s32 *)((u8 *)menu + 0x24)), display_state, state_changed);
    func_80021904();

    return;
}
