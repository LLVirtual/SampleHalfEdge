#ifndef CVERTEX_H_INCLUDED
#define CVERTEX_H_INCLUDED

#include <stdlib.h>
#include "CPoint.h"
#include "CHalfEdge.h"
#include <list>

namespace Meshlib
{
	class HalfEdge;
	///<summary>
	///建立顶点的基类
	///</summary>
	class Vertex
	{
	public:
		Vertex() { m_halfedge = NULL; };
		~Vertex() {};
		int m_vertex_id;
		Point m_position;
		HalfEdge *m_halfedge;

		//因为是简易的所以暂时不用封装
		std::list<Edge*> m_edges;
	};

}

#endif
