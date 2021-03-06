#pragma once

#include "utils.h"

#include <fstream>
#include <iostream>

struct SettingsStructure{

    std::string pathToProject = "/home/rferon/project/";
    std::string pathToOutput = pathToProject + "output/";
    std::string pathToReads = pathToProject + "data/reads/";
    std::string pathToBcalm = pathToProject + "code/bcalm/build/";
    std::string pathToBowtie = pathToProject + "tools/bowtie/" ;
    std::string pathToBowtie2 = pathToProject + "tools/bowtie2/" ;
    std::string pathToBwa = pathToProject + "tools/bwa/" ;
    std::string pathToBgreat = pathToProject + "code/BGREAT/";
    std::string pathToBowtieParser = "";
    std::string baseFileName = "";

    uint kmerSize = 31;
    uint abundanceThreshold = 5;
    uint nCores = 6;
    uint nAllowedMismatchesForBowtie = 3;
    uint readLength = 98;

    std::string bowtieMode = "fast";
    std::string aligner = "bowtie";

    // Loads settings from settings file
    void loadSettingsFile(std::string& settingsFilePath);

};
