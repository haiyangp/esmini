#include <iostream>
#include <gtest/gtest.h>
#include "RoadManager.hpp"
#include <vector>
#include <stdexcept>

using namespace roadmanager;


////////// TESTS FOR CLASS -> Polynomial //////////

class PolynomialTestFixture: public testing::Test
{
    public:
        PolynomialTestFixture();
        PolynomialTestFixture(double a, double b, double c, double d, double p_scale);
        virtual ~PolynomialTestFixture();
    protected:
        Polynomial poly;
};


PolynomialTestFixture::PolynomialTestFixture()
{
}

PolynomialTestFixture::PolynomialTestFixture(double a, double b, double c, double d, double p_scale)
{
}

PolynomialTestFixture::~PolynomialTestFixture()
{
}

TEST_F(PolynomialTestFixture, TestConstructorEmpty)
{
    ASSERT_EQ(0, poly.GetA());
    ASSERT_EQ(0, poly.GetB());
    ASSERT_EQ(0, poly.GetC());
    ASSERT_EQ(0, poly.GetD());
    ASSERT_EQ(1, poly.GetPscale());
}

TEST_F(PolynomialTestFixture, TestConstructorArgument)
{
    Polynomial poly = Polynomial(1,-2,3,-4);
    ASSERT_EQ(1, poly.GetA());
    ASSERT_EQ(-2, poly.GetB());
    ASSERT_EQ(3, poly.GetC());
    ASSERT_EQ(-4, poly.GetD());
    ASSERT_EQ(1, poly.GetPscale());
}

TEST_F(PolynomialTestFixture, TestConstructorArgumentPscale)
{
    Polynomial poly = Polynomial(1,-2,3,-4,2);
    ASSERT_EQ(1, poly.GetA());
    ASSERT_EQ(-2, poly.GetB());
    ASSERT_EQ(3, poly.GetC());
    ASSERT_EQ(-4, poly.GetD());
    ASSERT_EQ(2, poly.GetPscale());
}

TEST_F(PolynomialTestFixture, TestSetGet)
{
    poly.Set(1,-2,3,-4);
    ASSERT_EQ(1, poly.GetA());
    ASSERT_EQ(-2, poly.GetB());
    ASSERT_EQ(3, poly.GetC());
    ASSERT_EQ(-4, poly.GetD());
    ASSERT_EQ(1, poly.GetPscale());
}

TEST_F(PolynomialTestFixture, TestSetGetPscale)
{
    poly.Set(1,-2,3,-4, 2);
    ASSERT_EQ(1, poly.GetA());
    ASSERT_EQ(-2, poly.GetB());
    ASSERT_EQ(3, poly.GetC());
    ASSERT_EQ(-4, poly.GetD());
    ASSERT_EQ(2, poly.GetPscale());
}

TEST_F(PolynomialTestFixture, TestSetGetIndividual)
{
    poly.SetA(1);
    poly.SetB(-2);
    poly.SetC(3);
    poly.SetD(-4);
    ASSERT_EQ(1, poly.GetA());
    ASSERT_EQ(-2, poly.GetB());
    ASSERT_EQ(3, poly.GetC());
    ASSERT_EQ(-4, poly.GetD());
}

class PolynomialTestEvaluateEmptyParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_empty;
};

