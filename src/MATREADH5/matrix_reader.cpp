#include <iostream>
#include <string>
#include <vector>
#include <hdf5.h>

int main() {
    // 1. Open the HDF5 file
    const std::string filename = "my_matrix.h5"; 
    hid_t file_id = H5Fopen(filename.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT); 
    if (file_id < 0) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1; 
    }

    // 2. Open the dataset 
    hid_t dataset_id = H5Dopen2(file_id, "/home/aaron", H5P_DEFAULT); 
    if (dataset_id < 0) {
        std::cerr << "Error: Could not open dataset." << std::endl;
        H5Fclose(file_id);
        return 1;
    }

    // 3. Get dataset dimensions
    hid_t dataspace = H5Dget_space(dataset_id);
    int rank = H5Sget_simple_extent_ndims(dataspace); 
    if (rank <= 0) {
        std::cerr << "Error: Invalid dataset rank." << std::endl;
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 1;
    }

    // Use a vector to store dimensions
    std::vector<hsize_t> dims(static_cast<std::size_t>(rank)); 
    H5Sget_simple_extent_dims(dataspace, dims.data(), NULL);
    H5Sclose(dataspace); 

    // 4. Calculate array size
    size_t array_size = 1;
    for (hsize_t dim : dims) {
        array_size *= dim;
    }

    // 5. Create a vector for data
    std::vector<double> data(array_size); 

    // 6. Create memory dataspace
    hid_t memspace = H5Screate_simple(rank, dims.data(), NULL); 

    // 7. Read data from HDF5 file
    herr_t status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, memspace, memspace, H5P_DEFAULT, data.data());
    if (status < 0) {
        std::cerr << "Error: Failed to read data from HDF5 file." << std::endl;
        H5Sclose(memspace);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
        return 1;
    }

    // 8. Close resources
    H5Sclose(memspace);
    H5Dclose(dataset_id);
    H5Fclose(file_id);

    // 9. Print the data (optional)
    unsigned int rows = static_cast<unsigned int>(dims[0]);
    unsigned int cols = static_cast<unsigned int>(dims[1]);
    for (unsigned int i = 0; i < rows; ++i) {
      for (unsigned int j = 0; j < cols; ++j ){ 
        std::cout << data[(i*cols) + j] << " ";
      }
      std::cout << std::endl;
    }

    return 0;
}

