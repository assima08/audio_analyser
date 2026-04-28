//
// Created by faba on 2026-04-26.
//

#include "AudioReader.h"

AudioReader::AudioReader(const std::string& filePath) : filePath(filePath), samples(), sampleRate(0),
                                                        channels(0){

}
/**
 * \brief implémentation de la classe AudioReader qui vérifie la validité du fichier.
 * @param p_nomFichier
 * @return un bool si un fichier à bien été trouvé
 */
bool AudioReader::load() {
    std::ifstream file(filePath,std::ios::binary );
    if (!file){
        std::cerr<<"Erreur : Fichier introuvable! \n";
        return false;
    }samples.clear();
    std::cout<<"FIchier ouvert avec succès ! \n";

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
    if (channels == 0) {
        return 0;
    }
    return samples.size();
}

