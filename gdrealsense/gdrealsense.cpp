#include "gdrealsense.h"

using namespace godot;

//Register methods that should be exposed to gdscript
void Realsense::_register_methods() {
    register_method("get_depth_frame", &Realsense::get_depth_frame);
    register_method("get_frame_width", &Realsense::get_frame_width);
    register_method("get_frame_height", &Realsense::get_frame_height);
}

Realsense::Realsense() : depth_frame(rs2::frame()) {
    //Initialize Decimation Filter
    dec_filter.set_option(RS2_OPTION_FILTER_MAGNITUDE, 2);

    //Initialize depth to disparity transform
    rs2::disparity_transform depth_to_disparity(true);

    //Initialize Spatial Filter
    spat_filter.set_option(RS2_OPTION_FILTER_MAGNITUDE, 5);
    spat_filter.set_option(RS2_OPTION_FILTER_SMOOTH_ALPHA, 0.25f);
    spat_filter.set_option(RS2_OPTION_FILTER_SMOOTH_DELTA, 50);

    //Initialize Temporal Filter
    temp_filter.set_option(RS2_OPTION_FILTER_SMOOTH_ALPHA, 0.4f); //0.0f
    temp_filter.set_option(RS2_OPTION_FILTER_SMOOTH_DELTA, 20.0f); //100.0f
    temp_filter.set_option(RS2_OPTION_HOLES_FILL, 8);

    //Initialize disparity to depth transform
    rs2::disparity_transform disparity_to_depth(false);

    //Initialize hole filing
	hole_filter.set_option(RS2_OPTION_HOLES_FILL, 0);

    //Start Pipeline
    rs2::pipeline_profile selection = pipeline.start();

    rs2::device selected_device = selection.get_device();
    auto depth_sensor = selected_device.first<rs2::depth_sensor>();
    //depth_sensor.set_option(RS2_OPTION_DEPTH_UNITS, 0.009f);
    depth_units = depth_sensor.get_option(RS2_OPTION_DEPTH_UNITS);
}


void Realsense::_init() {
    // initialize any variables here
}

PoolByteArray Realsense::get_depth_frame(int t_off, int r_off, int b_off, int l_off, int seg_size) {
    //Init
    t_offset = t_off;
    r_offset = r_off;
    b_offset = b_off;
    l_offset = l_off;
    segment_size = seg_size;
    
    //Configuration
    float max_depth = 0.9f;
    float min_depth = 0.7f;

    //Block program until frame arrives
    rs2::frameset frames = pipeline.wait_for_frames();

    //Get depth frame
    depth_frame = frames.get_depth_frame();

    //Apply filters
    depth_frame = dec_filter.process(depth_frame);
    //depth_frame = depth_to_disparity.process(depth_frame);
    //depth_frame = spat_filter.process(depth_frame);
    depth_frame = temp_filter.process(depth_frame);
    //depth_frame = disparity_to_depth.process(depth_frame);
    depth_frame = hole_filter.process(depth_frame);

    //Store in array
    pixels = (uint16_t*)depth_frame.get_data();

    // Get the depth frame's dimensions
    frame_width = depth_frame.get_width();
    frame_height = depth_frame.get_height();

    PoolByteArray depth_array;

    for (int y = t_offset; y <= (frame_height - b_offset); y+= segment_size) {
        for (int x = l_offset; x <= (frame_width - r_offset); x+= segment_size) {
            float depth = pixels[frame_width * y + x] * depth_units;

            //Clamp depth values
            depth = std::min(depth, max_depth);
            depth = std::max(depth, min_depth);

            depth_array.push_back(((depth - min_depth)/(max_depth - min_depth)) * 255.0f);
        }
    }

    return depth_array;
}

int Realsense::get_frame_width() {
    return ceil((frame_width - r_offset - l_offset)/segment_size) + 1;
}

int Realsense::get_frame_height() {
    return ceil((frame_height - t_offset - b_offset)/segment_size) + 1;
}
