#include "graphics.h"

using namespace std;
using namespace mssm;

vector<Vec2d> findMinAndMax(const vector<Vec2d>& initial)
{
    vector<Vec2d> MinAndMax;
    Vec2d minPoint;
    Vec2d maxPoint;
    for (int i = 0; i < initial.size(); i++)
    {
        if (i == 0)
        {
            minPoint = initial[i];
            maxPoint = initial[i];
            continue;
        }
        if (initial[i].x < minPoint.x)
        {
            minPoint = initial[i];
        }
        if (initial[i].x > maxPoint.x)
        {
            maxPoint = initial[i];
        }
    }
    MinAndMax.push_back(minPoint);
    MinAndMax.push_back(maxPoint);
    return MinAndMax;
}

bool isLeft(Vec2d a, Vec2d b, Vec2d c)
{
    Vec2d line = b - a;
    Vec2d toBeCompared = c - a;
    double p = crossProduct(line, toBeCompared);
    if (p > 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

vector<Vec2d> ConvexHullRecursive(vector<Vec2d> initial, Vec2d a, Vec2d b)
{
    if (initial.size() == 0)
    {
        vector<Vec2d> twoPoints;
        twoPoints.push_back(a);
        twoPoints.push_back(b);
        return twoPoints;
    }
    vector<Vec2d> leftHalf;
    vector<Vec2d> rightHalf;
    Vec2d line = b - a;
    Vec2d normal = {-line.y, line.x};
    normal = normal.unit();
    double p = 0;
    Vec2d p1 = initial[0];
    for (int i = 0; i < initial.size(); i++)
    {
        Vec2d toBeCompared = initial[i] - a;
        //double m = abs(dotProduct(toBeCompared, normal));
        double m = abs(crossProduct(line, toBeCompared));
        if (m > p)
        {
            p = m;
            p1 = initial[i];
        }
    }
    for (int i = 0; i < initial.size(); i++)
    {
        if (initial[i].x == p1.x && initial[i].y == p1.y)
        {
            continue;
        }
        if (isLeft(a, p1, initial[i]))
        {
            leftHalf.push_back(initial[i]);
        }

        else if (isLeft(p1, b, initial[i]))
        {
            rightHalf.push_back(initial[i]);
        }
    }

    vector<Vec2d> left = ConvexHullRecursive(leftHalf, a, p1);
    vector<Vec2d> right = ConvexHullRecursive(rightHalf, p1, b);
    vector<Vec2d> final;
    for (int i = 0; i < left.size() - 1; i++)
    {
        final.push_back(left[i]);
    }
    for (int i = 0; i < right.size(); i++)
    {
        final.push_back(right[i]);
    }

    return final;

}
vector<Vec2d> ConvexHull(const vector<Vec2d> initial)
{
    if (initial.size() == 2)
    {
        return initial;
    }
    vector<Vec2d> final;
    vector<Vec2d> MinAndMax;
    MinAndMax = findMinAndMax(initial);
    Vec2d line = MinAndMax[1] - MinAndMax[0];
    vector<Vec2d> topHalf;
    vector<Vec2d> bottomHalf;
    for (int i = 0; i < initial.size(); i++)
    {

        if ((initial[i].x == MinAndMax[0].x) && (initial[i].y == MinAndMax[0].y))
        {
            continue;
        }
        if ((initial[i].x == MinAndMax[1].x) && (initial[i].y == MinAndMax[1].y))
        {
            continue;
        }
        Vec2d toBeCompared = initial[i] - MinAndMax[0];
        double p = crossProduct(line, toBeCompared);
        if (p > 0)
        {
            topHalf.push_back(initial[i]);
        }
        if (p < 0)
        {
            bottomHalf.push_back(initial[i]);
        }

    }
    Vec2d a = MinAndMax[0];
    Vec2d b = MinAndMax[1];
    vector<Vec2d> top = ConvexHullRecursive(topHalf, a, b);
    vector<Vec2d> bottom = ConvexHullRecursive(bottomHalf, b, a);
    for (int i = 0; i < top.size() - 1; i++)
    {
        final.push_back(top[i]);
    }
    for (int i = 0; i < (bottom.size() - 1); i++)
    {
        final.push_back(bottom[i]);
    }
    return final;
}

int main()
{
    Graphics g("ConvexHull", 1024, 768);

    int x = 0;
    vector<Vec2d> initial;

    while (g.draw()) {
        if (!g.isDrawable()) {
            continue;
        }
        if (g.onMousePress(MouseButton::Left))
        {
            initial.push_back(g.mousePos());
        }
        g.points(initial, RED);
        if (initial.size() >= 2)
        {
        vector<Vec2d> extremes;
        extremes.push_back((findMinAndMax(initial))[0]);
        extremes.push_back((findMinAndMax(initial))[1]);
        g.points(extremes, GREEN);
        vector<Vec2d> final = ConvexHull(initial);
        g.polygon(final, BLUE);
        }


    }

    return 0;
}


