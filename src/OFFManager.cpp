#include "OFFManager.h"

bool OFFFileHandler::read(const std::string& filename, Mesh_2& mesh2)
{
    std::ifstream myfile(filename.c_str());
	Mesh_3 mesh3;
	if (!myfile.is_open()) {
		std::cerr << "Could not open file " << filename << std::endl;
		return false;
	}
	if(!CGAL::IO::read_OFF(myfile, mesh3) )
	{
		std::cerr << "Invalid OFF file " << filename << std::endl;
		return false;
	}
	project_to_2d(mesh3, mesh2);
    return true;
}

bool OFFFileHandler::write(const std::string& filename, Mesh_2& mesh2) 
{
	std::ofstream myfile(filename.c_str());
	Mesh_3 mesh3;
	project_to_3d(mesh2, mesh3);
	if (!myfile.is_open()) {
		std::cerr << "Could not open file " << filename << std::endl;
		return false;
	}
	if (!CGAL::IO::write_OFF(myfile, mesh3))
	{
		std::cerr << "Could not write to file " << filename << std::endl;
		return false;
	}
	return true;
}
//
//bool OFFFileHandler::draw(const Mesh_2& mesh)
//{
//	CGAL::draw(mesh);
//	return true;
//}

void OFFFileHandler::project_to_2d(Mesh_3& mesh3, Mesh_2& mesh2)
{
        mesh2.clear();
        std::map<Mesh_3::Vertex_index, Mesh_2::Vertex_index> vertex_map;

        for (auto v : mesh3.vertices()) {
            Point_3 p3 = mesh3.point(v);
            Point_2 p2(p3.x(), p3.y());  // Project to 2D (ignoring z-coordinate)
            vertex_map[v] = mesh2.add_vertex(p2);
        }

        for (auto f : mesh3.faces()) {
            std::vector<Mesh_2::Vertex_index> vertices;
            for (auto v : vertices_around_face(mesh3.halfedge(f), mesh3)) {
                vertices.push_back(vertex_map[v]);
            }
            mesh2.add_face(vertices);
        }
}

void OFFFileHandler::project_to_3d(Mesh_2& mesh2, Mesh_3& mesh3)
{
	mesh3.clear();
	std::map<Mesh_2::Vertex_index, Mesh_3::Vertex_index> vertex_map;

	for (auto v : mesh2.vertices()) {
		Point_2 p2 = mesh2.point(v);
		Point_3 p3(p2.x(), p2.y(), 0);  // Project to 3D (z-coordinate is 0)
		vertex_map[v] = mesh3.add_vertex(p3);
	}

	for (auto f : mesh2.faces()) {
		std::vector<Mesh_3::Vertex_index> vertices;
		for (auto v : vertices_around_face(mesh2.halfedge(f), mesh2)) {
			vertices.push_back(vertex_map[v]);
		}
		mesh3.add_face(vertices);
	}
}
