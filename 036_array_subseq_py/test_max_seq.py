import unittest
from max_seq import max_seq

class TestMaxSequence(unittest.TestCase):
    """Validates finding the maximum increasing contiguous subsequence in the list"""
    def setUp(self):
        pass
    def tearDown(self):
        pass

    def test_empty(self):
        """Empty list"""
        seq = max_seq([])
        self.assertEqual(seq,[])

    def test_string_float(self):
        """encounter string or float element"""
        with self.assertRaises(Exception) as context:
            seq = max_seq([5,1,2,"A",-1,1,2,3,"B",7,9.9])
        self.assertTrue(type(context.exception) == TypeError,"Wrong exception type raised")
        
    def test_one_contiguous(self):
        """Only encounter one increasing contiguous subsequence in the list"""
        seq = max_seq([5,1,2,3,4,-1])
        self.assertEqual(seq,[1,2,3,4])

    def test_two_contiguous(self):
       """Encounter two increasing contiguous subsequence in th list"""
       seq = max_seq([-10,1,2,3,-1,0,1,3,5,-10])
       self.assertEqual(seq,[-1,0,1,3,5])







unittest.main(argv=['unittest','TestMaxSequence'], verbosity=2, exit=False)
