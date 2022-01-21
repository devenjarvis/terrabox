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
#	var depth_array = realsense.get_depth_frame()
#
#	img.create_from_data(realsense.get_frame_width() - 32, realsense.get_frame_height() - 18, false, Image.FORMAT_R8, depth_array)
#	#img.save_png("./test.png")
#	texture.set_data(img)
	clear()

	# Begin draw.
	begin(Mesh.PRIMITIVE_TRIANGLES)#, texture)

	# Prepare attributes for add_vertex.
	set_color(Color.red)
	set_normal(Vector3(0, 0, 1))
	set_uv(Vector2(0, 0))
	# Call last for each vertex, adds the above attributes.
	add_vertex(Vector3(-1, -1, 0))

	set_color(Color.green)
	set_normal(Vector3(0, 0, 1))
	set_uv(Vector2(0, 1))
	add_vertex(Vector3(-1, 1, 0))

	set_color(Color.blue)
	set_normal(Vector3(0, 0, 1))
	set_uv(Vector2(1, 1))
	add_vertex(Vector3(1, 1, 0))

	# End drawing.
	end()
