#include "game_layer.h"
#include <core/window.h>
#include <core/application.h>
#include <core/input.h>

#include <graphics/img_texture2d.h>
#include <graphics/shader.h>
#include <graphics/sprite_batch.h>
#include <scene/camera.h>

#include <glad/glad.h>

Shader sprite_shader;
SpriteBatch *batch;
Camera2D main_camera;
ImgTexture2D albedo;

vec2 cam_vel;

bool debug_mode;
 
void GameLayer::onAttach()
{
	auto& window = Application::Get().window();

	load_glsl_shader("res/sprite.vert" , "res/sprite.frag", sprite_shader);
	batch = new SpriteBatch(512);

	main_camera.size = vec2(window.width, window.height);
	main_camera.scale = 1/3.0;
	albedo.init("res/props.png", TextureFiltering::NEAREST);

	use_shader_program(sprite_shader);
	shader_upload_int(sprite_shader, "uAlbedo", 0);
}

void GameLayer::onDetach()
{
	delete_shader_program(sprite_shader);
	albedo.cleanup();
	delete batch;
}


void GameLayer::onUpdate(float deltaTime)
{
	clear_viewport(0.13f, 0.13f, 0.13f, 1.0f);

	cam_vel.x = cam_vel.y = 0;

	if(Input::isKeyPressed(KEY_D))
		cam_vel.x = 1.0;
	if(Input::isKeyPressed(KEY_A))
		cam_vel.x =-1.0;
	if(Input::isKeyPressed(KEY_W))
		cam_vel.y = 1.0;
	if(Input::isKeyPressed(KEY_S))
		cam_vel.y =-1.0;

	cam_vel = normalize(cam_vel);
	
	main_camera.position += cam_vel * 128 * deltaTime;


	Sprite s;
	s.size = {45};
	s.texture_coord_min = {42, 19};
	s.texture_coord_max = {87, 64};

	batch->beginBatch();
	batch->addSprite(s);
	batch->endBatch();

	use_shader_program(sprite_shader);
	albedo.bind(0);

	shader_upload_float(sprite_shader, "uDebugMix", debug_mode ? 1.0 : 0.0);

	shader_upload_vec2(sprite_shader, "uCamera.position", main_camera.position.x, main_camera.position.y);
	shader_upload_vec2(sprite_shader, "uCamera.size", main_camera.size.x * main_camera.scale, main_camera.size.y * main_camera.scale);
	batch->drawBatch();
	
}

void GameLayer::onEvent(const Event& e)
{
	if(e.type == EventType::RESIZE)
	{
		auto& window = Application::Get().window();
		main_camera.size = {(float)window.width, (float)window.height};
		set_render_region(0, 0, e.resizeData.width, e.resizeData.height);
	}
	else if(e.type == EventType::KEY_CLICK)
	{
		switch (e.keyData.key)
		{
			case KEY_TAB:
				if(e.keyData.action == PRESS)
				{
					debug_mode = !debug_mode;
					glPolygonMode(GL_FRONT_AND_BACK, debug_mode ? GL_LINE : GL_FILL);
				}
			break;

			case KEY_F:
				if(e.keyData.action == PRESS)
				{
					std::cout << "FPS: " << Application::Get().framerate() << '\n';
				}
			break;
		}
	}
}
