#include "common.h"
extern void update_actor_spell_action(void *,void *,void *,void *);

/* Logical switch allocation owned by update_actor_spell_action.
 * This ledger projection is not included in the native TU. The complete
 * C switch owner independently emits every physical case relocation. */
const void *const D_80170838[7]={
 ((u8 *)update_actor_spell_action+0x11C),
 ((u8 *)update_actor_spell_action+0x114),
 ((u8 *)update_actor_spell_action+0x10C),
 ((u8 *)update_actor_spell_action+0x124),
 ((u8 *)update_actor_spell_action+0xCC),
 ((u8 *)update_actor_spell_action+0xC4),
 ((u8 *)update_actor_spell_action+0xBC),
};
