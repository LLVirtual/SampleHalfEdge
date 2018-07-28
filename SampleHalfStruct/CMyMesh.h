#ifndef _CMYMESH_H
#define _CMYMESH_H

#define MAX_LINE 2048
#include "CVertex.h"
#include "CEdge.h"
#include "CFace.h"
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace Meshlib;

class MyMesh
{
public:
	MyMesh();
	~MyMesh();
	
	Vertex *idVertex(int id);
	void read_m(const char *input);
	void write_m();

	Vertex *createVertex(int id);

	Edge *createEdge(Vertex *v1,Vertex *v2);

	Face *createFace(std::vector<Vertex *> & v, int id);

	int numVertex();
	int numFaces();
	int numEdge();

	std::list<Edge*>    & edges() { return m_edges; };
	std::list<Face*>    & faces() { return m_faces; };
	std::list<Vertex*>  & vertices(){ return m_verts; };
private:
	std::list<Edge *> m_edges;
	std::list<Face *> m_faces;
	std::list<Vertex *>m_verts;

	std::map<int, Vertex*> m_map_verts;
	std::map<int, Face*> m_map_face;

	
};

MyMesh::MyMesh()
{
}

MyMesh::~MyMesh()
{
}

Vertex * MyMesh::idVertex(int id)
{
	return m_map_verts[id];
}
//返回类的指针和引用的区别到底有多少？
Vertex * MyMesh::createVertex(int id)
{
	Vertex *v = new Vertex();
	assert(v != NULL);
	v->m_vertex_id = id;
	m_verts.push_back(v);
	m_map_verts.insert(std::pair<int, Vertex*>(id, v));
	return v;
}
Edge *MyMesh::createEdge(Vertex *v1, Vertex *v2)
{
	//ok finsh 
	Vertex *pv = (v1->m_vertex_id < v2->m_vertex_id) ? v1 : v2;
	std::list<Edge*> &leges = pv->m_edges;//加入一层引用

	//判断是否已经存在这条边
	for (std::list<Edge*>::iterator te = leges.begin(); te != leges.end(); te++)
	{
		Edge *e = *te;
		HalfEdge *pH = (HalfEdge*)e->m_halfedges[0];//相当与更新半边信息
		if (pH->source() == v1&&pH->target() == v2)
		{
			return e;
		}

		if (pH->source() == v2&&pH->target() == v1)
		{
			return e;
		}
	}

	Edge *pe = new Edge();
	assert(pe != NULL);
	m_edges.push_back(pe);
	pe->m_edge_id = (int)m_edges.size();//从1开始
	leges.push_back(pe);
	return pe;
}
//此处需要使用引用的原因是什么呢
Face * MyMesh::createFace(std::vector<Vertex *> & v, int id)
{
	Face *f = new Face();
	assert(f != NULL);
	m_faces.push_back(f);
	f->m_face_id = id;
	m_map_face.insert(std::pair<int, Face*>(id, f));

	//建立半边结构
	//create halfedges;
	std::vector<HalfEdge*> hes;

	//3条半边
	for (size_t i = 0; i < v.size(); i++)
	{
		HalfEdge *pH = new HalfEdge();
		assert(pH);
		Vertex *pv = v[i];
		pH->m_vertex = pv;
		pv->m_halfedge = pH;
		hes.push_back(pH);
	}

	//数据link 起来了
	for (size_t i = 0; i < hes.size(); i++)
	{
		hes[i]->m_next_halfedge = hes[(i + 1) % hes.size()];
		hes[i]->m_prev_halfedge = hes[(i + hes.size() - 1) % hes.size()];
	}

	//linking to face
	for (size_t i = 0; i < hes.size(); i++)
	{
		hes[i]->m_face = f;
		f->m_halfedge = hes[i];
	}

	//
	//把边连接起来
	for (size_t i = 0; i < hes.size(); i++)
	{
		Edge *e = createEdge(v[i], v[(i + hes.size() - 1) % hes.size()]);
		if (e->m_halfedges[0] == NULL)
		{
			e->m_halfedges[0] = hes[i];
		}
		else
		{
			assert(e->m_halfedges[1] == NULL);
			if (e->m_halfedges[1] != NULL)
			{
				std::cout << "Illegal Face Construction " << id << std::endl;
			}
			e->m_halfedges[1] = hes[i];
		}
		hes[i]->m_edge = e;
	}
	return f;
}


void MyMesh::read_m(const char *input) {
	std::cout << "测试下有没有错误，么有的话开始进行编写\n";
	std::fstream is(input, std::fstream::in);

	if (is.fail())
	{
		fprintf(stderr, "Error in opening file %s\n", input);
		return;
	}
	char buffer[MAX_LINE];
	int id;
	int fid;
	std::string test;
	while (is.getline(buffer, MAX_LINE)) {

		std::string line(buffer);
		std::stringstream stringin(line);
		stringin >> test;
		if (test == "Vertex")
		{
			
			stringin >> test;
			id = atoi(test.c_str());

			stringin >> test;
			float x = atof(test.c_str());
			
			stringin >> test;
			float y = atof(test.c_str());

			stringin >> test;
			float z = atof(test.c_str());

			Point p;
			p.x = x;
			p.y = y;
			p.z = z;

			Vertex *pv = createVertex(id);
			pv->m_position = p;
			pv->m_vertex_id = id;
			
		}
		
		if (test == "Face")
		{
			
			stringin >> test;
			fid = atoi(test.c_str());

			std::vector<Vertex *> vlist;
			while (stringin >> test)
			{
				int vid = atoi(test.c_str());
				vlist.push_back(idVertex(vid));
			}
			
			Face * f = createFace(vlist,fid);

			std::cout << f->m_face_id << "\n";;
			continue;
		}
	}

}

inline int MyMesh::numVertex()
{
	return m_verts.size();
}

inline int MyMesh::numFaces()
{
	return m_faces.size();
}

inline int MyMesh::numEdge()
{
	return m_edges.size();
}
#endif // !_CMYMESH_H
