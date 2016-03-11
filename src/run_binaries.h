#pragma once

#include "settings.h"


// Runs bgreat to align reads on multiple unitigs
void runBgreat(SettingsStructure& settings);

// Builds bowtie index from reference genome (DB graph unitigs)
void buildBowtieIndex(SettingsStructure& settings);

// Runs bowtie to align reads on DB graph unitigs
void runBowtie(SettingsStructure& settings);

// Builds bowtie 2 index from reference genome (DB graph unitigs)
void buildBowtie2Index(SettingsStructure& settings);

// Runs bowtie 2 to align reads on DB graph unitigs
void runBowtie2(SettingsStructure& settings);

// Builds BWA index from reference genome (DB graph unitigs)
void buildBwaIndex(SettingsStructure& settings);

// Runs BWA to align reads on DB graph unitigs
void runBwa(SettingsStructure& settings);

// Runs Bcalm to generate DB graph from original reads
void runBcalm(SettingsStructure& settings);

// Runs Bglue to generate unitigs from Bcalm output
void runBglue(SettingsStructure& settings);

