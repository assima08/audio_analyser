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
    std::string             filePath;
    std::vector<double>     sample;         //le son lui même
    int                     sampleRate;     //rythme du signal
    size_t                  channels;       //stereo ou mono

};

#endif //AUDIOANALYSER_AUDIOREADER_H
