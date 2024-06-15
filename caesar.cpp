#include <string>
using namespace std;

extern "C" {
    __declspec(dllexport) string encrypt(string rawText, int key) {
        for (size_t i = 0; i < rawText.size(); ++i) {
            rawText[i] += key;
        }

        return rawText;
    }

    __declspec(dllexport) string decrypt(string rawText, int key) {
        for (size_t i = 0; i < rawText.size(); ++i) {
            rawText[i] -= key;
        }

        return rawText;
    }
}
