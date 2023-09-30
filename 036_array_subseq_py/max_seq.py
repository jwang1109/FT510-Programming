import pdb

def max_seq(l):
   """
   max_seq returns a the maximum increasing contiguous subsequence in the list.
   
   Args:
   l(list): list of numbers

   Returns:
   the maxiumum increasing contiguous subsequence as a list. If the l is empty,
   an empty list is returned

   Raises:
   TypeError is the function contains an item that is not arithmetically 
   compatible with ints and floats
   """
   ans =[]
   temp_ans = []
   temp = None
   for i in l:
      # raise value of the string
      if type(i) != int and type(i) != float:
         raise TypeError("All elements in the list must be ints or floats")
      # let the temp be the first element first
      if temp == None:
         temp = i
      if i > temp:
         temp_ans.append(i)
         if len(ans) < len(temp_ans):
            ans = temp_ans
      else:
         if len(ans) < len(temp_ans):
            ans = temp_ans
         temp_ans = []
         temp_ans.append(i)
      temp = i

   return ans

print(max_seq([1,2,3,-1,0,3]))

