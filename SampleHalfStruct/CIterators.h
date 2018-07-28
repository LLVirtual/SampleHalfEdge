
#ifndef _ITERATORS_H
#define _ITERATORS_H

#include "CMyMesh.h"
namespace Meshlib
{
	class MeshVertexIterator
	{
	public:
		MeshVertexIterator(MyMesh *pMesh)
		{
			m_pMesh = pMesh;
			m_iter = m_pMesh->vertices().begin();
		}
		Vertex *value()
		{
			return *m_iter;
		}

		Vertex *operator*() { return value(); }
		///<summary>
		///怎么重写加加
		///</summary>
		void operator++() { ++m_iter; }

		void operator++(int) { ++m_iter; }

		bool end() { return m_iter == m_pMesh->vertices().end(); }

	private:
		MyMesh *m_pMesh;
		typename std::list<Vertex*>::iterator m_iter;

	};
}

#endif // !_ITERATORS_H
