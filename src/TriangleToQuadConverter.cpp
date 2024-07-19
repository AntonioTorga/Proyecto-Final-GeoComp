#include "TriangleToQuadConverter.h"

bool TriangleToQuadConverter::TriangleSplitting(const Mesh& triangleMesh, Mesh& quadMesh) 
{
	// Check if the input mesh is a triangle mesh
	if (!checkIfTriangleMesh(triangleMesh)) return false;
	// Create a new mesh
	Mesh newMesh;
	// Iterate over the faces of the input mesh
	for (f_index face : triangleMesh.faces()) {
		// Get the vertices of the face and put on a vector
		splitTriangle(triangleMesh, face, newMesh);
	}
	quadMesh = newMesh;
}


bool TriangleToQuadConverter::TriangleMerging(const Mesh & triangleMesh, Mesh & quadMesh)
{
	// Check if the input mesh is a triangle mesh
	if (!checkIfTriangleMesh(triangleMesh)) return false;
	Mesh newMesh;

	auto triangles = triangleMesh.faces();
	for (auto triangle : triangles) {
		mergeTriangle(triangleMesh, triangle, newMesh);
	}
	quadMesh = newMesh;
}

bool TriangleToQuadConverter::checkIfTriangle(const Mesh& mesh, const f_index& face)
{
	auto half_edge = mesh.halfedge(face);
	auto h_edge = half_edge;
	int count = 0;
	do {
		if (mesh.is_border(h_edge)) return false;
		h_edge = mesh.next(h_edge);
		count++;
	} while (h_edge != half_edge);
	return count == 3;
}

bool TriangleToQuadConverter::checkIfTriangleMesh(const Mesh& mesh)
{
	// Iterate over the faces of the mesh
	for (auto face : mesh.faces()) {
		if (!checkIfTriangle(mesh, face)) return false;
	}
	return true;
}

void TriangleToQuadConverter::getVerticesFromFace(const Mesh& triangleMesh, const f_index& face, Point& v0, Point& v1, Point& v2)
{
	if (!checkIfTriangle(triangleMesh, face)) return;
	h_index halfedge = triangleMesh.halfedge(face);
	h_index next_halfedge = triangleMesh.next(halfedge);
	v0 = triangleMesh.point(triangleMesh.source(halfedge));
	v1 = triangleMesh.point(triangleMesh.target(halfedge));
	v2 = triangleMesh.point(triangleMesh.target(next_halfedge));
}

void TriangleToQuadConverter::splitTriangle(const Mesh& triangleMesh, const f_index& face, Mesh& newMesh)
{
	Point v0, v1, v2;

	getVerticesFromFace(triangleMesh, face, v0, v1, v2);

	// Compute the circumcenter of the vertices
	Point c = CGAL::circumcenter(v0, v1, v2);

	Point mid_v0v1 = CGAL::midpoint(v0, v1), mid_v1v2 = CGAL::midpoint(v1, v2), mid_v2v0 = CGAL::midpoint(v2, v0);


	// Create vertices and faces in new mesh
	v_index c_index = newMesh.add_vertex(c), v0_index = newMesh.add_vertex(v0), v1_index = newMesh.add_vertex(v1), v2_index = newMesh.add_vertex(v2);
	v_index mid_v0v1_index = newMesh.add_vertex(mid_v0v1), mid_v1v2_index = newMesh.add_vertex(mid_v1v2), mid_v2v0_index = newMesh.add_vertex(mid_v2v0);

	newMesh.add_face(v0_index, mid_v0v1_index,c_index, mid_v2v0_index);
	newMesh.add_face(mid_v0v1_index, v1_index, mid_v1v2_index, c_index);
	newMesh.add_face(mid_v2v0_index, c_index, mid_v1v2_index, v2_index);
}

void TriangleToQuadConverter::mergeTriangle(const Mesh& triangleMesh, const f_index& face, Mesh& newMesh)
{
	
}

f_index TriangleToQuadConverter::getNextTriangle(const Mesh& mesh, const f_index& face)
{
	auto halfedge = mesh.halfedge(face);
	auto h_edge = halfedge;
	do {
		f_index pos_triangle = mesh.face(mesh.opposite(h_edge));
		if (checkIfTriangle(mesh, pos_triangle)) return pos_triangle;
	} while (h_edge != halfedge);

	return face;
}

