#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cstdint>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <set>
#include <queue>

const unsigned int ENDIAN_LITTLE = 0x4949;
const unsigned int ENDIAN_BIG = 0x4d4d;

#endif /* __PROGTEST__ */

class Image {
private:
    std::ifstream inFile;
    std::ofstream outFile;
    std::uint16_t endianInput;
    std::uint16_t width;
    std::uint16_t widthRotated;
    std::uint16_t widthPadding;
    std::uint16_t widthPaddingRotated;
    std::uint16_t height;
    std::uint16_t heightRotated;
    std::uint16_t heightPadding;
    std::uint16_t heightPaddingRotated;
    std::uint16_t format;
    std::uint8_t bitsPerChannel;
    int bytesPerChannel;
    std::uint8_t channels;
    std::vector<std::vector<std::vector<std::uint16_t>>> matrix;
    std::vector<std::vector<std::vector<std::uint16_t>>> matrixRotated;
    int angle;
    unsigned int endianOutput;
    bool loadHeader ();
    bool printHeader ();
    bool validateAngel ();
    bool load ();
    bool print ();
    void rotate ();

public:
    Image (const char *srcFileName, const char *dstFileName, const int angle, const unsigned int byteOrder);
    ~Image ();
    bool process ();
};

Image::Image (const char *srcFileName, const char *dstFileName, const int angle, const unsigned int byteOrder) {
    inFile.open(srcFileName, std::ios::binary | std::ios::in);
    outFile.open(dstFileName, std::ios::binary | std::ios::out);

    this->angle = angle;
    this->endianOutput = byteOrder;
}

Image::~Image () {
    inFile.close();
    outFile.close();
}

bool Image::process () {
    if (!inFile.is_open() || !outFile.is_open()) {
//        std::cout << "a" << std::endl;
        return false;
    }

    switch (endianOutput) {
        case ENDIAN_LITTLE:
        case ENDIAN_BIG:
            break;
        default:
            return false;
    }

//    std::cout << " -- a -- " << std::endl;

    if (!validateAngel()) {
//        std::cout << "b" << std::endl;
        return false;
    }

    if (!loadHeader()) {
//        std::cout << "d" << std::endl;
        return false;
    }

//    std::cout << " -- b -- " << std::endl;

//    if (angle == 0) {
//        std::cout << "c" << std::endl;
//
//        return copyWholeFile();
//    }

//    matrix.resize(heightPadding, std::vector<Pixel>(widthPadding, Pixel()));
//    matrix.resize(heightPadding, std::vector<Pixel>(widthPadding, Pixel()));
    matrix.resize(heightPadding, std::vector<std::vector<std::uint16_t>>(widthPadding, std::vector<std::uint16_t>(channels)));
    matrixRotated.resize(heightPaddingRotated, std::vector<std::vector<std::uint16_t>>(widthPaddingRotated, std::vector<std::uint16_t>(channels)));

//    std::cout << " -- c -- " << std::endl;

    if (!load()) {
        return false;
    }

//    std::cout << " -- d -- " << std::endl;

//    std::cout << +channels << std::endl;
//    std::cout << +bytesPerChannel << std::endl;
//    std::cout << width << " x " << height << std::endl;
//    std::cout << widthPadding << " x " << heightPadding << std::endl;
//    std::cout << "" << std::endl;
//
//    for (int i = 0; i < heightPadding; ++i) {
//        for (int j = 0; j < widthPadding; ++j) {
//            std::cout << std::setw(6) << +matrix[i][j][0];
//        }
//        std::cout << "" << std::endl;
//    }

    rotate();

//    std::cout << "" << std::endl;
//    std::cout << angle << std::endl;
//    std::cout << "" << std::endl;
//
//    for (int i = 0; i < heightPaddingRotated; ++i) {
//        for (int j = 0; j < widthPaddingRotated; ++j) {
//            std::cout << std::setw(6) << +matrixRotated[i][j][0];
//        }
//        std::cout << "" << std::endl;
//    }

    if (!printHeader()) {
        return false;
    }

    if (!print()) {
        return false;
    }

    return true;
}