TEST_P(PolynomialTestEvaluateEmptyParametrized, TestEvaluateEmptyConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    poly_empty.SetA(1);
    poly_empty.SetB(-2);
    poly_empty.SetC(3);
    poly_empty.SetD(-4);
    ASSERT_EQ(poly_empty.Evaluate(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateParamEmpty, PolynomialTestEvaluateEmptyParametrized, testing::Values(
                                                std::make_tuple(2,-23),
                                                std::make_tuple(0, 1)));

class PolynomialTestEvaluateArgumentParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_argument{1,-2,3,-4,2};
};

TEST_P(PolynomialTestEvaluateArgumentParametrized, TestEvaluateArgumentConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    ASSERT_EQ(poly_argument.Evaluate(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluateParamArgument, PolynomialTestEvaluateArgumentParametrized, testing::Values(
                                                std::make_tuple(2,-215),
                                                std::make_tuple(0, 1)));


class PolynomialTestEvaluatePrimEmptyParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_empty;
};

TEST_P(PolynomialTestEvaluatePrimEmptyParametrized, TestEvaluatePrimEmptyConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    poly_empty.SetA(1);
    poly_empty.SetB(-2);
    poly_empty.SetC(3);
    poly_empty.SetD(-4);
    ASSERT_EQ(poly_empty.EvaluatePrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimParamEmpty, PolynomialTestEvaluatePrimEmptyParametrized, testing::Values(
                                                std::make_tuple(2,-38),
                                                std::make_tuple(0, -2)));

class PolynomialTestEvaluatePrimArgumentParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_argument{1,-2,3,-4,2};
};

TEST_P(PolynomialTestEvaluatePrimArgumentParametrized, TestEvaluatePrimArgumentConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    ASSERT_EQ(poly_argument.EvaluatePrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimParamArgument, PolynomialTestEvaluatePrimArgumentParametrized, testing::Values(
                                                std::make_tuple(2,-170),
                                                std::make_tuple(0, -2)));

class PolynomialTestEvaluatePrimPrimEmptyParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_empty;
};

TEST_P(PolynomialTestEvaluatePrimPrimEmptyParametrized, TestEvaluatePrimPrimEmptyConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    poly_empty.SetA(1);
    poly_empty.SetB(-2);
    poly_empty.SetC(3);
    poly_empty.SetD(-4);
    ASSERT_EQ(poly_empty.EvaluatePrimPrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimPrimParamEmpty, PolynomialTestEvaluatePrimPrimEmptyParametrized, testing::Values(
                                                std::make_tuple(2,-42),
                                                std::make_tuple(0, 6)));

class PolynomialTestEvaluatePrimPrimArgumentParametrized: public testing::TestWithParam<std::tuple<double, double>>
{
    public:
    protected:
        Polynomial poly_argument{1,-2,3,-4,2};
};

TEST_P(PolynomialTestEvaluatePrimPrimArgumentParametrized, TestEvaluatePrimPrimArgumentConstructor)
{
    std::tuple<double, double> tuple = GetParam();
    ASSERT_GE(std::get<0>(tuple), 0);
    ASSERT_EQ(poly_argument.EvaluatePrimPrim(std::get<0>(tuple)), std::get<1>(tuple));
}

INSTANTIATE_TEST_CASE_P(TestEvaluatePrimPrimParamArgument, PolynomialTestEvaluatePrimPrimArgumentParametrized, testing::Values(
                                                std::make_tuple(2,-90),
                                                std::make_tuple(0, 6)));

//////////////////////////////////////////////////////////////////////

////////// TESTS FOR CLASS -> OSIPoints //////////

class OSIPointsTestFixture: public testing::Test
{
    public:
        OSIPointsTestFixture();
        OSIPointsTestFixture(std::vector<double> s, std::vector<double> x, std::vector<double> y, std::vector<double> z, std::vector<double> h);
        virtual ~OSIPointsTestFixture();
    protected:
        OSIPoints osi_points;
};

OSIPointsTestFixture::OSIPointsTestFixture()
{
}

OSIPointsTestFixture::OSIPointsTestFixture(std::vector<double> s, std::vector<double> x, std::vector<double> y, std::vector<double> z, std::vector<double> h)
{
}

OSIPointsTestFixture::~OSIPointsTestFixture()
{
}

TEST_F(OSIPointsTestFixture, TestConstructorEmpty)
{
    ASSERT_EQ(0, osi_points.GetS().size());
    ASSERT_EQ(0, osi_points.GetX().size());
    ASSERT_EQ(0, osi_points.GetY().size());
    ASSERT_EQ(0, osi_points.GetZ().size());
    ASSERT_EQ(0, osi_points.GetH().size());
}

TEST_F(OSIPointsTestFixture, TestConstructorArgument)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points = OSIPoints(s, x, y, z, h);

    std::vector<double> s_expected = osi_points.GetS();
    std::vector<double> x_expected = osi_points.GetX();
    std::vector<double> y_expected = osi_points.GetY();
    std::vector<double> z_expected = osi_points.GetZ();
    std::vector<double> h_expected = osi_points.GetH();

    ASSERT_EQ(s, s_expected);
    ASSERT_EQ(x, x_expected);
    ASSERT_EQ(y, y_expected);
    ASSERT_EQ(z, z_expected);
    ASSERT_EQ(h, h_expected);
}

TEST_F(OSIPointsTestFixture, TestSetGet)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};
    
    osi_points.Set(s,x,y,z,h);

    std::vector<double> s_expected = osi_points.GetS();
    std::vector<double> x_expected = osi_points.GetX();
    std::vector<double> y_expected = osi_points.GetY();
    std::vector<double> z_expected = osi_points.GetZ();
    std::vector<double> h_expected = osi_points.GetH();

    ASSERT_EQ(s, s_expected);
    ASSERT_EQ(x, x_expected);
    ASSERT_EQ(y, y_expected);
    ASSERT_EQ(z, z_expected);
    ASSERT_EQ(h, h_expected);
}

