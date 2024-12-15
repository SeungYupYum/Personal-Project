def insertion_sort(nums: list[int]):

    for i in range(1, len(nums)):
        current = nums[i]
        maxIndex = i - 1
        
        while maxIndex >= 0 and current < nums[maxIndex]:
            nums[maxIndex + 1] = nums[maxIndex]
            maxIndex -= 1
        nums[maxIndex + 1] = current