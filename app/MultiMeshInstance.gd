extends MultiMeshInstance

func _ready():
	# Create multimesh resource that will contain 4 cubes
	var mm = MultiMesh.new()
	mm.transform_format = MultiMesh.TRANSFORM_3D
	mm.instance_count = 40
	mm.mesh = get_node("../Tree").get_mesh()

	# Set position of all cubes at random
	for i in range(mm.instance_count):
		var pos = Vector3(rand_range(-8, 8), rand_range(-1, 1), rand_range(-4.5, 4.5))
		var t = Transform(Basis().scaled(Vector3(0.02, 0.02, 0.02)), pos)
		print(mm.get_instance_color(i))
		mm.set_instance_transform(i, t)

	# Assign multimesh to be rendered by the MultiMeshInstance
	self.multimesh = mm
