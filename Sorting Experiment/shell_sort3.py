def nums_list_generator(n):
    nums_list = [1]
    index_1 = 0
    index_2 = 0
    threshold = 0
    while threshold < n:
        yield nums_list[-1]
        n1 = 2 * nums_list[index_1]
        n2 = 3 * nums_list[index_2]
        threshold = min(n1, n2)
        if threshold < n:
            nums_list.append(threshold)
        index_1 += n1 <= n2
        index_2 += n1 >= n2
    print("sequence: ", nums_list)
    return nums_list

def shell_sort3(nums: list[int]):
    n = len(nums)
    sequence_list = list(nums_list_generator(n))

    for gap in sequence_list[::-1]:
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
    

arr = []
for i in range(0,96):
    arr.append(i)

print("size of arr: ", len(arr))
shell_sort3(arr)
