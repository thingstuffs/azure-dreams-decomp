"""append_jsonl / append_jsonl_rows: locked single-write appends (concurrent writers, rename-replace composition).
Run: python3 -m unittest tools/tests/test_append_locked.py   (from the repo root)"""
import json, multiprocessing, os, subprocess, sys, tempfile, unittest
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import common


def _worker(path, tag, n):
    for i in range(n):
        common.append_jsonl(path, {"w": tag, "i": i, "pad": "x" * 6000})


class AppendLocked(unittest.TestCase):
    def test_basic_and_rows(self):
        with tempfile.TemporaryDirectory() as d:
            p = Path(d) / "j.jsonl"
            common.append_jsonl(p, {"a": 1})
            common.append_jsonl_rows(p, [{"b": 2}, {"c": 3}])
            self.assertEqual(p.read_text(), '{"a":1}\n{"b":2}\n{"c":3}\n')

    def test_symlink_followed(self):
        with tempfile.TemporaryDirectory() as d:
            t = Path(d) / "t.jsonl"; t.write_text('{"a":1}\n'); l = Path(d) / "l.jsonl"; l.symlink_to(t)
            common.append_jsonl(l, {"b": 2})
            self.assertTrue(l.is_symlink()); self.assertEqual(t.read_text(), '{"a":1}\n{"b":2}\n')

    def test_concurrent_writers_no_torn_lines(self):
        with tempfile.TemporaryDirectory() as d:
            p = str(Path(d) / "j.jsonl")
            ps = [multiprocessing.Process(target=_worker, args=(p, t, 40)) for t in range(6)]
            for x in ps: x.start()
            for x in ps: x.join()
            rows = [json.loads(l) for l in Path(p).read_text().splitlines()]   # a torn/interleaved line raises
            self.assertEqual(len(rows), 240)
            for t in range(6):
                self.assertEqual([r["i"] for r in rows if r["w"] == t], list(range(40)))

    def test_inode_swap_retries(self):
        """the file is replaced by rename while an appender waits for the lock: the line lands in the NEW file"""
        import fcntl
        with tempfile.TemporaryDirectory() as d:
            p = Path(d) / "j.jsonl"; p.write_text('{"old":1}\n')
            holder = os.open(p, os.O_RDONLY); fcntl.flock(holder, fcntl.LOCK_EX)
            # a subprocess, not a fork: a forked child would inherit the held lock descriptor
            proc = subprocess.Popen([sys.executable, "-c", "import sys; sys.path.insert(0, %r); import common; "
                                     "common.append_jsonl(sys.argv[1], {'w': 1})" % str(Path(common.__file__).parent), str(p)])
            import time; time.sleep(0.5)
            tmp = Path(d) / "new.tmp"; tmp.write_text('{"new":1}\n'); os.replace(tmp, p)
            os.close(holder); proc.wait(timeout=20)
            rows = [json.loads(l) for l in p.read_text().splitlines()]
            self.assertEqual([list(r)[0] for r in rows], ["new", "w"])


if __name__ == "__main__":
    unittest.main()
