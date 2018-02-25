// by kririae
// Kririae's Compute Geometry Library

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <deque>

using std::cin;
using std::endl;
using std::cout;

namespace Basic
{
    template<typename T>
    inline T abs(T val)
    {
        return val < 0 ? -val : val;
    }

    template <typename T>
    inline T min(T a, T b)
    {
        return a < b ? a : b;
    }

    template <typename T>
    inline T max(T a, T b)
    {
        return a < b ? b : a;
    }
}

namespace Compute_Geometry
{
    using namespace Basic;
    const double eps = 1e-8;

    class Point
    {
    public:
        double x;
        double y;

        Point() {}
        
        template<typename T>
        Point(T a, T b):
            x(double(a)), y(double(b)) {}

        friend std::ostream &operator<<(std::ostream &os, const Point &p);

        bool operator== (const Point &a)
        {
            return abs(x - a.x) < eps && abs(y - a.y) < eps;
        }

        Point operator+ (const Point &a)
        {
            return Point(x + a.x, y + a.y);
        }

        Point operator- (const Point &a)
        {
            return Point(x - a.x, y - a.y);
        }

        bool operator< (const Point &a)
        {
            return abs(x - a.x) < eps ? y < a.y : x < a.x;
        }

        double operator* (const Point &a)
        {
            return x * a.y - a.x * y;
        }

        Point operator* (double val)
        {
            return Point(x * val, y * val);
        }

        Point operator/ (double val)
        {
            return Point(x / val, y / val);
        }
    };
    
    class Vector 
    {
    public:
        double x;
        double y;

        Vector(Point a, Point b)
        {
            x = b.x - a.x, y = b.y - a.y;
        }
        
        template<typename T>
        Vector(T a, T b) :x(a), y(b){}

        Vector operator+ (const Vector &a)
        {
            return Vector(x + a.x, y + a.y);
        }

        Vector operator- (const Vector &a)
        {
            return Vector(x - a.x, y - a.y);
        }

        double operator* (const Vector &a)
        {
            return x * a.y - a.x * y;
        }
    };

    template<typename T>
    inline Point make_point(T a, T b)
    {
        return Point(double(a), double(b));
    }

    bool parallel(Point a1, Point a2, Point b1, Point b2)
    {
        return abs((a2.x - a1.x) * (b2.y - b1.y) - (b2.x - b1.x) * (a2.y - a1.y)) < eps;
    }

