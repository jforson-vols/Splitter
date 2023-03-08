#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <tuple>
#include <vector>
#include <stdio.h>
#include <math.h>
#include <complex>
#include <stdint.h>
#include <string.h>
#include <algorithm>

int main(){

//Open RunTimes.txt
  std::string RunTimes;
  std::ifstream runs("RunTimes.txt");
  if(!runs.good()){
    std::cerr << "Couldn't Open RunTimes.txt" << std::endl;
    return 0;
  }
  
//Open FullDat.txt
  std::string FullData;
  std::ifstream data("FullDat.txt");
  if(!data.good()){
    std::cerr << "Couldn't Open FullDat.txt" << std::endl;
    return 0;
  }
  
//Start Loop 1
  std::string ends;
  int run = 0;
  while (std::getline(runs , ends)){
    std::ofstream runfile;
    int n = ends.length();
    char ends_array[n+1];
    strcpy(ends_array,ends.c_str());
    run++;
    std::cout << "Run: " << run << " " << ends << std::endl;
    
//Open a run_XXX.dat file
    if(run <= 9){
      std::string str1 = "./runs/run_00";
      std::string str2 = std::to_string(run);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
    }
    if((run >= 10) && (run <= 99)){
      std::string str1 = "./runs/run_0";
      std::string str2 = std::to_string(run);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
    }
    if(run >= 100){
      std::string str1 = "./runs/run_";
      std::string str2 = std::to_string(run);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
    }
    
//Read a Line from RunTimes.txt
    char *token = strtok(ends_array, " - : \t");
    int iday = std::stoi(token);
    token = strtok(NULL, " - : \t ");
    std::string imonth = token;
    token = strtok(NULL, " - : \t ");
    int iyear = std::stoi(token);
    token = strtok(NULL, " - : \t ");
    int ihour = std::stoi(token);
    token = strtok(NULL, " - : \t ");
    int imin = std::stoi(token);
    token = strtok(NULL, " - : \t ");
    int isec = std::stoi(token);
    token = strtok(NULL, " - : \t ");
    int fday = std::stoi(token);
    token = strtok(NULL, " - : \t ");
    std::string fmonth = token;
    token = strtok(NULL, " - : \t ");
    int fyear = std::stoi(token);
    token = strtok(NULL, " - : \t ");
    int fhour = std::stoi(token);
    token = strtok(NULL, " - : \t ");
    int fmin = std::stoi(token);
    token = strtok(NULL, " - : \t ");
    int fsec = std::stoi(token);
    
//Prep for Comparison
    if((iday != fday) || (!imonth.compare(fmonth) == 0) || (iyear != fyear)) fhour = fhour + 24;
    int start = (ihour*10000) + (imin*100) + isec;
    int end = (fhour*10000) + (fmin*100) + fsec;
    int imon, fmon;
    if(imonth.compare("Apr") == 0) imon = 4;
    if(fmonth.compare("Apr") == 0) fmon = 4;
    if(imonth.compare("May") == 0) imon = 5;
    if(fmonth.compare("May") == 0) fmon = 5;
    
//Start Loop 2
    std::string datapoint;
    int j = 0;
    while (std::getline(data , datapoint)){
      int m = datapoint.length();
      char data_array[m+1];
      strcpy(data_array,datapoint.c_str());
      j++;
      std::cout << "Loop: " << j << " " << datapoint << std::endl;
      
//Read a Line from FullDat.txt
      char *pch = strtok(data_array, " - : \t ");
      int year = std::stoi(pch);
      year = year - 2000;
      pch = strtok(NULL, " - : \t ");
      int mon = std::stoi(pch);
      pch = strtok(NULL, " - : \t ");
      int day = std::stoi(pch);
      pch = strtok(NULL, " - : \t ");
      int hour = std::stoi(pch);
      pch = strtok(NULL, " - : \t ");
      int min = std::stoi(pch);
      pch = strtok(NULL, " - : \t ");
      int sec = std::stoi(pch);
      pch = strtok(NULL, " - : \t ");
      float value = std::stoi(pch);

      int time = (hour*10000) + (min*100) + sec;
      
//If point FullDat point is between RunTimes points, write to run_XXX.dat
      if((iyear <= year) && (fyear >= iyear) && (imon <= mon) && (fmon >= mon) && (iday <= day) && (fday >= day) && (start <= time) && (end >= time) ){
	runfile << value << std::endl;
      }
      
//End Loop 2
    }
    data.clear();
    data.seekg(0);
    std::cout << "Check New 1" << std::endl;
//Close run_XXX.dat
    runfile.close();
    
//End Loop 1
  }
  
//Close FullDat.txt
  data.close();

//Close RunTimes.txt
  runs.close();
  
//End
  return 0;
}
