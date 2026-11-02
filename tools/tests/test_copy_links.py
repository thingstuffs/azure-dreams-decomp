"""Same-image copy links (tools/gate/linklist.py copy_link_*): the opt-in record, the rule, the object rewrite,
window inputs and the link-graph round trip.  No retail data; the object test needs mipsel binutils."""
import json
from pathlib import Path
import shutil
import subprocess
import sys
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parent))
from test_linklist import Fixture, image, HOME, COPY, K  # noqa: E402

CALLER = "dungeon/func_80F8E000"       # a home row inside bank_fad000 (no link-list entry of its own)
CALLER_FOFF = 0xFAE800


class Rule(Fixture):
    def setUp(self):
        super().setUp()
        self.tables = self.pair()

    def record(self, units):
        K.write_copy_links(self.root, units)

    def test_rule_picks_the_copy_in_the_image(self):
        self.assertEqual(K.copy_link_target(self.tables, "dungeon/bank_fad000", 0x80F8A664), 0x8016DE64)
        # the home's true-space entry vma names the same TU
        self.assertEqual(K.copy_link_target(self.tables, "dungeon/bank_fad000", 0x80173E64), 0x8016DE64)

    def test_home_image_and_unknown_symbols_refuse(self):
        with self.assertRaisesRegex(ValueError, "home of"):
            K.copy_link_target(self.tables, "dungeon/bank_fa7000", 0x80F8A664)
        with self.assertRaisesRegex(ValueError, "names 0 placed homes"):
            K.copy_link_target(self.tables, "dungeon/bank_fad000", 0x80F8A000)
        with self.assertRaisesRegex(ValueError, "not a link-list load image"):
            K.copy_link_target(self.tables, "dungeon/check_x", 0x80F8A664)

    def test_two_instances_in_one_image_are_ambiguous(self):
        twin = dict(COPY, row="dungeon/func_80F90700", foff="0xFB0700", vma="0x8016DF00")
        self.write(image("bank_fa7000", "0xFA7000", "0x80170800", [HOME]),
                   image("bank_fad000", "0xFAD000", "0x8016A800", [COPY, twin]))
        with self.assertRaisesRegex(ValueError, "holds 2 instances"):
            K.copy_link_target(K.load(self.root), "dungeon/bank_fad000", 0x80F8A664)

    def test_record_is_checked_against_the_rule(self):
        self.assertEqual(K.copy_link_renames(self.root, CALLER, "dungeon/bank_fad000"), {})
        self.record({CALLER: {"func_80F8A664": "func_8016DE64"}})
        self.assertEqual(K.copy_link_renames(self.root, CALLER, "dungeon/bank_fad000"),
                         {"func_80F8A664": "func_8016DE64"})
        self.assertEqual(K.copy_link_renames(self.root, CALLER, container="dungeon", foff=CALLER_FOFF),
                         {"func_80F8A664": "func_8016DE64"})
        self.record({CALLER: {"func_80F8A664": "func_8016DE68"}})
        with self.assertRaisesRegex(ValueError, "the record says"):
            K.copy_link_renames(self.root, CALLER, "dungeon/bank_fad000")
        with self.assertRaisesRegex(ValueError, "no load image"):
            self.record({CALLER: {"func_80F8A664": "func_8016DE64"}})
            K.copy_link_renames(self.root, CALLER, container="dungeon", foff=0x100)

    def test_record_schema(self):
        (self.root / "config/link/copy_links.json").write_text(json.dumps(
            {"schema": K.COPY_SCHEMA, "units": {CALLER: {"func_80F8A664": "D_8016DE64"}}}))
        with self.assertRaises(ValueError):
            K.copy_links(self.root)
        self.record({})
        self.assertFalse((self.root / "config/link/copy_links.json").exists())
        self.assertEqual(K.copy_links(self.root), {})

    def test_window_inputs_bind_the_record_and_the_callee_lists(self):
        self.assertEqual(K.window_files(self.root, [CALLER]), [])
        self.record({CALLER: {"func_80F8A664": "func_8016DE64"}})
        self.assertEqual(K.window_files(self.root, [CALLER]),
                         ["config/link/copy_links.json", "config/link/dungeon/bank_fa7000.json",
                          "config/link/dungeon/bank_fad000.json"])

    def test_link_lists_ignore_the_record_file(self):
        self.record({CALLER: {"func_80F8A664": "func_8016DE64"}})
        self.assertEqual(set(K.load(self.root)[0]), {"dungeon/bank_fa7000", "dungeon/bank_fad000"})

    def test_load_views_match_the_production_selection(self):
        sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'link'))
        from combined import selected_images
        docs = {"town/a": {"vma": "0x80016000"}, "town/b": {"vma": "0x80017800"}, "dungeon/bank_1": {"vma": 1},
                "dungeon/engine": {"vma": 2}, "main/x": {"vma": "0x80016000"}}
        self.assertEqual(sorted(i for i, d in docs.items() if K.is_load_view(i, int(str(d["vma"]), 0))),
                         selected_images(docs))


@unittest.skipUnless(shutil.which("mipsel-linux-gnu-as") and shutil.which(K.OBJCOPY), "mipsel binutils")
class Object(Fixture):
    def test_object_reference_binds_to_the_copy(self):
        self.pair()
        src = self.root / "c.s"
        src.write_text(".section .text.func_80F8E000,\"ax\"\n.globl func_80F8E000\nfunc_80F8E000:\n"
                       " jal func_80F8A664\n nop\n jal func_800AB464\n nop\n")
        obj = self.root / "c.o"
        subprocess.run(["mipsel-linux-gnu-as", "-EL", "-march=r3000", "-o", str(obj), str(src)], check=True)
        self.assertEqual(K.copy_link_object(self.root, CALLER, obj, "dungeon/bank_fad000"), {})
        K.write_copy_links(self.root, {CALLER: {"func_80F8A664": "func_8016DE64"}})
        log = self.root / "copylink.txt"
        self.assertEqual(K.copy_link_object(self.root, CALLER, obj, "dungeon/bank_fad000", log=log),
                         {"func_80F8A664": "func_8016DE64"})
        names = subprocess.run([K.NM, str(obj)], capture_output=True, text=True, check=True).stdout
        self.assertIn("U func_8016DE64", names); self.assertNotIn("func_80F8A664", names)
        self.assertIn("U func_800AB464", names)
        self.assertEqual(log.read_text(), "func_80F8A664 -> func_8016DE64\n")
        # a record naming a symbol the object does not import fails closed
        with self.assertRaisesRegex(ValueError, "does not import"):
            K.copy_link_object(self.root, CALLER, obj, "dungeon/bank_fad000")


class Graph(Fixture):
    def test_graph_compare_sees_the_record(self):
        sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'link'))
        import graph as G
        self.pair()
        K.write_copy_links(self.root, {CALLER: {"func_80F8A664": "func_8016DE64"}})

        class Fake:
            def documents(self, validate=False):
                return {}
            def stats(self):
                return {}
            def __init__(self, links):
                self.links = links
            def copy_links(self):
                return self.links
        _, holds = G.compare(Fake({CALLER: {"func_80F8A664": "func_8016DE64"}}), self.root / "config/link")
        self.assertFalse([h for h in holds if h['image'] == 'copy_links'])
        _, holds = G.compare(Fake({}), self.root / "config/link")
        self.assertEqual([h['image'] for h in holds if h['image'] == 'copy_links'], ['copy_links'])


if __name__ == "__main__":
    unittest.main()
