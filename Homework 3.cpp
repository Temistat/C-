#include <iostream>
#include <vector>
#include <string>
using namespace std;

//Task 1
void reverseCString(char* str) {
    if (str == nullptr) {
        return;
    }
    char* front = str;
    char* rear = str;
    while (*rear != '\0') {
        ++rear;
    }
    --rear;
    while (front < rear) {
        char temp = *front;
        *front = *rear;
        *rear = temp;
        ++front;
        --rear;
    }
}
//Task 2
#include <iostream>

int* enlargeAndInsert(int* arr, int size, int item) {
    int* newArr = new int[size+1];
    int insertIndex = 0;
    while (insertIndex < size && arr[insertIndex] < item) {
        ++insertIndex;
    }
    int newIndex = 0;
    for (; newIndex < insertIndex; ++newIndex) {
        newArr[newIndex] = arr[newIndex];
    }
    newArr[newIndex] = item;
    ++newIndex;
    for (; newIndex < size+1; ++newIndex) {
        newArr[newIndex] = arr[newIndex - 1];
    }
    delete[] arr;
    return newArr;
}
//Task 3
int findMax(const vector<int>& grades) {
    int max = 0;
    for (int num : grades) {
        if (num > max){
            max = num;
        }
    }
    return max;
}
void histogram(const vector<int>& grades) {
    int num = findMax(grades); // To find the max grade
    int* arr = new int[num+1];
    for (size_t i = 0; i < num+1; ++i) {
        arr[i] = 0;
    }
    for (size_t i = 0; i < grades.size(); ++i) {
        arr[grades[i]] += 1;
    }
    for (size_t i = 0; i < num+1; ++i) {
        if (arr[i] != 0) {
            cout << "Number of " << i << "'s: " << arr[i] << endl;
        }
    }
}
int main() {
    // Tester for task 1
    char str1[] = "Temiloluwa"; // Odd-sized array
    cout << "Original: " << str1 << std::endl;
    reverseCString(str1);
    cout << "Reversed: " << str1 << std::endl;

    char str2[] = "awulolimeT"; // Even-sized array
    cout << "Original: " << str2 << std::endl;
    reverseCString(str2);
    cout << "Reversed: " << str2 << std::endl;

    // Tester for task 2
    int size = 5;
    int* arr = new int[size] { 1, 3, 5, 7, 9 };
    int newItem = 6;
    cout << "Original Array: \n";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << endl;
    }
    cout << endl;
    arr = enlargeAndInsert(arr, size, newItem);
    ++size;
    cout << "Array after enlargement and insertion: \n";
    for (int i = 0; i < size; ++i) {
        cout << arr[i] << "\n";
    }
    cout << endl;
    delete[] arr;
    // Tester for test 3
    vector<int> grades;
    int num;
    while (num != -1) {
        cout << "What  is the grade? ";
        cin >> num;
        grades.push_back(num);
    }
    histogram(grades);
}
