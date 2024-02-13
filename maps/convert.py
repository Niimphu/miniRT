import sys
import os.path
from stl import mesh

# Check if the correct number of arguments is provided
if len(sys.argv) != 2:
    print("Usage: python convert_stl.py <input_file.stl>")
    sys.exit(1)

# Get the input file path from the command-line argument
input_file = sys.argv[1]

# Verify the input file exists
if not os.path.isfile(input_file):
    print(f"Error: File '{input_file}' does not exist.")
    sys.exit(1)

# Extract the input file's name and extension
input_file_name, input_file_ext = os.path.splitext(input_file)

# Check if the input file has the .stl extension
if input_file_ext.lower() != '.stl':
    print("Error: Input file must have the .stl extension.")
    sys.exit(1)

# Load the STL file
your_mesh = mesh.Mesh.from_file(input_file)

# Create the output file path with the .rt extension
output_file = f"{input_file_name}.rt"

# Open the output file for writing
with open(output_file, 'w') as f:
    # Iterate through each triangle
    for triangle in your_mesh.vectors:
        # Write each vertex of the triangle on a single line
        f.write ("tr  ");
        for vertex in triangle:
            # Format the vertex coordinates and write to the file
            f.write(f"{vertex[0]},{vertex[1]},{vertex[2]}  ")
        # Add an empty line to separate triangles
        f.write('100,100,100  \n')

print(f"Conversion successful. Output written to '{output_file}'.")
