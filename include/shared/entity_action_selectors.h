#ifndef SHARED_ENTITY_ACTION_SELECTORS_H
#define SHARED_ENTITY_ACTION_SELECTORS_H

/* D_800DDE84: halfwords indexed by ActorRecord.species (+0x13). Callers extract
 * two-bit selectors at shifts 0, 2, 4, 6 and 8 and pass them to the same action
 * decision routine. The selectors' individual meanings and table length are
 * not established. Byte-addressed callers retain an explicit byte view. */
typedef unsigned short EntityActionSelectors;
extern EntityActionSelectors entity_action_selectors[];

#endif
