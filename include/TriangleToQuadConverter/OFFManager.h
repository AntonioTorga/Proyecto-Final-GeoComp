#include <CGAL/Surface_mesh.h>
#include <CGAL/Surface_mesh/IO/OFF.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
//#include <CGAL/draw_surface_mesh.h>

#include <fstream>
#include <iostream>
#include <fstream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3 Point_3;
typedef Kernel::Point_2 Point_2;
typedef CGAL::Surface_mesh<Point_2> Mesh_2;
typedef CGAL::Surface_mesh<Point_3> Mesh_3;

class OFFFileHandler {
public:
    // Reads an OFF file and loads it into a Mesh object
    static bool read(const std::string& filename, Mesh_2& mesh);

    // Writes a Mesh object to an OFF file
    static bool write(const std::string& filename, Mesh_2& mesh);

	//static bool draw(const Mesh_2& mesh);
private:
    static void project_to_2d(Mesh_3& mesh3, Mesh_2& mesh2);
	static void project_to_3d(Mesh_2& mesh2, Mesh_3& mesh3);
};