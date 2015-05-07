/*
 * VoronoiNet.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: Stefan Jakob
 */

#include "pathplanner/VoronoiNet.h"

namespace msl
{

	VoronoiNet::VoronoiNet(MSLWorldModel* wm)
	{
		this->wm = wm;
		sc = supplementary::SystemConfig::getInstance();
		status = VoronoiStatus::New;
		this->voronoi = make_shared<VoronoiDiagram>();

	}

	VoronoiNet::~VoronoiNet()
	{
	}

	/**
	 * inserts sites into the VoronoiDiagram
	 * @param points vector<Site_2>
	 */
	void VoronoiNet::insertPoints(vector<Site_2> points)
	{
		this->voronoi->insert(points.begin(), points.end());
	}

	/**
	 * gets the closest Vertex to a given position
	 * @param pos position
	 */
	shared_ptr<VoronoiDiagram::Vertex> VoronoiNet::findClosestVertexToOwnPos(Point_2 pos)
	{
		shared_ptr<VoronoiDiagram::Vertex> ret = nullptr;
		VoronoiDiagram::Vertex_iterator iter = voronoi->vertices_begin();
		int minDist = std::numeric_limits<int>::max();
		while (iter != voronoi->vertices_end())
		{
			if (ret == nullptr)
			{
				ret = make_shared<VoronoiDiagram::Vertex>(*iter);
				iter++;
			}
			else
			{
				int dist = calcDist(pos, iter->point());
				if (dist < minDist)
				{
					ret = make_shared<VoronoiDiagram::Vertex>(*iter);
					minDist = dist;
					iter++;
				}
			}
		}
		return ret;
	}

	/**
	 * calculates distance between two points
	 * @param ownPos Point_2
	 * @param vertexPoint Point_2
	 */
	int VoronoiNet::calcDist(Point_2 ownPos, Point_2 vertexPoint)
	{
		int ret = sqrt(pow((vertexPoint.x() - ownPos.x()), 2) + pow((vertexPoint.y() - ownPos.y()), 2));
		return ret;
	}

	/**
	 * gets SearchNode with minimal distance to goal
	 * @param open shared_ptr<vector<shared_ptr<SearchNode> > > vector with minimal searchnode
	 */
	shared_ptr<SearchNode> VoronoiNet::getMin(shared_ptr<vector<shared_ptr<SearchNode> > > open)
	{
		if (open->size() > 0)
		{
			sort(open->begin(), open->end(), SearchNode::compare);
			return open->at(0);
		}
		else
		{
			return nullptr;
		}

	}

	/**
	 * gets Vertices connected to SeachNode vertex
	 * @param currentNode shared_ptr<SearchNode>
	 * @return vector<shared_ptr<SearchNode>>
	 */
	vector<shared_ptr<SearchNode>> VoronoiNet::getNeighboredVertices(shared_ptr<SearchNode> currentNode)
	{
		vector<VoronoiDiagram::Vertex> neighbors;
		for (VoronoiDiagram::Edge_iterator it = this->voronoi->edges_begin(); it != this->voronoi->edges_end(); it++)
		{
			if (it->source()->point().x() == currentNode->getVertex()->point().x()
					&& it->source()->point().y() == currentNode->getVertex()->point().y())
			{
				if (find(neighbors.begin(), neighbors.end(), *it->target()) == neighbors.end())
				{
					neighbors.push_back(*it->target());
				}
			}
		}
		vector<shared_ptr<SearchNode>> ret;
		for (int i = 0; i < neighbors.size(); i++)
		{
			ret.push_back(
					make_shared<SearchNode>(
							SearchNode(make_shared<VoronoiDiagram::Vertex>(neighbors.at(i)), 0, nullptr)));
		}
		return ret;
	}

