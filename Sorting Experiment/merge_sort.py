def merge_sort(nums: list[int]):
    if len(nums) > 1:
        mid = len(nums) // 2
        left_half = nums[:mid]
        right_half = nums[mid:]

        merge_sort(left_half)
        merge_sort(right_half)

        left_index = 0
        right_index = 0
        merged_index = 0

        # Case 1: Left and Right are not empty, one of them must empty after this.
        while left_index < len(left_half) and right_index < len(right_half):            
            if left_half[left_index] < right_half[right_index]:
                nums[merged_index] = left_half[left_index]
                left_index += 1
            else:                
                nums[merged_index] = right_half[right_index]
                right_index += 1
            merged_index += 1

        # Case 2: Left is not empty after case 1.
        while left_index < len(left_half):
            nums[merged_index] = left_half[left_index]
            left_index += 1
            merged_index += 1
            
        # Case 3: Right is not empty after case 1.
        while right_index < len(right_half):
            nums[merged_index] = right_half[right_index]
            right_index += 1
            merged_index += 1