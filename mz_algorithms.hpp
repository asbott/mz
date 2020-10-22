#pragma once
/*

MIT License

Copyright (c) 2020 Charlie Malmqvist (asbott https://github.com/asbott)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include "mz_vector.hpp"

namespace mz {
    template <typename lhs_t, typename rhs_t>
    constexpr inline bool rect_contains(const rect<lhs_t>& r, const vec2<rhs_t>& p) {
        static_assert(std::is_convertible<lhs_t, rhs_t>() || std::is_convertible<rhs_t, lhs_t>(), "mz::contains: types are not convertible");
        if constexpr (std::is_convertible<lhs_t, rhs_t>()) {
            return p.x > (rhs_t)r.left() && p.x < (rhs_t)r.right() && p.y > (rhs_t)r.bot() && p.y < (rhs_t)r.top();
        } else {
            return (rhs_t)p.x > r.left() && (rhs_t)p.x < r.right() && (rhs_t)p.y > r.bot() && (rhs_t)p.y < r.top();
        }
    }

    template <typename lhs_t, typename rhs_t>
    constexpr inline bool rects_intersect(const rect<lhs_t>& a, const rect<rhs_t>& b) {
        static_assert(std::is_convertible<lhs_t, rhs_t>() || std::is_convertible<rhs_t, lhs_t>(), "mz::intersects: types are not convertible");

        if constexpr (std::is_convertible<lhs_t, rhs_t>()) {
            return (rhs_t)a.left()   < b.right() && (rhs_t)a.right() > b.left() 
                && (rhs_t)a.bottom() < b.top()   && (rhs_t)a.top()   > b.bottom();
        } else {
            return a.left()   < (lhs_t)b.right() && a.right() > (lhs_t)b.left() 
                && a.bottom() < (lhs_t)b.top()   && a.top()   > (lhs_t)b.bottom();
        }
    }

    template <typename lhs_t, typename rhs_t, typename intersection_t = f32>
    constexpr inline bool ray2ds_intersect(const ray2d<lhs_t>& a, const ray2d<rhs_t>& b, const vec2<intersection_t>* intersection = NULL) {
        static_assert(std::is_convertible<lhs_t, rhs_t>() || std::is_convertible<rhs_t, lhs_t>(), "mz::intersects: types are not convertible");

        if constexpr (std::is_convertible<lhs_t, rhs_t>()) {
            rhs_t s1_x, s1_y, s2_x, s2_y;
            s1_x = (rhs_t)(a.p2.x - a.p1.x); s1_y = (rhs_t)(a.p2.y - a.p1.y);
            s2_x = b.p2.x - b.p1.x; s2_y = b.p2.y - b.p1.y;

            rhs_t s, t;
            s = (-s1_y * ((rhs_t)a.p1.x - b.p1.x) + s1_x * ((rhs_t)a.p1.y - b.p1.y)) / (-s2_x * s1_y + s1_x * s2_y);
            t = ( s2_x * ((rhs_t)a.p1.y - b.p1.y) - s2_y * ((rhs_t)a.p1.x - b.p1.x)) / (-s2_x * s1_y + s1_x * s2_y);

            if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
            {
                if (intersection) {
                    intersection->x = (intersection_t)((rhs_t)a.p1.x + (t * s1_x));
                    intersection->y = (intersection_t)((rhs_t)a.p1.y + (t * s1_y));
                }
                return true;
            }

            return false;
        } else {
            lhs_t s1_x, s1_y, s2_x, s2_y;
            s1_x = a.p2.x - a.p1.x; s1_y = a.p2.y - a.p1.y;
            s2_x = (lhs_t)(b.p2.x - b.p1.x); s2_y = (lhs_t)(b.p2.y - b.p1.y);

            lhs_t s, t;
            s = (-s1_y * (a.p1.x - (lhs_t)b.p1.x) + s1_x * (a.p1.y - (lhs_t)b.p1.y)) / (-s2_x * s1_y + s1_x * s2_y);
            t = ( s2_x * (a.p1.y - (lhs_t)b.p1.y) - s2_y * (a.p1.x - (lhs_t)b.p1.x)) / (-s2_x * s1_y + s1_x * s2_y);

            if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
            {
                if (intersection) {
                    intersection->x = (intersection_t)(a.p1.x + (t * s1_x));
                    intersection->y = (intersection_t)(a.p1.y + (t * s1_y));
                }
                return true;
            }

            return false;
        }
    }

    template <typename value_t>
    struct Polygon2D {
        typedef vec2<value_t> vec2_t;
        const vec2_t* points;
        u32 npoints;
    };

    template <typename lhs_t, typename rhs_t>
    inline bool polygon2ds_intersect(const Polygon2D<lhs_t>& a, const Polygon2D<rhs_t>& b)
    {
        // loop over the vertices(-> edges -> axis) of the first polygon
        for(auto i = 0u; i < a.npoints + 0; ++i) {
            // calculate the normal vector of the current edge
            // this is the axis will we check in this loop
            auto current = a.points[i];
            auto next = a.points[(i + 1) % a.npoints];
            auto edge = next - current;

            vec2<rhs_t> axis;
            axis.x = -edge.normalize().y;
            axis.y = edge.normalize().x;

            // loop over all vertices of both polygons and project them
            // onto the axis. We are only interested in max/min projections
            auto aMaxProj = -std::numeric_limits<float>::infinity();
            auto aMinProj = std::numeric_limits<float>::infinity();
            auto bMaxProj = -std::numeric_limits<float>::infinity();
            auto bMinProj = std::numeric_limits<float>::infinity();
            for (u32 j = 0; j < a.npoints; j++) {
                auto proj = axis.dot(a.points[j]);
                if(proj < aMinProj) aMinProj = proj;
                if(proj > aMaxProj) aMaxProj = proj;
            }

            for (u32 j = 0; j < b.npoints; j++) {
                auto proj = axis.dot(b.points[j]);
                if(proj < bMinProj) bMinProj = proj;
                if(proj > bMaxProj) bMaxProj = proj;
            }

            // now check if the intervals the both polygons projected on the
            // axis overlap. If they don't, we have found an axis of separation and
            // the given polygons cannot overlap
            if(aMaxProj < bMinProj || aMinProj > bMaxProj) {
                return false;
            }
        }

        // at this point, we have checked all axis but found no separating axis
        // which means that the polygons must intersect.
        return true;
    }

    template <typename lhs_t, typename rhs_t>
    inline bool quads_intersect(const quad<lhs_t>& lhs, const quad<rhs_t>& rhs) {
        return polygon2ds_intersect<lhs_t, rhs_t>({ lhs.ptr, 4 }, { rhs.ptr, 4 });
    }
}