bool Image::loadHeader () {

    if (!inFile) {
        return false;
    }

    inFile.read((char *) &endianInput, 2);

    if (inFile.fail()) {
        return false;
    }

    switch (endianInput) {
        case ENDIAN_LITTLE:
        case ENDIAN_BIG:
            break;
        default:
            return false;
    }

    inFile.read((char *) &width, 2);

    if (inFile.fail()) {
        return false;
    }

    inFile.read((char *) &height, 2);

    if (inFile.fail() || height == 0 || width == 0) {
        return false;
    }

    inFile.read((char *) &format, 2);

    if (inFile.fail()) {
        return false;
    }

    if (endianInput == ENDIAN_BIG) {
        width = (std::uint16_t) ((((width & 0xFF00) >> 8) + ((width & 0x00FF) << 8)));
        height = (std::uint16_t) ((((height & 0xFF00) >> 8) + ((height & 0x00FF) << 8)));
        format = (std::uint16_t) ((((format & 0xFF00) >> 8) + ((format & 0x00FF) << 8)));
    }

    widthPadding = (std::uint16_t) (width + (8 - (width % 8)) % 8);
    heightPadding = (std::uint16_t) (height + (8 - (height % 8)) % 8);

    if ((angle % 180) == 0) {
        heightRotated = height;
        heightPaddingRotated = heightPadding;
        widthRotated = width;
        widthPaddingRotated = widthPadding;
    } else {
        heightRotated = width;
        heightPaddingRotated = widthPadding;
        widthRotated = height;
        widthPaddingRotated = heightPadding;
    }

    // bits 8-15 has to be 0
    if ((format & 0xFF00) != 0) {
        return false;
    }

    bitsPerChannel = (std::uint8_t) ((format & 0x00F0) >> 4);

    // 0, 2, 3 or 4
    switch (bitsPerChannel) {
        case 0:
        case 2:
        case 3:
            bytesPerChannel = 1;
            break;
        case 4:
            bytesPerChannel = 2;
            break;
        default:
            return false;
    }

    // <1; 15>
    channels = (std::uint8_t) (format & 0x000F);

    return channels != 0;
}

bool Image::printHeader () {
    if (!outFile) {
        return false;
    }

    if (endianOutput == ENDIAN_BIG) {
        widthRotated = (std::uint16_t) ((((widthRotated & 0xFF00) >> 8) + ((widthRotated & 0x00FF) << 8)));
        heightRotated = (std::uint16_t) ((((heightRotated & 0xFF00) >> 8) + ((heightRotated & 0x00FF) << 8)));
        format = (std::uint16_t) ((((format & 0xFF00) >> 8) + ((format & 0x00FF) << 8)));
    }

    outFile.write((char *) &endianOutput, 2);

    if (outFile.fail()) {
        return false;
    }

    outFile.write((char *) &widthRotated, 2);

    if (outFile.fail()) {
        return false;
    }

    outFile.write((char *) &heightRotated, 2);

    if (outFile.fail()) {
        return false;
    }

    outFile.write((char *) &format, 2);

    return !outFile.fail();
}

bool Image::validateAngel () {

    if ((angle % 90) != 0) {
        return false;
    }

    angle %= 360;

    switch (angle) {
        case -270:
            angle = 90;
            break;
        case -180:
            angle = 180;
            break;
        case -90:
            break;
        case 0:
            break;
        case 90:
            break;
        case 180:
            break;
        case 270:
            angle = -90;
            break;
        default:
            return false;
    }

    return true;
}

bool Image::load () {
    if (!inFile) {
        return false;
    }

    std::uint16_t test;

    for (int j = 0; j < heightPadding / 8; ++j) {
        for (int i = 0; i < widthPadding / 8; ++i) {
            for (int k = 0; k < channels; ++k) {
                for (int step = 0; step < 8; step++) {
                    for (int y = 0 + j * 8, x = step + i * 8; y <= step + j * 8; y++, --x) {
                        inFile.read((char *) &test, bytesPerChannel);

                        if (inFile.fail()) {
                            return false;
                        }

                        if (endianInput == ENDIAN_BIG) {
                            test = (std::uint16_t) ((((test & 0xFF00) >> 8) + ((test & 0x00FF) << 8)));
                        }

                        matrix[y][x][k] = (std::uint16_t) test;
                    }
                }

                for (int step = 1; step < 8; step++) {
                    for (int y = step + j * 8, x = 7 + i * 8; x >= step + i * 8; y++, --x) {
                        inFile.read((char *) &test, bytesPerChannel);

                        if (inFile.fail()) {
                            return false;
                        }

                        if (endianInput == ENDIAN_BIG) {
                            test = (std::uint16_t) ((((test & 0xFF00) >> 8) + ((test & 0x00FF) << 8)));
                        }

                        matrix[y][x][k] = (std::uint16_t) test;
                    }
                }
            }
        }
    }

    inFile.get();
    return inFile.eof();
}