TEST_F(OSIPointsTestFixture, TestGetFromIdxEmpty)
{
    ASSERT_THROW(osi_points.GetXfromIdx(-1), std::runtime_error);
    ASSERT_THROW(osi_points.GetYfromIdx(-1), std::runtime_error);
    ASSERT_THROW(osi_points.GetZfromIdx(-1), std::runtime_error);
    ASSERT_THROW(osi_points.GetXfromIdx(0), std::runtime_error);
    ASSERT_THROW(osi_points.GetYfromIdx(0), std::runtime_error);
    ASSERT_THROW(osi_points.GetZfromIdx(0), std::runtime_error);
    ASSERT_THROW(osi_points.GetXfromIdx(1), std::runtime_error);
    ASSERT_THROW(osi_points.GetYfromIdx(1), std::runtime_error);
    ASSERT_THROW(osi_points.GetZfromIdx(1), std::runtime_error);
}

TEST_F(OSIPointsTestFixture, TestGetFromIdx)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points = OSIPoints(s, x, y, z, h);

    ASSERT_EQ(osi_points.GetXfromIdx(0), (double)0);
    ASSERT_EQ(osi_points.GetXfromIdx(1), (double)-1);
    ASSERT_EQ(osi_points.GetXfromIdx(2), (double)2);

    ASSERT_EQ(osi_points.GetYfromIdx(0), (double)0);
    ASSERT_EQ(osi_points.GetYfromIdx(1), (double)-1);
    ASSERT_EQ(osi_points.GetYfromIdx(2), (double)2);

    ASSERT_EQ(osi_points.GetZfromIdx(0), (double)0);
    ASSERT_EQ(osi_points.GetZfromIdx(1), (double)-1);
    ASSERT_EQ(osi_points.GetZfromIdx(2), (double)2);
}

TEST_F(OSIPointsTestFixture, TestGetNumOfOSIPointsCorrupt)
{
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points = OSIPoints(s, x, y, z, h);
    ASSERT_THROW(osi_points.GetNumOfOSIPoints(), std::runtime_error);
}

TEST_F(OSIPointsTestFixture, TestGetNumOfOSIPoints)
{
    ASSERT_EQ(osi_points.GetNumOfOSIPoints(), 0);
    std::vector<double> s {0, -1, 2};
    std::vector<double> x {0, -1, 2};
    std::vector<double> y {0, -1, 2};
    std::vector<double> z {0, -1, 2};
    std::vector<double> h {0, -1, 2};

    OSIPoints osi_points_second = OSIPoints(s, x, y, z, h);
    ASSERT_EQ(osi_points_second.GetNumOfOSIPoints(), 3);
}




/*class OSIPoints
	{
		public:
			OSIPoints() {}
			OSIPoints(std::vector<double> s, std::vector<double> x, std::vector<double> y, std::vector<double> z, std::vector<double> h) : x_(x), y_(y), z_(z), h_(h) {}
			void Set(std::vector<double> s, std::vector<double> x, std::vector<double> y, std::vector<double> z, std::vector<double> h) { s_ = s; x_ = x; y_ = y; z_ = z; h_ = h;}
			std::vector<double> GetS() {return s_;}
			std::vector<double> GetX() {return x_;}
			std::vector<double> GetY() {return y_;}
			std::vector<double> GetZ() {return z_;}
			std::vector<double> GetH() {return h_;}
			double GetXfromIdx(int i) {return x_[i];}
			double GetYfromIdx(int i) {return y_[i];}
			double GetZfromIdx(int i) {return z_[i];}
			int GetNumOfOSIPoints() {return (int)x_.size();}

		private:
			std::vector<double> s_;
			std::vector<double> x_;
			std::vector<double> y_;
			std::vector<double> z_;
			std::vector<double> h_;
	};*/


//////////////////////////////////////////////////////////////////////


/******************************************
* Test the LineLink class
******************************************/
// Tests the class constructor.
TEST(LaneLinkTest, DefaultConstructor) {
    LaneLink lane_link(UNKNOWN, 0);
    EXPECT_EQ(UNKNOWN, lane_link.GetType());
    EXPECT_EQ(0,lane_link.GetId());
}

/******************************************
* Test the LaneWidth class
******************************************/
// Tests the class constructor.
TEST(LaneWidthTest, DefaultConstructor) {
    LaneWidth lane_width(1, 1, 1, 1, 1);
    EXPECT_EQ(1, lane_width.GetSOffset());
}

/******************************************
* Test the LaneBoundaryOSI class
******************************************/

/******************************************
* Test the LaneRoadMarkTypeLine class
******************************************/
class LaneRoadMarkTypeLineTest :public ::testing::TestWithParam<std::tuple<double,double,double,double,LaneRoadMarkTypeLine::RoadMarkTypeLineRule,double>> {};
// inp: length,space,t_offset,s_offset,rule,width

