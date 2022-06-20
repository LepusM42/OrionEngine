
function Start()
	i=0;
	x = Transform.getCoord(transform, 0);
	y = Transform.getCoord(transform, 1);
	print("START1")
	return
end
function Update()
	--print("UPDATE1")

	if(Input.isPressed(69)) then
	Sprite.setColor(sprite,1,.1,.1);
	end
	if(Input.isHeld(69)) then
	Sprite.setColor(sprite,.1,1,.1);
	end
	if(Input.isReleased(69)) then
	Sprite.setColor(sprite,.1,.1,1);
	end

	if(Input.isLeftPressed()) then
		x = x - .01;
	end
	if(Input.isRightPressed()) then
		x = x + .01;
	end
	if(Input.isUpPressed()) then
		y = y + .01;
	end
	if(Input.isDownPressed()) then
		y = y - .01;
	end

	Transform.setPos(transform, x, y);

	return
end