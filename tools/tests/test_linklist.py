"""Link lists (docs/LINK_LISTS.md): load checks, address rules, input binding, resolver and proof-view guards.
No retail data needed; the objcopy test needs the mipsel binutils the gate already requires."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest

TOOLS = Path(__file__).resolve().parents[1]
sys.path[:0] = [str(TOOLS / 'lanes'), str(TOOLS), str(TOOLS / 'gate')]
import linklist as K
import source_layout as L
from lanes import proof_receipts as P

HOME = {"row": "dungeon/func_80F8A664", "tu": "src/dungeon/func_80F8A664.c", "home": "dungeon/func_80F8A664",
        "foff": "0xFAA664", "vma": "0x80173E64", "size": 56, "bindings": {}}
COPY = {"row": "dungeon/func_80F90664", "tu": "src/dungeon/func_80F8A664.c", "home": "dungeon/func_80F8A664",
        "foff": "0xFB0664", "vma": "0x8016DE64", "size": 56, "bindings": {}}


def image(name, foff, vma, entries, size="0x6000", layout="bank_family", **extra):
    doc = {"schema": K.SCHEMA, "image": "dungeon/" + name, "container": "dungeon", "foff": foff, "size": size,
           "vma": vma, "entries": entries}
    if layout:
        doc["layout"] = layout
    doc.update(extra)
    return doc


class Fixture(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR'))
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name).resolve()
        (self.root / "config").mkdir()

    def write(self, *docs):
        d = self.root / "config/link/dungeon"
        if d.exists():
            shutil.rmtree(d)
        d.mkdir(parents=True)
        for doc in docs:
            (d / (doc["image"].split("/")[1] + ".json")).write_text(json.dumps(doc))

    def pair(self, copy=None, **copy_image):
        self.write(image("bank_fa7000", "0xFA7000", "0x80170800", [HOME]),
                   image("bank_fad000", "0xFAD000", "0x8016A800", [dict(COPY, **(copy or {}))], **copy_image))
        return K.load(self.root)


class Inert(Fixture):
    def test_no_link_directory_changes_nothing(self):
        self.assertEqual(K.load(self.root), ({}, {}, {}, {}))
        self.assertIsNone(K.placement(self.root, "dungeon", 0xFB0664, row="dungeon/func_80F90664"))
        self.assertEqual(K.window_files(self.root, ["dungeon/func_80F90664"]), [])
        self.assertEqual(K.evidence_offsets(self.root, "dungeon", {0xFB0664}), set())
        self.assertEqual(K.check(self.root, {}, {}, lambda rid: None), [])


class Load(Fixture):
    def test_valid_pair(self):
        images, by_place, by_row, local = self.pair()
        self.assertEqual(by_place[("dungeon", 0xFB0664)]["row"], COPY["row"])
        self.assertEqual(local["dungeon/bank_fad000"][0x80173E64], [("dungeon/bank_fa7000", 0x8016DE64)])

    def test_refusals(self):
        cases = [({"vma": "0x8016DE68"}, "image vma"), ({"foff": "0xFB3000"}, "outside"), ({"size": 52}, "size differs"),
                 ({"home": "dungeon/func_X"}, "not placed"), ({"tu": "src/dungeon/other.c"}, "share the TU"),
                 ({"extra": 1}, "entry keys"), ({"row": "town/func_80F90664"}, "another container")]
        for change, message in cases:
            with self.subTest(change=change):
                with self.assertRaisesRegex(ValueError, message):
                    self.pair(change)
        bad_home = dict(HOME, bindings={"0x1": "0x2"})
        self.write(image("bank_fa7000", "0xFA7000", "0x80170800", [bad_home]))
        with self.assertRaisesRegex(ValueError, "home entry takes no bindings"):
            K.load(self.root)
        second = dict(COPY, row="dungeon/func_80F90600", foff="0xFB0640", vma="0x8016DE40")
        self.write(image("bank_fa7000", "0xFA7000", "0x80170800", [HOME]),
                   image("bank_fad000", "0xFAD000", "0x8016A800", [COPY, second]))
        with self.assertRaisesRegex(ValueError, "out of order or overlapping"):
            K.load(self.root)
        self.write(image("bank_fa7000", "0xFA7000", "0x80170800", [HOME]),
                   dict(image("bank_fad000", "0xFAD000", "0x8016A800", [COPY]), container="town"))
        with self.assertRaisesRegex(ValueError, "outside its container directory"):
            K.load(self.root)

    def test_placement_names_its_row(self):
        self.pair()
        self.assertEqual(K.placement(self.root, "dungeon_engine", 0xFB0664)["row"], COPY["row"])
        with self.assertRaisesRegex(ValueError, "names dungeon/func_80F90664"):
            K.placement(self.root, "dungeon", 0xFB0664, row="dungeon/func_80F9FFFF")


class Rules(Fixture):
    def test_rules_in_order(self):
        _, _, by_row, _ = self.pair({"bindings": {"0x80171000": "0x80123456"}}, symbols={"0x800D0000": "0x800D1000"})
        e = by_row[COPY["row"]]
        b = lambda a: K.binding(self.root, e, a)
        self.assertEqual(b(0x80173E64), 0x8016DE64)       # 1 own entry
        self.assertEqual(b(0x80171000), 0x80123456)       # 2 explicit
        self.assertEqual(b(0x80171138), 0x8016B138)       # 4 same layout, inside the home image
        self.assertEqual(b(0x800D0000), 0x800D1000)       # 5 image symbols
        self.assertEqual(b(0x800AB464), 0x800AB464)       # 6 resident
        self.assertEqual(K.binding(self.root, by_row[HOME["row"]], 0x80171138), 0x80171138)  # home: unchanged

    def test_no_layout_tag_means_no_shift(self):
        _, _, by_row, _ = self.pair(layout=None)
        self.assertEqual(K.binding(self.root, by_row[COPY["row"]], 0x80171138), 0x80171138)

    def test_local_definition_wins_and_is_keyed_by_home_image(self):
        helper_home = {"row": "dungeon/func_800CF1BC", "tu": "src/dungeon/func_800CF1BC.c", "home": "dungeon/func_800CF1BC",
                       "foff": "0xEF1BC", "vma": "0x800D491C", "size": 56}
        helper_copy = dict(helper_home, row="dungeon/func_80FB0700", foff="0xFB0700", vma="0x8016DF00")
        # another TU whose home (another bank) shares the vma of a home-image function of COPY's TU
        alias_home = {"row": "dungeon/func_81000000", "tu": "src/dungeon/func_81000000.c", "home": "dungeon/func_81000000",
                      "foff": "0x1000938", "vma": "0x80171138", "size": 8}
        alias_copy = dict(alias_home, row="dungeon/func_80FB0800", foff="0xFB0800", vma="0x8016E000")
        self.write(image("engine", "0xA0000", "0x80085760", [helper_home], size="0x60000", layout=None),
                   image("bank_fa7000", "0xFA7000", "0x80170800", [HOME]),
                   image("bank_x", "0x1000000", "0x80170800", [alias_home], layout="other"),
                   image("bank_fad000", "0xFAD000", "0x8016A800", [COPY, helper_copy, alias_copy]))
        e = K.load(self.root)[2][COPY["row"]]
        self.assertEqual(K.binding(self.root, e, 0x800D491C), 0x8016DF00)  # rule 3, outside the home image
        # 0x80171138 lies in COPY's home image: it is THAT image's function (rule 4), not bank_x's TU
        self.assertEqual(K.binding(self.root, e, 0x80171138), 0x8016B138)

    def test_ambiguous_local_address_fails_closed(self):
        a = {"row": "dungeon/func_81000000", "tu": "src/dungeon/a.c", "home": "dungeon/func_81000000",
             "foff": "0x1000000", "vma": "0x800F0000", "size": 8}
        b = dict(a, row="dungeon/func_82000000", tu="src/dungeon/b.c", home="dungeon/func_82000000", foff="0x2000000")
        self.write(image("bank_fa7000", "0xFA7000", "0x80170800", [HOME]),
                   image("img_a", "0x1000000", "0x800F0000", [a], layout=None),
                   image("img_b", "0x2000000", "0x800F0000", [b], layout=None),
                   image("bank_fad000", "0xFAD000", "0x8016A800",
                         [COPY, dict(a, row="dungeon/func_80FB0700", foff="0xFB0700", vma="0x8016DF00"),
                          dict(b, row="dungeon/func_80FB0800", foff="0xFB0800", vma="0x8016E000")]))
        e = K.load(self.root)[2][COPY["row"]]
        with self.assertRaisesRegex(ValueError, "home of 2 TUs"):
            K.binding(self.root, e, 0x800F0000)


class Inputs(Fixture):
    def test_window_files_bind_placements_only(self):
        self.pair()
        self.assertEqual(K.window_files(self.root, [HOME["row"]]), [])
        self.assertEqual(K.window_files(self.root, ["dungeon/func_unrelated"]), [])
        self.assertEqual(K.window_files(self.root, [COPY["row"]]),
                         ["config/link/dungeon/bank_fa7000.json", "config/link/dungeon/bank_fad000.json"])
        self.assertEqual(K.evidence_offsets(self.root, "dungeon", {0xFB0664, 0xFAA664}), {0xFAA664})

    def test_window_files_include_rule3_home_images(self):
        helper_home = {"row": "dungeon/func_800CF1BC", "tu": "src/dungeon/h.c", "home": "dungeon/func_800CF1BC",
                       "foff": "0xEF1BC", "vma": "0x800D491C", "size": 56}
        self.write(image("engine", "0xA0000", "0x80085760", [helper_home], size="0x60000", layout=None),
                   image("bank_fa7000", "0xFA7000", "0x80170800", [HOME]),
                   image("bank_fad000", "0xFAD000", "0x8016A800",
                         [COPY, dict(helper_home, row="dungeon/func_80FB0700", foff="0xFB0700", vma="0x8016DF00")]))
        self.assertIn("config/link/dungeon/engine.json", K.window_files(self.root, [COPY["row"]]))

    def test_cross_container_home_compiles_with_its_own_family_evidence(self):
        # decision 75 (A): a dungeon placement of a town home binds the TOWN scope, under a separate key
        town_home = {"row": "town/func_8008D7CC", "tu": "src/town/t.c", "home": "town/func_8008D7CC",
                     "foff": "0x1B7CC", "vma": "0x8008D7CC", "size": 56}
        self.write(image("bank_fa7000", "0xFA7000", "0x80170800", [HOME]),
                   image("bank_fad000", "0xFAD000", "0x8016A800",
                         [COPY, dict(town_home, row="dungeon/func_80FB0800", foff="0xFB0800", vma="0x8016E000")]))
        d = self.root / "config/link/town"
        d.mkdir(parents=True)
        (d / "engine.json").write_text(json.dumps(dict(image("engine", "0x0", "0x80072000", [town_home], size="0x80000",
                                                               layout=None), image="town/engine", container="town")))
        e = K.load(self.root)[2]["dungeon/func_80FB0800"]
        self.assertEqual(K.evidence_scope(self.root, e), ("town", 0x1B7CC))
        self.assertEqual(K.evidence_offsets(self.root, "dungeon", {0xFB0664, 0xFB0800}), {0xFAA664})
        self.assertEqual(K.cross_evidence(self.root, "dungeon", {0xFB0664, 0xFB0800}), {"town": {0x1B7CC}})
        with self.assertRaisesRegex(ValueError, "evidence_scope"):
            K.evidence_foff(self.root, e)


class Check(Fixture):
    def test_split_registry_and_module_consistency(self):
        self.pair()
        split = lambda name, foff, vma, **kw: dict({"func_vram": name, "foff": foff, "size": 56, "result": "MATCH",
                                                     "vram": 0, "true_vram": vma}, **kw)
        splits = {"dungeon": [split("func_80F8A664", 0xFAA664, 0x80173E64), split("func_80F90664", 0xFB0664, 0x8016DE64)]}
        reg = {HOME["row"]: {"c_path": "x/func_80F8A664.c"}, COPY["row"]: {"c_path": "x/func_80F90664.c", "source_row": HOME["row"]}}
        tu = lambda rid: "src/dungeon/func_80F8A664.c"
        self.assertEqual(K.check(self.root, splits, reg, tu), [])
        bad = dict(splits, dungeon=[splits["dungeon"][0], split("func_80F90664", 0xFB0664, 0x8016DE68)])
        self.assertTrue(any("vma" in p for p in K.check(self.root, bad, reg, tu)))
        bad = dict(splits, dungeon=[splits["dungeon"][0], split("func_80F90664", 0xFB0664, 0x8016DE64, result="FAIL")])
        self.assertTrue(any("not a MATCH" in p for p in K.check(self.root, bad, reg, tu)))
        stale = dict(reg); stale[COPY["row"]] = {"c_path": "x/func_80F90664.c"}
        self.assertTrue(any("source_row" in p for p in K.check(self.root, splits, stale, tu)))
        orphan = dict(reg); orphan["dungeon/func_1"] = {"c_path": "x", "source_row": HOME["row"]}
        self.assertTrue(any("no link list places it" in p for p in K.check(self.root, splits, orphan, tu)))
        self.assertTrue(any("tu src" in p for p in K.check(self.root, splits, reg, lambda rid: "src/dungeon/moved.c")))
        (self.root / "config/overlays").mkdir()
        (self.root / "config/overlays/modules.json").write_text(json.dumps({"modules": [{"members": [{"id": HOME["row"]}]}]}))
        self.assertEqual(K.check(self.root, splits, reg, tu), [])      # a module-member home is allowed
        (self.root / "config/overlays/modules.json").write_text(json.dumps({"modules": [{"members": [{"id": COPY["row"]}]}]}))
        self.assertTrue(any("module member" in p for p in K.check(self.root, splits, reg, tu)))


@unittest.skipUnless(shutil.which("mipsel-linux-gnu-as") and shutil.which(K.OBJCOPY), "mipsel binutils")
class Rebind(Fixture):
    def test_object_symbols_follow_the_address_rules(self):
        self.pair()
        src = self.root / "t.s"
        src.write_text(".section .text.func_80173E64,\"ax\"\n.globl func_80173E64\nfunc_80173E64:\n"
                       " jal func_80171138\n nop\n jal func_800AB464\n nop\n")
        obj = self.root / "t.o"
        subprocess.run(["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-o", str(obj), str(src)], check=True)
        e = K.load(self.root)[2][COPY["row"]]
        log = self.root / "rebind.txt"
        renames = K.rebind_object(self.root, e, obj, log=log)
        self.assertEqual(renames, {"func_80173E64": "func_8016DE64", "func_80171138": "func_8016B138"})
        names = subprocess.run([K.NM, str(obj)], capture_output=True, text=True, check=True).stdout
        self.assertIn("T func_8016DE64", names); self.assertIn("U func_8016B138", names); self.assertIn("U func_800AB464", names)
        sections = subprocess.run(["mipsel-linux-gnu-objdump", "-h", str(obj)], capture_output=True, text=True).stdout
        self.assertIn(".text.func_8016DE64", sections)
        self.assertEqual(K.rebind_object(self.root, K.load(self.root)[2][HOME["row"]], obj), {})

    def _asm(self, body):
        src = self.root / "a.s"
        src.write_text(".section .text.func_80173E64,\"ax\"\n.globl func_80173E64\nfunc_80173E64:\n" + body)
        obj = self.root / "a.o"
        subprocess.run(["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-o", str(obj), str(src)], check=True)
        return obj

    def test_two_references_merge_onto_one_destination(self):
        # opus_place1: the destination keeps one table where the home kept two -> both references bind to it
        self.pair(copy={"bindings": {"0x80174AD4": "0x8016E000", "0x80174AFC": "0x8016E000"}})
        obj = self._asm(" lui $2,%hi(D_80174AD4)\n lw $2,%lo(D_80174AD4)($2)\n"
                        " lui $3,%hi(D_80174AFC)\n lw $3,%lo(D_80174AFC)($3)\n")
        renames = K.rebind_object(self.root, K.load(self.root)[2][COPY["row"]], obj)
        self.assertEqual(renames["D_80174AD4"], "D_8016E000")
        self.assertEqual(renames["D_80174AFC"], "D_8016E000")
        names = subprocess.run([K.NM, str(obj)], capture_output=True, text=True, check=True).stdout
        self.assertNotIn("D_80174AD4", names); self.assertNotIn("D_80174AFC", names)
        rel = subprocess.run(["mipsel-linux-gnu-readelf", "-rW", str(obj)], capture_output=True, text=True).stdout
        self.assertEqual(rel.count("D_8016E000"), 4)

    def test_a_definition_never_merges(self):
        # a reference binding onto the placement's own (defined) entry name is still a collision
        self.pair(copy={"bindings": {"0x80174AD4": "0x8016DE64"}})
        obj = self._asm(" lui $2,%hi(func_80174AD4)\n lw $2,%lo(func_80174AD4)($2)\n")
        with self.assertRaises(SystemExit):
            K.rebind_object(self.root, K.load(self.root)[2][COPY["row"]], obj)


class Resolver(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')); self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name).resolve()
        (self.root / "ledger").mkdir()
        self.rows = [{"id": "dungeon/func_A", "container": "dungeon", "c_path": "overlays/dungeon/func_A.c"},
                     {"id": "dungeon/func_B", "container": "dungeon", "c_path": "overlays/dungeon/func_B.c",
                      "source_row": "dungeon/func_A"},
                     {"id": "dungeon/func_C", "container": "dungeon", "c_path": "overlays/dungeon/func_C.c"}]
        (self.root / "ledger/rows.jsonl").write_text("".join(json.dumps(r) + "\n" for r in self.rows))
        for name in ("func_A", "func_C", "local.h"):
            p = self.root / "src/dungeon" / (name if name.endswith(".h") else name + ".c")
            p.parent.mkdir(parents=True, exist_ok=True); p.write_text(name + "\n")

    def test_placement_resolves_to_its_home(self):
        home = self.root / "src/dungeon/func_A.c"
        self.assertEqual(L.row_path("dungeon/func_B", self.root), home)
        self.assertEqual(L.row_path({"container": "dungeon", "c_path": "func_B.c"}, self.root), home)
        self.assertEqual(L.validate(self.root), 3)
        self.assertEqual([rid for rid, _ in L.source_items(self.root)], ["dungeon/func_A", "dungeon/func_C"])
        self.assertEqual(L.row_ids_for_paths(["src/dungeon/func_A.c"], self.root), ["dungeon/func_A", "dungeon/func_B"])
        self.assertEqual(L.row_ids_for_paths(["src/dungeon/func_B.c"], self.root), ["dungeon/func_B"])
        (self.root / "ledger/layout.jsonl").write_text(json.dumps({"id": "dungeon/func_B", "path": "src/dungeon/x/func_B.c"}) + "\n")
        with self.assertRaisesRegex(ValueError, "placement has no source path"):
            L.row_path("dungeon/func_C", self.root)

    def test_chained_placement_refused(self):
        self.rows[2]["source_row"] = "dungeon/func_B"
        (self.root / "ledger/rows.jsonl").write_text("".join(json.dumps(r) + "\n" for r in self.rows))
        with self.assertRaisesRegex(ValueError, "own-file home"):
            L.row_path("dungeon/func_C", self.root)

    def test_projection_plan_is_the_projection_and_the_view_check_is_exact(self):
        view = self.root / "build_ovl"; view.mkdir()
        flat = L.materialize_flat(view / "layout_flat", self.root)
        self.assertEqual(flat, view / "layout_flat")
        plan = L.projection_plan(self.root)
        self.assertEqual(sorted(plan), ["dungeon/func_A.c", "dungeon/func_B.c", "dungeon/func_C.c", "dungeon/local.h"])
        self.assertEqual(os.readlink(flat / "dungeon/func_B.c"), str(self.root / "src/dungeon/func_A.c"))
        facade = view / "overlays/dungeon/first_pass_matched"; facade.parent.mkdir(parents=True)
        facade.symlink_to(flat / "dungeon", target_is_directory=True)
        source_dir = "overlays/dungeon/first_pass_matched"
        current = lambda: P._projection_current(self.root, view, source_dir, "dungeon")
        self.assertTrue(current())
        shadow = flat / "dungeon/common.h"; shadow.write_text("#define X 1\n")   # unmanaged real file
        self.assertFalse(current())
        shadow.unlink(); self.assertTrue(current())
        stale = flat / "dungeon/func_B.c"; stale.unlink()
        (self.root / "func_B_copy.c").write_text("old copy\n"); stale.symlink_to(self.root / "func_B_copy.c")
        self.assertFalse(current())
        self.assertEqual(L.materialize_flat(view / "layout_flat", self.root), flat)
        self.assertTrue(current())
        (flat / ".source_layout_projection").unlink(); self.assertFalse(current())


class ViewLinkDirectory(unittest.TestCase):
    def test_view_must_read_the_canonical_link_lists(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get('TMPDIR')) as td:
            root = Path(td) / "root"; view = Path(td) / "view"
            for name in ('src', 'include', 'ledger', 'config/overlays', 'toolchain', '.venv'):
                (root / name).mkdir(parents=True, exist_ok=True)
                q = view / name; q.parent.mkdir(parents=True, exist_ok=True); q.symlink_to(root / name)
            def refused():
                try:
                    P.validate_view(root, view, 'config/overlays/none.overlay.yaml')
                except ValueError as exc:
                    return 'config/link' in str(exc)
                except Exception:
                    return False
                return False
            self.assertFalse(refused())                      # neither side has link lists
            (view / 'config/link').symlink_to(root / 'config/link')
            self.assertFalse(refused())                      # dangling managed link (tree without lists)
            (root / 'config/link/dungeon').mkdir(parents=True)
            self.assertFalse(refused())
            (view / 'config/link').unlink(); (view / 'config/link').mkdir()
            self.assertTrue(refused())                       # a private copy of the lists
            (view / 'config/link').rmdir()
            self.assertTrue(refused())                       # lists in the tree, none in the view


if __name__ == "__main__":
    unittest.main()
