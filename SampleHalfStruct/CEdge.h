#ifndef EDGE_h
#define EDGE_H

namespace Meshlib {
	//为什么要这样写呢？ 之前写是不正确的
	class HalfEdge;
		
	class Edge
	{
	public:
		Edge();
		~Edge();
		int m_edge_id;

		HalfEdge *m_halfedges[2];
	private:

	};

	Edge::Edge()
	{
		m_halfedges[0] = NULL; m_halfedges[1] = NULL;
	}

	Edge::~Edge()
	{
	}

}
#endif // !EDGE_h

