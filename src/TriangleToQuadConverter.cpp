#include "TriangleToQuadConverter.h"

bool TriangleToQuadConverter::TriangleSplitting(const Mesh& triangleMesh, Mesh& quadMesh) 
{
	// Check if the input mesh is a triangle mesh
	if (!checkIfTriangleMesh(triangleMesh)) return false;
	// Create a new mesh
	Mesh newMesh;
	// Iterate over the faces of the input mesh
	for (f_index face : triangleMesh.faces()) {
		splitTriangle(triangleMesh, face, newMesh);
	}
	// cast newMesh to polygon soup
	quadMesh = newMesh;
	return true;
}

bool TriangleToQuadConverter::TriangleMerging(const Mesh & triangleMesh, Mesh & quadMesh)
{
	// Check if the input mesh is a triangle mesh
	if (!checkIfTriangleMesh(triangleMesh)) return false;
	quadMesh.clear();

	auto triangles = triangleMesh.faces();
	std::vector<f_index> triangles_vector(triangles.begin(), triangles.end());

	while (triangles_vector.size()>0) {
		f_index face = triangles_vector.back();
		triangles_vector.pop_back();
		h_index h_e;
		f_index other_face = getNextTriangle(triangleMesh, face, triangles_vector, h_e);
		if (face == other_face) {
			// If the face has no other triangle to merge with, add it to the new mesh as a triangle

			// Get three vertices of the triangle
			Point v0, v1, v2;
			getVerticesFromFace(triangleMesh, face, v0, v1, v2);
			quadMesh.add_face(quadMesh.add_vertex(v0), quadMesh.add_vertex(v1), quadMesh.add_vertex(v2));

			continue;
		}
		// Erase other_face from vector
		triangles_vector.erase(std::find(triangles_vector.begin(), triangles_vector.end(), other_face));
		// If the face has another triangle to merge with, merge them into a quad
		mergeTriangle(triangleMesh, h_e, quadMesh);
	}
	return true;
}

bool TriangleToQuadConverter::checkIfTriangle(const Mesh& mesh, const f_index& face)
{
	return mesh.degree(face) == 3;
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

	// Compute the centroid of the vertices
	Point c = CGAL::centroid(v0, v1, v2);

	Point mid_v0v1 = CGAL::midpoint(v0, v1), mid_v1v2 = CGAL::midpoint(v1, v2), mid_v2v0 = CGAL::midpoint(v2, v0);


	// Create vertices and faces in new mesh
	v_index c_index = newMesh.add_vertex(c), v0_index = newMesh.add_vertex(v0), v1_index = newMesh.add_vertex(v1), v2_index = newMesh.add_vertex(v2);
	v_index mid_v0v1_index = newMesh.add_vertex(mid_v0v1), mid_v1v2_index = newMesh.add_vertex(mid_v1v2), mid_v2v0_index = newMesh.add_vertex(mid_v2v0);

	newMesh.add_face(v0_index, mid_v0v1_index,c_index, mid_v2v0_index);
	newMesh.add_face(mid_v0v1_index, v1_index, mid_v1v2_index, c_index);
	newMesh.add_face(mid_v2v0_index, c_index, mid_v1v2_index, v2_index);
}

void TriangleToQuadConverter::mergeTriangle(const Mesh& oldMesh, h_index h_e, Mesh& newMesh)
{
	// get the 4 vertices of the quad
	v_index v0 = oldMesh.target(h_e);
	v_index v1 = oldMesh.target(oldMesh.next(h_e));
	v_index v2 = oldMesh.source(h_e);
	v_index v3 = oldMesh.target(oldMesh.next(oldMesh.opposite(h_e)));

	//add the 4 vertices to the new mesh
	v_index v0_index = newMesh.add_vertex(oldMesh.point(v0));
	v_index v1_index = newMesh.add_vertex(oldMesh.point(v1));
	v_index v2_index = newMesh.add_vertex(oldMesh.point(v2));
	v_index v3_index = newMesh.add_vertex(oldMesh.point(v3));

	//add the face to the new mesh
	newMesh.add_face(v0_index, v1_index, v2_index, v3_index);
}

f_index TriangleToQuadConverter::getNextTriangle(const Mesh& mesh, const f_index& face, std::vector<f_index>& triangles_vector, h_index& h_e)
{
	auto halfedge = mesh.halfedge(face);
	auto h_edge = halfedge;
	do {
		f_index pos_triangle = mesh.face(mesh.opposite(h_edge));
		if (std::find(triangles_vector.begin(), triangles_vector.end(), pos_triangle) != triangles_vector.end())
		{
			h_e = h_edge;
			return pos_triangle;
		}
		h_edge = mesh.next(h_edge);
	} while (h_edge != halfedge);
	return face;
}

