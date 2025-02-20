#include <iostream>
#include <netcdf>
#include <array>
#include <stdexcept>

int main() {
    try {
        // Open the NetCDF file for reading
        netCDF::NcFile dataFile("matrix.nc", netCDF::NcFile::read);

        // Try to retrieve the variable (assuming it's named "matrix")
        netCDF::NcVar matrixVar;
        try {
            matrixVar = dataFile.getVar("matrix");
        } catch (netCDF::exceptions::NcException& e) {
            std::cerr << "Error: The variable 'matrix' does not exist in the file.\n";
            return 1;
        }

        // Check if the variable has exactly two dimensions (i.e., is a matrix)
        if (matrixVar.getDimCount() != 2) {
            std::cerr << "Error: The variable 'matrix' is not a 2D matrix.\n";
            return 1;
        }

        // Get the dimensions of the matrix
        size_t dim1 = matrixVar.getDim(0).getSize();
        size_t dim2 = matrixVar.getDim(1).getSize();

        // Print dimensions
        std::cout << "Matrix dimensions: (" << dim1 << ", " << dim2 << ")\n";

        // Create a vector of appropriate size (stack-allocated if possible)
        std::array<double, dim1*dim2> matrixData;  // Assuming matrix is of type float

        // Read the data from the NetCDF variable into the vector
        matrixVar.getVar(matrixData.data());

        // Optionally, print the matrix data to verify it was read correctly
        for (size_t i = 0; i < dim1; ++i) {
            for (size_t j = 0; j < dim2; ++j) {
                std::cout << matrixData[i * dim2 + j] << " ";
            }
            std::cout << std::endl;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