	/**
	 * expands Nodes given in current node
	 * @param currentNode shared_ptr<SearchNode>
	 */
	void VoronoiNet::expandNode(shared_ptr<SearchNode> currentNode, shared_ptr<vector<shared_ptr<SearchNode>>> open,
	shared_ptr<vector<shared_ptr<SearchNode>>> closed, Point_2 goal)
	{
		// get neighbored nodes
		vector<shared_ptr<SearchNode>> neighbors = getNeighboredVertices(currentNode);
		for(int i = 0; i < neighbors.size(); i++)
		{
			// if node is already closed skip it
			if(contains(closed, neighbors.at(i)))
			{
				continue;
			}
			//calculate cost with current cost and way to next vertex
			double cost = currentNode->getCost() + calcDist(currentNode->getVertex()->point(), neighbors.at(i)->getVertex()->point());
			// if node has still to be expaned but there is a cheaper way skip it
			if(contains(open, neighbors.at(i)) && cost >= neighbors.at(i)->getCost())
			{
				continue;
			}
			//set predecessor and cost
			neighbors.at(i)->setPredecessor(currentNode);
			neighbors.at(i)->setCost(cost);
			// add heuristic cost
			cost += calcDist(neighbors.at(i)->getVertex()->point(), goal);
			//if node is already in open change cost else add node
			if(contains(open, neighbors.at(i)))
			{
				for(int j = 0; j < open->size(); j++)
				{
					if(open->at(i)->getVertex()->point().x() == neighbors.at(i)->getVertex()->point().x()
					&& open->at(i)->getVertex()->point().y() == neighbors.at(i)->getVertex()->point().y())
					{
						open->at(j)->setCost(cost);
					}
				}
			}
			else
			{
				neighbors.at(i)->setCost(cost);
				open->push_back(neighbors.at(i));
			}
		}
	}

	/**
	 * expands Nodes given in current node
	 * @param currentNode shared_ptr<SearchNode>
	 */
	void VoronoiNet::expandNodeCarefully(shared_ptr<SearchNode> currentNode, shared_ptr<vector<shared_ptr<SearchNode>>> open,
	shared_ptr<vector<shared_ptr<SearchNode>>> closed, Point_2 goal, double robotDiameter, bool haveBall)
	{
		// get neighbored nodes
		vector<shared_ptr<SearchNode>> neighbors = getNeighboredVertices(currentNode);
		for(int i = 0; i < neighbors.size(); i++)
		{
			// if node is already closed skip it
			if(contains(closed, neighbors.at(i)))
			{
				continue;
			}
			//calculate cost with current cost and way to next vertex
			double cost = currentNode->getCost() + calcDist(currentNode->getVertex()->point(), neighbors.at(i)->getVertex()->point());
			// if node has still to be expaned but there is a cheaper way skip it
			if(contains(open, neighbors.at(i)) && cost >= neighbors.at(i)->getCost())
			{
				continue;
			}
			//set predecessor and cost
			neighbors.at(i)->setPredecessor(currentNode);
			neighbors.at(i)->setCost(cost);
			// only if we have more than one way we could go
			if(neighbors.size() > 1)
			{
				//TODO needs to be tested on robots
				pair<shared_ptr<Point_2>, shared_ptr<Point_2>> sites = getSitesNextToHalfEdge(currentNode->getVertex(), neighbors.at(i)->getVertex());
				if(calcDist(*sites.first, *sites.second) < robotDiameter)
				{
					cost += calcDist(neighbors.at(i)->getVertex()->point(), goal);
				}
				if(calcDist(*sites.first, *sites.second) < robotDiameter && haveBall)
				{
					cost += calcDist(neighbors.at(i)->getVertex()->point(), goal);
				}
			}
			// add heuristic cost
			cost += calcDist(neighbors.at(i)->getVertex()->point(), goal);
			//if node is already in open change cost else add node
			if(contains(open, neighbors.at(i)))
			{
				for(int j = 0; j < open->size(); j++)
				{
					if(open->at(i)->getVertex()->point().x() == neighbors.at(i)->getVertex()->point().x()
					&& open->at(i)->getVertex()->point().y() == neighbors.at(i)->getVertex()->point().y())
					{
						open->at(j)->setCost(cost);
					}
				}
			}
			else
			{
				neighbors.at(i)->setCost(cost);
				open->push_back(neighbors.at(i));
			}
		}
	}

	/**
	 * generates a VoronoiDiagram and inserts given points
	 * @param points vector<CNPoint2D>
	 * @return shared_ptr<VoronoiDiagram>
	 */
	shared_ptr<VoronoiDiagram> VoronoiNet::generateVoronoiDiagram(vector<CNPoint2D> points)
	{
		lock_guard<mutex> lock(netMutex);
		this->status = VoronoiStatus::Calculating;
		vector<Site_2> sites;
		for (int i = 0; i < points.size(); i++)
		{
			Site_2 site = Site_2(points.at(i).x, points.at(i).y);
			sites.push_back(site);
		}
		insertPoints(sites);
		return this->voronoi;
	}

