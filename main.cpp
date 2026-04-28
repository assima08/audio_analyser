#include <iostream>
#include "AudioReader.h"

int main() {
    AudioReader monfichier("C:\\Users\\faba\\Downloads\\SHUBA-K _ SCRATCH PACK - INSTU & TOOLS\\Shuba-K Scratch Sample 2.wav");
    monfichier.load();
    std::cout <<monfichier.reqAudioFormate() << std::endl;
    return 0;
}
