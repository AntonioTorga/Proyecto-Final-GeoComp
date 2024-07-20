#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include "OFFManager.h"
#include "TriangleToQuadConverter.h"

int main(int argc, char** argv)
{
	Mesh_2 mesh;
	Mesh_2 quadMesh;

	std::string conversion_type = argv[1];
	std::string file_path = argv[2];
	std::string output_path = argv[3];

	if (OFFFileHandler::read(file_path, mesh)) {
		std::cout << "File: "<<file_path<<" read successfully" << std::endl;
	}
	else {
		std::cout << "Error reading file" << std::endl;
	}
	if (conversion_type == "-split") {
		std::cout << "Conversion algorithm: Splitting triangles" << std::endl;
		TriangleToQuadConverter::TriangleSplitting(mesh, quadMesh);
	}
	else if (conversion_type == "-merge") {
		std::cout << "Conversion algorithm: Merging triangles" << std::endl;
		TriangleToQuadConverter::TriangleMerging(mesh, quadMesh);
	}
	else {
		std::cout << "Invalid conversion type" << std::endl;
		return 1;
	}

	if (OFFFileHandler::write(output_path, quadMesh)) {
		std::cout << "File: "<< output_path <<"written successfully" << std::endl;
	}
	else {
		std::cout << "Error writing file" << std::endl;
	}
	//OFFFileHandler::draw(mesh);
	return 0;
}