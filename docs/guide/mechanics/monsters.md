# Monster action selection and specials

[Mechanics index](README.md) · [Dungeon source map](../dungeon.md) · [Combat](combat.md) · [Familiars](familiars.md)

## How an action is chosen

Verified by reading
[`select_creature_action_and_target`](../../../src/dungeon/actor/select_creature_action_and_target.c),
[`choose_usable_ability_or_attack`](../../../src/dungeon/actor/ability_eligibility.c)
and [`roll_actor_flag_once`](../../../src/dungeon/actor/state/roll_actor_flag_once.c).
The shared selector combines MP, statuses, side, behavior byte, nearby actors,
items and species-specific tests. Species callbacks then execute the returned
action. A numeric return code is a dispatch choice, not a universal named
attack with one fixed animation across every monster bank.

The selector can defer with -1 while work is pending. Zero integer MP selects
an idle/default path. At low MP it searches for category-12 Meat in the room,
except for Weadog. On reaching it the current C consumes it without restoring
MP, and can leave the tile's item flag set:
[DB001/DB007](../../BUGS.md#dungeon-audit-db001-db007).

Player-side, unblinded and unconfused creatures branch on behavior byte +0x12
before the ordinary species switch. They can prioritize an ability-definition
kind `0x1e` for the player or another familiar when range and the target's
HP threshold tests pass. Different behavior cases use different target scoring
and adjacent-attack preferences. Without the menu-label data binding these
numeric behavior values should not be assigned confident public command names.

Ordinary ability selection rejects an absolute height difference of 64 or
more, computes Chebyshev distance and facing, and can choose an adjacent
physical attack (action 8) if the caller prefers it and the diagonal side
check passes. Otherwise a cached eligibility roll gates the three ability
slots. Among eligible slots it tests effect already present, range, definition
kind, alignment/path for line attacks and a cyclic element score. The score
compares the definition's bits with the **acting creature's** property bits;
it is not a demonstrated target-defense damage optimizer. Strictly better
scores replace the current choice, so scan order resolves equal scores.

The scan starts at `turn_counter & 3`, wraps slot 3 to zero, and considers
three slots. A line attack checks occupancy using different masks for each
side. Magic bind blocks the eligibility roll. Other gates include distance
from the player, actor class/party flags and remembered eligibility bits;
there is no single flat spell probability valid for every state and caller.

## When the shared selector requests a species special

Verified by reading the species switch in
[`select_creature_action_and_target`](../../../src/dungeon/actor/select_creature_action_and_target.c)
and the IDs in [`monster_ids.h`](../../../include/shared/monster_ids.h).
The table describes **selection conditions**, not every effect implemented in
the linked species folder. `roll(d)` means the cached roll helper tests
`(random() & 0xffff) % d == 0` and sets actor +0x98 bit `0x100`; it rerolls
only after +0x14 bit `0x8000` has been cleared. Divisors are not asserted
independent per-frame probabilities. All rows also have earlier shared gates.

| Species folder | Additional special-selection conditions visible here |
| --- | --- |
| [Baloon](../../../src/dungeon/monster/baloon/) | `roll(16)`, forward target is the player, own HP threshold passes; requests action family 6 |
| [Troll](../../../src/dungeon/monster/troll/) | Held item is kind 15, player awareness, player within distance 10, line alignment and clear terrain path; requests attack family 1 |
| [Golem](../../../src/dungeon/monster/golem/) | `roll(4)`, player awareness, distance 2..8, aligned, height difference at most 32, compatible target along heading, clear path, byte +0xae zero |
| [Tyrant](../../../src/dungeon/monster/tyrant/) | `roll(32)`, player awareness, +0x98 bit `0x8000` clear |
| [Weadog](../../../src/dungeon/monster/weadog/) | `roll(32)`, player awareness, room present, at least one active familiar has low MP |
| [Garuda](../../../src/dungeon/monster/garuda/) | `roll(16)`, eligible adjacent active familiar within height 32, linked/global exclusion test clear; stores that target at +0xa8 |
| [Killer](../../../src/dungeon/monster/killer/) | `roll(64)` toggles +0x98 bit `0x8000`; this branch itself does not immediately return a special action |
| [Dreamin](../../../src/dungeon/monster/dreamin/) | `roll(2)`, compatible forward target not already asleep; sets +0x98 bit `0x8000` for later action processing |
| [Stealth](../../../src/dungeon/monster/stealth/) | `roll(4)`, player awareness, halfword +0xa6 zero, floor flag 4 clear |
| [Zu](../../../src/dungeon/monster/zu/) | `roll(2)`, compatible forward target without paralysis |
| [Mandara](../../../src/dungeon/monster/mandara/) | `roll(16)`, compatible forward target without confusion; sets +0x98 bit `0x8000` |
| [Picket](../../../src/dungeon/monster/picket/) | Without a held item, `roll(2)` and the player directly ahead. With a held item, the branch chooses movement/retreat logic when aware and not blind/confused. |
| [Viper](../../../src/dungeon/monster/viper/) | No held item, an egg found in the room; approaches it, then selects the special at distance one |
| [Naplass](../../../src/dungeon/monster/naplass/) | `roll(32)` selects the special branch |
| [U-Boat](../../../src/dungeon/monster/u_boat/) | At distance at least two with byte +0xb5 zero, `roll(8)` requests family 6; the nonzero-byte path checks the shared tile and awareness |
| [Glacier](../../../src/dungeon/monster/glacier/) | `roll(4)`, player awareness, aligned at distance 2..8; every step passes the terrain/height scan |
| [Blume](../../../src/dungeon/monster/blume/) | `roll(4)`, eligible adjacent active familiar within height 32 and without brainwash |
| [Saber](../../../src/dungeon/monster/saber/), [Snowman](../../../src/dungeon/monster/snowman/) | An adjacent actor has species ID `0x33`..`0x36` (the named wall/rock group) |
| [Noise](../../../src/dungeon/monster/noise/) | `roll(16)`, forward target is a party familiar other than the player |
| [Volcano](../../../src/dungeon/monster/volcano/) | Awareness, `roll(32)`, valid clear forward tile under mask `0xb712`, player distance exactly two |
| [Cyclone](../../../src/dungeon/monster/cyclone/) | `roll(8)`, forward nonplayer party target without paralysis |
| [Pulunpa](../../../src/dungeon/monster/pulunpa/) | Byte +0xa7 nonzero, +0xa8 zero, player ahead |
| [Manoeva](../../../src/dungeon/monster/manoeva/) | Fallback branch excludes a tested transformed flag, then considers eligible forward species or a floor item according to byte +0xac |

Most immediately selected specials above return family 5 with action word
`0x8009`; the explicit exceptions and modifier-only branches are described
in their rows. The caller and bank controller determine the effect.

## Concrete execution examples

Verified by reading the following effect bodies:

- [Barong's replacement selector](../../../src/dungeon/monster/barong/select_random_replacement_item.c)
  makes up to 16 candidate attempts, excludes eggs/coins and disabled entries,
  then replaces the four-byte item. For balls it derives a charge parameter
  from integer MP (except subtype 17). Its rarity comparison rereads the input,
  so candidate rarity is not enforced:
  [B001](../../BUGS.md#barong-item-rarity).
- [Picket's pickup helper](../../../src/dungeon/monster/picket/pick_up_adjacent_item.c)
  first copies/removes a forward ground item, otherwise probes the forward
  actor. For the player it checks inventory/item eligibility; for another
  actor it can transfer the held word at +0x48, excluding the tested flag.
  This helper alone does not prove a second usable duplicate item; the
  [Manoeva/Picket report remains unresolved](../../BUGS.md#manoevapicket-item-duplication).
- [Viper's item-grab callback](../../../src/dungeon/monster/viper/update_viper_item_grab.c)
  copies an adjacent kind-18 egg into the actor's held-item group, removes
  the ground record, animates the lunge and return, then charges `0x100`
  raw MP (one MP) and advances statuses.
- [Kraken's constructor](../../../src/dungeon/monster/kraken/spawn_kraken.c)
  explicitly assigns the Kraken species ID and distinguishes familiar/side
  spawn modes. The ordinary unforced spawn can install sleep with duration
  `(random & 63) | 32` when its resistance check permits it. This is a spawn
  condition, not a claim about its unreviewed special attack.

Other source routes include [Kid](../../../src/dungeon/monster/kid/) and
[Arachne](../../../src/dungeon/monster/arachne/) for
[level-triggered replacement](familiars.md#evolution-after-leveling), and
[Kewne](../../../src/dungeon/monster/kewne/) for the entry action shown in the
dungeon folder guide. Species that lack a hard-coded branch above can still
have template abilities and controller-specific actions. The remaining folders
can be reached through the [dungeon index](../../../src/dungeon/INDEX.md).

Folder labels and slot variants are a navigation aid; the existing dungeon
guide cautions that some bank/species associations remain provisional. A
complete all-bank special-effect catalog needs constructor IDs, callback
dispatch and effect-body checks together. It is not implied by these links.

## Original-bug reading routes

The [bug catalog](../../BUGS.md) links exact affected functions:

- [U-Boat and Mazarr B017](../../BUGS.md#mazarr-and-an-exhausted-u-boat): pending
  level-up ownership conflicts with its exhausted-state handler.
- [Golem B028](../../BUGS.md#golem-idle-animation-and-select): an idle reservation
  and null callback can survive Select/watchdog recovery.
- [Salamander B023](../../BUGS.md#off-screen-salamander-kill-softlock) and
  [B025](../../BUGS.md#salamander-attacks-that-miss): EXP/removal ownership and
  the distance-zero corner check are distinct defects.
- [Manoeva/Oleem B024](../../BUGS.md#oleem-and-an-item-form-manoeva): two completion
  paths consume one reserved action.
- [Gaia Shoot B018](../../BUGS.md#gaia-shoot-uses-water): the caller supplies
  water flags, changing affinity and visuals regardless of the move name.