bool Image::print () {
    if (!outFile) {
        return false;
    }

    for (int j = 0; j < heightPaddingRotated / 8; ++j) {
        for (int i = 0; i < widthPaddingRotated / 8; ++i) {
            for (int k = 0; k < channels; ++k) {
                for (int step = 0; step < 8; step++) {
                    for (int y = 0 + j * 8, x = step + i * 8; y <= step + j * 8; y++, --x) {
                        std::uint16_t data = matrixRotated[y][x][k];

                        if (endianOutput == ENDIAN_BIG) {
                            data = (std::uint16_t) ((((data & 0xFF00) >> 8) + ((data & 0x00FF) << 8)));
                        }

                        outFile.write((char *) &data, bytesPerChannel);

                        if (outFile.fail()) {
                            return false;
                        }
                    }
                }

                for (int step = 1; step < 8; step++) {
                    for (int y = step + j * 8, x = 7 + i * 8; x >= step + i * 8; y++, --x) {
                        std::uint16_t data = matrixRotated[y][x][k];

                        if (endianOutput == ENDIAN_BIG) {
                            data = (std::uint16_t) ((((data & 0xFF00) >> 8) + ((data & 0x00FF) << 8)));
                        }

                        outFile.write((char *) &data, bytesPerChannel);

                        if (outFile.fail()) {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}

void Image::rotate () {
    for (int i = 0; i < heightRotated; ++i) {
        for (int j = 0; j < widthRotated; ++j) {
            for (int k = 0; k < channels; ++k) {
                if (angle == 90) {
                    matrixRotated[i][j][k] = matrix[widthRotated - j - 1][i][k];
                } else if (angle == -90) {
                    matrixRotated[i][j][k] = matrix[j][heightRotated - i - 1][k];
                } else if (angle == 180) {
                    matrixRotated[i][j][k] = matrix[heightRotated - i - 1][widthRotated - j - 1][k];
                } else if (angle == 0) {
                    matrixRotated[i][j][k] = matrix[i][j][k];
                }
            }
        }
    }

    for (int i = heightRotated; i < heightPaddingRotated; ++i) {
        for (int j = 0; j < widthPaddingRotated; ++j) {
            for (int k = 0; k < channels; ++k) {
                matrixRotated[i][j][k] = 0;
            }
        }
    }

    for (int i = 0; i < heightRotated; ++i) {
        for (int j = widthRotated; j < widthPaddingRotated; ++j) {
            for (int k = 0; k < channels; ++k) {
                matrixRotated[i][j][k] = 0;
            }
        }
    }
}

// MAIN FUNCTION

bool rotateImage (const char *srcFileName, const char *dstFileName, int angle, unsigned int byteOrder) {
    Image image(srcFileName, dstFileName, angle, byteOrder);

    return image.process();
}

#ifndef __PROGTEST__

bool identicalFiles (const char *fileName1, const char *fileName2) {
    std::ifstream file1;
    file1.open(fileName1, std::ios::binary | std::ios::in);

    std::ifstream file2;
    file2.open(fileName2, std::ios::binary | std::ios::in);

    if (!file1 || !file2) {
        std::cout << "c" << std::endl;
        return false;
    }

    if (file1.is_open() && file2.is_open()) {
        char b1;
        char b2;

        while (true) {
            file1.get(b1);
            file2.get(b2);

            if (file1.eof() && file2.eof() && b1 == b2) {
                file1.close();
                file2.close();
                return true;
            } else if (file1.eof() || file2.eof()) {
                file1.close();
                file2.close();
                std::cout << "a" << std::endl;
                return false;
            }
        }

    }

    file1.close();
    file2.close();
    std::cout << "b" << std::endl;
    return false;
}

int main (void) {

    assert (rotateImage("../sample/input_00.img", "../sample/output_00.img", 0, ENDIAN_LITTLE)
            && identicalFiles("../sample/output_00.img", "../sample/ref_00.img"));

    assert (rotateImage("../sample/input_01.img", "../sample/output_01.img", 90, ENDIAN_LITTLE)
            && identicalFiles("../sample/output_01.img", "../sample/ref_01.img"));

    assert (rotateImage("../sample/input_02.img", "../sample/output_02.img", 540, ENDIAN_LITTLE)
            && identicalFiles("../sample/output_02.img", "../sample/ref_02.img"));

    assert (rotateImage("../sample/input_03.img", "../sample/output_03.img", -900450, ENDIAN_LITTLE)
            && identicalFiles("../sample/output_03.img", "../sample/ref_03.img"));

    assert (rotateImage("../sample/input_04.img", "../sample/output_04.img", 90, ENDIAN_LITTLE)
            && identicalFiles("../sample/output_04.img", "../sample/ref_04.img"));

    assert (rotateImage("../sample/input_05.img", "../sample/output_05.img", 270, ENDIAN_LITTLE)
            && identicalFiles("../sample/output_05.img", "../sample/ref_05.img"));

    assert (rotateImage("../sample/input_06.img", "../sample/output_06.img", 90, ENDIAN_LITTLE)
            && identicalFiles("../sample/output_06.img", "../sample/ref_06.img"));

    assert (rotateImage("../sample/input_07.img", "../sample/output_07.img", 270, ENDIAN_LITTLE)
            && identicalFiles("../sample/output_07.img", "../sample/ref_07.img"));

    assert (!rotateImage("../sample/input_08.img", "../sample/output_08.img", 270, ENDIAN_LITTLE));

    assert (!rotateImage("../sample/input_09.img", "../sample/output_09.img", -275, ENDIAN_LITTLE));

    assert (rotateImage("../sample/in_2226435.bin", "../sample/output_2226435.img", 270, ENDIAN_LITTLE)
            && identicalFiles("../sample/output_2226435.img", "../sample/ref_2226435.bin"));

    assert (rotateImage("../sample/in_2226520.bin", "../sample/output_2226520.img", 90, ENDIAN_LITTLE)
            && identicalFiles("../sample/output_2226520.img", "../sample/ref_2226520.bin"));

    // extra inputs (optional & bonus tests)
    assert (rotateImage("../sample/extra_input_00.img", "../sample/extra_out_00.img", 90, ENDIAN_LITTLE)
            && identicalFiles("../sample/extra_out_00.img", "../sample/extra_ref_00.img"));
    assert (rotateImage("../sample/extra_input_01.img", "../sample/extra_out_01.img", 90, ENDIAN_BIG)
            && identicalFiles("../sample/extra_out_01.img", "../sample/extra_ref_01.img"));
    assert (rotateImage("../sample/extra_input_02.img", "../sample/extra_out_02.img", 180, ENDIAN_BIG)
            && identicalFiles("../sample/extra_out_02.img", "../sample/extra_ref_02.img"));
    assert (rotateImage("../sample/extra_input_03.img", "../sample/extra_out_03.img", 270, ENDIAN_LITTLE)
            && identicalFiles("../sample/extra_out_03.img", "../sample/extra_ref_03.img"));

    return 0;

    assert (rotateImage("../sample/extra_input_04.img", "extra_out_04.img", 90, ENDIAN_LITTLE)
            && identicalFiles("extra_out_04.img", "../sample/extra_ref_04.img"));
    assert (rotateImage("../sample/extra_input_05.img", "extra_out_05.img", 270, ENDIAN_LITTLE)
            && identicalFiles("extra_out_05.img", "../sample/extra_ref_05.img"));
    assert (rotateImage("../sample/extra_input_06.img", "extra_out_06.img", 180, ENDIAN_BIG)
            && identicalFiles("extra_out_06.img", "../sample/extra_ref_06.img"));
    assert (rotateImage("../sample/extra_input_07.img", "extra_out_07.img", 0, ENDIAN_BIG)
            && identicalFiles("extra_out_07.img", "../sample/extra_ref_07.img"));
    assert (rotateImage("../sample/extra_input_08.img", "extra_out_08.img", 90, ENDIAN_LITTLE)
            && identicalFiles("extra_out_08.img", "../sample/extra_ref_08.img"));
    assert (rotateImage("../sample/extra_input_09.img", "extra_out_09.img", 270, ENDIAN_LITTLE)
            && identicalFiles("extra_out_09.img", "../sample/extra_ref_09.img"));
    assert (rotateImage("../sample/extra_input_10.img", "extra_out_10.img", 180, ENDIAN_BIG)
            && identicalFiles("extra_out_10.img", "../sample/extra_ref_10.img"));
    assert (rotateImage("../sample/extra_input_11.img", "extra_out_11.img", 0, ENDIAN_BIG)
            && identicalFiles("extra_out_11.img", "../sample/extra_ref_11.img"));

    return 0;
}

#endif /* __PROGTEST__ */
