//
// Created by faba on 2026-04-26.
//
#ifndef AUDIOANALYSER_AUDIOREADER_H
#define AUDIOANALYSER_AUDIOREADER_H
#include "iostream"
#include "fstream"
#include "vector"
#include <cstdint>
#include "sstream"


class AudioReader {
public:
    AudioReader(const std::string& filePath);

    bool load();

    //accesseurs
    int                     getSampleRate()const;
    size_t                  getChannels()const;
    const std::vector<double>& getSamples()const;
    size_t                   getNumFrames()const;
    std::string              reqAudioFormate()const;

private:
    //reference pour le format audio : https://www.rtlaudiolab.com/009-reading-wave-files-in-systemverilog/
    //Riff Chunk ( entête du fichier )
#pragma pack(push,1) //eviter les espaces entre les champs
    struct RIFFHeader{
        char chunkId[4];
        uint32_t chunkSize ;
        char format[4] ;
    };

    //FMT

    // ✅ ordre correct selon la spec WAV
    struct FMTChunk {
        char     subChunk1Id[4];   // "fmt "
        uint32_t subChunk1Size;    // 16
        uint16_t audioFormat;      // 1 = PCM
        uint16_t numChannels;      // 1 ou 2
        uint32_t sampleRate;       // 44100...
        uint32_t byteRate;         // ← avant blockAlign
        uint16_t blockAlign;       // ← avant bitsPerSample
        uint16_t bitsPerSample;    // ← en dernier
    };
    //DATA
    struct DATAChunk{
        char subChunk2Id[4];
        uint32_t subChunk2Size ;
    };
#pragma  pack(pop)
    std::string             filePath;
    std::vector<double>     samples;         //le son lui même
    int                     sampleRate;     //rythme du signal
    size_t                  channels;       //stereo ou mono

};

#endif //AUDIOANALYSER_AUDIOREADER_H
