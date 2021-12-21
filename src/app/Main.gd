extends Spatial

# Declare member variables here. Examples:
# var a = 2
# var b = "text"

# Called when the node enters the scene tree for the first time.
func _ready():
	var mdt = MeshDataTool.new()
	var nd = get_node("Terrain")
	var mesh = nd.get_mesh()
	mdt.create_from_surface(mesh, 0)
	for i in range(mdt.get_vertex_count()):
		var vertex = mdt.get_vertex(i)
		mdt.set_vertex(i, vertex)
	mdt.commit_to_surface(mesh)

