//
// Created by faba on 2026-04-26.
//

#include "AudioReader.h"

AudioReader::AudioReader(const std::string& filePath) : filePath(filePath), samples(), sampleRate(0),
                                                        channels(0){

}
/**
 * \brief implémentation de la classe AudioReader qui vérifie la validité du fichier et en extrait les informations.
 * @param p_nomFichier
 * @return un bool si un fichier à bien été trouvé et traité
 */
bool AudioReader::load() {
    //on verifie la validité du fichier
    std::ifstream file(filePath,std::ios::binary );
    if (!file){
        std::cerr<<"Erreur : Fichier introuvable! \n";
        return false;
    }
    //1 - lire l'entête (le RIFF) - créer une instance du struct RIFFHeader et caster avec le fichier
    RIFFHeader riff;
    //Prendre la taille de RIFFHeader, et recuperer les emplacement qui correspondent pour stocker dans riff
    file.read(reinterpret_cast<char*>(&riff),sizeof(RIFFHeader));

    //si ces carractère ne sont ni "RIFF" ni "WAVE", ce n'est pas un fichier WAVE.
    if (std::string (riff.chunkId,4) != "RIFF" || std::string (riff.format,4) != "WAVE"){
        std::cerr<<"Erreur ! Ce n'est pas un fichier WAV valide \n";
        return false;
    }

    //2 - lire la partie FMT
    FMTChunk fmt;
    file.read(reinterpret_cast<char*>(&fmt),sizeof(FMTChunk));

    if (std::string(fmt.subChunk1Id,4) !="fmt "){
        std::cerr<<"Erreur ! FMT introuvable \n";
        return false;
    }
    if (fmt.audioFormat != 1 ){
        std::cerr<<"Erreur ! Seul le format PCM non compressé est supporté \n";
        return false;
    }
    //replir les attributs de fmt (en faisant les conversion pour s'assurer que les format sot bons.
    sampleRate = static_cast<int>(fmt.sampleRate);
    channels = static_cast<size_t>(fmt.numChannels);

    // 3 - Lire la partie DATA
    DATAChunk data;
    while (file.read(reinterpret_cast<char*>(&data), sizeof(data))) {
        //validons l'entête de la partie data
        if (std::string(data.subChunk2Id, 4) == "data") {
            break;
        }file.seekg(data.subChunk2Size, std::ios::cur);
    }
        //4 - lire la partie sample
        size_t numSamples = data.subChunk2Size / (fmt.bitsPerSample / 8);
        samples.reserve(numSamples);//alloue de l'espace correspondant au sample pour le remplir après

        if (fmt.bitsPerSample == 16) {
            int16_t raw;
            while (file.read(reinterpret_cast<char*>(&raw), sizeof(int16_t)))
                samples.push_back(raw / 32768.0);
        }
        else if (fmt.bitsPerSample == 8) {
            uint8_t raw;
            while (file.read(reinterpret_cast<char*>(&raw), sizeof(uint8_t)))
                samples.push_back((raw - 128) / 128.0);
        }
        else {
            std::cerr << "Erreur : " << fmt.bitsPerSample << " bits non supporté\n";
            return false;
        }
    return true;
}


/**
 * \brief Accesseur de la variable sampleRate
 * @return
 */
int  AudioReader::getSampleRate() const {
    return sampleRate;
}
/**
 * \brief Accesseur de la variable channels
 * @return
 */
size_t AudioReader::getChannels() const {
    return channels;
}
/**
 * \brief Accesseur du vector samples
 * @return
 */
const std::vector<double> &AudioReader::getSamples() const {
    return samples;
}
/**
 * \brief Accesseur de frame (le nombre d'unités de temps audio)
 * @return
 */

size_t AudioReader::getNumFrames() const {
    return channels > 0 ? samples.size() / channels : 0;
}
/**
 * \brief implantaion de l'accesseur reqAudioFormate
 * @return un string qui affiche les informations sur l'audio.
 */
std::string AudioReader::reqAudioFormate() const {
    std::ostringstream os;
    os<<"TITRE : "<<this->filePath<<"\n"
    <<"Sample Rate : "<< this->getSampleRate()<<"\n"
    <<"Channels number : "<< this->getChannels()<<"\n";
    return os.str();
}
