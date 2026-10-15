"""Cooperating lanes choose the same reservation within inherited affinity."""
import importlib.util
from pathlib import Path
import unittest

spec=importlib.util.spec_from_file_location('reserve_cores',Path(__file__).resolve().parents[1]/'lanes/reserve_cores.py')
R=importlib.util.module_from_spec(spec);spec.loader.exec_module(R)

class CoreReservation(unittest.TestCase):
    def test_sparse_affinity_and_eight_reserved(self):
        cpus=list(range(4,28,2))
        lane,landing=R.core_sets(cpus)
        self.assertEqual(len(landing),8);self.assertEqual(lane,[4,6,8,10])
        self.assertFalse(set(lane)&set(landing));self.assertEqual(set(lane+landing),set(cpus))
    def test_small_machines_leave_a_lane_cpu(self):
        self.assertEqual(R.core_sets([1,3,7]),([1],[3,7]))
        self.assertEqual(R.core_sets([7]),([7],[7]))
    def test_invalid_reservation_is_rejected(self):
        for cpus,n in [([],8),([1,2],0),([1,2],-1)]:
            with self.assertRaises(ValueError):R.core_sets(cpus,n)

if __name__=='__main__':unittest.main()
