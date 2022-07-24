
function Start()
	i=0;
	x = Transform.getCoord(transform, 0);
	y = Transform.getCoord(transform, 1);
	print("START1")
	return
end
function Update()
	--print("UPDATE1")

	if(Input.isLeftDown()) then
		x = x - 1;
	end
	if(Input.isRightDown()) then
		x = x + 1;
	end
	if(Input.isUpDown()) then
		y = y + 1;
	end
	if(Input.isDownDown()) then
		y = y - 1;
	end

	Transform.setPos(transform, x, y);

	return
end