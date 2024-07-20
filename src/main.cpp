#include <iostream>
#include <CGAL/Simple_cartesian.h>
#include "OFFManager.h"
#include "TriangleToQuadConverter.h"

int main()
{
	Mesh_2 mesh;
	if (OFFFileHandler::read("../../data/pikachu.off", mesh)) {
		std::cout << "File read successfully" << std::endl;
	}
	else {
		std::cout << "Error reading file" << std::endl;
	}
	Mesh_2 quadMesh;
	TriangleToQuadConverter::TriangleSplitting(mesh, quadMesh);
	if (OFFFileHandler::write("../../data/pikachu_quad.off", quadMesh)) {
		std::cout << "File written successfully" << std::endl;
	}
	else {
		std::cout << "Error writing file" << std::endl;
	}
	//OFFFileHandler::draw(mesh);
	return 0;
}