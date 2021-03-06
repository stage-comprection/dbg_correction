#include "settings.h"


// Loads settings from settings file
void SettingsStructure::loadSettingsFile(std::string& settingsFilePath){

    std::ifstream settingsFile;
    settingsFile.open(settingsFilePath);

    std::string line, key, value;
    std::vector<std::string> splittedLine;

    while(std::getline(settingsFile, line)){

        splittedLine = split(line, "=");
        key = splittedLine[0];
        value = splittedLine[1];

        if (key =="projectPath"){
            this->pathToProject = value;
        }
        else if (key =="outputPath"){
            this->pathToOutput = value;
        }
        else if (key =="readsPath"){
            this->pathToReads = value;
        }
        else if (key =="bcalmPath"){
            this->pathToBcalm = value;
        }
        else if (key =="bowtiePath"){
            this->pathToBowtie = value;
        }
        else if (key =="bowtie2Path"){
            this->pathToBowtie2 = value;
        }
        else if (key =="bwaPath"){
            this->pathToBwa = value;
        }
        else if (key =="bgreatPath"){
            this->pathToBgreat = value;
        }
        else if (key =="bowtieParserPath"){
            this->pathToBowtieParser = value;
        }
        else if (key =="baseFileName"){
            this->baseFileName = value;
        }
        else if (key =="kmerSize"){
            this->kmerSize = std::stoi(value);
        }
        else if (key =="abundance"){
            this->abundanceThreshold = std::stoi(value);
        }
        else if (key =="nCores"){
            this->nCores = std::stoi(value);
        }
        else if (key =="nMismatchesBowtie"){
            this->nAllowedMismatchesForBowtie = std::stoi(value);
        }
        else if (key =="readLength"){
            this->readLength = std::stoi(value);
        }
        else if (key =="aligner"){
            this->aligner = value;
        }

    }

    settingsFile.close();
}
