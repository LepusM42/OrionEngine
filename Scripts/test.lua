
function Start()
	i=0;
	print("START1")
	playerTransform = transform.new();
	return
end
function Update()
	--print("UPDATE1")
	transform.set(playerTransform, i, i);
	i = i + .1;
	return
end