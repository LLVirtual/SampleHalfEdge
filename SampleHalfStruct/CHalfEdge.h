#ifndef HAFLEDGE_H
#define HAFLEDGE_H



namespace Meshlib
{
	//类之间的相互调用 但是这样的数据结构耦合度真的号码
	class Vertex;
	class Edge;
	class Face;

	class HalfEdge
	{
	public:
		HalfEdge();
		~HalfEdge();
		
		Vertex *m_vertex;

		Vertex *m_source_vertex;
		Vertex *m_target_vertex;
		
	
		Edge *m_edge;

		HalfEdge *m_next_halfedge;
		HalfEdge *m_prev_halfedge;
		HalfEdge *m_symm_halfedge;

		Face *m_face;
	public:

		Vertex * & target() {
			return m_vertex;
		}

		Vertex * & source() {
			return m_prev_halfedge->m_vertex;
		}
	private:

	};

	HalfEdge::HalfEdge()
	{
		m_edge = NULL; m_vertex = NULL; m_prev_halfedge = NULL; m_next_halfedge = NULL; m_face = NULL; m_symm_halfedge = NULL;
	}

	HalfEdge::~HalfEdge()
	{
	}
}
#endif // !HAFLEDGE_H

