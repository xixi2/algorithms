#include <iostream>
#include <string>
#include <vector>

using namespace std;


/***
 * 对string类对象的数组进行的基数排序
 * 所有字符串的长度相同为stringLen
 * 从最后一个字符串开始对字符串中所有字符进行桶式排序
 * p266
 * 假设全部为ASCII码
 * @param arr
 * @param stringLen
 */
void radixSortA(vector<string> &arr, int stringLen) {
    const int BUCKETS = 256;
    vector<vector<string>> buckets(BUCKETS);

    for (int pos = stringLen - 1; pos >= 0; --pos) {
        for (string &s : arr) {
            cout << "s: " << s << " POS:" << pos << " s[pos] :" << s[pos] << " int( s[pos]):" << int(s[pos]) << endl;
            buckets[s[pos]].push_back(std::move(s));
        }

        int idx = 0;
        for (auto &thisBucket : buckets) {
            for (string &s : thisBucket) {
                arr[idx++] = std::move(s);
            }
            thisBucket.clear();
        }
        for (int i = 0; i < arr.size(); ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
        cout << endl;
    }
}

void testradixSortA() {
    vector<string> arr{"hell", "nice", "good", "moon"};
    radixSortA(arr, 4);
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


void bucketSort(vector<int> &arr, int max) {
    int i, j;
    vector<int> buckets(max, 0);    // 桶数组,所有

    if (arr.empty() || max < 1) {
        return;
    }
    for (int i = 0; i < arr.size(); ++i) {
        buckets[arr[i]]++;
    }
    for (int i = 0, j = 0; i < max; ++i) {
        while ((buckets[i]--) > 0)
            arr[j++] = i;
    }
}

void testBucketSort() {
    vector<int> arr = {8, 2, 3, 4, 3, 6, 6, 3, 9};
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << endl;
    bucketSort(arr, 10);
    for (int i = 0; i < arr.size(); ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void countingSort(vector<int> &nums) {
    if (nums.size() < 2) {
        return;
    }
    int maxVal = -2147483648;
    for (int i = 0; i < nums.size(); ++i) {
        maxVal = maxVal > nums[i] ? maxVal : nums[i];
    }
    vector<int> count(maxVal + 1, 0);
    // count[i]表示数组nums中等于i的元素个数
    for (int i = 0; i < nums.size(); ++i) {
        ++count[nums[i]];
    }

    // count[i]表示数组nums中小于等于i的元素个数
    for (int i = 1; i < count.size(); ++i) {
        count[i] += count[i - 1];
    }
    vector<int> aux(nums.size());
    for (int i = 0; i < nums.size(); ++i) {
        // count[nums[i]]表示数组nums中小于等于nums[i]的元素个数,因此count[nums[i]]也就是nums[i]在排序后数组中的位置
//        cout << "nums[" << i << "]:" << nums[i] << " count:" << count[nums[i]] << endl;
        aux[--count[nums[i]]] = nums[i];
    }
    for (int i = 0; i < nums.size(); ++i) {
        nums[i] = aux[i];
    }
    cout << endl;
}

void testcountingSort() {
//    vector<int> nums{2, 1, 2, 4, 5};
    vector<int> nums{5, 4, 3, 2, 2, 4, 1};
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << endl;
    countingSort(nums);
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

int maxminuGap(vector<int> &nums) {
    if (nums.size() < 2) {
        return 0;
    }
    int maxVal = -2147483648;
    for (int i = 0; i < nums.size(); ++i) {
        maxVal = maxVal < nums[i] ? nums[i] : maxVal;
    }

    int radix = 10;     // 0-9共10个桶
    int exp = 1;
    vector<int> aux(nums.size());
    while (maxVal / exp) {
        vector<int> count(radix, 0);
        for (int i = 0; i < nums.size(); ++i) {
            // count[(nums[i] / exp) % 10]表示第radix位上等于(nums[i] / exp) % 10的元素个数
            count[(nums[i] / exp) % 10]++;
        }

        /*  count[(nums[i] / exp) % 10]表示第radix位上小于等于(nums[i] / exp) % 10的元素个数
          也就是nums[i]在按照第radix位进行排序时的位置
          必须逆序, 这是因为有重复元素, 为了保持重复元素之间的相对位置必须逆序恢复
          例如给[1,2,2,1,5,4,77]排序,若按照逆序排序,
          那么第一次排序完成后的数组为: [1,1,2,2,4,5,77],
          第二次排序完成后的数组为: [5,4,2,2,1,1,77]
          */

        for (int i = 1; i < count.size(); ++i) {
            count[i] += count[i - 1];
        }

        for (int i = nums.size() - 1; i >= 0; i--) {
            // 这里为什么需要先自减1: nums[i]按照radix位排序时它的前面共有count[(nums[i] / exp) % 10]-1个元素
            // 所以它的位置是--count[(nums[i] / exp) % 10]
            aux[--count[(nums[i] / exp) % 10]] = nums[i];
        }
        for (int i = 0; i < nums.size(); ++i) {
            nums[i] = aux[i];
            cout << nums[i] << " ";
        }
        cout << endl;
        exp *= 10;
    }

    int maxGap = 0;
    for (int i = 0; i < nums.size() - 1; ++i) {
        maxGap = max(nums[i + 1] - nums[i], maxGap);
    }
    return maxGap;
}


void testMaxMinuGap() {
//    3, 6,
//    vector<int> nums{9, 15, 101, 86};
    vector<int> nums{1, 2, 2, 1, 5, 4, 77};
    int gap = maxminuGap(nums);
    cout << gap << endl;
}

void insectionSort(vector<int> &nums) {
    for (int i = 1; i < nums.size(); ++i) {
        int tmp = nums[i];

        int j = i;
        while (j > 0 && nums[j - 1] > tmp) {
            nums[j] = nums[j - 1];
            --j;
        }
        nums[j] = tmp;
    }
}

void testInsectionSort() {
//    vector<int> nums{5, 3, 1, 4, 2};
    vector<int> nums(5);
    for (int i = 0; i < nums.size(); ++i) {
        cin >> nums[i];
    }
    insectionSort(nums);
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;
}

void bucketSort1(vector<int> &nums, int bucketSize) {
    if (nums.size() < 2) {
        return;
    }
    vector<vector<int>> help(nums.size(), vector<int>(0));
    int i;
    int maxVal, minVal;
    maxVal = nums[0];
    minVal = nums[0];

    for (int i = 1; i < nums.size(); ++i) {
        if (nums[i] < minVal) {
            minVal = nums[i];
        } else if (nums[i] > maxVal) {
            maxVal = nums[i];
        }
    }

    int bucketCount = (maxVal - minVal) / bucketSize + 1;
    vector<vector<int>> buckets(bucketCount, vector<int>(0));

    for (int i = 0; i < nums.size(); ++i) {
        int index = (nums[i] - minVal) / bucketSize;
//        cout << "nums[" << i << "]" << nums[i] << " index:" << index << endl;
        buckets[index].push_back(nums[i]);
    }
    int arrIndex = 0;
    for (int i = 0; i < buckets.size(); ++i) {
        if (buckets[i].empty()) {
            continue;
        }
        insectionSort(buckets[i]);

//        cout << "第" << i << "个桶中:";
//        for (int j = 0; j < buckets[i].size(); ++j) {
//            cout << buckets[i][j] << " ";
//        }
//        cout << endl;

        for (int value : buckets[i]) {
            nums[arrIndex++] = value;
        }
    }
}

void testbucketSort() {
    vector<int> nums{8, 1, 2, 2, 1, 3, 4, 5};
    bucketSort1(nums, 2);
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i] << " ";
    }
    cout << endl;
}


int main() {
//    testMaxMinuGap();
//    testcountingSort();
//    testInsectionSort();
    testbucketSort();
    return 0;
}