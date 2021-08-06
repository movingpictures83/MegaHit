#include "PluginManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "MegaHitPlugin.h"

void MegaHitPlugin::input(std::string file) {
 inputfile = file;
 std::ifstream ifile(inputfile.c_str(), std::ios::in);
 while (!ifile.eof()) {
   std::string filename;
   ifile >> filename;
   fastqFiles.push_back(filename);
 }
}

void MegaHitPlugin::run() {
   
}

void MegaHitPlugin::output(std::string file) {
 // spades.py -o 02_MegaHit -1 $1 -2 $2 --careful
   std::string command = "[ -d "+file+" ] && rm -r "+file+"; megahit -o "+file+" -1 "+std::string(PluginManager::prefix())+"/"+fastqFiles[0]+" -2 "+std::string(PluginManager::prefix())+"/"+fastqFiles[1];
 std::cout << command << std::endl;

 system(command.c_str());

std::string copyCommand = "cp "+file+"/final.contigs.fa "+std::string(PluginManager::prefix());
 std::cout << copyCommand << std::endl;
 system(copyCommand.c_str());
}

PluginProxy<MegaHitPlugin> MegaHitPluginProxy = PluginProxy<MegaHitPlugin>("MegaHit", PluginManager::getInstance());