TEST_P(LaneRoadMarkTypeLineTest, DefaultConstructor) {
    LaneRoadMarkTypeLine lane_roadmarking = LaneRoadMarkTypeLine(
        std::get<0>(GetParam()),
        std::get<1>(GetParam()),
        std::get<2>(GetParam()),
        std::get<3>(GetParam()),
        std::get<4>(GetParam()),
        std::get<5>(GetParam()));

    EXPECT_EQ(lane_roadmarking.GetLength(),std::get<0>(GetParam()));
    EXPECT_EQ(lane_roadmarking.GetSpace(),std::get<1>(GetParam()));
    EXPECT_EQ(lane_roadmarking.GetTOffset(),std::get<2>(GetParam()));
    EXPECT_EQ(lane_roadmarking.GetSOffset(),std::get<3>(GetParam()));

    // Test SetGlobalId method
    // OSI related stuff not implemented yet
    //lane_roadmarking.SetGlobalId();
    //EXPECT_EQ(lane_roadmarking.GetGlobalId(), 0);
}

INSTANTIATE_TEST_CASE_P(LaneRoadMarkTypeLineTests,LaneRoadMarkTypeLineTest,::testing::Values(
    std::make_tuple(100,100,0,0,LaneRoadMarkTypeLine::NO_PASSING,2),
    std::make_tuple(10,10,-1,1,LaneRoadMarkTypeLine::CAUTION,6)));

/******************************************
* Test the LaneRoadMarkType class
******************************************/
class LaneRoadMarkTypeTest : public ::testing::Test {
    protected:
    void SetUp() override { lane_test_0 = new LaneRoadMarkType("test", 0.2); }
    LaneRoadMarkType* lane_test_0;
};

TEST_F(LaneRoadMarkTypeTest, DefaultConstructor) {
    EXPECT_EQ(lane_test_0->GetName(),"test");
    EXPECT_EQ(lane_test_0->GetWidth(),0.2);
}

TEST_F(LaneRoadMarkTypeTest,AddLine) {
    LaneRoadMarkTypeLine * line_0 = new LaneRoadMarkTypeLine(100,100,0,0,LaneRoadMarkTypeLine::NO_PASSING,2);
    lane_test_0->AddLine(line_0);
    EXPECT_EQ(lane_test_0->GetNumberOfRoadMarkTypeLines(), 1);

    // test GetLaneRoadMarkTypeLineByIdx method
    EXPECT_EQ(lane_test_0->GetLaneRoadMarkTypeLineByIdx(0)->GetLength(), line_0->GetLength());
}

/******************************************
* Test the LaneRoadMark class
******************************************/
class LaneRoadMarkTest :public ::testing::TestWithParam<std::tuple<double,LaneRoadMark::RoadMarkType,LaneRoadMark::RoadMarkWeight,LaneRoadMark::RoadMarkColor,LaneRoadMark::RoadMarkMaterial,LaneRoadMark::RoadMarkLaneChange,double,double>> {};
// inp: s_offset,type,weight,color,material,lane_change,width,height

TEST_P(LaneRoadMarkTest, DefaultConstructor) {
    LaneRoadMark lane_test_0 = LaneRoadMark(
        std::get<0>(GetParam()),
        std::get<1>(GetParam()),
        std::get<2>(GetParam()),
        std::get<3>(GetParam()),
        std::get<4>(GetParam()),
        std::get<5>(GetParam()),
        std::get<6>(GetParam()),
        std::get<7>(GetParam()));

    EXPECT_EQ(lane_test_0.GetSOffset(),std::get<0>(GetParam()));
    EXPECT_EQ(lane_test_0.GetType(),std::get<1>(GetParam()));
    EXPECT_EQ(lane_test_0.GetColor(),std::get<3>(GetParam()));
    EXPECT_EQ(lane_test_0.GetWidth(),std::get<6>(GetParam()));
    EXPECT_EQ(lane_test_0.GetHeight(),std::get<7>(GetParam()));

    LaneRoadMarkType * type_test_0 = new LaneRoadMarkType("test", 0.2);
    lane_test_0.AddType(type_test_0);
    EXPECT_EQ(lane_test_0.GetNumberOfRoadMarkTypes(),1);
    EXPECT_EQ(lane_test_0.GetLaneRoadMarkTypeByIdx(0)->GetName(),type_test_0->GetName());
}

INSTANTIATE_TEST_CASE_P(LaneRoadMarkTests,LaneRoadMarkTest,::testing::Values(
    std::make_tuple(0,LaneRoadMark::NONE_TYPE,
        LaneRoadMark::STANDARD,
        LaneRoadMark::STANDARD_COLOR,
        LaneRoadMark::STANDARD_MATERIAL,
        LaneRoadMark::INCREASE,0.2,0),
    std::make_tuple(100,LaneRoadMark::SOLID,
        LaneRoadMark::BOLD,
        LaneRoadMark::BLUE,
        LaneRoadMark::STANDARD_MATERIAL,
        LaneRoadMark::DECREASE,0.2,-1)));



int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}