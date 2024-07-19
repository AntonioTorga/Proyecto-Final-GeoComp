#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh/IO/OFF.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/draw_surface_mesh.h>

#include <iostream>
#include <fstream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Surface_mesh<Kernel::Point_2> Mesh;

class OFFFileHandler {
public:
    // Reads an OFF file and loads it into a Mesh object
    bool read(std::string& filename, Mesh& mesh);

    // Writes a Mesh object to an OFF file
 //   static bool write(const std::string& filename, const Mesh& mesh);

	//static bool draw(const Mesh& mesh);
};