Fully templated C++17 math library, mainly designed for graphics programming.

All files contains the license at the top, so you're welcome to yoink anything as long as you keep the license.

It's fully templated, so no building needed - just include what you need.

# Examples

Creating a transform matrix

    mz::fvec3 position;
    mz::fvec3 euler_angles;
    mz::fvec3 scale;

    mz::fmat4 transform = mz::transformation::translation(position)
                          .rotate(euler_angles.x, { 1, 0, 0 })
                          .rotate(euler_angles.y, { 0, 1, 0 })
                          .rotate(euler_angles.z, { 0, 0, 1 })
                          .scale(fvec3(1) - scale) // Translation matrix starts with scale of 1

Alias
    
    mz::fvec2 pos;
    mz::frange range; // typedef of fvec2

    pos.x = 3; 
    pos.y = 4; 

    range.min = 3; // x
    range.max = 4; // y

    mz::fvec2 size;
    size.width = 5;  // x
    size.height = 6; // y

    mz::frect rect; //typedef of fvec4
    rect.x = 7;
    rect.y = 8;
    rect.width = 9;    // z
    rect.height = 10;  // w
    rect.size = { 11, 12 }; // z, w

    mz::fray2d ray({10, 10}, {20, 20}); // typedef of fvec4
    ray.p1 = { 13, 14 }; // x, y
    ray.p2 = { 13, 14 }; // z, w

    mz::fquad quad; // typedef of vec4<fvec2>;

    quad.a = fvec2(100, 100); // x.x, x.y
    quad.b = fvec2(125, 125); // y.x, y.y
    quad.c = fvec2(150, 100); // z.x, z.y
    quad.d = fvec2(125, 75);  // w.x, w.y

Implicit conversions & casting

    mz::fvec2   fv2;
    mz::s64vec4 sv4;

    mz::ivec3 iv3 = fv2 * sv4; // OK

Physics & graphics algorithms

    // Line segment intersection check
    mz::fray2d ray1(fvec2(10, 10), fvec2(20, 20));
    mz::fray2d ray2(fvec2(20, 10), fvec2(10, 20));
    bool interesects = mz::ray2ds_intersect(ray1, ray2);

    // Rect contains point check
    mz::frect rect(100, 50, 32, 32);
    mz::fvec2 p(75, 60);
    bool rect_contains_p = rect_contains(rect, p);

    // Rects intersection check
    mz::frect rect2(140, 40, 48, 48);
    bool rect_intersects_rect2 = rects_intersect(rect, rect2);

    // Convex polygon intersection check
    mz::fvec2 ps1[] = {
        { 100, 100 }, { 125, 125 }, { 150, 125 }, { 175, 100 }, { 140, 75 }
    };
    mz::fvec2 ps2[] = {
        { 125, 125 }, { 150, 150 }, { 175, 150 }, { 200, 125 }, { 165, 100 }, { 140, 100 }
    };
    bool polygons_intersect = polygon2ds_intersect<f32, f32>({ ps1, 5 }, { ps2, 6 });

    // Tip: quads can be used as polygons with 4 points
    mz::fquad quad1;
    mz::fquad quad2;
    bool quads_intersects = polygon2ds_intersect(<f32, f32>({ quad.ptr, 4 }, { quad2.ptr, 4 });



