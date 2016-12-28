/*
 * VoronoiNet.h
 *
 *  Created on: Apr 26, 2015
 *      Author: Stefan Jakob
 */

#ifndef CNC_MSL_MSL_WORLDMODEL_SRC_PATHPLANNER_VORONOINET_H_
#define CNC_MSL_MSL_WORLDMODEL_SRC_PATHPLANNER_VORONOINET_H_

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <CGAL/Voronoi_diagram_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_traits_2.h>
#include <CGAL/Delaunay_triangulation_adaptation_policies_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Delaunay_triangulation_2<Kernel> DelaunayTriangulation;
typedef CGAL::Delaunay_triangulation_adaptation_traits_2<DelaunayTriangulation> DelaunayAdaptionTraits;
typedef CGAL::Delaunay_triangulation_caching_degeneracy_removal_policy_2<DelaunayTriangulation> DelaunayAdaptionPolicy;
typedef CGAL::Voronoi_diagram_2<DelaunayTriangulation, DelaunayAdaptionTraits, DelaunayAdaptionPolicy> VoronoiDiagram;
typedef DelaunayAdaptionTraits::Point_2 Point_2;
typedef DelaunayAdaptionTraits::Site_2 Site_2;
typedef VoronoiDiagram::Vertex Vertex;

#include <vector>
#include <sstream>
#include <iostream>

#include "container/CNPoint2D.h"
#include "container/CNRobot.h"
#include "pathplanner/SearchNode.h"
#include "pathplanner/evaluator/IPathEvaluator.h"
#include "MSLFootballField.h"
#include "MSLEnums.h"

namespace supplementary {
    class SystemConfig;
}

using namespace std;

namespace msl
{

    /**
     * Class containing a CGAL voronoi diagramm and its status
     */
    class PathEvaluator;
    class MSLWorldModel;
    class VoronoiNet
    {
    public:
        VoronoiNet(MSLWorldModel* wm);
        VoronoiNet(shared_ptr<VoronoiNet> net);
        virtual ~VoronoiNet();
        bool ownPosAvail;
        /**
         * generates a VoronoiDiagram and inserts given points
         * @param points vector<shared_ptr<geometry::CNPoint2D>>
         * @return shared_ptr<VoronoiDiagram>
         */
        void generateVoronoiDiagram(bool ownPosAvail);
        /**
         * gets the SearchNode with lowest dist to goal
         * @param open shared_ptr<vector<shared_ptr<SearchNode>>>
         * @return shared_ptr<SearchNode>
         */
//      shared_ptr<SearchNode> getMin(shared_ptr<vector<shared_ptr<SearchNode>>> open);
        /**
         * gets the closest vertex to a given point
         * @param ownPos shared_ptr<geometry::CNPoint2D>
         * @return shared_ptr<VoronoiDiagram::Vertex>
         */
//      shared_ptr<VoronoiDiagram::Vertex> findClosestVertexToOwnPos(shared_ptr<geometry::CNPoint2D> ownPos);

        /**
         * return the sites near an egde defined by 2 points
         * @param v1 shared_ptr<geometry::CNPoint2D>
         * @param v2 shared_ptr<geometry::CNPoint2D>
         * @return pair<pair<shared_ptr<geometry::CNPoint2D>, int>, pair<shared_ptr<geometry::CNPoint2D>, int>>
         */
        //pair<pair<shared_ptr<geometry::CNPoint2D>, int>, pair<shared_ptr<geometry::CNPoint2D>, int>> getSitesNextToHalfEdge(shared_ptr<Vertex> v1, shared_ptr<Vertex> v2);
        /**
         * print the voronoi diagrams sites
         */
        void printSites();
        /**
         * print the voronoi diagrams vertices
         */
        void printVertices();
        /**
         * to string
         */
        string toString();

        /**
         * locates face of point and returns vertices
         * @param point shared_ptr<geometry::CNPoint2D>
         * @return shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>>
         */
        shared_ptr<vector<shared_ptr<Vertex>>> getVerticesOfFace(shared_ptr<geometry::CNPoint2D> point);

        /**
         * inserts sites into the VoronoiDiagram
         * @param points vector<Site_2>
         */
        void insertPoints(vector<Site_2> points);

        /**
         * insert additional points into the voronoi diagram
         * @param points shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>>
         */
        void insertAdditionalPoints(shared_ptr<vector<shared_ptr<geometry::CNPoint2D> > > points, EntityType type);

        /**
         * deletes sites from voronoi net and clears pointRobotKindMapping
         */
        void clearVoronoiNet();

        /**
         * gets the voronoi net
         */
        shared_ptr<VoronoiDiagram> getVoronoi();
        /**
         * sets the voronoi net
         * @param voronoi shared_ptr<VoronoiDiagram>
         */
        void setVoronoi(shared_ptr<VoronoiDiagram> voronoi);
        /**
         * find the face in which the point is situated
         * @param point VoronoiDiagram::Point_2
         * @return shared_ptr<VoronoiDiagram::Site_2>
         */
        shared_ptr<VoronoiDiagram::Site_2> getSiteOfFace(VoronoiDiagram::Point_2 point);

