#include <iostream>
#include <utility>
#include <array>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;

bool IsAllowFileType(string_view path) {
    const static array<string, 3> list{".jpg", ".jpeg", ".png"};
    return any_of(list.cbegin(), list.cend(), [&](string_view str) {
        return path.ends_with(str);
    });
}

pair<int, int> CalcSize(int width, int height) {
    float rate;
    if (width > height) {
        rate = 512.0f / (float) width;
        return {512, (float) height * rate};
    } else {
        rate = 512.0f / (float) height;
        return {(float) width * rate, 512};
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cout << "[ERROR] No image file input!" << endl;
        return 1;
    }

    cout << "============================\n"
         << "Welcome to use StickerMaker!\n"
         << "============================" << endl;

    for (int i = 1; i < argc; ++i) {
        string path = string(argv[i]);
        if (!IsAllowFileType(path)) {
            cout << "[WARN] The file with index " << i << " is not a valid image, skipped." << endl;
            continue;
        }
        cv::Mat img = cv::imread(path);
        if (img.empty()) {
            cout << "[WARN] The image with index " << i << " is empty, skipped." << endl;
            continue;
        }
        cout << "[INFO] The image resolution with index " << i << " is " << img.cols << "x" << img.rows << endl;
        auto retSize = CalcSize(img.cols, img.rows);
        cout << "[INFO] Resized: " << retSize.first << "x" << retSize.second << endl;
        cv::Mat resize;
        cv::resize(img, resize, cv::Size(retSize.first, retSize.second));

        string outPath;
        char fileName[64]{0};
        sprintf_s(fileName, "output_%d", i);
        if (path.contains('/')) {
            string pt = path.substr(path.find_last_of('/'));
            outPath = pt.append(fileName).append(".png");
        } else if (path.contains('\\')) {
            string pt = path.substr(path.find_last_of('\\'));
            outPath = pt.append(fileName).append(".png");
        } else {
            outPath.append(fileName).append(".png");
        }

        if (cv::imwrite(outPath, resize))
            cout << "[INFO] Saved image as \"" << outPath << "\"" << endl;
        else
            cout << "[ERROR] An error occurred while saving image \"" << outPath << "\", it will not be saved." << endl;
    }

    cout << "[INFO] Done!" << endl;
    system("pause");
    return 0;
}
