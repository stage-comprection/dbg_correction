#include "run_binaries.h"

using namespace std;


// Runs bgreat to align reads on multiple unitigs
void runBgreat(SettingsStructure& settings){

    cout<<"\n    ** Running Bgreat ... \n";

    // Initializes command to run bgreat in correction mode (-c) with desired path and parameters
    string command = settings.pathToBgreat + "bgreat -r " + settings.pathToReads + settings.baseFileName + ".fasta -k " + to_string(settings.kmerSize) +
                     " -g " + settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName + " -m " + to_string(settings.abundanceThreshold) +
                     " -c -t " + to_string(settings.nCores) + " -f " + settings.pathToOutput + "temp_bgreat_corrected_" + settings.baseFileName + " -o " +
                     settings.pathToOutput + "temp_bgreat_noOverlap_" + settings.baseFileName + " -a " + settings.pathToOutput + "temp_bgreat_noAlign_" +
                     settings.baseFileName + " 1>" + settings.pathToOutput + "logs_bgreat.txt" + " 2>/dev/null";

    // Runs command and stores state
    system(command.c_str());

}




// Builds bowtie index from reference genome (DB graph unitigs)
void buildBowtieIndex(SettingsStructure& settings){

    cout<<"\n    ** Building bowtie index ... \n";

    // Initializes command to build the bowtie index - see bowtie manual
    string command = settings.pathToBowtie + "bowtie-build " + settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName + " " +
                     settings.pathToOutput + "temp_index_" + settings.baseFileName + " 1>" + settings.pathToOutput + "logs_aligner_index.txt" +
                     " 2>/dev/null";

    // Runs command and stores state
    system(command.c_str());

}




// Runs bowtie to align reads on DB graph unitigs
void runBowtie(SettingsStructure& settings){

    cout<<"\n    ** Running Bowtie ... \n";

    // Initializes command to run bowtie with desired parameters and input/output files
    string command = settings.pathToBowtie + "bowtie -f -k 1 --best -v " + to_string(settings.nAllowedMismatchesForBowtie) + " -p " +
                     to_string(settings.nCores) + " " + settings.pathToOutput + "temp_index_" + settings.baseFileName + " " +
                     settings.pathToOutput + "temp_bgreat_uncorrected_" + settings.baseFileName + ".fasta 2>" + settings.pathToOutput + "logs_aligner.txt" +
                     " -S --sam-nohead --sam-nosq | " +
                     settings.pathToBowtieParser + "bowtie_to_reads  " + settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName + " false " +
                     settings.pathToOutput + "temp_aligner_corrected_" + settings.baseFileName;

    // Runs command and stores state
    system(command.c_str());

}




// Builds bowtie index from reference genome (DB graph unitigs)
void buildBowtie2Index(SettingsStructure& settings){

    cout<<"\n    ** Building bowtie 2 index ... \n";

    // Initializes command to build the bowtie index - see bowtie manual
    string command = settings.pathToBowtie2 + "bowtie2-build -f " + settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName + " " +
                     settings.pathToOutput + "temp_index_" + settings.baseFileName + " 1>" + settings.pathToOutput + "logs_aligner_index.txt" +
                     " 2>/dev/null";

    // Runs command and stores state
    system(command.c_str());

}




// Runs bowtie to align reads on DB graph unitigs
void runBowtie2(SettingsStructure& settings){

    cout<<"\n    ** Running Bowtie 2 ... \n";

    // Initializes command to run bowtie with desired parameters and input/output files
    string command = settings.pathToBowtie2 + "bowtie2 -f --very-sensitive -p " +
                     to_string(settings.nCores) + " -x " + settings.pathToOutput + "temp_index_" + settings.baseFileName + " " +
                     settings.pathToOutput + "temp_bgreat_uncorrected_" + settings.baseFileName + ".fasta 2>" + settings.pathToOutput + "logs_aligner.txt" +
                     " --no-head --no-sq | " +
                     settings.pathToBowtieParser + "bowtie_to_reads  " + settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName + " false " +
                     settings.pathToOutput + "temp_aligner_corrected_" + settings.baseFileName;

    // Runs command and stores state
    system(command.c_str());

}




// Builds bowtie index from reference genome (DB graph unitigs)
void buildBwaIndex(SettingsStructure& settings){

    cout<<"\n    ** Building BWAindex ... \n";

    // Initializes command to build the bowtie index - see bowtie manual
    string command = settings.pathToBwa + "bwa index -p " + settings.pathToOutput + "temp_index_" + settings.baseFileName + " " +
                     settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName + " " +
                     " &>" + settings.pathToOutput + "logs_aligner_index.txt";

    // Runs command and stores state
    system(command.c_str());

}




// Runs bowtie to align reads on DB graph unitigs
void runBwa(SettingsStructure& settings){

    cout<<"\n    ** Running BWA ... \n";

    // Initializes command to run bowtie with desired parameters and input/output files
    string command = settings.pathToBwa + "bwa mem -t " +
                     to_string(settings.nCores) + " " + settings.pathToOutput + "temp_index_" + settings.baseFileName + " " +
                     settings.pathToOutput + "temp_bgreat_uncorrected_" + settings.baseFileName + ".fasta 2>" + settings.pathToOutput + "logs_aligner.txt" +
                     " | " +
                     settings.pathToBowtieParser + "bowtie_to_reads  " + settings.pathToOutput + "temp_formatted_bglue_" + settings.baseFileName + " false " +
                     settings.pathToOutput + "temp_aligner_corrected_" + settings.baseFileName;

    // Runs command and stores state
    system(command.c_str());

}




// Runs Bcalm to generate DB graph from original reads
void runBcalm(SettingsStructure& settings){

    cout<<"\n    ** Running Bcalm ... \n";

    // Initializes command to run bcalm on original reads with desired input/output files
    string command = settings.pathToBcalm + "bcalm -in " + settings.pathToReads + settings.baseFileName + ".fasta -k " + to_string(settings.kmerSize) +
                     " -abundance " + to_string(settings.abundanceThreshold) + " -out " + settings.pathToOutput + "temp_bcalm_" +
                     settings.baseFileName + " -verbose 0 -nb-cores " + to_string(settings.nCores) + " 1>" + settings.pathToOutput + "logs_bcalm.txt" +
                     " 2>/dev/null";

    // Runs command and stores state
    system(command.c_str());

}




// Runs Bglue to generate unitigs from Bcalm output
void runBglue(SettingsStructure& settings){

    cout<<"\n    ** Running Bglue... \n";

    // Initializes command to run bglue on bcalm output with desired input/output files
    string command = settings.pathToBcalm + "bglue -in " + settings.pathToOutput + "temp_bcalm_" + settings.baseFileName + ".h5 -verbose 0 -k " +
                     to_string(settings.kmerSize) + " -nb-cores " + to_string(settings.nCores) + " -out " + settings.pathToOutput +
                     "temp_bglue_" + settings.baseFileName + " 1>" + settings.pathToOutput + "logs_bglue.txt" + " 2>/dev/null";

    // Runs command and stores state
    system(command.c_str());

}
