#ifndef FACE_H
#define FACE_H

namespace Meshlib
{
	class HalfEdge;

	class Face
	{
	public:
		Face();
		~Face();
		int m_face_id;
		 HalfEdge *m_halfedge;

	private:

	};

	Face::Face()
	{
	}

	Face::~Face()
	{
	}
}
#endif // !FACE_H