	void msl::VoronoiNet::printSites()
	{
		cout << "Voronoi Diagram Sites: " << endl;
		for(VoronoiDiagram::Face_iterator it = this->voronoi->faces_begin(); it != this->voronoi->faces_end(); it++ )
		{
			cout << it->dual()->point() << endl;
		}
	}

	void msl::VoronoiNet::printVertices()
	{
		cout << "Voronoi Diagram Vertices: " << endl;
		for(VoronoiDiagram::Vertex_iterator it = this->voronoi->vertices_begin(); it != this->voronoi->vertices_end(); it++)
		{
			cout <<  it->point() << endl;
		}
	}

	string msl::VoronoiNet::toString()
	{
		stringstream ss;
		ss << "Voronoi Diagram Vertices: " << endl;
		for(VoronoiDiagram::Vertex_iterator it = this->voronoi->vertices_begin(); it != this->voronoi->vertices_end(); it++)
		{
			ss <<  it->point() << endl;
		}
		ss << "Voronoi Diagram Sites: " << endl;
		for(VoronoiDiagram::Face_iterator it = this->voronoi->faces_begin(); it != this->voronoi->faces_end(); it++ )
		{
			ss << it->dual()->point() << endl;
		}
		return ss.str();
	}

	/**
	 * checks if a SearchNode is part of a vector
	 * @param vector shared_ptr<vector<shared_ptr<SearchNode> > >
	 * @param vertex shared_ptr<SearchNode>
	 * @return bool
	 */
	bool VoronoiNet::contains(shared_ptr<vector<shared_ptr<SearchNode> > > vector, shared_ptr<SearchNode> vertex)
	{
		for (int i = 0; i < vector->size(); i++)
		{
			if (vector->at(i)->getVertex()->point().x() == vertex->getVertex()->point().x()
					&& vector->at(i)->getVertex()->point().y() == vertex->getVertex()->point().y())
			{
				return true;
			}
		}
		return false;
	}

	/**
	 * gets the status of the VoronoiDiagram
	 * @return VoronoiStatus
	 */
	VoronoiStatus VoronoiNet::getStatus()
	{
		return status;
	}

	/**
	 * sets the status of the VoronoiDiagram
	 * @param status VoronoiStatus
	 */
	void VoronoiNet::setStatus(VoronoiStatus status)
	{
		this->status = status;
	}

	/**
	 * return the sites near an egde defined by 2 points
	 * @param v1 VoronoiDiagram::Vertex
	 * @param v2 VoronoiDiagram::Vertex
	 * @returnpair<shared_ptr<Point_2>, shared_ptr<Point_2>>
	 */
	pair<shared_ptr<Point_2>, shared_ptr<Point_2>> VoronoiNet::getSitesNextToHalfEdge(shared_ptr<VoronoiDiagram::Vertex> v1,
																					  shared_ptr<VoronoiDiagram::Vertex> v2)
	{
		pair<shared_ptr<Site_2>, shared_ptr<Site_2>> ret;
		ret.first = nullptr;
		ret.second = nullptr;
		for (VoronoiDiagram::Face_iterator fit = this->voronoi->faces_begin(); fit != this->voronoi->faces_end(); ++fit)
		{
			bool foundFirst = false;
			bool foundSecond = false;
			VoronoiDiagram::Halfedge_handle begin = fit->halfedge()->opposite();
			VoronoiDiagram::Halfedge_handle edge = begin;
			do {
			    if(edge->source()->point().x() == v1->point().x() &&
			    		edge->source()->point().y() == v1->point().y())
			    {
			    	foundFirst = true;
			    }
			    if(edge->source()->point().x() == v2->point().x() &&
			    		edge->source()->point().y() == v2->point().y())
			    {
			    	foundSecond = true;
			    }
			    edge = edge->previous();
			} while (edge != begin);
			if(ret.first == nullptr)
			{
				ret.first = make_shared<Point_2>(fit->dual()->point());
				continue;
			}
			if(ret.second == nullptr && ret.first->x() != fit->dual()->point().x()
					&& ret.first->y() != fit->dual()->point().y())
			{
				ret.second = make_shared<Point_2>(fit->dual()->point());
				break;
			}
		}
		return ret;
	}

} /* namespace msl */
