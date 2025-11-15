#include <cstdint>
#include <iostream>
#include <climits>

using namespace std;

int main() {
    int64_t a;
    int64_t b;
    cin >> a >> b;

    if (a > 0 && b > 0) {
        if (a > LLONG_MAX - b) {
            cout << "Overflow!" << endl;
        }
        else {
            cout << a + b << endl;
        }
    }
    else if (a < 0 && b < 0) {
        if (a < LLONG_MIN - b) {
            cout << "Overflow!" << endl;
        }
        else {
            cout << a + b << endl;
        }
    }
    else {
        cout << a + b << endl;
    }
}