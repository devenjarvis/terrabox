extends ImmediateGeometry


# Declare member variables here. Examples:
#Load realsense
var realsense = preload("res://bin/x11/gdrealsense.gdns").new()

var texture = ImageTexture.new()
var img = Image.new()


# Called when the node enters the scene tree for the first time.
func _ready():
	var depth_array = realsense.get_depth_frame()

	img.create_from_data(realsense.get_frame_width() - 32, realsense.get_frame_height() - 18, false, Image.FORMAT_R8, depth_array)
	texture.create_from_image(img, 2048)

	img.save_png("./test.png")


func _process(_delta):
	var depth_array = realsense.get_depth_frame()
	var width = realsense.get_frame_width() - 32
	var height = realsense.get_frame_height() - 18
	var w_segment_size = 10
	var h_segment_size = 10

	img.create_from_data(realsense.get_frame_width() - 32, realsense.get_frame_height() - 18, false, Image.FORMAT_R8, depth_array)
	img.lock()
	#img.save_png("./test.png")
	#texture.set_data(img)
	clear()

	# Begin draw.
	begin(Mesh.PRIMITIVE_TRIANGLE_FAN)

	for y in range(18, height, h_segment_size):
		for x in range(32, width, w_segment_size):
			#print(img.get_pixel(x, y).r)
			add_vertex(Vector3(((8.0*x)/(width)) - 1.5, ((4.5 * y)/(height)) - 3.4, -1.0 * img.get_pixel(x, y).r))
	# End drawing.
	end()
	img.unlock()
