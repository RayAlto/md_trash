#include <vector>

class Solution {
public:
    static int search(std::vector<int>& nums, int target) {
        const int num_count = static_cast<int>(nums.size());
        int left = 0;
        int right = num_count - 1;
        int index = 0;
        while (left <= right) {
            index = left + (right - left) / 2;
            const int& num = nums[index];

            if (num == target) {
                return index;
            }

            if (num > target) {
                right = index - 1;
            }
            else {
                left = index + 1;
            }
        }
        return left;
    }
};
