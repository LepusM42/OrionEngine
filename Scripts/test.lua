
function Start()
	i=0;
	print("START1")
	return
end
function Update()
	--print("UPDATE1")
	Transform.setPos(transform, math.sin(i), -1);
	Sprite.setColor(sprite,1,.2,.5);
	i = i + .1;
	return
end