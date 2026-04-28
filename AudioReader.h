//
// Created by faba on 2026-04-26.
//
#ifndef AUDIOANALYSER_AUDIOREADER_H
#define AUDIOANALYSER_AUDIOREADER_H
#include "iostream"
#include "fstream"
#include "vector"


class AudioReader {
public:
    AudioReader(const std::string& filePath);

    bool load();

    //accesseurs
    int                     getSampleRate()const;
    size_t                  getChannels()const;
    const std::vector<double>& getSamples()const;
    size_t                   getNumFrames()const;

private:
    //reference pour le format audio : https://www.rtlaudiolab.com/009-reading-wave-files-in-systemverilog/
    //Riff Chunk ( entête du fichier )
    struct RIFF{
        const std::string chunkId = "RIFF";
        const std::string chunkSize = "---";
        const std::string format = "WAVE";
    };

    //FMT

    struct FMT {
        const std::string subChunk1Id = "fmt";
        const int subChunk1Size = 16;
        const int audioFormat = 1;
        const size_t numChannels = 2;
        const int sampleRate = sampleRate;
        const int bitsPerSample = 16;
        const int byteRate = sampleRate * numChannels *(bitsPerSample/8);
        const int blockAlign = numChannels * (bitsPerSample /8);
    };

    //DATA
    struct DATA{
        const std::string subChunk2Id = "data";
        const std::string subChunk2Size = "----";
    };

    std::string             filePath;
    std::vector<double>     samples;         //le son lui même
    int                     sampleRate;     //rythme du signal
    size_t                  channels;       //stereo ou mono

};

#endif //AUDIOANALYSER_AUDIOREADER_H
