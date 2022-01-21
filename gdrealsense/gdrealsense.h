#ifndef REALSENSE_H
#define REALSENSE_H

#include <Godot.hpp>
#include <Node.hpp>

#include <librealsense2/rs.hpp>
#include <librealsense2/hpp/rs_internal.hpp>
#include <librealsense2/rs_advanced_mode.hpp>

#include <algorithm>
#include <string>
#include <fstream>
#include <streambuf>
#include <cmath>

namespace godot {

class Realsense : public Node {
    GODOT_CLASS(Realsense, Node)

    private:
        rs2::pipeline pipeline;
        rs2::depth_frame depth_frame;
        float depth_units;
        uint16_t* pixels;
        int frame_width;
        int frame_height;
        int t_offset;
        int r_offset;
        int b_offset;
        int l_offset;
        int segment_size;

        rs2::decimation_filter dec_filter;
        rs2::spatial_filter spat_filter;
        rs2::temporal_filter temp_filter;
        rs2::hole_filling_filter hole_filter;

    public:
        static void _register_methods();

        Realsense();
        PoolByteArray get_depth_frame(int, int, int, int, int);
        int get_frame_width();
        int get_frame_height();

        void _init(); // our initializer called by Godot
};

}

#endif
