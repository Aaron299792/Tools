#include<iostream>
#include<netcdf>
#include<vector>
#include<cmath>
#include<string>

std::vector<double> readmat(std::string const filename){
  std::vector<double>  matdata;
  netCDF::NcFile matfile(filename, netCDF::NcFile::read);
  matfile.getVar("matrix").getVar(matdata.data());
  return matdata;
}

int main(){
  

  std::vector<double> matrix = readmat("matrix.nc");


  return 0;
}
