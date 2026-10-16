#ifndef MODULES_TOWN_OVL_3EF1C8_H
#define MODULES_TOWN_OVL_3EF1C8_H
#include "common.h"
#include "shared/game_work.h"
#include "shared/record_ptrs.h"
#include "shared/town_event_state.h"
#include "shared/town_pointees.h"
#include "shared/town_root.h"

typedef s32 (*SceneHandler3)(s32, s32, s32);
typedef struct S_8001747C_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_8001747C_0;
typedef struct S_80017824_2 {
    u8 pad_00[0x4];
    SceneHandler3 handler;
} S_80017824_2;
typedef struct S_80017824_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80017824_0;
typedef struct S_80017824_1 {
    u8 pad_00[0x8];
    s32 * unk_08;
} S_80017824_1;
typedef struct S_800178B4_3 {
    u8 pad_00[0x4];
    SceneHandler3 handler;
    s32 * unk_08;
} S_800178B4_3;
typedef struct S_800178B4_0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
} S_800178B4_0;
typedef struct S_800178B4_1 {
    u8 pad_00[0x4];
    SceneHandler3 handler;
} S_800178B4_1;
typedef struct S_800178B4_2 {
    u8 pad_00[0x8];
    s32 * unk_08;
} S_800178B4_2;
extern u8 D_8001A92C;
extern s32 D_8001E2F8;
extern s32 D_8001E634;
extern s32 D_8001E79C;
extern s32 D_8001E9C0;
extern s32 D_8001EB10;
extern s32 D_8001EC04;
extern s32 D_8001A934;
extern s32 D_8001B1F8;
extern s32 D_8001B63C;
extern s32 D_8001A93C;
extern s32 D_8001A944;
extern s32 D_8001A94C;
extern s32 D_80020E5C;
extern s32 D_8001A954;
extern s32 D_800211DC;
extern s32 D_8001A95C;
extern s32 D_8001B1FC;
extern s32 D_8001A964;
extern s32 D_8001A96C;
extern s32 D_8001AC3C;
extern s32 D_8001A974;
extern s32 D_8001B6D0;
extern s32 D_8001B824;
extern s32 D_8001C5FB;
extern s32 D_8001C64E;
extern s32 D_8001A97C;
extern s32 D_8001CDF2;
extern s32 D_8001A984;
extern s32 D_8001F560;
extern s32 D_8001A98C;
extern s32 D_8001F690;
extern s8 D_8001FB7F;
extern s32 D_8001A994;
extern s8 D_8001B7AE;
extern s8 D_8001EDD0;
extern s32 D_8001A99C;
extern s8 D_8001EF6C;
extern s8 D_8001F543;
extern s32 D_8001B208;
extern s32 D_8001A9A4;
extern s32 D_8001A9AC;
extern s32 D_8001CFB4;
extern s32 D_8001A9B4;
extern s32 D_8001A9BC;
extern s32 D_8001D270;
extern s32 D_8001A9C4;
extern s32 D_8001B718;
extern s32 D_8001B81C;
extern s32 D_8001AB4C;
extern s32 D_8001AB54;
extern s32 D_8001AB5C;
extern s16 D_8001A91E;
extern s32 D_8001AB94;
extern s32 D_8001ABE8;
extern s32 D_8001B320;
s32 func_8001A7B0(u8);
s32 func_8001A510(s32 code);
void func_8001A418(s32 code);
void func_8001A490(s32 code);
s32 func_80016164(s32 first_value, s32 second_value);
s32 func_8001A7F8(void);
s32 func_80019A04(void *table, s32 key, s32 context);
s32 *func_80019ABC(void *table, void *state, s32 key, s32 context);
s32 func_80019928();
s32 func_80019880(void);
s32 func_800196F4();
s32 func_80019778();
void func_80018F74();
s32 func_8001979C();
void func_800187AC(void);
s32 func_80019618(s32 object, s32 index);
s32 func_80019814(void *object, s32 index);
s32 func_8001A220(s32, s32, s32);
s32 func_800161C8(void);
s32 townLookupVariantWithSpecialOverrides(s32 requiredFlag, s32 completionFlag);
s32 *func_8001628C(s32 first_value, s32 second_value, s32 unused_context);
s32 townSelectTableResultWithOverride(s32 context, s32 check_value, s32 selector);
void func_80016480(s32 context, s32 entry_index);
s32 townQueryStateWithSelector10(s32 context, s32 check_value, s32 selector);
void townForwardContextValueToHandlerA(s32 input_a, s32 input_b);
s32 func_80016570(s32 context, s32 check_value, s32 selector);
void townForwardContextValueToHandlerB(s32 first_value, s32 second_value);
void *townSelectLookupWithProgressThreshold(s32 selector, s32 check_value, s32 lookup_value);
void townForwardContextValueToHandlerC(s32 context, s32 value);
s32 townSelectLookupWithCountThreshold(s32 object, s32 check_value, s32 selection);
void func_80016800(s32 context, s32 entry_index);
s32 func_80016820(s32 context, s32 check_value, s32 selector);
s32 townUpdateSceneActionFlags(s32 context, s32 check_value, s32 selector);
s32 townDispatchCode7A0ByStatus(void);
void townInvokeHandlerWithCode7A0(void);
s32 townCheckInteraction13Type3(void);
s32 townSelectInteractionResultWithRefresh(s32 input, s32 check_value, s32 context);
void townInvokeMatchCallbackOrLookup(void);
void townInvokeHandlerWithCode7A1(void);
void townInvokeAlternateHandlerWithCode7A1(void);
void func_80016BA8(void);
void townInvokeHandlerWithCode47D(void);
s32 *townSelectResponseBySelectorAndFlags(s32 context, s32 check_value, s32 selector);
s32 townWaitForDialogueThenClose(void);
s32 townSelectDialogueWith799Override(s32 speaker, s32 interaction, s32 dialogue_id);
s32 func_80016DF4(s32 handler_arg_a, s32 handler_arg_b);
s32 townSelectLookupOrThresholdFallback(s32 value, s32 check_value, s32 lookup_value);
s32 townDispatchMenuPairBy798State(s32 slot_index, s32 slot_value);
s32 townSelectObjectResponseByStatus(void *object, s32 check_mode, s32 context);
s32 townDispatchEntryBy798State(s32 handler_arg_a, s32 handler_arg_b);
s8 *townGetProgressBytePointer(void);
s32 func_80017098(s32 primaryInput, s32 secondaryInput);
s32 func_80017100(s32 value, s32 check_value, s32 lookup_value);
s32 func_80017198(s32 slot_index, s32 slot_value);
s32 townSelectOneTimeInteractionResponse(void *object, s32 check_value, s32 selection);
s32 townDispatchEntryBy799Flag(s32 context, s32 entryIndex);
s32 func_80017358(s32 context, s32 check_value, s32 selector);
s32 townDispatchEntryAndSet11FBWhenFlagged(s32 context, s32 entry_index);
s32 func_8001747C(s32 object, s32 request, s32 context);
s32 townDispatchEntryBy798And799Flags(s32 context, s32 entry_index);
s32 func_800175B4(s32 context, s32 check_value, s32 selector);
s32 townSelectModeNineLookup(s32 input, s32 context, s32 mode);
s32 func_80017724(void);
s32 func_80017758(s32 context, s32 check_value, s32 selector);
void townMarkProgressStateReady(void);
s32 townInitializeIndexedEntryOnFirst479(S_80017824_0 *obj, s32 index);
s32 func_800178B4(S_800178B4_0 *menu, s32 index);
s32 func_8001799C(s32 input, s32 check_value, s32 context);
void townForwardContextValueToHandlerD(s32 first_arg, s32 second_arg);
s32 func_80017A70(s32 context, s32 check_value, s32 selector);
void townForwardContextValueToHandlerE(s32 first_input, s32 second_input);
s32 func_80017B40(s32 context, s32 check_value, s32 selector);
void townClearProgressAndDispatchCode12CB(s32 handler_id, s32 handler_arg);
void townInvokeHandlerWithCode780(void);
void townInvokeAlternateHandlerWithCode780(void);
void townInvokeStatusHandlerWithCode780(void);
void townInvokeStatusHandlerWithCode1470(void);
void townInvokeHandlerWithCode1470(void);
void townInvokeAlternateHandlerWithCode79E(void);
void townInvokeHandlerWithCode79E(void);
void func_80017D24(void);
void townInvokeHandlerWithCode798(void);
void townInvokeHandlerWithCode799(void);
void townInvokeHandlerWithCode11FB(void);
void townInvokeAlternateHandlerWithCode11FB(void);
void func_80017E34(void);
s32 townStartCallbackWithFixedParameters(void);
/* Incomplete inherited argument-list evidence; retain the caller register passthrough. */
s32 townCheckTableResultBelowMinus47();

#endif
