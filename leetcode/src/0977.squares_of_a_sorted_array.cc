#include <vector>

class Solution {
public:
    static std::vector<int> sortedSquares(std::vector<int>& nums) {
        const int num_count = static_cast<int>(nums.size());
        std::vector<int> result(num_count, 0);
        int left = 0;
        int right = num_count - 1;
        int index = right;
        int left_value = 0;
        int right_value = 0;
        do {
            left_value = nums[left];
            right_value = nums[right];
            if (left_value + right_value > 0) {
                result[index] = right_value * right_value;
                right -= 1;
            }
            else {
                result[index] = left_value * left_value;
                left += 1;
            }
            index -= 1;
        } while (left_value < 0 && right_value >= 0);
        while (left_value < 0 && index >= 0) {
            left_value = nums[left];
            result[index] = left_value * left_value;
            index -= 1;
            left += 1;
        }
        while (right_value >= 0 && index >= 0) {
            right_value = nums[right];
            result[index] = right_value * right_value;
            index -= 1;
            right -= 1;
        }
        return result;
    }
};