        /**
         * check if an edge belongs to face of given point
         * @param pos shared_ptr<geometry::CNPoint2D>
         * @param currentNode shared_ptr<SearchNode>
         * @param nextNode shared_ptr<SearchNode>
         * @return bool
         */
//      bool isOwnCellEdge(shared_ptr<geometry::CNPoint2D> pos, shared_ptr<SearchNode> currentNode, shared_ptr<SearchNode> nextNode);

        /**
         * return the teammate positions
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int> > >
         */
        //shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int> > > getTeamMatePositions();

        /**
         * return the obstacle positions
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int> > >
         */
        shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> getObstaclePositions();

        /**
         * return the Opponent positions
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int> > >
         */
        shared_ptr<vector<shared_ptr<geometry::CNPoint2D> > > getOpponentPositions();

        /**
         * return the site positions
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int> > >
         */
//      shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int> > > getSitePositions();

        // DATA for constructing this voronoi net
        shared_ptr<vector<shared_ptr<geometry::CNRobot> > > getAlloClusteredObsWithMe();

        // DATA for constructing this voronoi net
        shared_ptr<vector<shared_ptr<geometry::CNPoint2D> > > getArtificialObstacles();

        shared_ptr<vector<shared_ptr<geometry::CNPoint2D> > > getAdditionalObstacles();

        /**
         * return vertices teammates voronoi face
         * @param teamMateId int
         * @return shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>>
         */
//      shared_ptr<vector<shared_ptr<Vertex>>> getTeamMateVertices(int teamMateId);

        shared_ptr<vector<shared_ptr<geometry::CNPoint2D> > > getTeamMateVerticesCNPoint2D(int teamMateId);
        /**
         * removes given sites from voronoi net
         * @param sites shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>>
         */
        void removeSites(shared_ptr<vector<shared_ptr<geometry::CNPoint2D>>> sites);

        /**
         * removes given sites from voronoi net
         * @param sites shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int>>>
         */
        void removeSites(shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int>>> sites);

        /**
         * bolck opponent penalty area
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int>>>
         */
        void blockOppPenaltyArea();

        /**
         * bolck opponent goal area
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int>>>
         */
        void blockOppGoalArea();

        /**
         * bolck own penalty area
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int>>>
         */
        void blockOwnPenaltyArea();

        /**
         * bolck own goal area
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int>>>
         */
        void  blockOwnGoalArea();

        /**
         * bolck 3 meters around the ball
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int>>>
         */
        void blockThreeMeterAroundBall();

        /**
         * bolck circle shaped area
         * @param centerPoint shared_ptr<geometry::CNPoint2D>
         * @param radious double
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int>>>
         */
        void blockCircle(shared_ptr<geometry::CNPoint2D> centerPoint, double radius);

        /**
         * bolck opponent penalty area
         * @param upLeftCorner shared_ptr<geometry::CNPoint2D>
         * @param lowRightCorner shared_ptr<geometry::CNPoint2D>
         * @return shared_ptr<vector<pair<shared_ptr<geometry::CNPoint2D>, int>>>
         */
        void blockRectangle(shared_ptr<geometry::CNPoint2D> upLeftCorner, shared_ptr<geometry::CNPoint2D> lowRightCorner);

        int getTypeOfSite(Site_2 site);

    private:
        /**
         * checks if a SearchNode is part of a vector
         * @param vector shared_ptr<vector<shared_ptr<SearchNode>>>
         * @param vertex shared_ptr<SearchNode>
         * @return bool
         */
        bool contains(shared_ptr<vector<shared_ptr<SearchNode>>> vector, shared_ptr<SearchNode> vertex);


    protected:
        Kernel kernel;
        DelaunayTriangulation delaunayTriangulation;
        DelaunayAdaptionTraits delaunayTraits;
        DelaunayAdaptionPolicy delaunayPolicy;
        shared_ptr<VoronoiDiagram> voronoi;
        MSLWorldModel* wm;
        supplementary::SystemConfig* sc;
        mutex netMutex;
        /**
         * team = robot id, obstacle = -1, artificial obstacle = -2
         */
        //map<shared_ptr<geometry::CNPoint2D>, int> pointRobotKindMapping;
        map<Site_2, int> pointRobotKindMapping;

        // DATA for constructing this voronoi net
        shared_ptr<vector<shared_ptr<geometry::CNRobot> > > alloClusteredObsWithMe;
                shared_ptr<vector<shared_ptr<geometry::CNPoint2D> > > artificialObstacles;
                shared_ptr<vector<shared_ptr<geometry::CNPoint2D> > > additionalObstacles;
    };

} /* namespace msl */

#endif /* CNC_MSL_MSL_WORLDMODEL_SRC_PATHPLANNER_VORONOINET_H_ */
