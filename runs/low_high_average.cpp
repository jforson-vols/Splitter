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

//Subroutine: Check Runs Map
bool CheckRuns(int i){  
  int a, b;
  std::ifstream RunMap("DataRunsMap.txt");
  if(!RunMap.good()){
    std::cout << "Couldn't Read Map";
    return 0;
  } 
  while(RunMap.good()){
    RunMap >> a >> b;
    if((a <= i) && (b >= i)) return true;
  }
  return false;
}

//Subroutine: Find Lowest Value in a run file
float Lowest(int i){
  std::ifstream runfile;
  
  if(i <= 9){
      std::string str1 = "run_00";
      std::string str2 = std::to_string(i);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
      if(!runfile.good()){
        std::cerr << "Couldn't Open run_0" << i << std::endl;
        return 0;
      }
    }
    if((i >= 10) && (i <= 99)){
      std::string str1 = "run_0";
      std::string str2 = std::to_string(i);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
      if(!runfile.good()){
        std::cerr << "Couldn't Open run_00" << i << std::endl;
        return 0;
      }
    }
    if(i >= 100){
      std::string str1 = "run_";
      std::string str2 = std::to_string(i);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
      if(!runfile.good()){
        std::cerr << "Couldn't Open run_" << i << std::endl;
        return 0;
      }
    }

    float lowest = 0.0, a;
    while(runfile.good()){
      runfile >> a;
      if((lowest == 0.0) || (a <= lowest)) lowest = a; 
      }
    runfile.clear();
    runfile.seekg(0);
    return lowest;
}

//Subroutine: Find Highest Value in a run file
float Highest(int i){
  std::ifstream runfile;
  
  if(i <= 9){
      std::string str1 = "run_00";
      std::string str2 = std::to_string(i);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
      if(!runfile.good()){
        std::cerr << "Couldn't Open run_0" << i << std::endl;
        return 0;
      }
    }
    if((i >= 10) && (i <= 99)){
      std::string str1 = "run_0";
      std::string str2 = std::to_string(i);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
      if(!runfile.good()){
        std::cerr << "Couldn't Open run_00" << i << std::endl;
        return 0;
      }
    }
    if(i >= 100){
      std::string str1 = "run_";
      std::string str2 = std::to_string(i);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
      if(!runfile.good()){
        std::cerr << "Couldn't Open run_" << i << std::endl;
        return 0;
      }
    }

    float highest = 0.0, a;
    while(runfile.good()){
      runfile >> a;
      if((highest == 0.0) || (a >= highest)) highest = a; 
      }
    runfile.clear();
    runfile.seekg(0);
    return highest;
}

//Subroutine: Find the Average Value in a run file
float Mean(int i){
 std::ifstream runfile;

  if(i <= 9){
      std::string str1 = "run_00";
      std::string str2 = std::to_string(i);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
      if(!runfile.good()){
        std::cerr << "Couldn't Open run_0" << i << std::endl;
	return 0;
      }
    }
    if((i >= 10) && (i <= 99)){
      std::string str1 = "run_0";
      std::string str2 = std::to_string(i);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
      if(!runfile.good()){
        std::cerr << "Couldn't Open run_00" << i << std::endl;
        return 0;
      }
    }
    if(i >= 100){
      std::string str1 = "run_";
      std::string str2 = std::to_string(i);
      std::string str3 = ".dat";
      runfile.open(str1 + str2 + str3);
      if(!runfile.good()){
        std::cerr << "Couldn't Open run_" << i << std::endl;
	return 0;
      }
    }

    float mean = 0.0, sum = 0.0, a;
    int n = 0;
    while(runfile.good()){
      runfile >> a;
      sum = sum + a;
      n++;
    }
    
    if( n == 0 ) n++;
    std::cout << sum << " " << n << std::endl; 
    mean = sum / n;
    runfile.clear();
    runfile.seekg(0);
    return mean;

}


int main() {
  
//Create Low file
  std::ofstream lowfile;
  lowfile.open("./lha/lows.txt");
  
//Create High file
  std::ofstream highfile;
  highfile.open("./lha/highs.txt");

//Create Average file
  std::ofstream averagefile;
  averagefile.open ("./lha/averages.txt");

  float lowest, highest, mean;
//Loop 1
  for(int i = 1 ; i <= 192 ; i++){
    
//Check against Runs Map1

    //-If Yes, Run Low subroutine for Value and Write to Low File   
    //-If Yes, Run High subroutine for Value and Write to High File                    
    //-If Yes, Run Average subroutine for Value and Write to Average File    
    if(CheckRuns(i) == true){
      lowest = Lowest(i);
      lowfile << i << " " << lowest << std::endl;
      highest = Highest(i);
      highfile << i << " " << highest << std::endl;
      mean = Mean(i);
      averagefile << i << " " << mean << std::endl;
    }


    //if check against the Runs Map comes back No, write 0 to all files.
    if(CheckRuns(i) == false){
      lowfile << i << " 0" << std::endl;
      highfile << i << " 0" << std::endl;
      averagefile << i << " 0" << std::endl;
    }
    
//-If Yes, Run Low subroutine for Value and Write to Low File
//-If Yes, Run High subroutine for Value and Write to High File
//-If Yes, Run Average subroutine for Value and Write to Average File
    
//End Loop 1
  }
//End
}
