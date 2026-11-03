# Static votes for the type-flow solver

`tools/typing/type_flow_static.py` adds static evidence to `type_flow_solve.py` for holders the runtime never
labelled: functions the campaign never ran, lines it never reached, locals loaded from untyped members or call
results. The runtime solver needs cells. A holder without cells gets no seed, and every cast through it is
`unproven`, so no component through it can be whole. Static votes give such holders cells built from the declared
types around them. Runtime identity keeps priority.

## Evidence model

A static cell is `('static', T, off)`, where `T` is a named record pointer (`rec:Name*`). The voters of a static
cell are the anchor holders that named `T`. The cell joins the existing machinery as it stands:

- `node_type` and `polymorphic` use static cells like runtime cells. A holder with two static types has a share
  below 0.75, so it becomes a polymorphic boundary.
- `cast_ok` returns `static_ok` when only static cells prove a cast. `wrong` and `unproven` keep their meaning.
- At `off != 0` a cell is typed only where `T` has an embedded record at `off`. Otherwise it stays unproven.

### Anchors

Each anchor is an edge from an open holder X to a holder Y. X is open when it is `int`, `void *`, a byte or scalar
pointer, or a generated S_ view, and has no runtime cells. Y carries a named type, either declared or as the
runtime type of an open holder. Precision comes from `calibrate`, measured on AC104 against 2,842 open parameters
that have a runtime type.

| kind | edge | strength | leave-one-out precision (co-view) |
|---|---|---|---|
| slot_rt | X = callback parameter; the slot parameter carries the runtime cells of the slot's other callbacks | strong | 0.985 |
| rt_flow | Y is an open holder with runtime cells of one type (share >= 0.75) | strong | 0.983 |
| slot_typed | X = callback parameter; the slot's function-pointer type names the parameter | strong | 1.00 (31) |
| kind | X = arg0 of an update callback in a static object kind (`object_kinds.py report`) whose other callbacks agree | strong | 1.00 (19) |
| caller_all | X = parameter; every argument edge into it passes the same named type | strong | 0.965 |
| caller / callee | typed argument in / X passed to a typed parameter | medium | 0.95 / 0.85 |
| member / store / return / returned / global | load from or store into a named member, return value, global | medium | 0.83 (member) |
| flow | local or parameter assignment within one function | weak | 0.54 |
| cmp | comparison | weak | - |

An edge whose explicit pointer cast names a different record is not an anchor, because the source spells another
object. Casts to a generated view, `void *` or a byte pointer are allowed.

### Propagation and admission

- Anchors travel along the solver's own coupling adjacency (offset 0) to open holders without runtime cells,
  for at most 4 hops (`TYPE_FLOW_STATIC_HOPS`). They stop at runtime-labelled holders, at holders whose own direct
  anchors disagree, and at generic hubs. A hub is a `void *` parameter its own body never views, or a holder with
  more than 12 coupling edges.
- A label is admitted only when every non-weak anchor names the same type and either one strong anchor reaches it,
  or two independent anchors do. Two anchors are independent when they are different holders in different
  functions, or of different kinds. Weak anchors never admit a label.
- A label with anchors that disagree is `mixed`. It gets one cell per type, so the solver treats the holder as a
  boundary. `single` and `weak` labels get no cells.

### Precedence

1. Runtime first, by construction. A holder with runtime cells never gets static cells.
2. Static cells label only open holders. They never retype a named declaration; only the runtime's `mistyped`
   path can do that.
3. A static label that disagrees with a component's runtime-derived target is a `runtime_other` boundary, so the
   component stops growing there.
4. `type_flow_apply.py` keeps its runtime checks (`runtime_contradiction`, `mixed_runtime`, ...) and still compares
   native diagnostics and measured casts. Byte proof is still `tools/lanes/prove_batch.sh`.

### Verdicts

| verdict | meaning | landable |
|---|---|---|
| `whole` | as before: runtime evidence only | yes |
| `static_whole` | net casts fall, no wrong, unproven or missing-member casts, and some evidence is `static_ok`, or a node or seed is static | yes, with the usual apply and proof |
| `static_bridge` | a bridge that depends on static evidence | no: the bridge ruling needs runtime- or flow-backed declarations; take bridges from the plain solve |

## Installer respelling (simulation)

`--respell hidden_edges.tsv` rewrites the value an installer stores for each `data_alias` row (`&alias` or `alias`
in the installer's function) to `&FN:<callback>`, as the installer-names respelling will. `couple_slot` then
couples the slot with the callback. Use this to predict the unlock before that respelling lands. After it lands,
the plain graph has the edges and the flag is no longer needed.

## Commands

    type_flow_static.py census    --graph G --rt RT [--kinds kinds.json] [--respell hidden_edges.tsv] --out DIR
    type_flow_static.py calibrate --graph G --rt RT [--kinds kinds.json] --out DIR
    type_flow_static.py dryrun    --graph G --rt RT [--kinds ...] [--respell ...] --seed-tsv SEEDS --rt-seeds --out DIR
    type_flow_static.py yield     --graph G --solve DIR --baseline BASE_SOLVE [--views views.tsv] --out DIR

`dryrun` is `type_flow.py dryrun` plus `static_labels.tsv` and `static_stats.json`, with `static:<kind>` seed sources.
Apply works unchanged:
`type_flow_apply.py --graph G --solve DIR --rt RT --ids <static_whole ids> --out A [--members]`.

## Why not an external engine

Retypd (constraint-based subtype inference) and similar engines infer structure from accesses. Static votes do
something narrower: they choose among the tree's existing named records and prove each cast against them. Most
holders that stay unlabelled have no typed neighbour at all. No inference algebra creates identity without an
anchor, and a structural answer is a generated layout again. Ideas worth borrowing: separate load and store
variance for members, per-call-site instantiation of generic callees (the hub rule is a coarse version), and
calibrated weights for weak hints (as in OSPREY-style probabilistic recovery).
