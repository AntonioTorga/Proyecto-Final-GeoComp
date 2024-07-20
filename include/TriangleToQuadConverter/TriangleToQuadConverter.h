#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <CGAL/draw_surface_mesh.h>
#include <CGAL/Polygon_mesh_processing/repair_polygon_soup.h>

#include <algorithm>
#include <iostream>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point;
typedef CGAL::Surface_mesh<Point> Mesh;
typedef Mesh::Vertex_index v_index;
typedef Mesh::Face_index f_index;
typedef Mesh::Halfedge_index h_index;
typedef Mesh::Edge_index e_index;

namespace PMP = CGAL::Polygon_mesh_processing;


class TriangleToQuadConverter {
public:
	static bool TriangleSplitting(const Mesh& triangleMesh, Mesh& quadMesh);
	static bool TriangleMerging(const Mesh& triangleMesh, Mesh& quadMesh);
private:
	static bool checkIfTriangle(const Mesh& mesh, const f_index& face);
	static bool checkIfTriangleMesh(const Mesh& mesh);
	static void splitTriangle(const Mesh& triangleMesh, const f_index& face, Mesh& newMesh);
	static void mergeTriangle(const Mesh& oldMesh, h_index h_e, Mesh& newMesh);
	static void getVerticesFromFace(const Mesh& mesh, const f_index& face, Point& v0, Point& v1, Point& v2);
	static f_index getNextTriangle(const Mesh& mesh, const f_index& face, std::vector<f_index>& triangles_vector, h_index& h_e);
};