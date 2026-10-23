# Items: kinds, effects and rarity

[Mechanics index](README.md) · [Familiars](familiars.md) · [Dungeon generation](dungeon-generation.md) · [Prices](town.md#shops-and-prices)

## Four-byte entries and kind dispatch

Verified by reading
[`item_ids.h`](../../../include/shared/item_ids.h),
[`dispatch_dungeon_category_action`](../../../src/dungeon/player/dispatch_dungeon_category_action.c)
and [`process_dungeon_menu_selection`](../../../src/dungeon/player/process_dungeon_menu_selection.c).
An item entry has subtype ID at +0, kind at +1, a parameter at +2 and flags
at +3. The parameter is kind-specific: a charge count, signed equipment
modifier or egg heat count, for example. It is not a universal item level.

| Kind | Header name / role | Route to read |
| --- | --- | --- |
| 0 | None | Empty entry |
| 1, 2, 3 | Herb, fruit, seed | Per-subtype callback from `D_800DD6B8[kind-1][id-1]` |
| 4 | Ball | [`use_magic_ball`](../../../src/dungeon/item/use_magic_ball.c) |
| 5, 6, 7 | Scroll, crystal, bell | Per-subtype callback; shared food/target fallback can apply |
| 8, 9, 10 | Glasses, loupe, sand | Per-subtype callback; reveal/identify/charge handlers below |
| 11..13 | Not named by this header | Retain numeric kind when a specific branch uses it; kind 12 includes Meat and Blue Collar |
| 14 | Coin | Category-specific data and value handling |
| 15, 16, 17 | Sword, wand, shield | Equipment handlers and signed parameter; [combat](combat.md#physical-damage) |
| 18, 19 | Egg, familiar | Egg special dispatch, heating, familiar registry and deployment |
| 20, 21 | Elevator, trap | Floor objects; traps dispatch the floor slot handler at the actor tile |

The category dispatcher reconstructs a callback pointer from the low 24 bits
of a tagged table word; a nonzero high-byte tag also triggers a preparation
call. Ordinary categories use both kind and subtype. Eggs and traps take
special branches before that lookup. A kind name alone does not identify a
particular use effect.

## Checked use effects

Verified by reading the linked handlers below. These are effect-body rules;
a complete mapping of every subtype to its callback is not established here.
Many handlers defer the player to an action callback first. A creature target
may instead refuse/eat the item through its species food preference; refusal
can put the item back. A global/item target can take another branch entirely.
[`dispatch_item_target_action`](../../../src/dungeon/item/dispatch_item_target_action.c)
selects preference bits 0..1 or 4..5 depending on item-definition flag `0x8000`.
See [MP feeding amounts](leveling.md#mp-is-an-88-quantity).

| Handler | Implemented effect after its target/preference checks |
| --- | --- |
| [`use_item_to_heal_small_random_amount`](../../../src/dungeon/item/use_item_to_heal_small_random_amount.c) | Queues `min(max_hp-hp, (random & 3)+7)` HP: 7..10 before the missing-HP cap |
| [`use_item_to_increase_attack`](../../../src/dungeon/item/use_item_to_increase_attack.c) | At the effective attack limit, raises base attack by one below 255 and recomputes limits; raises current attack by one if below its limit and 255 |
| [`use_item_to_increase_defense`](../../../src/dungeon/item/use_item_to_increase_defense.c) | Corresponding base/current defense operation |
| [`use_item_to_increase_luck`](../../../src/dungeon/item/use_item_to_increase_luck.c) | Increments luck byte below 255; the player turn updater can later overwrite its own luck byte |
| [`use_level_gain_item`](../../../src/dungeon/item/use_level_gain_item.c) | Below level 99, seeds EXP to the next threshold and clears pending EXP |
| [`use_item_to_apply_poison`](../../../src/dungeon/item/use_item_to_apply_poison.c) | Requests poison status with value 8; feedback has the slot-index bug |
| [`use_item_to_stop_magic_drain`](../../../src/dungeon/item/use_item_to_stop_magic_drain.c) | For the creature branch, requests no-MP-drain status with value 16 |
| [`use_item_to_reveal_elevator`](../../../src/dungeon/item/use_item_to_reveal_elevator.c) | Global-target branch sets floor flag `0x100` |
| [`use_item_to_reveal_items`](../../../src/dungeon/item/use_item_to_reveal_items.c) | Global-target branch sets floor flag `0x200` |
| [`use_item_to_reveal_traps`](../../../src/dungeon/item/use_item_to_reveal_traps.c) | Global-target branch sets floor flag `0x800` |
| [`use_item_to_increase_ball_charges`](../../../src/dungeon/item/use_item_to_increase_ball_charges.c) | Selected-item branch increments a kind-4 charge parameter below 99 |

The ball handler rejects a zero-charge use; a completed cast decrements the
charge parameter. When fed to a creature, a ball with signed parameter at
least 10 and ID below 16 can teach its spell group in an empty ability slot,
choosing the creature's elemental variant and stored/effective level
`parameter / 10`. An already-known group takes the consume branch. Lower
charge counts and other IDs use the ordinary feeding route. Verified by
reading [`use_magic_ball`](../../../src/dungeon/item/use_magic_ball.c).

Known effect exceptions include the area level-up item's user-level test
(DB002), and status feedback treating successful slot zero as false and
rejected -1 as true (DB003-DB006):
[dungeon item audit](../../BUGS.md#dungeon-audit-db001-db007).

## Identification and curses

Verified by reading
[`identify_selected_item`](../../../src/dungeon/item/identify_selected_item.c),
[`clear_selected_item_flag_400`](../../../src/dungeon/actor/effect/effect.c),
[`get_item_category_flags`](../../../src/engine/item/get_item_category_flags.c)
and [`get_item_name_text`](../../../src/engine/item/get_item_name_text.c).
Identification has both instance and category state. The selected-item path
clears entry flag `0x80`, clears the recorded category/subtype pair and clears
definition flag `0x400`. Name selection consults the category flag query and
can return an unknown-name fallback. The query is mode-dependent and treats
balls/equipment differently from ordinary definition flags; do not collapse
these into one global identified Boolean.

Verified by reading
[`equip_item_and_update_status`, `change_equipped_item_and_notify`](../../../src/dungeon/player/equipment_status_g00319.c).
Equipment flag `0x40` blocks replacing/removing the current item. Equipping
clears the parameter-hidden flag `0x80`, sets equipped flag `0x20`, and cursed
equipment sets the actor's curse flag. The de-curse handler clears the Cursed
slot and equipment `0x40` flags but can leave the actor curse effect active:
[B014](../../BUGS.md#de-curse-leaves-the-curse-effect).

## Floor rarity

Verified by reading `build_cumulative_item_weights`,
`select_weighted_floor_item`, `select_floor_item_with_special_overrides` and
`init_random_floor_item_parameters` in
[`spawn.c`](../../../src/dungeon/level/spawn.c).
Ordinary selection scans kinds 1..18 and IDs 1 through each category's
`count-1`. Definition flag `0x10` excludes an entry; flag `0x40` excludes it
unless mode equals 2. The rarity field is `(flags & 0x3000) >> 12`:

| Rarity field | Weight per eligible item |
| --- | ---: |
| 0 | 128 |
| 1 | 85 |
| 2 | 32 |
| 3 | 1 |

The code totals weights cumulatively across categories, rolls
`random16 % total`, then scans the chosen category's eligible entries. A
probability proportional to weight is **inferred** from this selection method;
modulo bias and the actual boundary bug mean it is not an exact published
percentage. Equality at a category endpoint selects the exhausted category
and can return kind/ID zero: [B004](../../BUGS.md#b004--cumulative-boundaries-lose-floor-items).
This function does not multiply a rarity weight by floor number.

Floor-specific exceptions are separate. In mode zero and before a special
has been selected, the wrapper can request these pairs:

| Floor | Kind/ID | Additional source tests |
| --- | --- | --- |
| 12 | 12/4 (Blue Collar) | Player byte +0xfb is zero |
| 15 | 13/1 | Resident bit `0x145e` set, `0x1460` clear, pair not already recorded |
| 20 | 13/6 | Resident bit `0xac` set, `0x12c6` clear, pair not already recorded |
| 28 | 1/8 (Healing Herb in the bug catalog) | Resident bit `0xfc3` set, `0xfad` clear, pair not already recorded |

The ordinary population loop also tracks fruit/egg overrides from counters
and RNG; eggs sample the floor species pool. A pending fruit override uses
kind 2, ID 1 except when `(random & 15)==0`, which selects ID 2. These
overrides are not evidence that every item has its own floor rarity table.
Item rooms skip special selection and can fill the low slots before ordinary
population reaches the wrapper, suppressing the special:
[B029](../../BUGS.md#special-encounter-and-item-records-overwritten).

Parameter generation is also distinct from rarity. Balls normally start with
`(random & 7) | 4` charges, except subtype 17 starts at one. Swords/shields
can receive a small signed modifier before the shared equipment branch;
that branch independently sets parameter -1 and curse bit `0x40` when
`(random & 7)==0`. Sword subtype 9 starts cursed. Wands go directly through
the shared branch. Eggs receive the heat count described in
[Familiars](familiars.md#finding-eggs-and-heating-them).

Barong uses another replacement selector, not this weighted floor roll. Its
rarity comparison reads the original item again, so it accepts the first
otherwise eligible replacement without enforcing that item's rarity:
[B001](../../BUGS.md#barong-item-rarity).
