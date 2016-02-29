#include "run_binaries.h"

using namespace std;


// Runs bgreat to align reads on multiple unitigs
void runBgreat(SettingsStructure& settings){

    cout<<endl<<"Running Bgreat ... "<<endl;

    // Initializes command to run bgreat in correction mode (-c) with desired path and parameters
    string command = settings.pathToBgreat + "bgreat -r " + settings.pathToReads + settings.baseFileName + ".fasta -k " + to_string(settings.kmerSize_bgreat) +
                     " -g " + settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName + " -m " + to_string(settings.abundanceThreshold_bgreat) +
                     " -c -t " + to_string(settings.nCores) + " -f " + settings.pathToOutput + "temp_bgreat_corrected_" + settings.baseFileName + " -o " +
                     settings.pathToOutput + "temp_bgreat_noOverlap_" + settings.baseFileName + " -a " + settings.pathToOutput + "temp_bgreat_noAlign_" +
                     settings.baseFileName + " &> logs_bgreat.txt";

    // Runs command and stores state
    system(command.c_str());

}




// Builds bowtie index from reference genome (DB graph unitigs)
void buildBowtieIndex(SettingsStructure& settings){

    cout<<endl<<"Building bowtie index ... "<<endl;

    // Initializes command to build the bowtie index - see bowtie manual
    string command = settings.pathToBowtie + "bowtie-build " + settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName + " " +
                     settings.pathToOutput + "temp_index_" + settings.baseFileName + "&> logs_bowtie_index.txt";

    // Runs command and stores state
    system(command.c_str());

}




// Runs bowtie to align reads on DB graph unitigs
void runBowtie(SettingsStructure& settings){

    cout<<endl<<"Running bowtie ... "<<endl;

    // Initializes command to run bowtie with desired parameters and input/output files
    string command = settings.pathToBowtie + "bowtie -f -k 1 --best -v " + to_string(settings.nAllowedMismatchesForBowtie) + " -p " +
                     to_string(settings.nCores) + " " + settings.pathToOutput + "temp_index_" + settings.baseFileName + " " +
                     settings.pathToOutput + "temp_bgreat_uncorrected_" + settings.baseFileName + ".fasta -S --sam-nohead --sam-nosq | " +
                     settings.pathToBowtieParser + "bowtie_to_reads  " + settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName + " false " +
                     settings.pathToOutput + "temp_bowtie_corrected_" + settings.baseFileName + "&> logs_bowtie.txt";

    // Runs command and stores state
    system(command.c_str());

}




// Runs Bcalm to generate DB graph from original reads
void runBcalm(SettingsStructure& settings){

    cout<<endl<<"Running Bcalm ... "<<endl;

    // Initializes command to run bcalm on original reads with desired input/output files
    string command = settings.pathToBcalm + "bcalm -in " + settings.pathToReads + settings.baseFileName + ".fasta -k " + to_string(settings.kmerSize_bcalm) +
                     " -abundance " + to_string(settings.abundanceThreshold_bcalm) + " -out " + settings.pathToOutput + "temp_bcalm_" +
                     settings.baseFileName + " -verbose 0 -nb-cores " + to_string(settings.nCores) + "&> logs_bcalm.txt";

    // Runs command and stores state
    system(command.c_str());

}




// Runs Bglue to generate unitigs from Bcalm output
void runBglue(SettingsStructure& settings){

    cout<<endl<<"Running Bglue... "<<endl;

    // Initializes command to run bglue on bcalm output with desired input/output files
    string command = settings.pathToBcalm + "bglue -in " + settings.pathToOutput + "temp_bcalm_" + settings.baseFileName + ".h5 -verbose 0 -k " +
                     to_string(settings.kmerSize_bcalm) + " -nb-cores " + to_string(settings.nCores) + " -out " + settings.pathToOutput +
                     "temp_bglue_" + settings.baseFileName + "&> logs_bglue.txt";

    // Runs command and stores state
    system(command.c_str());

}
