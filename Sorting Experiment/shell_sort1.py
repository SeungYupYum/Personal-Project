# Shell Sort 1: [n/2^k ], ..., 1, for k=1,2,...,log n, where [*] denotes the floor function.
def shell_sort1(nums: list[int]):
    n = len(nums)
    gap = n // 2 
    
    while gap > 0:
        # NOTE: Swap all the way down if first swap happen
        for i in range(0, n - gap):
            # from 0 to n - gap, looping
            # j is for next index that is apart from index i (just gap difference)
            j = i + gap
            # for efficiency, check first swap
            # if condition is not met, just skip
            if nums[i] > nums[j]:
                # just do first swap
                target = nums[i]
                nums[i] = nums[j]
                nums[j] = target
                j = i
                # Since first swap is happen, check all the way down.
                # Initially J is I posision. Need to check j - gap, j - 2gap, j - 3gap
                # In order to c heck j - 2 gap, j - 1 gap need to be swapped.
                # So the condition is j > = 0 since it will go all the way down,
                # and nums[j-gap] > nums [j].
                # after loop, decrease gap.
                while j - gap >= 0 and nums[j - gap] > nums[j]:
                    target = nums[j - gap]
                    nums[j - gap] = nums[j]
                    nums[j] = target
                    j -= gap
        gap //= 2