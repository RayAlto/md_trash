class Solution {
public:
    bool isBadVersion(int version);
    int firstBadVersion(int n) {
        int left = 1;
        int right = n;
        int index = 1;
        while (left < right) {
            index = left + (right - left) / 2;
            if (isBadVersion(index)) {
                right = index;
            }
            else {
                left = index + 1;
            }
        }
        return left;
    }
};
