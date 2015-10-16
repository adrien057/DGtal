/**
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

/**
 * @file testConvexHull2D-catch.cpp
 * @ingroup Tests
 * @author Bertrand Kerautret (\c kerautre@loria.fr )
 * LORIA (CNRS, UMR 7503), University of Nancy, France
 *
 * @date 2015/10/16
 *
 * Functions for testing class ConvexHull2D-catch.
 *
 * This file is part of the DGtal library.
 */

///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include "DGtal/base/Common.h"
#include "ConfigTest.h"
#include "DGtalCatch.h"
#include "DGtal/helpers/StdDefs.h"
#include "DGtal/geometry/tools/Hull2DHelpers.h"
#include "DGtal/geometry/tools/determinant/InHalfPlaneBySimple3x3Matrix.h"


///////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace DGtal;

///////////////////////////////////////////////////////////////////////////////
// Functions for testing class ConvexHull2D-catch.
///////////////////////////////////////////////////////////////////////////////

TEST_CASE( "Testing Rotating Caliper of ConvexHull2D (basic convex hull)" )
{
  typedef PointVector<2,DGtal::int32_t> Point;
  typedef InHalfPlaneBySimple3x3Matrix<Point, DGtal::int64_t> Functor;  
   DGtal::MelkmanConvexHull<Point, Functor> ch; 
   ch.add(Point(0,0));
   ch.add(Point(1,0));
   ch.add(Point(1,1));

   Point pHV,qHV,sHV, pE,qE,sE;
   double thicknessHV = 
     DGtal::functions::Hull2D::computeHullThickness(ch.begin(), ch.end(), 
                                                    DGtal::functions::Hull2D::HorizontalVerticalThickness,
                                                    pHV, qHV, sHV);
   
   double thicknessEucl = 
     DGtal::functions::Hull2D::computeHullThickness(ch.begin(), ch.end(), 
                                                    DGtal::functions::Hull2D::EuclideanThickness,
                                                    pE, qE, sE);
   
   SECTION("Testing computation of horizontal/vertical thickness of ConvexHull2D")
     {
       REQUIRE( (thicknessHV == 1.0) );
       REQUIRE(  (pHV == Point(0,0)) && (qHV==Point(1,0)) && sHV==Point(1,1) );
     }
   

   SECTION("Testing computation of euclidean thickness of ConvexHull2D")
     {
       REQUIRE( (floor(thicknessEucl/0.0000001)*0.0000001 == floor((std::sqrt(2.0)/2.0)/0.0000001)*0.0000001) );
       REQUIRE( (pE == Point(1,1)) && (qE==Point(0,0)) && (sE==Point(1,0)) );
     }
   
}


TEST_CASE( "Testing Rotating Caliper of ConvexHull2D (convex hull with floating coordinates)" )
{
  typedef PointVector<2, double_t> Point;
  typedef InHalfPlaneBySimple3x3Matrix<Point, double> Functor;  
  DGtal::MelkmanConvexHull<Point, Functor> ch; 
  
  ch.add(Point(104.0, 54.2));
  ch.add(Point(104.2, 53.2));
  ch.add(Point(103.2, 53.4));
  ch.add(Point(103.3, 52.3));
  ch.add(Point(102.3, 52.3));
  ch.add(Point(102.2, 51.0));
  ch.add(Point(102.2, 50.2));
  ch.add(Point(101.0, 50.0));
  ch.add(Point(101.0, 49.1));
  ch.add(Point(101.2, 48.2));
  ch.add(Point(100.0, 48.2));
  ch.add(Point(100.4, 47.4));
  
  Point pHV,qHV,sHV, pE,qE,sE;

  double thicknessHV = 
    DGtal::functions::Hull2D::computeHullThickness(ch.begin(), ch.end(), 
                                                   DGtal::functions::Hull2D::HorizontalVerticalThickness,
                                                   pHV, qHV, sHV);
  double thicknessEucl = 
    DGtal::functions::Hull2D::computeHullThickness(ch.begin(), ch.end(), 
                                                   DGtal::functions::Hull2D::EuclideanThickness,
                                                   pE, qE, sE);
  
   SECTION("Testing antipodal points of ConvexHull2D")
     {
       REQUIRE(  (pHV == Point(101.2, 48.2)) && (qHV==Point(104.2, 53.2)) && sHV==Point(102.3, 52.3) );
     }
   SECTION("Testing antipodal points of ConvexHull2D")
     {
       REQUIRE(  (pE == Point(101.2, 48.2)) && (qE==Point(104.2, 53.2)) && sE==Point(102.3, 52.3) );
     }
}

/** @ingroup Tests **/