    std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }

    bool a_left(Point a, Point b)
    {
        return a * b < -eps;
    }

    double area(Point a, Point b, Point c)
    {
        return abs((a - c) * (b - c) / 2.0);
    }

    Point inter(Point a1, Point a2, Point b1, Point b2)
    {
        double s1 = area(b1, b2, a1), s2 = area(b1, b2, a2);
        return (a1 - a2) / (s1 + s2) * s2 + a2;
    }

    // bool intersect(Point a1, Point a2, Point b1, Point b2)
    // {
    //     Point interse = inter(a1, a2, b1, b2);
    //     return parallel(interse, b2, b1, b2);
    // }
    inline bool eql(double a, double b)
    {
        if(abs(a - b) < eps) return true;
        return false;
    }
    
    bool intersect(Point a1, Point a2, Point b1, Point b2)
    {
        // return (make_point(b1.x - a1.x, b1.y - a1.y) * make_point(b2.x - a1.x, b2.y - a1.y) < 0) &&
        //     (make_point(b1.x - a2.x, b1.y - a2.y) * make_point(b2.x - a2.x, b2.y - a2.y)) < 0;
        Vector v(a1, a2);
        if((v * Vector(a1, b1)) * (v * Vector(a1, b2)) < eps) return true;
        return false;
    }
    double dis(const Point &a, const Point &b)
    {
        return sqrt((a.x - b.x) * (a.x - b.x)
                    + (a.y - b.y) * (a.y - b.y));
    }

    std::pair<int, int> manhattan_dis(const Point &a, const Point &b) // []
    {
        return std::make_pair(abs(a.x - b.x), abs(a.y - b.y));
    }

    namespace algorithms
    {

        // inline bool angle_compare
        // (Compute_Geometry::Point a, Compute_Geometry::Point b)
        // {
        //  return std::atan2(a.y, a.x) < std::atan2(b.y, b.x);
        // }

        inline std::vector<Compute_Geometry::Point>
        convex_package(std::vector<Compute_Geometry::Point> a)
        {
            // 是否利用极角排序 -> type(未测试)
            using std::vector;
            using std::deque;
            using namespace Compute_Geometry;
            static deque<Point> ret;

            // if (type) sort(a.begin(), a.end(), angle_compare);
            // else sort(a.begin(), a.end());
            // sort(a.begin(), a.end());
            for (int i = 0; i < a.size(); ++i)
            {
                while(ret.size() > 1 && a_left(
                            ret[ret.size() - 1] - ret[ret.size() - 2],
                            a[i] - ret[ret.size() - 1]))
                    ret.pop_back();
                ret.push_back(a[i]);
            }
            int size = ret.size();
            for (int i = a.size() - 2; i >= 0; --i)
            {
                while(ret.size() > size && a_left(
                            ret[ret.size() - 1] - ret[ret.size() - 2],
                            a[i] - ret[ret.size() - 1]))
                    ret.pop_back();
                ret.push_back(a[i]);
            }
            return vector<Point>(ret.begin(), ret.end());
            // 有序输出
        }

        inline double
        // polygon_area(std::vector<Compute_Geometry::Point> a, bool type)
        polygon_area(std::vector<Compute_Geometry::Point> a)
        {
            // 是否极角排序(可能必要)
            // auto angle_compare =
            // [](Compute_Geometry::Point a, Compute_Geometry::Point b)
            // { atan2(a.y, a.x) < atan2(b.y, b.x); };
            //  if (type) sort(a.begin(), a.end(), type);
            double tot = 0;
            for (int i = 1; i < a.size() - 1; ++i)
                tot += area(a[0], a[i], a[i + 1]);
            return tot;
        }
    }
}

namespace solve
{
    using namespace Compute_Geometry;
    using namespace std;
    int t;
    vector<pair<Point, Point> > sgs;
    vector<Point> ps;
    double x1, y1, x2, y2;
    int n;
    
    inline bool judge(Point a, Point b)
    {
        if(eql(a.x, b.x) && eql(a.y, b.y)) return false;
        for (int i = 0; i < sgs.size(); ++i)
            if(!intersect(a, b, sgs[i].first, sgs[i].second)) {
                return false;
            }
        return true;
    }

    inline void init()
    {
        cin >> t;
    }

    inline void solve()
    {
        init();
        // cout << intersect(make_point(2, 1), make_point(2, 2), make_point(1, 3), make_point(3, 3)) << endl; //相交的
        // cout << intersect(make_point(2, 2341234), make_point(2, 2347819), make_point(1, 3), make_point(3, 3)) << endl;
        // 不相交的
        while(t--)
        {
            cin >> n;
            for (int i = 0; i < n; ++i)
            {
                cin >> x1 >> y1 >> x2 >> y2;
                sgs.push_back(make_pair(Point(x1, y1), Point(x2, y2)));
                ps.push_back(Point(x1, y1));
                ps.push_back(Point(x2, y2));
            }
            bool c = false;
            for (int i = 0; i < ps.size(); ++i)
            {
                for (int j = 0; j < ps.size(); ++j)
                {
                    if(judge(ps[i], ps[j])) {
                        c = true;
                    }
                }
            }
            if (c) cout << "Yes!" << endl;
            else cout << "No!" << endl;
            sgs.clear();
            ps.resize(0);
        }
    }
}

int main()
{
    std::cin.tie(0);
    std::ios::sync_with_stdio(false);
    solve::solve();
    return 0;
}