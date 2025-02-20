# Create a new NetCDF file and define dimensions (3x3)
ncgen -o matrix.nc - <<EOF
netcdf matrix {
dimensions:
    x = 3;
    y = 3;
variables:
  double matrix(x, y);
data:
    matrix =
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0;
}
EOF

