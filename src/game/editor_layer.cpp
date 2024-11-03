#include "editor_layer.h"

#include <cmath>
#include <core/input.h>

#include "editor_utils.h"

vec2 cam_move;
vec2 cam_pos;
float grid_size = 1;

std::vector<vec2> points;

void EditorLayer::onAttach()
{
	auto& window = Application::Get().window();
	sprite_batch = new SpriteBatch(1024);
	camera.size = {(float) window.width, (float) window.height};
	camera.scale = 1/30.0;
	load_glsl_shader("res/sprite.vert", "res/sprite.frag", sprite_shader);
}

void EditorLayer::onDetach()
{
	delete_shader_program(sprite_shader);
	delete sprite_batch;
}


void EditorLayer::onUpdate(float deltaTime)
{
	clear_viewport(color_from_hexcode("000000"));

	cam_move.x = cam_move.y = 0;
	if(Input::isKeyPressed(KEY_W))
		cam_move.y = 1.0;
	if(Input::isKeyPressed(KEY_S))
		cam_move.y =-1.0;
	if(Input::isKeyPressed(KEY_D))
		cam_move.x = 1.0;
	if(Input::isKeyPressed(KEY_A))
		cam_move.x =-1.0;
	if(Input::isKeyPressed(KEY_E))
		camera.scale -= deltaTime * 1/40;
	if(Input::isKeyPressed(KEY_Q))
		camera.scale += deltaTime * 1/40;
	
	cam_move = normalize(cam_move);

	cam_pos += cam_move * 256/20  * deltaTime;
	camera.position = lerp(camera.position, cam_pos, 10 * deltaTime);

	
	sprite_batch->beginBatch();
	
	vec2 bottom_left_corner = camera.position - camera.size * 0.5 * std::fmin(camera.scale, 1.0/30);
	vec2 top_right_corner = camera.position + camera.size * 0.5 * std::fmin(camera.scale, 1.0/30);

	Sprite b;
	b.color = color_from_hexcode("131313");
	b.position = bottom_left_corner ;
	b.size = top_right_corner - bottom_left_corner;
	sprite_batch->addSprite(b);

	int count = 0;
	for(float x = nearest_grid_floor(bottom_left_corner.x, grid_size); x <= nearest_grid_ceil(top_right_corner.x , grid_size); x += grid_size)
	{
		for(float y = nearest_grid_floor(bottom_left_corner.y, grid_size); y <= nearest_grid_ceil(top_right_corner.y , grid_size); y += grid_size)
		{
			Sprite s;
			s.size = vec2{camera.scale};
			if(x == 0 && y == 0)
			{
				s.color = color_from_hexcode("ffffff");
				s.size *= 2;
			}
			else if(x == 0)
				s.color = color_from_hexcode("00ff00");
			else if(y == 0)
				s.color = color_from_hexcode("ff0000");
			else
				s.color = color_from_hexcode("666666");
			
			s.position = {x - s.size.x/2, y - s.size.y/2};
			sprite_batch->addSprite(s);
		}
	}


	for(auto& p : points)
	{
		Sprite s;
		s.size = {4 * camera.scale};
		s.position = p - s.size * 0.5;
		sprite_batch->addSprite(s);
	}

	sprite_batch->endBatch();

	use_shader_program(sprite_shader);
	shader_upload_vec2(sprite_shader, "uCamera.position", camera.position.x, camera.position.y);
	shader_upload_vec2(sprite_shader, "uCamera.size", camera.size.x * camera.scale, camera.size.y * camera.scale);
	sprite_batch->drawBatch();
}

void EditorLayer::onEvent(const Event& e)
{
	if(e.type == EventType::CURSOR_MOVE)
	{
		if(Input::isKeyPressed(KEY_SPACE))
		{
			cam_pos -= vec2{(float)e.cursorMoveData.Dx, (float)e.cursorMoveData.Dy} * camera.scale;
		}
	}
	else if(e.type == EventType::MOUSE_CLICK)
	{
		auto[x, y] = Input::getCursorPosition();
		if(e.mouseButtonData.button == 0 && e.mouseButtonData.action == PRESS)
		{
			vec2 click_coord = camera.screenToWorld(x, y);
			vec2 point = nearest_grid_floor(click_coord + vec2{grid_size * 0.5f}, grid_size);
			bool flag = false;
			for(auto& p : points)
			{
				if(p == point)
				{
					flag = true;
					break;
				}
			}
			if(!flag)
				points.emplace_back(point);
		}
	}else if(e.type == EventType::KEY_CLICK)
	{
		switch (e.keyData.key)
		{
			case KEY_F:
				if(e.keyData.action == PRESS)
				{
					printf("fps: %ld\n", Application::Get().framerate());
				}
			break;
		}
	}
}
