
function Start()
	i=0;
	print("START1")
	return
end
function Update()
	--print("UPDATE1")
	Transform.setPos(transform, math.sin(i), -1);
	i = i + .1;
	if(Input.isPressed(69)) then
	Sprite.setColor(sprite,1,.1,.1);
	end
	if(Input.isHeld(69)) then
	Sprite.setColor(sprite,.1,1,.1);
	end
	if(Input.isReleased(69)) then
	Sprite.setColor(sprite,.1,.1,1);
	end
	return
end