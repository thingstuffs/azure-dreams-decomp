# How the tree is organised

The source tree groups code by subsystem and feature. Disc containers,
registered rows and compiler inputs keep separate identities. Start with
[the reader guides](guide/README.md) for concrete functions and call paths;
use [the source resolver](SOURCE_LAYOUT.md) whenever an old address name does
not lead to a file.

## Top-level map

| Path | Contents and authority |
| --- | --- |
| `src/` | Editable reconstructed C, including initialized tables and a small number of local headers |
| `include/` | Shared records, constants, subsystem interfaces and project SDK declaration stand-ins |
| `config/` | Symbol names, compiler/assembler recipes, module and placement manifests, split/link descriptions |
| `ledger/` | Registered rows, source-layout mappings, coverage and machine-maintained evidence/quality records |
| `link/` | Link descriptions and support used to assemble the checked images |
| `tools/` | Setup, source lookup, build, verification, naming, type and documentation tools |
| `docs/` | Reader guides, current references, known bugs and dated research evidence |
| `STATUS.md` | Generated coverage and quality snapshot from `tools/status.py` |
| `NOTICE`, `LICENSE` | Rights, dependencies, credit and the licence for original project work |

Local `bin/`, `baserom/`, `work/disc/`, `toolchain/`, `.venv/`, `build/`,
`build_slus/` and `build_ovl/` contain user inputs, installed tools or generated
outputs. They are ignored by Git; see [.gitignore](../.gitignore).
The build views adapt stable historical names to current sources. Change the
editable source, not those generated views. [BUILD.md](BUILD.md) explains how
to create them from your own disc.

## Subsystems and feature folders

| Source root | What to look for | Guide |
| --- | --- | --- |
| `src/slus/` | Resident executable, initialization, CD and sound services; grouped executable TUs | [SLUS](guide/slus.md) |
| `src/engine/` | Shared object lists, resources, scripts, graphics, audio and frame services | [Engine](guide/engine.md) |
| `src/main/` | Remaining MAIN-specific code, notably card-server support | [MAIN](guide/main.md) |
| `src/frontend/` | Card menus, settings and frontend state | [Frontend](guide/frontend.md) |
| `src/town/` | Scene, map, building, dialogue, shop, character and minigame features | [Town](guide/town.md) |
| `src/dungeon/` | Floor generation, actors, player actions, monster callbacks, items and effects | [Dungeon](guide/dungeon.md) |
| `src/movie/`, `src/ovmovie/` | Movie requests, MDEC/display lifecycle and remaining OVMOVIE code | [Movie](guide/movie.md) |

Features can have deeper folders: `src/engine/node/` owns list-node helpers,
`src/town/shop/` owns shop behavior, and `src/dungeon/monster/<name>/` groups
monster callbacks. Related functions may share a physical C file; a filename
is not a guarantee of one function or one original object file. Some folders
and names remain provisional; use the cited implementation and evidence to
assess their meaning.

## Rows, translation units and placements

A **row** identifies a registered function or data extent, for example
`town/func_8008D54C`. A **translation unit** (TU) is a compiler input and may
contain several rows and static helpers. A **placement** links a home's code
at another address or in another image, including across containers. Source
folders describe ownership, so engine and frontend source can still belong
to rows whose IDs say `town`, `dungeon` or `main`.

Run from the repository root without a disc:

```sh
python3 tools/source_layout.py path town/func_8008D54C
python3 tools/source_layout.py ids src/town/scene/copy_words_backward_from_offset.c
python3 tools/source_layout.py --root . check
```

The first resolves to `src/town/scene/copy_words_backward_from_offset.c` at
this snapshot; the second finds associated row IDs. Resolve again after a
source move. `ledger/layout.jsonl` maps homes, `ledger/layout_inline.jsonl`
records members merged into larger TUs, and placement/link records identify
reused source. Generated container indexes under `src/` list row recipes and
locations. See [source layout](SOURCE_LAYOUT.md) and [link lists](LINK_LISTS.md).

Edit the complete physical TU. Do not recreate removed per-row files or copy
a shared implementation into a second folder. Moves must update layout,
manifests, includes and proof together. A stable row ID, a symbol rename and a
source move are different operations.

## Where names, constants and types live

| Need | Start here |
| --- | --- |
| Function/data aliases and their evidence | [config/names.tsv](../config/names.tsv), [symbol rules](SYMBOLS.md), [evidence guide](EVIDENCE.md) |
| Common integer types and basic declarations | [include/common.h](../include/common.h) |
| Shared game records | [include/shared/](../include/shared/), including [entity.h](../include/shared/entity.h) and [game_work.h](../include/shared/game_work.h) |
| Reusable offset-anchored record views awaiting fuller names | [include/records/](../include/records/), [type consolidation](TYPE_CONSOLIDATION.md) |
| Named IDs, masks and selectors | Concept headers such as [item_ids.h](../include/shared/item_ids.h), [monster_ids.h](../include/shared/monster_ids.h), [actor_status_flags.h](../include/shared/actor_status_flags.h) and [object_flags.h](../include/shared/object_flags.h) |
| Function prototypes and owned data declarations | The defining feature's header under `include/<subsystem>/`; see the ownership rule below |
| Library calls with no C definition here | Project declarations in [include/sdk/](../include/sdk/), without copied SDK header text |

Keep a constant near its owning feature or shared concept and reuse existing
IDs/flags. A local implementation detail can remain local. Record the evidence
for a literal's meaning; replacing a number with an unsupported name does not
improve understanding.

`ActorRecord` and `PlayerRecord` come from `include/shared/entity.h`.
`ObjectPosition` is separate from the actor body. Actor offsets +0x24/+0x25
are fractional/integer familiar or monster MP, not a player food meter;
`max_mp` is at +0x66. Preserve widths, signedness, alignment and proven field
relationships. Legacy address names and unknown fields remain where meaning
is not established. See [the naming rules](guide/README.md#naming-and-ownership).

## Header ownership: decision 74

A function's prototype belongs in **one header for its owning source folder**,
`include/<subsystem>/<feature>.h`, grouping related functions. For example,
functions in `src/engine/node/` use
[include/engine/node.h](../include/engine/node.h). Deeper feature folders can
have corresponding deeper header paths. Rename a declaration together with
its definition and callers; do not add a header per function or C file.

A C file includes its own folder header and the owning headers of the
functions it calls. Owning headers include shared type headers rather than
other interface headers. Shared records belong under `include/shared/` or
`include/records/`; they are not repositories for unrelated function externs.
Data defined in C has one extern in its owning folder header; retail-imported
symbols without a C definition use per-image data headers. Library declarations
belong in `include/sdk/<lib>.h` and are project-written stand-ins.

Some existing declarations still have byte-sensitive exceptions. A prototype
move or type correction must preserve every consumer's complete-TU output;
keep the unresolved exception documented when it changes bytes. The
[decision record](evidence/r97_decisions.md) is authoritative, especially
61 (names), 73 (records), 74 (headers) and 75 (shared placements).

For changes and proof requirements, continue with
[CONTRIBUTING.md](../CONTRIBUTING.md). For known gameplay behavior and its
community sources, see [BUGS.md](BUGS.md).
